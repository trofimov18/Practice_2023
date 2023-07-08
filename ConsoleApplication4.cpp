/**
* @file ConsoleApplication4.cpp
* @author Ананєнко Д.В., гр. 515а, варіант 30
* @date 08 червня 2023
* @brief Навчальна практика
*
* База даних дисертацій
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <time.h>
#include "Header.h"

#define MAX_SIZE 100
#define MAX_KEY_LENGTH 50
typedef struct {
	int id;
	char* council_code;
	int defense_date;
	int registration_date;
} Dissertation;
typedef struct {
	Dissertation* dissertations;
	int count;
} DissertationDatabase;
/**
Добавляет диссертацию в базу данных.
@param database Указатель на структуру базы данных диссертаций
@param license_key Ключ лицензии
@param registration_date Дата регистрации
@param defense_date Дата защиты
*/
void addDissertation(DissertationDatabase* database, const char*
	license_key, int registration_date, int defense_date) {
	if (database->count < MAX_SIZE) {
		Dissertation* dissertation = &database->dissertations[database->count];
		dissertation->id = database->count + 1;
		dissertation->council_code = (char*)malloc(strlen(license_key) +1);
		strcpy(dissertation->council_code, license_key);
		dissertation->defense_date = defense_date;
		dissertation->registration_date = registration_date;
		database->count++;
		printf("Диссертация успешно добавлена.\n");
	}
	else {
		printf("База данных диссертаций заполнена.\n");
	}
}
/**
Удаляет диссертацию из базы данных по заданному
идентификатору.
@param database Указатель на структуру базы данных диссертаций
@param dissertation_id Идентификатор диссертации
*/
void deleteDissertation(DissertationDatabase* database, int
	dissertation_id) {
	if (dissertation_id >= 1 && dissertation_id <= database->count) {
		Dissertation* dissertation = &database->dissertations[dissertation_id - 1];
		free(dissertation->council_code);
		memmove(dissertation, dissertation + 1, (database->count -
			dissertation_id) * sizeof(Dissertation));
		database->count--;
		printf("Диссертация успешно удалена.\n");
	}
	else {
		printf("Ошибка: Неверный ID диссертации.\n");
	}
}
/**
Выводит список диссертаций из базы данных.
@param database Указатель на структуру базы данных диссертаций
*/
void displayDissertations(DissertationDatabase* database) {
	printf("+----+-----------------+------------------+-------------------+\n");
	printf("| ID | Код совета      | Дата регистрации | Дата защиты       | \n");
	printf("+----+-----------------+------------------+-------------------+\n");
	for (int i = 0; i < database->count; i++) {
		Dissertation* dissertation = &database->dissertations[i];
		printf("| %-2d | %-15s | %-16d | %-17d |\n", dissertation->id,
			dissertation->council_code, dissertation->registration_date
			, dissertation->defense_date);
	}
	printf("+----+-----------------+------------------+-------------------+\n");
}
/**
Редактирует данные диссертации в базе данных.
@param database Указатель на структуру базы данных диссертаций
@param dissertation_id Идентификатор диссертации
*/
void editDissertation(DissertationDatabase* database, int
	dissertation_id) {
	if (dissertation_id >= 1 && dissertation_id <= database->count) {
		Dissertation* dissertation = &database->dissertations[dissertation_id - 1];
		printf("Текущие данные диссертации:\n");
		printf("ID: %d\n", dissertation->id);
		printf("Код совета: %s\n", dissertation->council_code);
		printf("Дата защиты: %d\n", dissertation->defense_date);
		printf("Дата регистрации: %d\n", dissertation->registration_date);
		printf("Введите новую дату регистрации (ГГГГММДД): ");
		scanf("%d", &dissertation->registration_date);
		printf("Введите новую дату защиты (ГГГГММДД): ");
		scanf("%d", &dissertation->defense_date);
		printf("Данные диссертации успешно обновлены.\n");
	}
	else {
		printf("Ошибка: Неверный ID диссертации.\n");
	}
}
/**
Вычисляет разницу между двумя датами в днях.
@param date1 Первая дата в формате "ГГГГММДД"
@param date2 Вторая дата в формате "ГГГГММДД"
@return Разница между датами в днях
*/
int calculateDateDifference(const char* date1, const char* date2) {
	struct tm tm1 = { 0 };
	struct tm tm2 = { 0 };
	sscanf(date1, "%4d%2d%2d", &tm1.tm_year, &tm1.tm_mon,
		&tm1.tm_mday);
	sscanf(date2, "%4d%2d%2d", &tm2.tm_year, &tm2.tm_mon,
		&tm2.tm_mday);
	time_t time1 = mktime(&tm1);
	time_t time2 = mktime(&tm2);
	return (int)difftime(time2, time1) / (60 * 60 * 24);
}
/**
Выводит максимальную дату защиты диссертации для заданного
кода совета.
@param database Указатель на структуру базы данных диссертаций
@param council_code Код совета**/
void displayMaxDefenseDate(DissertationDatabase* database, const
	char* council_code) {
	int max_defense_date = 0;
	for (int i = 0; i < database->count; i++) {
		Dissertation* dissertation = &database->dissertations[i];
		if (strcmp(dissertation->council_code, council_code) == 0 &&
			dissertation->defense_date > max_defense_date) {
			max_defense_date = dissertation->defense_date;
		}
	}
	if (max_defense_date > 0) {
		printf("Максимальная дата защиты диссертации в раде %s:% d\n", council_code, max_defense_date);
	}
	else {
		printf("В раде %s нет диссертаций.\n", council_code);
	}
}
/**
Выводит список диссертаций, зарегистрированных менее чем через
10 дней после защиты.
@param database Указатель на структуру базы данных диссертаций
*/

