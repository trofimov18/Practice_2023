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

#include "config_manager.h"
#include "license_key.h"

void hot_keys() {
	printf("\n q -- exit program\n k -- editing license key\n p -- edit path to BD");
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
	if ((read_pathDB(cfg_filename, DB_path) != 0) || (read_key(cfg_filename, &license_key))) {
		// вивід повідомлення про помилку
		printf("\nRead .cfg file error\nCreating new .cfg file");
		// створення базового конфігураційного файлу
		make_cfg_file(cfg_filename);
		printf("\n.cfg file created");
	}
	// виведення назви бази данних
	printf("\nYou now working with DB file: %s", DB_path);
	program_activate = key_generate(license_key);
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
		}
	}
	return 0;
}