#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <windows.h>
#include<dos.h>
#include<time.h>
#define RETURNTIME 15;









void view();
void add();
void delete();
void edit();
int getdata();
int checkid();
void login();
void issue();
int sid();
void mainmenu();
void search();
void submit();




char catagories[][15]={"Computer","Electronics","Electrical","Civil","Mechanical"};





FILE *fp,*ft,*fl,*fs;
int c;
char findbook='f';


	


struct meroDate
{
int mm,dd,yy;
};





struct books
{
char bname[20];
int bid;
char Author[20];
int quantity;
float Price;
int rackno;
char *cat;
int sid;
struct meroDate issued;
struct meroDate duedate;
};
struct books a;


struct login
{	char sname[30];
	unsigned int sid;
	char username[30];
	char password[30];
};
struct login l;






char user[30],pass[30];





void main()
{
	login();
}









void login()
{
	char ch;
	int i=0,flag=1;
	fl=fopen("data.dat","ab+");
	system("cls");
			printf("\t\t.......LOGIN.......\n\n");
			printf("Enter username     ");
			fflush(stdin);
			scanf("%s",user);
			if(strcmp(user,"admin")==0)
			{
				flag=0;
				printf("\nEnter password   ");
				while(ch!=13)
				{
				ch=getch();
				
				if(ch!=13 && ch!=8){
				putch('*');
				pass[i] = ch;
				i++;
				}
				}
				pass[i] = '\0';			
				if(strcmp(pass,"admin")==0)
				{
				system("cls");
				printf("you have successfully logged in");
				sleep(1);
				system("cls");
				mainmenu();
				}
				else
				{	
				printf("you have entered wrong paasword");
				sleep(1);
				login();
				}
			}
			if(flag==1)
			{
			printf("you have entered wrong username");
			sleep(1);
			login();
			}
}









void mainmenu()
{
system("cls");
printf("........................\n\tMAINMENU\n........................\n\n");
printf("1. Issue a Book\n");
printf("2. Return a Book\n");
printf("3. Add a Book\n");
printf("4. Delete a Book\n");
printf("5. Edit Book Detail \n");
printf("6. Search a Book\n");
printf("7. View Book List\n");
printf("8. Close Application\n\n");
printf("\t\tEnter your choice:");
switch(getche())
{
case '1':
	issue();
	break;
case '2':
	submit();
	break;
case '3':
	add();
	break;
case '4':
	delete();
	break;
case '5':
	edit();
	break;
case '6':
	search();
	break;
case '7':
	view();
	break;
case '8':
{
system("cls");
printf("\n******************************************\n");
printf("Library Management System");
printf("\n\tProject in C");
printf("\n\t\tby ROHIT GROVER");
printf("\n******************************************");
Sleep(1500);
exit(0);
}
default:
{
printf("\n\aWrong Entry!!Please re-entered correct option");
sleep(1);
mainmenu();
}
}
}









void edit()  
{
int f=0;
int d,e;
char another='y';
while(another=='y')
{
system("cls");
printf("................................\n\tEdit Books Section\n................................\n");
printf("\nEnter Book Id to be edited: ");
scanf("%d",&d);
fp=fopen("Book.dat","ab+");
rewind(fp);
while(fread(&a,sizeof(a),1,fp)==1)
{
if(a.bid==d)
{
printf("\nThe book is availble");
printf("\nThe Book ID:%d",a.bid);
printf("\nCategory: %s",a.cat);
printf("\nName: %s",a.bname);
printf("\nAuthor: %s",a.Author);
printf("\nQuantity: %d",a.quantity);
printf("\nPrice: %f",a.Price);
printf("\nRackno: %d",a.rackno);
f=1;
}
{
ft=fopen("test.dat","wb+");  
rewind(fp);
while(fread(&a,sizeof(a),1,fp)==1)
{
if(a.bid!=d)
{
fseek(ft,0,SEEK_CUR);
fwrite(&a,sizeof(a),1,ft); 
}                              
}
fclose(ft);
fclose(fp);
remove("Book.dat");
rename("test.dat","Book.dat"); 
}
if(f==1)
{
fp=fopen("Book.dat","rb+");    
printf("\n\n\tEnter new deatils");
printf("\n\t\tSelect new category\n");
printf("1. Computer\n");
printf("2. Electronics\n");
printf("3. Electrical\n");
printf("4. Civil\n");
printf("5. Mechanical\n");
c=getch();
a.cat=catagories[c-1];
printf("\nEnter new name:");scanf("%s",a.bname);
printf("Enter new Author:");scanf("%s",a.Author);
printf("Enter new quantity:");scanf("%d",&a.quantity);
printf("Enter new price:");scanf("%f",&a.Price);
printf("Enter new rackno:");scanf("%d",&a.rackno);
a.bid=d;
fseek(fp,0,SEEK_END);
fwrite(&a,sizeof(a),1,fp);
printf("\nThe record is modified");
fclose(fp);
}
}
if(f==0)
{
printf("\nNo record found");
}
printf("\nModify another Record?(Y/N) ");
fflush(stdin);
another=getch() ;
}
mainmenu();
}









