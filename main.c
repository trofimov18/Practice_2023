/**
* @file main.c
* @author Радченко Р.А., гр. 515, варіант 18
* @date 29 червня 2023
* @brief Навчальна практика
*
* База даних контактів
*/

#include <stdio.h>
#include <String.h>
#include <stdlib.h>
#include <windows.h>
// вимкнув повідомлення про використання небезпечних функцій з string.h
#pragma warning(disable : 4996)
#pragma warning(disable : 6031)

#include "config_manager.h"
#include "license_key.h"
#include "db_manager.h"

void hot_keys() {
	printf("\n q -- exit program\n k -- editing license key\n p -- edit path to BD\n l -- show list of contacts\n n -- add new contact");
}


int main(int argc, char* argv[]) {
	// шлях до бази данних
	char DB_path[200];
	// зчитаний ключ з конфігураційного файлу
	int license_key = 0;
	// генерація імені файла
	char cfg_filename[200];
	// валідність ключа
	int program_activate = 1;
	// код кнопки
	char operation;
	// для айді
	int for_id;

	// для роботи функцій
	char name[100] = "";
	char fone[15] = "";
	int bith = 0;
	int tg = 0;

	// ініціалізіція першого елементу
	struct Person* head = NULL;


	// отримуємо назву
	strcpy(cfg_filename, argv[0]);
	// отримуємо довжину рядка
	int lengh = strlen(cfg_filename);
	// закриваємо рядок
	cfg_filename[lengh] = '\0';
	// заміняємо букви
	cfg_filename[lengh - 1] = 'g';
	cfg_filename[lengh - 2] = 'f';
	cfg_filename[lengh - 3] = 'c';


	// перевірка чи вдалося зчитати
	if ((read_pathDB(cfg_filename, DB_path) == -1) || (read_key(cfg_filename, &license_key))) {
		// вивід повідомлення про помилку
		printf("\nRead .cfg file error\nCreating new .cfg file");
		// створення базового конфігураційного файлу
		make_cfg_file(cfg_filename);
		printf("\n.cfg file created");
	}


	// коректна назва фалйлу
	DB_path[strlen(DB_path) - 1] = '\0';

	// перевірка чи є цей файл
	if (read_database_file(DB_path, &head) != 0) {
		printf("\nDB file error\nCreating  DB file");
		make_database_file(DB_path);
	}
	// виведення назви бази данних
	printf("\nYou now working with DB file: %s", DB_path);


	program_activate = key_valid(license_key);
	program_activate == 0 ? printf("\nYou using full version of programm") : printf("\nLicense key invalid you can`t use advansed programm funcs");


	// нескінченний цикл де все "крутиться"
	for (;;) {
		hot_keys();
		// отримуємо горячу клавішу (тільки англ розкладка)
		operation = getch();
		switch (operation)
		{
			//q - вихід з программи
		case 113:
			exit(0);


			//k - зміна ключа
		case 107:
			printf("\nInput license key: ");
			scanf("%d", &license_key);
			//зміна ключа успішна
			if (edit_key(cfg_filename, license_key) == 0) {
				printf("\nNew license key saved\nPlease restart the program");
				exit(0);
			}
			//помилка відкриття файлу чи невірний формат ключа
			printf("\nEditing key error");
			break;


			//p - назви бази даних
		case 112:
			printf("\nInput name  of DB: ");
			scanf("%s", DB_path);
			//зміна ключа успішна
			if (edit_pathDB(cfg_filename, DB_path) == 0) {
				printf("\nNew DB path saved\nPlease restart the program");
				exit(0);
			}
			//помилка відкриття файлу чи невірний формат ключа
			printf("\nEditing DB path error");
			break;


			//l виведення списку контактів
		case 108:
			// очищуємо консоль
			system("cls");
			// виводимо всі контакти
			printf("\n Full list of contacts");
			read_database_file(DB_path, &head);
			break;


		//n додавання новго запису
		case 110:
			// для задання новий айді
			for_id = read_database_file(DB_path, &head);

			//system("cls");
			printf("\n Making new contact");
			struct Person new_person;
			// запису старими значеннями
			new_person.id = for_id;
			new_person.deleted = 0;

			// ввід імені
			printf("\n What`s name of new contact: ");

			// захист від пропуску запису через вибір режиму
			gets(name);
			if (strlen(name) == 0) gets(name);
			strcpy(new_person.name_lastname, name);

			// ввід телефону
			printf("\n What`s phone number: ");
			gets(fone);
			strcpy(new_person.phone, fone);

			// ввід дати народження
			printf(" What`s birtday (DDMMYYYY format): ");
			scanf_s("%d", &bith);
			new_person.birtday = bith;

			// ввід телеграму
			printf("Has this contact telegram? (1 - yes/0 - no): ");
			scanf_s("%d", &tg);
			new_person.telegram = tg;


			new_person.next = NULL;


			add_to_db(DB_path, &new_person);
	
			break;


		default:
			printf("\n%d", operation);
		}
	}
	return 0;
}