#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "Header.h"

struct {
	char name[50];
	int day;
	int month;
	int year;
	double wage_rate;
	double base_salary;
	int number;
} worker[MAX];

int num = 0;


int new_rec()
{
	FILE* file;
	file = fopen("info.txt", "a");
	char* fname;
	fname = (char*)malloc(50 * sizeof(char));
	num++;
	worker[num].number = num;
	fprintf(file, "Record number: %d\n\n", worker[num].number);
	if (file == NULL)
	{
		perror("Error opening file");
		return -1;
	}
	printf("Input full name: ");
	getchar();
	if (fgets(fname, 50, stdin) != NULL)
	{
		fprintf(file, "Full name: %s", fname);
	}
	strcpy(worker[num].name, fname);

	printf("Input date of employment: ");
	for (int i = 0; ;)
	{
		scanf_s("%d", &worker[num].day);
		scanf_s("%d", &worker[num].month);
		scanf_s("%d", &worker[num].year);
		if (worker[num].day < 1 || worker[num].day>31)
		{
			printf("Please enter a valid date: ");
			continue;
		}

		if (worker[num].month < 1 || worker[num].month>12)
		{
				printf("Please enter a valid date: ");
				continue;
		}
		
		if (worker[num].year>2023)
		{
			printf("Please enter a valid date: ");
			continue;
		}
		
		fprintf(file, "Date of employment: %d %d %d\n", worker[num].day, worker[num].month, worker[num].year);
		break;
	}

	printf("Input wage rate: ");
	scanf_s("%lf", &worker[num].wage_rate);
	fprintf(file, "Wage rate: %.2lf\n", worker[num].wage_rate);
	printf("Input base salary: ");
	scanf_s("%lf", &worker[num].base_salary);
	fprintf(file, "Base salary: %.2lf\n\n", worker[num].base_salary);
	printf("Saved successfully, record number: %d\n\n", num);
	fclose(file);
	free(fname);	
}

int delete_rec()
{ 
	FILE* file;
	file = fopen("info.txt", "a");
	int number, i;
	if (num == 0)
	{
		printf("The database is empty");
		return;
	}
	printf("Input record number: ");
	scanf_s("%d", &number);
	if (number > num)
	{
		printf("Record with this number does not exist");
		return;
	}
	i = find_rec(number);
	worker[i].number = 0;
	
	printf("Successfully deleted!\n");
	fprintf(file, "Record number %d was deleted", number);
	fclose(file);

}

int find_rec(int number)
{
	for (int i = 0; i <= num; i++)
	{
		if (worker[i].number == number)
			return i;
	}
	return -1;
}

int all_recs()
{
	for (int i = 1; i <= num; i++)
	{
		if (worker[i].number != 0)
		{
			printf("Record number: %d\n\n", worker[i].number);
			printf("Full name: %s", worker[i].name);
			printf("Employment date: %d %d %d\n", worker[i].day, worker[i].month, worker[i].year);
			printf("Wage rate: %.2lf\n", worker[i].wage_rate);
			printf("Base salary: %.2lf\n\n", worker[i].base_salary);
		}
	}
}

int update()
{
	FILE* file;
	file = fopen("info.txt", "a");
	char* fname;
	fname = (char*)malloc(50 * sizeof(char));
	int number, i;
	if (num == 0)
	{
		printf("The database is empty");
		return;
	}
	printf("Input record number: ");
	scanf_s("%d", &number);
	if (number > num)
	{
		printf("Record with this number does not exist\n");
		return;
	}
	i = find_rec(number);
	printf("What would you like to change?:\n"
		"\"1\" full name\n"
		"\"2\" employment name\n"
		"\"3\" wage rate\n"
		"\"4\" base salary\n");
	int operation;
	scanf_s("%d", &operation);
	switch (operation)
	{
	case 1:printf("Input new full name: "); 
		if (fgets(fname, 50, stdin) != NULL)
		{
			printf("Full name successfully changed!");
		}
		strcpy(worker[i].name, fname);
		fprintf(file, "Record number %d updated\nFull name: %s", i, worker[i].name);
		break;
	case 2:printf("Input new employment date: ");
		scanf_s("%d %d %d", &worker[i].day, &worker[i].month, &worker[i].year);
		fprintf(file, "Record number %d updated\n Employment date: %d %d %d\n", i, worker[i].day, worker[i].month, worker[i].year);
		printf("Changed successfully!\n"); break;
	case 3: printf("Input new wage rate: ");
		scanf_s("%lf", &worker[i].wage_rate);
		printf("Changed successfully!\n");
		fprintf(file, "Record number %d updated\n Wage rate: %.2lf\n", i, worker[i].wage_rate);
		break;
	case 4:printf("Input new base salary: ");
		scanf_s("%lf", &worker[i].base_salary);
		printf("Changed successfully!\n");
		fprintf(file, "Record number %d updated\n Base salary: %.2lf\n", i, worker[i].base_salary);
		break;
	default: printf("Wrong operation\n"); break;
	}

	fclose(file);
}


int after_date()
{
	int day, month, year;
	printf("Input date: ");
	for(;;)
	{
		scanf_s("%d", &day);
		scanf_s("%d", &month);
		scanf_s("%d", &year);
		if (day > 31 || month > 12 || year > 2023)
		{
			printf("Input valid date: ");
			continue;
		}
		else break;
	}
	if (num == 0)
	{
		printf("The database is empty");
		return;
	}
	
	for (int i = 1; i <=num; i++)
	{
		if (worker[i].year > year)
		{
			printf("%d %s\n", worker[i].number, worker[i].name);
			continue;
		}
		else if (worker[i].month > month && worker[i].year == year)
		{
			printf("%d %s\n", worker[i].number, worker[i].name);
			continue;
		}
		else if (worker[i].day > day && worker[i].month == month && worker[i].year == year)
		{
			printf("%d %s\n", worker[i].number, worker[i].name);
			continue;
		}
	}
	
}

int salary()
{
	double low, high;
	if (num == 0)
	{
		printf("The database is empty");
		return;
	}
	printf("Enter lower bound: ");
	scanf_s("%lf", &low);
	printf("Enter higher bound: ");
	scanf_s("%lf", &high);
	
	for (int i = 1; i <= num; i++)
	{
		double buff = worker[i].base_salary * worker[i].wage_rate;
		if (buff >= low && buff <= high)
		{
			printf("%d %s\n", worker[i].number, worker[i].name);
		}
	}
}

int key()
{
	char gen_key[KEY_LEN+1];
	char poss[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'F' };
	srand(time(NULL));
	FILE* f_key = fopen("config.cfg", "a");
	int randnum;

	for (int i = 0; i < KEY_LEN; i++)
	{
		randnum = rand() % 15;
		gen_key[i] = poss[randnum];
		
	}
	gen_key[KEY_LEN] = '\0';

	fprintf(f_key, "DB = base.dat\n");
	fprintf(f_key, "KEY = %s\n", gen_key);
	fclose(f_key);
}