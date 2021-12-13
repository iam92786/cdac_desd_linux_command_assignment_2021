                
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

#define DB_FILE "bankacc.db"

typedef struct bank_acc{
	int acc_no;
	char name[20];
	double bal;
}acc_t;

void accept_account(acc_t *acc);
void print_account(acc_t *acc);
void add_record(acc_t acc);
void display_records(void);
void search_record_no(int key);
void edit_record(int key, double new_bal);

int menu_list(void)
{
	int choice;
	printf("0. Exit\n");
	printf("1. Add record\n");
	printf("2. Display records\n");
	printf("3. Search Record\n");
	printf("4. Edit record\n");
	printf("Enter choice : ");
	scanf("%d", &choice);

	return choice;
	
}

int main(void)
{
	int choice, key;
	double new_bal;
	acc_t acc;
	//accept_account(&acc);
	//print_account(&acc);

	while((choice = menu_list()) != 0)
	{
		switch(choice)
		{
			case 1:
					accept_account(&acc);
					add_record(acc);
					break;
			case 2:
					display_records();
					break;
			case 3:
					printf("Enter key to be searched : ");
					scanf("%d", &key);
					search_record_no(key);
					break;
			case 4:
					printf("Enter key to be searched : ");
					scanf("%d", &key);
					printf("Enter new balance : ");
					scanf("%lf", &new_bal);
					edit_record(key, new_bal);
					break;
		}
	}
	return 0;
}

void add_record(acc_t acc)
{
	int fd;
	//1. Open file in write|append|create mode
	fd = open(DB_FILE, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if(fd < 0)
	{
		printf("open() failed\n");
		exit(1);
	}
	//2. write record into file
	write(fd, &acc, sizeof(acc_t));
	//3. close the file
	close(fd);
}


void display_records(void)
{
	int fd;
	acc_t acc;
	//1. open file into read mode
	fd = open(DB_FILE, O_RDONLY);
	// err check

	printf("%-4s %-20s %-20s\n", "No", "Name", "Balance");
	//2. read all records one by one
	while((read(fd, &acc, sizeof(acc_t))) > 0)
	{
		//3. display individual record on console
		print_account(&acc);
	}
	//4. close file
	close(fd);
}

void search_record_no(int key)
{
	int fd, found=0;
	acc_t acc;
	//1. Open file into read mode
	fd = open(DB_FILE, O_RDONLY);
	//2. read all records one by one from file
	while((read(fd, &acc, sizeof(acc_t))) > 0)
	{
		//3. check if key is matching with acc no of current reacord, if it is matching means record is found
		if(key == acc.acc_no)
		{
			found = 1;
			//4. Once record is found break the loop
			break;
		}
	}
	//5. print same record on to the console
	if(found == 1)
		print_account(&acc);
	//6. close file
	close(fd);
}


void edit_record(int key, double new_bal)
{
	int fd, found=0;
	acc_t acc;
	//1. Open file into read mode
	fd = open(DB_FILE, O_RDWR);
	//2. read all records one by one from file
	while((read(fd, &acc, sizeof(acc_t))) > 0)
	{
		//3. check if key is matching with acc no of current reacord, if it is matching means record is found
		if(key == acc.acc_no)
		{
			found = 1;
			//4. Once record is found break the loop
			break;
		}
	}
	//5. print same record on to the console
	if(found == 1)
	{
		print_account(&acc);
		//6. update the same record with new balance
		acc.bal = new_bal;
		//7. change file position to 1 record behind
		lseek(fd, -1 * sizeof(acc_t), SEEK_CUR);
		//8. write updated record back into the file
		write(fd, &acc, sizeof(acc_t));
	}
	//9. close file
	close(fd);

}
void accept_account(acc_t *acc)
{
	printf("Enter account info : (acc no, name, balance) : ");
	scanf("%d %s %lf", &acc->acc_no, acc->name, &acc->bal);
}

void print_account(acc_t *acc)
{
	printf("%-4d %-20s %-.2lf\n", acc->acc_no, acc->name, acc->bal);
}