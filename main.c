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
// вимкнув повідомлення про використання небезпечних функцій з string.h
#pragma warning(disable : 4996)

#include "config_manager.h"
#include "license_key.h"




int main(int argc, char* argv[]) {

	// шлях до бази данних
	char DB_path[200];

	// зчитаний ключ з конфігураційного файлу
	int license_key;

	// генерація імені файла
	char cfg_filename[200];
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
	
	// виводимо шлях поточної програми
	printf("name of file: %s", cfg_filename);

	// редагуємо ключ та назву БД
	printf("\nkey: %d\n", key_generate());
	edit_key(cfg_filename, 2921221);
	edit_pathDB(cfg_filename, "LongExampleDataBaseName.dat");
	make_cfg_file(cfg_filename);
	
	// перевірка чи вдалося зчитати
	if ((read_pathDB(cfg_filename, DB_path) != 0) || (read_key(cfg_filename, &license_key))) {
		// вивід повідомлення про помилку
		printf("\nError occurupted\n");
		return 1;
	}
	// виведення назви бази данних
	else {
		printf("\nname of DB file: %s\nkey: %d", DB_path, license_key);
		printf("\nis valid %d", key_valid(license_key));
	}

	return 0;
}