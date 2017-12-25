#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

struct student
{
    char roll[20],name[20],dept[4],status[20];
};

typedef struct student std;

FILE *fptr;

char fpath[100];

void insert()
{
    int ch,flag;
    char name[20];
    std s;
    printf("\n*****INSERT*****\n");
    printf("*****MENU*****\n1.Create a new file\n2.write in existing file\n");
    printf("Choice :");
    scanf("%d",&ch);
    if(ch==1)
    {
        printf("\nEnter the departed year of students to insert:");
        scanf("%s",name);
        strcat(name,".dat");
        if((fptr=fopen(name,"wb"))==NULL)
        {
            printf("File was not created!\n");
            return;
        }
        do
        {
            printf("\nEnter Student details :\n");
            printf("\nEnter the name :");
            fflush(stdin);
            gets(s.name);
            printf("Enter the roll :");
            gets(s.roll);
            printf("Enter the dept :");
            gets(s.dept);
            printf("Enter the work status :");
            gets(s.status);
            fwrite(&s,sizeof(s),1,fptr);
            printf("Do you want to continue insertion? 1 or 0 :");
            scanf("%d",&flag);
        }while(flag==1);
        fclose(fptr);
    }
    if(ch==2)
    {
        printf("\nEnter the departed year of students to insert:");
        scanf("%s",name);
        strcat(name,".dat");
        if((fptr=fopen(name,"a"))==NULL)
        {
            printf("File was not Opened!\n");
            return;
        }

        do
        {
            printf("\nEnter Student details :\n");
            printf("\nEnter the name :");
            fflush(stdin);
            gets(s.name);
            printf("Enter the roll :");
            gets(s.roll);
            printf("Enter the dept :");
            gets(s.dept);
            printf("Enter the work status :");
            gets(s.status);
            fwrite(&s,sizeof(s),1,fptr);
            printf("Do you want to continue insertion? 1 or 0 :");
            scanf("%d",&flag);
        }while(flag==1);
        fclose(fptr);
    }

}

long int count(char *name)
{
    long int i=0;
    std s;
    if((fptr=fopen(name,"rb"))==NULL)
    {
        return;
    }
    while(!feof(fptr))
    {
        fread(&s,sizeof(s),1,fptr);
        i++;
    }
    fclose(fptr);
    return (i);
}

void search()
{
    std s;
    long int i,j=0;
    char sroll[10],name[20],fpath[100];
    printf("\n*****SEARCH*****\n");
    printf("Enter the roll number of the student : ");
    fflush(stdin);
    gets(sroll);
    fflush(stdin);
    printf("Enter the departed year of that student:");
    scanf("%s",name);
    strcat(name,".dat");
    i = count(name);
    if((fptr=fopen(name,"rb"))==NULL)
    {
        printf("File was not opened!\n");
        return;
    }
    while(j<i)
    {
        fread(&s,sizeof(s),1,fptr);
        if(!strcmp(s.roll,sroll))
        {
            printf("\nSearch successful!\n");
            printf("\nName :");
            puts(s.name);
            printf("Roll :");
            puts(s.roll);
            printf("Dept :");
            puts(s.dept);
            printf("Work status :");
            puts(s.status);
            printf("\n");
            break;
        }
        j++;
    }
    if(j>=i)
    {
        printf("Search unsuccessful!\n");
    }
    fclose(fptr);
}

void update()
{
    std s;
    long int i,j=0,k;
    char sroll[10],name[20],fpath[100],stat[20];
    printf("\n*****UPDATE*****\n");
    printf("Enter the roll number of the student to update info: ");
    fflush(stdin);
    gets(sroll);
    printf("Enter the departed year of that student :");
    scanf("%s",name);
    strcat(name,".dat");
    i = count(name);
    k=sizeof(std);
    if((fptr=fopen(name,"rb+"))==NULL)
    {
        printf("File was not opened!\n");
        return;
    }
    while(j<i)
    {
        fread(&s,sizeof(s),1,fptr);
        if(!strcmp(s.roll,sroll))
        {
            printf("\nSearch is successful!\n");
            printf("\nName :");
            puts(s.name);
            printf("Roll :");
            puts(s.roll);
            printf("Dept :");
            puts(s.dept);
            printf("Work status :");
            puts(s.status);
            printf("\n");
            printf("Enter the new work status :");
            gets(stat);
            gets(stat);
            fseek(fptr,-k,SEEK_CUR);
            strcpy(s.status,stat);
            fwrite(&s,sizeof(s),1,fptr);
            printf("\nData successfully Updated!\n");
            break;
        }
        j++;
    }
    if(j==i)
    {
        printf("Search unsuccessful!\n");
    }
    fclose(fptr);
}