void displayRecentRegistrations(DissertationDatabase* database) {
	printf("+----+-----------------+------------------+---------------+\n");
	printf("| ID | Код совета      | Дата регистрации | Дата защиты   |\n");
	printf("+----+-----------------+------------------+---------------+\n");
	int validCount = 0;
	for (int i = 0; i < database->count; i++) {
		Dissertation* dissertation = &database->dissertations[i];
		char defense_date_str[MAX_KEY_LENGTH];
		char registration_date_str[MAX_KEY_LENGTH];
		sprintf(defense_date_str, "%08d", dissertation->defense_date);
		sprintf(registration_date_str, "%08d", dissertation->registration_date);
		int dateDifference = calculateDateDifference(defense_date_str, registration_date_str);
		// Получаем последние две цифры даты защиты и даты регистрации
		int defense_last_two_digits = dissertation->defense_date % 100;
		int registration_last_two_digits = dissertation->registration_date % 100;
		// Проверяем условие четвертого пункта
		if (dateDifference >= 0 && dateDifference < 10 && registration_last_two_digits >= defense_last_two_digits) {
			// Выводим данные только для диссертаций, удовлетворяющих условиям
			printf("| %02d | %-15s | %-16s | %-13s |\n", dissertation->id, dissertation->council_code, registration_date_str, defense_date_str);
			validCount++;
		}
	}
	printf("+----+-----------------+------------------+---------------+\n");
	if (validCount > 0) {
		printf("Найдено %d диссертаций, зарегистрированных менее чем через 10 дней после защиты.\n", validCount);
	}
	else {
		printf("Нет диссертаций, зарегистрированных менее чем через 10 дней после защиты.\n");
	}
}


void saveDatabaseToFile(DissertationDatabase* database, const char* filename) {
	// Открыть файл для записи
	FILE* file = fopen(filename, "wb");
	if (file == NULL) {
		printf("Ошибка: Не удалось открыть файл %s для записи.\n", filename);
		return;
	}

	// Записать базу данных в файл
	fwrite(database, sizeof(DissertationDatabase), 1, file);

	// Закрыть файл
	fclose(file);

	printf("База данных успешно сохранена в файле %s.\n", filename);
}



void exportDatabaseToCSV(DissertationDatabase* database, const char* filename) {
	// Открыть файл для записи
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		printf("Ошибка: Не удалось открыть файл %s для записи.\n", filename);
		return;
	}

	// Записать заголовок CSV
	fprintf(file, "ID,Код совета,Дата регистрации,Дата защиты\n");

	// Записать данные диссертаций в формате CSV
	for (int i = 0; i < database->count; i++) {
		Dissertation* dissertation = &database->dissertations[i];
		fprintf(file, "%d,%s,%d,%d\n", dissertation->id, dissertation->council_code,
			dissertation->registration_date, dissertation->defense_date);
	}

	// Закрыть файл
	fclose(file);

	printf("База данных успешно экспортирована в файле %s.\n", filename);
}
typedef struct {
	int blockSize;
	int maxBlocks;
} DissertationFileSettings;

void changeFileSettings(const char* filename) {
	// Открыть файл для чтения и записи
	FILE* file = fopen(filename, "r+b");
	if (file == NULL) {
		printf("Ошибка: Не удалось открыть файл %s для чтения и записи.\n", filename);
		return;
	}

	// Получить текущие настройки файла
	DissertationFileSettings settings;
	fread(&settings, sizeof(DissertationFileSettings), 1, file);

	// Вывести текущие настройки файла
	printf("Текущие настройки файла %s:\n", filename);
	printf("Размер блока данных: %d\n", settings.blockSize);
	printf("Максимальное количество блоков: %d\n", settings.maxBlocks);

	// Запросить новые настройки у пользователя
	printf("Введите новые настройки файла:\n");

	printf("Размер блока данных (больше 0): ");
	scanf("%d", &settings.blockSize);

	printf("Максимальное количество блоков (больше 0): ");
	scanf("%d", &settings.maxBlocks);

	// Переместить указатель в начало файла
	fseek(file, 0, SEEK_SET);

	// Записать новые настройки в файл
	fwrite(&settings, sizeof(DissertationFileSettings), 1, file);

	// Закрыть файл
	fclose(file);

	printf("Настройки файла %s успешно изменены.\n", filename);
}

