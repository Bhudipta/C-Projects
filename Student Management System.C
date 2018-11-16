#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<ctype.h>

struct subscriber
{
char idnumber[20];
char name[50];
int mark;
}s;
void addrecords();
void listrecords();
void modifyrecords();
void deleterecords();
void searchrecords();
void payment();
char get;
int main()
{	int password;
	int idnumber;
	char choice;



	system("cls");

	printf("\n\n\n\n\n\n\n\n\n");
	printf("\n\t\t\t\t*****WELCOME TO THE STUDENT MANAGEMENT SYSTEM*****");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n\t\t\t\tPress any Key to Continue.....");
	getch();
    system("cls");
	while (1)
	{
		system("cls");
			printf("\n Press A to add new records");
			printf("\n Press L to view the records");
			printf("\n Press M to modify the records.");
			printf("\n Press S to search records.");
			printf("\n Press D to delete records.");
			printf("\n\n Press E to exit\n\n");
		choice=getche();
		choice=toupper(choice);
		switch(choice)
		{
			case 'A':
				addrecords();break;
			case 'L':
				listrecords();break;
			case 'M':
				modifyrecords();break;
			case 'S':
				searchrecords();break;
			case 'D':
				deleterecords();break;
			case 'E':
				system("cls");
				printf("\n\t\t\t\t*****THANK YOU*****");
				printf("\n\t\t\t\t*****HAVE A NICE DAY*****");
				printf("This c program will exit in 10 seconds.\n");
				Sleep(10000);
				exit(0);
				break;
			default:
				system("cls");
				printf("Incorrect Input");
				printf("\nAny key to continue");
				getch();
		}
	}
}
void addrecords()
{
	FILE *f;
	char test;
	f=fopen("c:/file.ojs","ab+");
	if(f==0)
	{   f=fopen("c:/file.ojs","wb+");
		system("cls");
		printf("Loading.... Please Wait...");
		printf("/npress any key to continue");
		getch();
	}
	while(1)
	{
		system("cls");
		printf("\n Enter ID number:");
		scanf("%s",&s.idnumber);
		printf("\n Enter Student's name:");
		fflush(stdin);
		scanf("%[^\n]",&s.name);
		printf("\n Enter Mark:");
		scanf("%d",&s.mark);
		fwrite(&s,sizeof(s),1,f);
		fflush(stdin);
		system("cls");
		printf("1 record successfully added");
		printf("\n\n\n Press esc key to exit, any other key to add other record:");
		test=getche();

		if(test==27)
			break;
	}
	fclose(f);
}
void listrecords()
{
	FILE *f;
	int i;
	if((f=fopen("c:/file.ojs","rb"))==NULL)
		exit(0);
	system("cls");
	printf("ID Number\t\tStudent's Name\t\t\tMark\n");
	for(i=0;i<79;i++)
		printf("-");
	while(fread(&s,sizeof(s),1,f)==1)
	{
		printf("\n%-10s\t\t%-20s\t\t%d",s.idnumber,s.name,s.mark);
	}
	printf("\n");
	for(i=0;i<79;i++)
		printf("-");

fclose(f);
getch();
}
void deleterecords()
{
	FILE *f,*t;
	int i=1;
	char idnumber[20];
	if((t=fopen("c:/temp.ojs","w+"))==NULL)
	exit(0);
	if((f=fopen("c:/file.ojs","rb"))==NULL)
	exit(0);
	system("cls");
	printf("Enter the ID number to be deleted from the Database\n\n");
	fflush(stdin);
	scanf("%[^\n]",idnumber);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.idnumber,idnumber)==0)
		{       i=0;
			continue;

		}
		else
			fwrite(&s,sizeof(s),1,t);
	}
	if(i==1)
	{       system("cls");
		printf("Phone number \"%s\" not found",idnumber);
		remove("c:/file.ojs");
		rename("c:/temp.ojs","c:/file.ojs");
		getch();
		fclose(f);
		fclose(t);
		main();
	}
	remove("c:/file.ojs");
	rename("c:/temp.ojs","c:/file.ojs");
	system("cls");
	printf("The ID %s has been successfully DELETED!!!!",idnumber);
	fclose(f);
	fclose(t);
	getch();
}
void searchrecords()
{
	FILE *f;
	char idnumber[20];
	int flag=1;
	f=fopen("c:/file.ojs","rb+");
	if(f==0)
		exit(0);
	fflush(stdin);
	system("cls");
	printf("Enter ID Number to be searched in the database\n\n");
	scanf("%s", idnumber);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.idnumber,idnumber)==0)
		{	system("cls");
			printf(" Record Found ");
			printf("\n\nID Number: %s\nName: %s\nMark: %d\n",s.idnumber,s.name,s.mark);
			flag=0;
			break;
		}
		else if(flag==1)
		{	system("cls");
			printf("Requested ID Number has not been found in the database");
		}
	}
	getch();
	fclose(f);
}
void modifyrecords()
{
	FILE *f;
	char idnumber[20];
	long int size=sizeof(s);
	if((f=fopen("c:/file.ojs","rb+"))==NULL)
		exit(0);
	system("cls");
	printf("Enter the ID number to modify:");
	scanf("%[^\n]",idnumber);
	fflush(stdin);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.idnumber,idnumber)==0)
		{
			system("cls");
			printf("\n Enter ID number:");
			scanf("%s",&s.idnumber);
			printf("\n Enter name: ");
			fflush(stdin);
			scanf("%[^\n]",&s.name);
			printf("\n Enter Mark: ");
			scanf("%d",&s.mark);
			fseek(f,-size,SEEK_CUR);
			fwrite(&s,sizeof(s),1,f);
			break;
		}
	}
	fclose(f);
}