void delete()    
{
system("cls");
printf(".............................\n\tDelete Section\n.............................\n");
int d;
char another='y';
while(another=='y')  
{
printf("\nEnter the Book ID to  delete: ");
scanf("%d",&d);
fp=fopen("Book.dat","rb+");
rewind(fp);
while(fread(&a,sizeof(a),1,fp)==1)
{
if(a.bid==d)
{

printf("\nThe book record is available\n");
printf("Book name is %s\n",a.bname);
printf("Rack No. is %d\n",a.rackno);
findbook='t';
}
}
if(findbook!='t')
{
printf("No record is found modify the search\n");
if(getch())
mainmenu();
}
if(findbook=='t' )
{
printf("\nDo you want to delete it?(Y/N): ");
if(getche()=='y')
{
ft=fopen("test.dat","wb+");  
rewind(fp);
while(fread(&a,sizeof(a),1,fp)==1)
{
if(a.bid!=d)
{
fseek(ft,0,SEEK_CUR);
fwrite(&a,sizeof(a),1,ft); 
}                              
}
fclose(ft);
fclose(fp);
remove("Book.dat");
rename("test.dat","Book.dat");
fp=fopen("Book.dat","rb+");    
if(findbook=='t')
{
printf("\nThe record is sucessfully deleted\n");
printf("Delete another record?(Y/N) ");
}
}
else
mainmenu();
fflush(stdin);
another=getche();
}
}
mainmenu();
}









void add()
{
system("cls");
printf("...........................\n\tADD SECTION\n...........................\n\n\n.......SELECT CATEGOIES.......\n");
printf("1. Computer\n");
printf("2. Electronics\n");
printf("3. Electrical\n");
printf("4. Civil\n");
printf("5. Mechanical\n");
printf("6. Back to main menu\n\n");
printf("\t\tEnter your choice: ");
scanf("%d",&c);
if(c==6)
{
mainmenu() ;
}
system("cls");
fp=fopen("Book.dat","ab+");
if(getdata()==1)
{
a.cat=catagories[c-1];
fseek(fp,0,SEEK_END);
fwrite(&a,sizeof(a),1,fp);
fclose(fp);
printf("\nThe record is sucessfully saved\n");
printf("Save any more?(Y / N): ");
if(getch()=='n')
mainmenu();
else
system("cls");
add();
}
}