/** Читает лицензионный ключ из файла.
@param filename Имя файла
@return Указатель на строку с лицензионным ключом (NULL, если
файл не удалось открыть)
*/
char* readLicenseKeyFromFile(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("Ошибка: Не удалось открыть файл %s.\n", filename);
		return NULL;
	}
	char* license_key = (char*)malloc(MAX_KEY_LENGTH *
		sizeof(char));
	fgets(license_key, MAX_KEY_LENGTH, file);
	char* newline_char = strchr(license_key, '\n');
	if (newline_char != NULL) {
		*newline_char = '\0';
	}
	fclose(file);
	return license_key;
}
/**
Основная функция программы.
@return Код завершения программы
*/
int main() {
	/*const char* filename = "database.bin";
	changeFileSettings(filename);*/
	setlocale(LC_ALL, "Russian");
	DissertationDatabase database;
	database.dissertations = (Dissertation*)malloc(MAX_SIZE *
		sizeof(Dissertation));
	database.count = 0;
	int choice = -1;
	while (choice != 0) {
		printf("Меню:\n");
		printf("1. Добавить диссертацию\n");
		printf("2. Удалить диссертацию\n");
		printf("3. Просмотреть диссертации\n");
		printf("4. Диссертации, зарегистрированные менее чем через 10 дней после защиты\n");
		printf("5. Максимальная дата защиты в раде\n");
		printf("6.Внести изменения в дату диссертации\n");
		printf("7. Сохранить базу данных в файл с выбранным именем \n ");
		printf("8. Экспорт бази данных в текстовий файл формата CSV\n");
		printf("9. Изменить настройки файла\n");
		printf("0. Выход\n");
		printf("Введите ваш выбор: ");
		scanf("%d", &choice);
		if (choice == 1) {
			char filename[MAX_SIZE];
			int defense_date, registration_date;
			printf("Введите название файла с лицензионным ключом: ");
			scanf("%s", filename);
			char* license_key = readLicenseKeyFromFile(filename);
			if (license_key != NULL) {


				printf("Введите дату регистрации (ГГГГММДД): ");
				scanf("%d", &registration_date);
				printf("Введите дату защиты (ГГГГММДД): ");
				scanf("%d", &defense_date);
				addDissertation(&database, license_key, registration_date,
					defense_date);
				free(license_key);
			}
		}
		else if (choice == 2) {
			int dissertation_id;
			printf("Введите ID диссертации: ");
			scanf("%d", &dissertation_id);
			deleteDissertation(&database, dissertation_id);
		}
		else if (choice == 3) {
			displayDissertations(&database);
		}
		else if (choice == 4) {
			int numRecentRegistrations = 0; // Переменная для отслеживания количества диссертаций, зарегистрированных менее чем через 10 дней после защиты
			for (int i = 0; i < database.count; i++) {
				Dissertation* dissertation = &database.dissertations[i];
				char defense_date_str[MAX_KEY_LENGTH];
				char registration_date_str[MAX_KEY_LENGTH];
				sprintf(defense_date_str, "%08d", dissertation->defense_date);
				sprintf(registration_date_str, "%08d", dissertation->registration_date);
				int dateDifference =
					calculateDateDifference(defense_date_str, registration_date_str);
				if (dateDifference >= 0 && dateDifference < 10) {
					numRecentRegistrations++;
					break; // Прерываем цикл, если найдена хотя бы одна диссертация
				}
			}
			if (numRecentRegistrations > 0) {
				displayRecentRegistrations(&database);
			}
			else {
				printf("Нет диссертаций, зарегистрированных менее чем через 10 дней после защиты.\n");
			}
		}
		else if (choice == 5) {
			char council_code[MAX_KEY_LENGTH];
			printf("Введите код рады: ");
			scanf("%s", council_code);
			displayMaxDefenseDate(&database, council_code);
		}
		else if (choice == 6) {
			int dissertation_id;
			printf("Введите ID диссертации: ");
			scanf("%d", &dissertation_id);
			editDissertation(&database, dissertation_id);
		}
		else if (choice == 7) {
			char filename[MAX_SIZE];
			printf("Введите имя файла для сохранения базы данных: ");
			scanf("%s", filename);
			saveDatabaseToFile(&database, filename);
		}
		else if (choice == 8) {
			char filename[MAX_SIZE];
			printf("Введите имя файла для экспорта базы данных в формате CSV: ");
			scanf("%s", filename);
			exportDatabaseToCSV(&database, filename);
		}
		else if (choice == 9) {
			char filename[MAX_SIZE];
			printf("Введите имя файла для изменения настроек: ");
			scanf("%s", filename);
			changeFileSettings(filename);
		}

		else if (choice == 0) {
			printf("Программа завершена.\n");
		}
		else {
			printf("Ошибка: Неверный выбор. Попробуйте снова.\n");
		}
	}
	for (int i = 0; i < database.count; i++) {
		free(database.dissertations[i].council_code);
	}
	free(database.dissertations);
	return 0;
}
