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




int main(int argc, char* argv[]) {

	// шлях до бази данних
	char DB_path[200];


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

	
	// перевірка чи вдалося зчитати
	if (read_pathDB(cfg_filename, DB_path) != 0) {
		// вивід повідомлення про помилку
		printf("\nError occurupted\n");
		return 1;
	}
	// виведення назви бази данних
	else {
		printf("\nname of DB file: %s", DB_path);
	}

	return 0;
}