void view()
{
system("cls");	
printf("\t\t>>>>>>>>>>>>>>>>>> View Section <<<<<<<<<<<<<<<<<<\n\n");
printf("\n1. All Books");
printf("\n2. Issued Books");
printf("\n3. Student Data");
printf("\n4. Go Back to MainMenu");
switch(getch())
{
	case '1':
	system("cls");									
	fp=fopen("book.dat","r");
	printf("CATEGORY\tBOOK ID\t\tBOOK\t\tAUTHOR\t\tRACK NO.\t\tQUANTITY\t\tprice\n\n\n");
	int i=0;
	for(;i<5;i++)
	{
		rewind(fp);
		while(fread(&a,sizeof(a),1,fp)==1)
		{	
			if(strcmp(a.cat,catagories[i])==0)
			{
			printf("%-13s\t%d\t\t%s\t\t%s\t\t%d\t\t\t%d\t\t\t%.1f",a.cat,a.bid,a.bname,a.Author,a.rackno,a.quantity,a.Price);
			printf("\n");
			}
		}
	}
	fclose(fp);
	if(getch())
	{
		mainmenu();
	}
		break;
	case '2':
		system("cls");								
		fp=fopen("issue.dat","r");
		fseek(fp,0,SEEK_SET);
		printf("Sid\tBid\tBname\tIssued Date\tReturn Date\n\n");
			while(fread(&l,sizeof(l),1,fp)==1)
			{	
				printf("%d\t%d\t%s\t%d-%d-%d\t%d-%d-%d",a.sid,a.bid,a.bname,a.issued.dd,a.issued.mm,a.issued.yy,a.duedate.dd,a.duedate.mm,a.duedate.yy);
				printf("\n");
			}
		fclose(fp);
		if(getch())
		{
		mainmenu();
		}
		break;
	case '3':
		system("cls");									
		fp=fopen("data.dat","r");
		printf("Sid\tSname\t\tUsername\t\tPassword\n\n\n");
		
			rewind(fp);
			while(fread(&l,sizeof(l),1,fp)==1)
			{	
				printf("%d\t%s\t\t%s\t\t\t%s",l.sid,l.sname,l.username,l.password);
				printf("\n");
			}
		fclose(fp);
		if(getch())
		{
			mainmenu();
		}
		break;
	case '4':
		mainmenu();
		break;
}
}









