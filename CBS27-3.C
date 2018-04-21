
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

char password[10]={"ghrce2007"};
void mypassword(void);
void mainmenu();
void addproduct();
void searchproduct();
void updateproduct();
void deleteproduct();
void display();
void purchase();
void bill_generation(struct node *);
struct CBS
	{
		char p_name[10];
		int p_id,p_cost,p_quantity;

	};

struct node
	{
		int u_id, u_quantity, u_cost;
		char u_name[10];
		struct node *next;
	}*start=NULL, *newnode;

int main()
	{
		system("CLS");
		mypassword();
		getch();
	}
void mypassword(void)
{
	char dis[50]={"PASSWORD PROTTECTED"};
	int i, j;
	char ch, pass[10];
	for(i=0;i<20;i++)
	{

		printf("%c",dis[i]);
	}
	for(i=0;i<20;i++)
	{
		printf("*");
	}
	printf("\nENTER PASSWORD\t");
	j=0;
	while(ch!=13)
	{
		ch=getch();
		if(ch!=8&&ch!=13)
		{
			putch('*');
			pass[j]=ch;
			j++;
		}
	}
	pass[j]='\0';
	if(strcmp(pass,password)==0)
	{
		system("CLS");
		printf("\nPASSWORD MATCHED\n\t");
		mainmenu();
	}
	else
	{
		printf("\nPASSWORD INCORRECT\n\t");
		mypassword();
	}

}
void mainmenu()
{
	int ab;
	system("CLS");
	printf("\nWELCOME TO THE BILLING SYSTEM\n");
	//printf("\n1.Add product\n2.Search product\n3.Update product\n4.Delete product\n5.Display\n6.Purchase\n7.Bill_generation\n");
    printf("\n1.Add product\n2.Search product\n3.Update product\n4.Delete product\n5.Display\n6.Purchase\n");
	scanf("%d",&ab);
	switch(ab)
	{
		case 1: /*Add product module*/
		addproduct();
		break;
		case 2:/*Search product module*/
		searchproduct();
		break;
		case 3:/*Update product module*/
		updateproduct();
		break;
		case 4:/*Delete product module*/
		deleteproduct();
		break;
		case 5:/*Display module*/
		display();
		break;
		case 6:/*Purchase module*/
		purchase();
		break;
		//case 7:/*Bill_generation*/
		//bill_generation();
		break;
	}
	getch();
}
void searchproduct()
	{
	  FILE *fp;
	  struct CBS s;
	  int y,found=0;
	  system("CLS");
	  printf("\n------- SEARCH YOUR PRODUCT --------\n");
	  printf("\n ENTER p_id : \t");
	  scanf("%d",&y);
	  fp=fopen("CBS","r");
	  if(fp==NULL)
	  {
		printf("\t\t SORRY !!!!!!!!!..........PRODUCT NOT AVAILABLE\t\t");
		exit(0);
	  }
	  else
	  {
		while(fread(&s,sizeof(s),1,fp)!=NULL)
		{
			if(y==s.p_id)
			{
				printf("\n product name=%s",s.p_name);
				printf("\n product id=%d",s.p_id);
				printf("\n product cost=%d",s.p_cost);
				found=1;
			}

		}
		if(found==0)
		{
			printf("-----------PRODUCT NOT FOUND-------------");
		}
	  }
	}

void updateproduct()
	{
		FILE *fp;
		int i,id1,found=0;
    	struct CBS s;
    	system("CLS");
    	printf("Enter ID to Update: ");
    	scanf("%d",&id1);
    	fp=fopen("CBS","rb+");
    	if(fp==NULL)
     	{
      		printf("\nPRODUCT  IS  NOT  AVAILABLE");
      		exit(0);
     	}
    	while(fread(&s,sizeof(s),1,fp)==1)
    	{

       		if(s.p_id==id1)
          		{
              		printf("\nEnter Name: ");
              		scanf("%s",s.p_name);
              		fseek(fp,-sizeof(s),SEEK_CUR);
              		found=fwrite(&s,sizeof(s),1,fp);
              		break;
          		}
    	}
    	fclose(fp);
    	if(found==0)
     	printf("\n\n PRODUCT  NOT  AVAILABLE  FOR  UPDATION");
     	else
      	printf("\n\n INFORMATION  OF  PRODUCT  UPDATED  SUCCESSFULLY");
	}


