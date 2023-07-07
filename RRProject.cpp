/**
* @file RRProject.cpp
* @author Коваленко І. В., гр. 515-б, варіант 11
* @date 18.05.2023
* @brief Розрахункова робота
*
* База даних студентів
*/

#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
#include "RRPModuleC.h"

int main(int argc, char* argv[]) {

	//підключення язикових пакетів
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "ukr");

	//підключення файлів проекту та перевірка їх на цілісність
	FILE* fppr;
	FILE* fcsv;
	if (fopen_s(&fppr ,"Murka.txt", "r")) {
		puts("\n Помилка відкриття файлу Murka.txt");
		return ERROR_TYPE;
	}
	if (fopen_s(&fcsv, "mybd.csv", "r+b")) {
		puts("\n Помилка відкриття файлу mybd.csv");
		return ERROR_TYPE;
	}

	//основна программа
	else {
		//допоміжні буфери
		char dbPath[100] = " ";
		char key[100] = " ";
		char buffer[100];

		//цикл на зчитування конфігуруючого файлу
		while (fgets(buffer, sizeof(buffer), fppr)) {
			// Пропускаем строки-комментарии
			if (buffer[0] == ';' || buffer[0] == '#') {
				continue;
			}
			//запис
			sscanf_s(buffer, "DB = %99s\n", dbPath, 99);
			sscanf_s(buffer, "KEY = %99s\n", key, 99);
		}
				
				/*
						Принцип генерації ключа, якщо число доякого відняти 6,
					буде ділитись на 13 без остачі, тоді ключ вірний
				
						Тобто, 123 - 6 = 117; => 117 % 13 = 0;
				
						Если ответ 0, тогда ключ валиден.
				*/
		int license = 6 + atoi(key);

		//перевірка шляху до бд
		if (strcmp(dbPath, "mybd.csv")) {
			printf("Помилка при считуванні шляху.\n");
		}

		//перевірка на ключ
		if (!(((license - 6) % 13) == 0)) {
#ifdef DEF
			printf("%i\n", (license % 13) == 0);
#endif
			printf("Помилка при считуванні ліцензійного ключа.\n");
		}

		//основна програма
		if ((strcmp(dbPath, "mybd.csv") == 0) && (((license - 6) % 13) == 0)) {
			
			//вказівник на структурний список, ініціалізаці та перевірка
			struct Stuff** IKnowAll = (struct Stuff**)malloc(SIZE * sizeof(struct Stuff*));
			if (IKnowAll == NULL) {
#ifdef DEF
				printf("err: creating of list is down");
#endif
				return ERROR_TYPE;
			}
			
			//встановлення останнього вузла списку на початок
			*IKnowAll = NULL;

			//зчитування данних із бази данних
			readDataFromFile(IKnowAll, fcsv);
			fclose(fcsv);

			//виведення інформації про программу до користувача
			printf(
				"\n\tЦя программа - є базою данних продуктів.\n\n"
				"\t\tЦе повідомлення ви побачите одноразово при запуску програми.\n\n"
				"\t\t\tДля користування програмою, користуйтесь меню на вашому єкрані.\n\n"
			);

			//виклик меню
			menu(IKnowAll);

			//звільнення списку
			free(IKnowAll);
		}
		//звільнення файлу
		fclose(fppr);
	}
	//завершення задачі
	return 0;
}