void search()
{	int ch1,ch2,sid1,bid1,i,flag=0;;
	system("cls");
	printf("......... search section .........\n");
	printf("1. From All Books\n");
	printf("2. From Issued Books\n");
	printf("3. search student data");
	printf("\n\t\tpress 8 to go back to mainmenu\n");
	scanf("%d",&ch1);
	switch(ch1)
	{
	case 1:
		{	system("cls");
			printf(">>>>>>> search from all books <<<<<<<\n\n");
			printf("1. search by book id\n");
			printf("2. search by category\n");
			scanf("%d",&ch2);
			switch(ch2)
		{
		case 1:
				{
				system("cls");
				printf(">>>>>>> searching from all book by book id <<<<<<<\n\n");	
				printf("Enter book id\n");
				scanf("%d",&bid1);								
				fp=fopen("book.dat","r");
				printf("CATEGORY\tBOOK ID\t\tBOOK\t\tAUTHOR\t\tRACK NO.\t\tQUANTITY\t\tprice\n\n\n");
					rewind(fp);
					while(fread(&a,sizeof(a),1,fp)==1)
					{	
						if(a.bid==bid1)
						{
							flag=1;
						printf("%-13s\t%d\t\t%s\t\t%s\t\t%d\t\t\t%d\t\t\t%.1f",a.cat,a.bid,a.bname,a.Author,a.rackno,a.quantity,a.Price);
						printf("\n");
						}
					}
					if(flag==0)
					{
						printf("no record found");
					}
					getch();
				fclose(fp);
					}
			break;
			case 2:
				{
				system("cls");
				printf(">>>>>>> searching from all books by category <<<<<<<\n\n");
				fp=fopen("book.dat","r");
				printf("\t\tSelect categories\n");
				printf("1. Computer\n");
				printf("2. Electronics\n");
				printf("3. Electrical\n");
				printf("4. Civil\n");
				printf("5. Mechanical\n");
				scanf("%d",&i);
				printf("CATEGORY\tBOOK ID\t\tBOOK\t\tAUTHOR\t\tRACK NO.\t\tQUANTITY\t\tprice\n\n\n");
				rewind(fp);
				while(fread(&a,sizeof(a),1,fp)==1)
				{	
					if(strcmp(a.cat,catagories[i-1])==0)
					{
						flag=1;
					printf("%-13s\t%d\t\t%s\t\t%s\t\t%d\t\t\t%d\t\t\t%.1f",a.cat,a.bid,a.bname,a.Author,a.rackno,a.quantity,a.Price);
					printf("\n");
					}
				}
				if(flag==0)
				{
					printf("no record found");
				}
				getch();
				fclose(fp);
				}
				break;
		}
		mainmenu();
		}
		break;
	case 2:
		{
		system("cls");
		printf(">>>>>>> search from issued books <<<<<<<\n\n");
		printf("1. search by book id\n");
		printf("2. search by student id\n");
		scanf("%d",&ch2);
		switch(ch2)
		{
			case 1:
			{
			system("cls");
			printf(">>>>>>> searching issued book by book id <<<<<<<\n");
			printf("Enter book id\n");
			scanf("%d",&bid1);
			system("cls");								
			fp=fopen("issue.dat","r");
			fseek(fp,0,SEEK_SET);
			printf("Sid\tBid\tBname\tIssued Date\tReturn Date\n\n");
			while(fread(&l,sizeof(l),1,fp)==1)
			{	
				if(a.bid==bid1)
				{
					flag=1;
					printf("%d\t%d\t%s\t%d-%d-%d\t%d-%d-%d",a.sid,a.bid,a.bname,a.issued.dd,a.issued.mm,a.issued.yy,a.duedate.dd,a.duedate.mm,a.duedate.yy);
					printf("\n");
				}	
			}
			if(flag==0)
			{
				printf("no record found");
			}
			getch();
			fclose(fp);
			}
		break;
		case 2:
		{
			system("cls");
			printf(">>>>>>> searching issued book by student id <<<<<<<\n\n");
			printf("Enter student id\n");
			scanf("%d",&sid1);
			system("cls");								
			fp=fopen("issue.dat","r");
			fseek(fp,0,SEEK_SET);
			printf("Sid\tBid\tBname\tIssued Date\tReturn Date\n\n");
			while(fread(&l,sizeof(l),1,fp)==1)
			{	
				if(a.sid==sid1)
				{	
					flag=1;
					printf("%d\t%d\t%s\t%d-%d-%d\t%d-%d-%d",a.sid,a.bid,a.bname,a.issued.dd,a.issued.mm,a.issued.yy,a.duedate.dd,a.duedate.mm,a.duedate.yy);
					printf("\n");
				}	
			}
			if(flag==0)
			{
				printf("no record found");
			}
			getch();
			fclose(fp);
			}
			break;
			}
		mainmenu();
	}
		break;
	case 3:
		{
		system("cls");
		printf(">>>>>>> searching student data <<<<<<<\n\n");
		fp=fopen("data.dat","r");
		printf("Enter student id\n");
		scanf("%d",&sid1);
		printf("Sid\tSname\t\tUsername\t\tPassword\n\n\n");
		
			rewind(fp);
			while(fread(&l,sizeof(l),1,fp)==1)
			{	
				if(l.sid==sid1)
				{
				flag=1;
				printf("%d\t%s\t\t%s\t\t\t%s",l.sid,l.sname,l.username,l.password);
				printf("\n");
				}
			}
			if(flag==0)
			{
				printf("no record found");
			}
			getch();
		fclose(fp);
		}
		mainmenu();
		break;
		case 8:
			mainmenu();
			break;
		default:
			printf("entered wrong choice\n");
			sleep(1);
			search();	
	}
}









void issue()
{	int t,i;
	system("cls");
	int c=0;
	char another='y';
	while(another=='y')
{
	fp=fopen("Book.dat","rb");
	fl=fopen("data.dat","rb");
	fs=fopen("issue.dat","ab+");
	printf("Enter book id: ");
	scanf("%d",&t);
	if(checkid(t)==0)
	{
	printf("Enter student id: ");
	scanf("%d",&i);
	if(sid(i)==0)
	{
	a.sid=i;
	struct tm *d; //for current date
	time_t t= time(NULL);
	time(&t);
	d=localtime(&t);

	a.issued.dd=(d->tm_mday);
	a.issued.mm=(d->tm_mon)+1;
	a.issued.yy=(d->tm_year)+1900;
printf("Issued date=%d-%d-%d\n",a.issued.dd,a.issued.mm,a.issued.yy);
printf("The BOOK of ID %d is issued",a.bid);
printf(" On Student ID %d",a.sid);
a.duedate.dd=a.issued.dd+RETURNTIME;   //for return date
a.duedate.mm=a.issued.mm;
a.duedate.yy=a.issued.yy;
if(a.duedate.dd>30)
{
a.duedate.mm+=a.duedate.dd/30;
a.duedate.dd-=30;

}
if(a.duedate.mm>12)
{
a.duedate.yy+=a.duedate.mm/12;
a.duedate.mm-=12;

}
printf("\nTo be return:%d-%d-%d",a.duedate.dd,a.duedate.mm,a.duedate.yy);
fseek(fs,sizeof(a),SEEK_END);
fwrite(&a,sizeof(a),1,fs);
fclose(fs);
c=1;
}
	else
	{
		printf("this student id doesn\'t exists");
	}
	}
if(c==0)
{
printf("No record found");
}
printf("\n\nIssue any more(Y/N):");
fflush(stdin);
another=getche();
fclose(fp);
}
mainmenu();
}









