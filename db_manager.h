#ifndef DB_MANAGER_H
#define DB_MANAGER_H

#include <stdio.h>
#include <String.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

// структура контакту
struct Person {
	unsigned int id;			// індефікаційний номер
	int deleted;				// видалено чи ні
	char name_lastname[100];	// імя або прізвище
	int birtday;				// дата народження в форматі DDMMYYYY
	char phone[14];				// номер мобільного (14 для запису в форматі +38000000000)
	int telegram;				// є чи немає телеграмм
	struct Node* next;			// адресса наступного елементу списку
};


// Оголошення функції створення файлу бази даних
int make_database_file(char* db_name);

// Зчитування значень з файла бази даних
int read_database_file(char* db_name, struct node** head);

// Додавання нових записів до бази даних
void add_to_db(char* db_name, const struct Person* person);

// функція зміни будь якого поля в базі данних
void update_contact(char* filename, unsigned int id, struct Person* new_person);

// експорт у .csv формат
void export_to_csv(char* outfile, struct node** head);


#endif