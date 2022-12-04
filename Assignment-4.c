#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
//struct for patient record
struct patientRecord//struct
{
    int id;
    char name[20];
    char CNIC[13];
    char phone_no[11];
    char disease[20];
    int isadmitted;
}p1;
//function prototypes
void addrecord(FILE*fp);
void deleteRecord(FILE*fp);
void updateRecord(FILE*fp);
void searchRecord(FILE*fp);
void displayRecord(FILE*fp);
int main()//main function
{
    int choice =0;
    FILE*fp=NULL;
    if((fp=fopen("Patient_record.txt","wb"))==NULL)
       {
           printf("Error: File could not be opened");
       }
    else{
    while(choice!=7)//check condition for while
    {
        printf("1.Add Patient\n2.Delete Patient\n3.Update Patient\n");
        printf("4.Search Patient\n5.Display all patients");
        printf("\n7.Exit program\n");
        printf("\nEnter your choice: ");
        scanf("%d",&choice);
        switch(choice)//switch statement
        {
        case 1:
            addrecord(fp);
            break;
        case 2:
            deleteRecord(fp);
            break;
        case 4:
            searchRecord(fp);
            break;
        default:
            printf("....You choose Exit....\n");
            break;
            }
            printf("\n***********************\n");
        }
        fclose(fp);//closing file
    }
    return 0;
    getch();
}
//function to delete record
void deleteRecord(FILE*fp)
{
     struct patientRecord p1;
     int id=0;
     printf("Enter the ID to be deleted: ");
     scanf("%d",&id);
     if((fp=fopen("Patient_record.txt","wb+"))==NULL)
     {
         printf("File could not be openend");
     }
     else{
            FILE*fp1=NULL;
         if((fp1=fopen("copy.txt","ab+")))
         {
             printf("Error: File could not be opened");
         }
         else{
            while((fread(&p1,sizeof(struct patientRecord),1,fp)==1))
            {
                 if(p1.id!=id)
                 {
                     fwrite(&p1,sizeof(struct patientRecord),1,fp1);
                 }
            }
     fclose(fp);
     fclose(fp1);
     remove("patientRecord.txt");
     rename("copy.txt","patientRecord.txt");
     if(p1.id!=id)
     printf("File deleted successfully");
     else
        printf("Does not exist");
        }
    }
}
//function for searching record
void searchRecord(FILE*fp)
{
     FILE*fp1;
     struct patientRecord p1;
     int id=0;
     int flag=0;//flag variable
     printf("Enter the ID to be searched: ");
     scanf("%d",&id);//prompting user from input
     if((fp=fopen("Patient_record.txt","wb+"))==NULL)//open file
     {
         printf("File could not be openend");
     }
    while((fread(&p1,sizeof(struct patientRecord),1,fp)>0 && flag==0))
     {
         if(p1.id==id)//check condition
         {
            flag=1;//update flag value
            printf("\nRecord is found");
            printf("ID: %d\nName: %s\nCNIC: &s",p1.id,p1.name,p1.CNIC);//displaying output
            printf("\nPhone_No: %s\nDisease: %s\n,Admission Status: %d",p1.phone_no,p1.disease,p1.isadmitted);
         }
     }
     if(flag==0)//if variable flag unchanged
     {
         printf("\nRecord not found");
     }
    fclose(fp);//closing file
}