void display()
{
    long int i,j=0;
    char name[20],c;
    std s;
    printf("\n*****DISPLAY*****\n");
    printf("Enter the departed Year to Display :");
    scanf("%s",name);
    strcat(name,".dat");
    i = count(name);
    if((fptr=fopen(name,"rb"))==NULL)
    {
        printf("File was not opened!\n");
        return;
    }
    printf("\n-------------------------------------------------------------------------\n");
    printf("Rollno.\t\tName\t\tDepartment\tWork Status\n");
    printf("-------------------------------------------------------------------------\n");
    while(/*!feof(fptr)*/j<i-1)
    {
        fread(&s,sizeof(s),1,fptr);
        //fscanf(fptr,"%c",&c);
        printf("%s\t\t",s.roll);
        printf("%-20s",s.name);
        printf("%s\t\t",s.dept);
        printf("%s",s.status);
        printf("\n--------------------------------------------------------------------------\n");
        j++;
        //for(i=0;i<300000000;i++);
    }
    fclose(fptr);
}

void chpass()
{
    FILE *fp;
    char fpass[11],npass[11],opass[11];
    fp = fopen("pass.txt","r");
    fflush(stdin);
    fscanf(fp,"%s",fpass);
    fclose(fp);
    printf("Enter the old password :");
    scanf("%s",opass);
    if(!strcmp(opass,fpass))
    {
        printf("Enter the new password :");
        scanf("%s",npass);
        fp = fopen("pass.txt","w");
        fprintf(fp,"%s",npass);
        fclose(fp);
        printf("\nPassword successfully updated !\n");
    }
    else
    {
        printf("Entered password is incorrect !\n");
        printf("No password Changed.....\n");
    }
    return;
}

int main()
{
    int choice,ch;
    char pass[11],fpass[11];
    FILE *fp;
    printf("******ALUMNI MANAGEMENT SYSTEM******\n");
    fp = fopen("pass.txt","r");
    fflush(stdin);
    fscanf(fp,"%s",fpass);
    fclose(fp);
    do
    {
        printf("\n****MENU****\n1.Admin\n2.Student\n3.Exit\n");
        printf("Enter your choice :");
        scanf("%d",&choice);
        if(choice==1)
        {
            printf("Enter the password :");
            fflush(stdin);
            gets(pass);
            fp = fopen("pass.txt","r");
            fflush(stdin);
            fscanf(fp,"%s",fpass);
            fclose(fp);
            if(strcmp(pass,fpass)!=0)
            {
                printf("Password entered is incorrect !\n");
                continue;
            }
            do
            {
                printf("\n*****Menu*****\n1.Insert\n2.Display\n3.Search\n4.Update\n5.Change Password\n6.Exit\n");
                printf("Enter your choice :");
                scanf("%d",&ch);
                switch(ch)
                {
                    case 1:insert();break;
                    case 2: display();break;
                    case 3:search();break;
                    case 4:update();break;
                    case 5:chpass();break;
                    case 6:ch=6;break;
                    default:printf("Invalid option try again :");
                }
            }while(ch!=6);
        }
        else if(choice==2)
        {
            do
            {
                printf("\n*****Menu*****\n1.Display\n2.Search\n3.Exit\n");
                printf("Enter your choice :");
                scanf("%d",&ch);
                switch(ch)
                {
                    case 1: display();break;
                    case 2:search();break;
                    case 3:ch=3;break;
                    default:printf("Invalid option try again :");
                }
            }while(ch!=3);
        }
        else if(choice==3)
        {
        }
        else
        {
            printf("Invalid option try again :\n");
        }
    }while(choice!=3);
    return 1;
}
