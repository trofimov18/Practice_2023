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
#include "db_pretty_output.h"


void hot_keys() {
	printf("\n l -- show list of contacts\n n -- add new contact\n d -- delete contact\n e -- edit contact\n\n t -- show list of contacts without telegram\n m -- show contacts witch birthday in chosen month\n\n x -- export DB to .csv format\n s -- save DB with another name\n\n k -- editing license key\n p -- edit path to BD\n\n q -- exit program");
}


int main(int argc, char* argv[]) {
	// шлях до бази данних
	char DB_path[200];
	// шлях до .csv файлу
	char csv_file[200];
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

	// для прапорця видалення
	char flag;

	// для роботи функцій
	char name[100] = "";
	char fone[15] = "";
	int bith = 0;
	int tg = 0;
	int month;
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
	if (read_database_file(DB_path, &head) == -1) {
		printf("\nDB file error\nCreating  DB file");
		make_database_file(DB_path);
	}
	// виведення назви бази данних
	printf("\nYou now working with DB file: %s", DB_path);


	program_activate = key_valid(license_key);
	program_activate == 0 ? printf("\nYou using full version of programm") : printf("\nLicense key invalid you can`t use advansed programm funcs");


	// нескінченний цикл де все "крутиться"
	for (;;) {

		// очищаємо список
		while (head != NULL) {
			struct Person* temp = head;
			head = head->next;
			free(temp);
		}

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
			pretty_output_base(&head);
			break;


			//t виведення списку контактів
		case 116:
			// очищуємо консоль
			system("cls");
			if (program_activate == 0) {
				// виводимо контакти
				printf("\n List of contacts without telegram");
				read_database_file(DB_path, &head);
				pretty_output_base_telegram(&head);
			}
			else printf("\n Sorry you can`t use this func, please enter valid license key");
			break;


			//m виведення списку контактів
		case 109:
			// очищуємо консоль
			
			if (program_activate == 0) {
				printf("\n Input month for showing this contacts (1-12): ");
				scanf("%d", &month);
				system("cls");
				// виводимо контакти
				printf("\n List of contacts with birthday in that month");
				read_database_file(DB_path, &head);
				pretty_output_base_month(&head, month);
			}
			else { system("cls"); printf("\n Sorry you can`t use this func, please enter valid license key");}
			break;


		//n додавання новго запису
		case 110:
			// для задання новий айді
			read_database_file(DB_path, &head);

			// прапореь вибору режиму (для заміни того що видалено чи створення нового запису)
			flag = 0;

			// шукаємо видалений запис
			while (head != NULL) {
				if (head->deleted == 1) {
					for_id = head->id;
					// взводимо прапорець
					flag = 1;
					printf("\nHas whitespace in .dat at %d id\n", head->id);
					break;

				}
				// перевіряємо наступний елемент списку
				head = head->next;
			}
			// очищаємо список
			while (head != NULL) {
				struct Person* temp = head;
				head = head->next;
				free(temp);
			}
			//system("cls");
			printf(" Making new contact");
			struct Person new_person;
			// запису старими значеннями
			new_person.id = for_id;
			new_person.deleted = 0;

			// ввід старого імені
			char name[50];
			printf("\n What`s name of new contact: ");

			// захист від пропуску запису через вибір режиму
			gets(name);
			if (strlen(name) == 0) gets(name);
			strcpy(new_person.name_lastname, name);

			// ввід старого телефону
			char fone[15];
			printf("\n What`s phone number: ");
			gets(fone);
			strcpy(new_person.phone, fone);

			// ввід старого дати народження
			int bith;
			printf("\n What`s birtday (DDMMYYYY format): ");
			scanf_s("%d", &bith);
			new_person.birtday = bith;

			// ввід старого імені
			int tg;
			printf("\n Has this contact telegram? (1 - yes/0 - no): ");
			scanf_s("%d", &tg);
			new_person.telegram = tg;


			new_person.next = NULL;

			// якщо немає видалених записів то створюємо новий
			if (flag == 0) {
				add_to_db(DB_path, &new_person);
			}
			// є видалені редагуємо
			else {
				update_contact(DB_path, for_id, &new_person);
			}
			system("cls");
			break;

			// d - delete
		case 100:
			//system("cls");
			// запрошення до вводу айді який треба видалити
			printf("\n Enter ID of contact that you want to delete: ");
			scanf_s("%u", &for_id);

			// зчитуємо всі значення
			read_database_file(DB_path, &head);

			// перебираємо вся значення
			while (head != NULL) {
				// якщо запис з таким айді є
				if (head->id == for_id) {

					struct Person modified_person;
					// Заповнення зміненої структури старими данними
					modified_person.id = for_id;
					// але взводимо прапорець що запис видалено
					modified_person.deleted = 1;
					strcpy(modified_person.name_lastname, head->name_lastname);
					modified_person.birtday = head->birtday;
					strcpy(modified_person.phone, head->phone);
					modified_person.telegram = head->telegram;
					modified_person.next = NULL;
					printf("\n%s - deleted\n", modified_person.name_lastname);
					// оновлюємо запис
					update_contact(DB_path, for_id, &modified_person);

					break;
				}
				// наступне значення
				head = head->next;
			}
			break;

			// e edit
		case 101:
			//system("cls");
			// запрощення до вводу айді яке потрібно редагувати
			printf("\n Enter ID of contact that you want to edit: ");
			scanf_s("%u", &for_id);

			// зчитуємо всі значення
			read_database_file(DB_path, &head);

			// перебираємо вся значення
			while (head != NULL) {
				// якщо контакт з тиким айді є
				if (head->id == for_id) {

					struct Person modified_person;
					// Заповнення зміненої структури старими значеннями
					modified_person.id = for_id;
					modified_person.deleted = 0;
					strcpy(modified_person.name_lastname, head->name_lastname);
					modified_person.birtday = head->birtday;
					strcpy(modified_person.phone, head->phone);
					modified_person.telegram = head->telegram;
					modified_person.next = NULL;
					printf("\n%s\n", modified_person.name_lastname);

					// запрошення до вибору що саме будемо змінювати
					printf("\nwhat you want to edit n - name, b - birthday, p - phone, t - telegram: ");
					char edit_choose;
					// отримуємо користувацький вибір
					edit_choose = getch();
					switch (edit_choose)
					{
						// n name
					case 110:
						// отримуємо нове ім'я
						printf("\n What`s name of new contact:\n");

						gets(name);
						if (strlen(name) == 0) gets(name);

						// записуємо нове ім'я до структури
						strcpy(modified_person.name_lastname, name);
						break;

						// p phone
					case 112:
						// зчитуємо телефон
						printf("\n What`s phone number: ");
						gets(fone);
						gets(fone);

						// записуємо новий номер телефону до структури
						strcpy(modified_person.phone, fone);
						break;
						// b - birthday
					case 98:
						// зчитуємо дату народження
						printf("\n What`s birtday (DDMMYYYY format): ");
						scanf_s("%d", &bith);

						// записуємо нову дату народження до структури
						modified_person.birtday = bith;
						break;

						// t - telegram
					case 116:
						// зчитуємо наявність телеграму
						printf("\n Has this contact telegram? (1 - yes/0 - no): ");
						scanf_s("%d", &tg);

						// записуємо нове значення
						modified_person.telegram = tg;
						break;

					default:
						break;
					}

					// редагуємо структуру новими данними
					update_contact(DB_path, for_id, &modified_person);

					break;
				}
				// наступний контакт
				head = head->next;
			}
			system("cls");
			break;

		case 115:
			// очищуємо консоль
			system("cls");
			printf("\n Please input name for saving DB file: ");
			scanf("%s", csv_file);
			make_database_file(csv_file);
			read_database_file(DB_path, &head);
			while (head != NULL) {
				add_to_db(csv_file, head);
				head = head->next;
			}
			break;

		// x - експорт
		case 120:
			// очищуємо консоль
			system("cls");
			printf("\n Please input name for .cvs file: ");
			scanf("%s", csv_file);
			// виводимо всі контакти
			//printf("\n Full list of contacts");
			read_database_file(DB_path, &head);
			export_to_csv(csv_file, &head);
			break;

		default:
			printf("\n%d", operation);
		}
	}
	return 0;
}