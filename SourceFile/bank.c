#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*This program reads a random aceess file sequentially updates data already written to the file ,create new data to be placed in the file , and delete data already in the file*/
struct clientData
{
	int acctNum;
	char lastName[15];
	char firstName[10];
	double balance;
}client;

//int enterChoice(void);
/*
void list(FILE *cfptr);
void updateRecord(FILE *);
void newRecord(FILE *);
void deleteRecord(FILE *);

int main()
{

	int Choice;
	FILE *cfptr;
	printf("\n\n\t::BANK ACCOUNT INFORMATION SYSTEM::");
	printf("\n\n-------------------------------------");
	cfptr=fopen("credit","rb+");
	if(cfptr==NULL)
	{
		cfptr=fopen("credit","wb+");
		if(cfptr==NULL)
		{
			puts("error in opening file\n");
			exit(1);
		}
	}
	while(1)
	{
		printf("\n1. Update account");
		printf("\n2. Add new account");
		printf("\n3. Delete all account");
		printf("\n4. List of record");
		printf("\n5. Exit\n");
		printf("Enter your choice: ");
		scanf("%d",&Choice);
		switch(Choice)
		{
			case 1:
				updateRecord(cfptr);
				break;
			case 2:
				newRecord(cfptr);
				break;
			case 3:
				deleteRecord(cfptr);
				break;
			case 4:
				list(cfptr);
				break;
			case 5:
				fclose(cfptr);
				exit(1);
			default:
				printf("wrong choice\n");
		}
	}
	fclose(cfptr);
	return 0;
}
*/
void textFile(FILE *readptr)
{
	FILE *writeptr;
	struct clientData client={0, "", "", 0.0};
	if((writeptr=fopen("accounts.txt","w"))==NULL)
		printf("File could not be opened.\n");
	else
	{
		rewind(readptr);
		fprintf(writeptr,"%6s%-16s%-11s%10s\n","Acct","Last Name", "First Name", "Balance");
		while(!feof(readptr))
		{
			fread(&client, sizeof(struct clientData), 1,readptr);
			if(client.acctNum!=0)
				fprintf(writeptr,"%-6d%-16s%-11s%10.2f\n",client.acctNum, client.lastName,client.firstName,client.balance);
		}
		fclose(writeptr);
	}
}

void updateRecord(FILE *fptr)
{
	int account;
	double transaction;
	struct clientData client={0,"", "", 0.0};
	printf("Enter account to update(1-100): ");
	scanf("%d",&account);
	fseek(fptr,(account-1) *sizeof(struct clientData),SEEK_SET);
	fread(&client, sizeof(struct clientData),1,fptr);
	if(client.acctNum==0)
		printf("Account #%d has no information.\n",account);
	else
	{
		printf("%-6d%-16s%-11s%10.2f\n\n",client.acctNum, client.lastName, client.firstName, client.balance);
		printf("Enter charge(+)or payment(-):");
		scanf("%lf",&transaction);
		client.balance+=transaction;
		printf("%-6d%-16s%-11s%10.2f\n\n",client.acctNum,client.lastName,client.firstName,client.balance);
		fseek(fptr,(account-1)*sizeof(struct clientData),SEEK_SET);
		fwrite(&client,sizeof(struct clientData),1,fptr);
	}
}

void deleteRecord(FILE *fptr)
{
	struct clientData client,blankclient={0,"","",0};
	int accountNum;
	printf("Enter account number to ""delete(1-100):");
	scanf("%d",&accountNum);
	fseek(fptr,(accountNum-1)*sizeof(struct clientData),SEEK_SET);
	fread(&client,sizeof(struct clientData),1,fptr);
	if(client.acctNum==0)
		printf("Account %d does not exist.\n",accountNum);
	else
	{
		fseek(fptr,(accountNum-1)*sizeof(struct clientData),SEEK_SET);
		fwrite(&blankclient,sizeof(struct clientData),1,fptr);
	}
}

void newRecord(FILE *fptr)
{
	struct clientData client={0,"","",0.0};
	int accountNum;
	printf("Enter new account number(1-100):");
	scanf("%d",&accountNum);
	fseek(fptr,(accountNum-1)*sizeof(struct clientData),SEEK_SET);
	fread(&client,sizeof(struct clientData),1,fptr);
	if(client.acctNum!=0)
		printf("Account #%d already contains information.\n",client.acctNum);
	else
	{
		printf("Enter firstname, lastname, balance:\n");
		scanf("%s%s%lf",client.firstName,client.lastName,&client.balance);
		client.acctNum = accountNum;
		fseek(fptr,(client.acctNum-1)*sizeof(struct clientData),SEEK_SET);
		fwrite(&client,sizeof(struct clientData),1,fptr);
	}
}

void list(FILE *cfptr)
{
	rewind(cfptr);
	printf("\nACCOUNT\t\tFIRSTNAME\t\tLASTNAME\t\t\tBalance\n\n");
	while(fread(&client,sizeof(client),1,cfptr)==1)
	{
		printf("%d\t\t",client.acctNum);
		printf("%s\t\t\t",client.lastName);
		printf("%s\t\t\t\t",client.firstName);
		printf("%lf\n",client.balance);
	}
	printf("\n");
}