void deleteproduct()
	{
		FILE *fp,*ft;
	 	int i,id1,found;
    	struct CBS s;
    	system("CLS");
    	printf("Enter ID to Delete:");
    	scanf("%d",&id1);
    	fp=fopen("CBS","r");
    	ft=fopen("CBS","wb");
    	if(fp==NULL)
     		{
      			printf("\nFile not Exits");
      			exit(0);
     		}
    	//fseek(fp,0,SEEK_SET);
    	while(fread(&s,sizeof(s),1,fp)==1)
    		{

       			if(s.p_id!=id1)
          			{
              			fwrite(&s,sizeof(s),1,ft);
			  		}

    		}
    	printf("\n\n PRODUCT  DELETED  SUCCESSFULLY") ;
    	fclose(fp);
    	fclose(ft);
    	remove("CBS");
    	rename("mystud","CBS");
    	remove("mystud");

	}


void display()
	{      
		FILE *fp;
		struct CBS s;int count=0;
		system("CLS");
		printf("\n\t\t----- DISPLAY PRODUCTS------\t\t\n");
		fp=fopen("CBS","r");
		if(fp==NULL)
		{
		 printf("File not Exists");
		 exit(0);
		}

		 while(fread(&s,sizeof(s),1,fp)==1)
		 {
		  count++;
		  printf("\n------------------------------\n");
		  printf("\n Product Name:%s",s.p_name);
		  printf("\n Product Id:%d",s.p_id);
		  printf("\n Product Quantity:%d",s.p_quantity);
		  printf("\n Product Cost:%d",s.p_cost);
		  printf("\n-------------------------------\n");
		  printf("\nEnter key to continuee");
		  getch();
		 }
		 fclose(fp);
		 printf("\n No. of products present in a file %d ",count);

	}


void addproduct()
	{
		FILE *fp;
		struct CBS s;
		system("CLS");
		printf("\n------- ADD YOUR PRODUCTS -------\n");
		printf("\nEnter p_name : ");
		scanf("%s",s.p_name);
		printf("\nEnter p_id : ");
		scanf("%d",&s.p_id);
		printf("\nEnter p_quantity : ");
		scanf("%d",&s.p_quantity);
		printf("\nEnter p_cost : ");
		scanf("%d",&s.p_cost);
		fp=fopen("CBS","a");
		fwrite(&s,sizeof(s),1,fp);
		printf("\nPRODUCT  ADDED  SUCCESSFULLY\n");
		fclose(fp);
	}

void bill_generation(struct node *n)
	{
		char Username[20];
		int User_id;
		int total= n->u_quantity*n->u_cost;
		system("CLS");
		printf("\n\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
		printf("\n\t\t\t\t\t          ALL INDIA STORES         \t\t\t\t\n");
		printf("\n\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Your Bill @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\t\t\n");
		printf("\n\n");
		printf(" Username : \t");
		scanf("%s",Username);
		printf(" User_id : \t");
		scanf("%d",&User_id);
		printf("\n\n");
		printf("\n\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
		printf("\n\n\t\tp_id\t\tp_name\t\t u_quantity\t\tp_cost\t\ttotal");
		printf("\n\n\t\t%d\t\t%s\t\t%d\t\t\t%d\t\t%d",n->u_id,n->u_name,n->u_quantity,n->u_cost,total);
		printf("\n\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
		printf("\n\n\n\t\t\t\t    THANK  YOU !!!!!!!!");
		printf("\n\n\n\t\t\t\t           VISIT AGAIN...........");
	}

void purchase()
	{
		FILE *fp;
		struct CBS s;
		char x[10]; int fd=1;
		int n, found=0;
		system("CLS");
		printf("\n------PURCHASING SCREEN---------\n");
		printf("\n Enter product name :");
		scanf("%s", x);

		fp=fopen("CBS","rb+");
		while(fread(&s,sizeof(s),1,fp)==1)
		{
			if(strcmp(s.p_name,x)==0)
			{
				printf("\n Enter quantiy to purchase : ");
	           	scanf("%d", &n);
				if(s.p_quantity>=n)
				{
					newnode=(struct node*)malloc(sizeof(struct node));
					newnode->u_id=s.p_id;

	              	strcpy(newnode->u_name,s.p_name);
					newnode->u_quantity=n;
					newnode->u_cost=s.p_cost;
					newnode->next=NULL;

					if(start==NULL)
					{
						newnode->next=NULL;
						start=newnode;
					}
					else
					{
						newnode->next=start;
						start=newnode;
					}

					s.p_quantity=s.p_quantity-n;
					fseek(fp,-sizeof(s),SEEK_CUR);
                    found=fwrite(&s,sizeof(s),1,fp);
                    break;
				}
			}
		}
		fclose(fp);
		 if(found==0)
             {
                printf("\nProduct Not Available");
               // mainmenu();
               exit(0);
			 }
		printf("\n-------PURCHASE SUCCCESSFUL------\n");
		printf("\n\n\nDo you want to generate a bill .............??????????\n\n\n If yes type 1 : ");
		scanf("%d",&fd);
		if(fd==1)
			{
				bill_generation(newnode);
			}

	}