void submit()
{
system("cls");
int b,cd,cm,cy,days;
struct tm *d; //for current date
	time_t t= time(NULL);
	time(&t);
	d=localtime(&t);

cd=(d->tm_mday);
cm=(d->tm_mon)+1;
cy=(d->tm_year)+1900;
FILE *fg;  //declaration of temporary file for delete
char another='y';
while(another=='y')
{
printf("Enter book id to remove:");
scanf("%d",&b);
fs=fopen("Issue.dat","rb+");
while(fread(&a,sizeof(a),1,fs)==1)
{
if(a.bid==b)
{
printf("The Book has taken on Student id %d\n",a.sid);
printf("Issued Date:%d-%d-%d\n",a.issued.dd,a.issued.mm,a.issued.yy);
printf("Returning Date:%d-%d-%d\n",a.duedate.dd,a.duedate.mm,a.duedate.yy);
days=365*(cy-a.duedate.yy)+30*(cm-a.duedate.mm)+cd-a.duedate.dd;
if(days>0)
{
	printf("you are late in returning the book.\nyour fine is2 * %d  is %d",days,2*days);
}
else
{
	printf("you are on time.There is no fine.");
}
findbook='t';
}

if(findbook=='t')
{
	sleep(3);
printf("Do You Want to Remove it?(Y/N)\n");
if(getch()=='y')
{
fg=fopen("record.dat","wb+");
rewind(fs);
while(fread(&a,sizeof(a),1,fs)==1)
{
if(a.bid!=b)
{
fseek(fs,0,SEEK_CUR);
fwrite(&a,sizeof(a),1,fg);
}
}
fclose(fs);
fclose(fg);
remove("Issue.dat");
rename("record.dat","Issue.dat");
printf("The issued book is removed from list\n");

}
}
if(findbook!='t')
{
printf("\nNo Record Found\n");
}
}
printf("Delete any more?(Y/N)\n");
another=getch();
}
mainmenu();
}









int checkid(int t)  
{
rewind(fp);
while(fread(&a,sizeof(a),1,fp)==1)
{
if(a.bid==t)
{
return 0;  
}
}
return 1; 
}










int getdata()
{
int t;
fp=fopen("Book.dat","ab+");
char book[20],author[20];
printf("\nEnter the Information Below\n");
printf("Category: ");
printf("%s",catagories[c-1]);
printf("\nBook ID: ");
scanf("%d",&t);
if(checkid(t) == 0)
{
printf("\n\aThre book id already exists\a\n");
getch();
mainmenu();
return 0;
}
a.bid=t;
printf("Book Name: ");
scanf("%s",book);
printf("Author:");
scanf("%s",author);
rewind(fp);
while(fread(&a,sizeof(a),1,fp)==1)
{
if(strcmp(catagories[c-1],a.cat)==0)
{
if(strcmp(book,a.bname)==0)
{
if(strcmp(author,a.Author)==0)
{
	printf("\n\aThe book already exists\a\n");
	sleep(1);
	mainmenu();
	return 0;
}
}
}
}
strcpy(a.bname,book);
strcpy(a.Author,author);
printf("Quantity:");
scanf("%d",&a.quantity);
printf("Price:");
scanf("%f",&a.Price);
printf("Rack No:");
scanf("%d",&a.rackno);
return 1;
}










int sid(int t)
{
	fseek(fl,0,SEEK_SET);
	while(fread(&l,sizeof(l),1,fl)==1)
	{
		if(t==l.sid)
		{
			return 0;
		}
	}
	return 1;
}
