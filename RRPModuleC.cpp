#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "RRPModuleC.h"

PUBLIC int readDataFromFile(struct Stuff** arr, FILE* fcsv) {		/* зчитування данних із бд */

	//буфер данних
	char temp[SIZE] = " ";
	//якщо перша строка
	bool isFirstLine = true;
	//поточний вузел
	struct Stuff* current = NULL;
	//вказівник на список після поточного
	struct Stuff** lastNextPtr = arr;

	//цикл на зчитування даних
	while (fgets(temp, sizeof(temp), fcsv)) {

		//перевірка на першу строку
		if (isFirstLine) {
			isFirstLine = false;
			continue; // Перехід на наступну строку
		}

		//ініціалізація поточного вузла
		current = (struct Stuff*)malloc(sizeof(struct Stuff));
		if (current == NULL) {
#ifdef DEF
			printf("err: reading stuff is failed");
#endif
			return ERROR_TYPE;
		}

		//виклик ініціалізації структури
		AddHelper(current);

		//поточний та наступний токен, для перевірки запису по клітинкам
		char* token = NULL;
		char* next_token = NULL;

		//зчитування слыв до ; за токеном
		token = strtok_s(temp, ";", &next_token);
		if (token != NULL) {
			// Зчитування Id
			current->id = atoi(token);

			// Зчитування Ім'я
			token = strtok_s(NULL, ";", &next_token);
			strncpy_s(current->name, SIZE, token, _TRUNCATE);

			// Зчитування Группи
			token = strtok_s(NULL, ";", &next_token);
			strncpy_s(current->group, SIZE, token, _TRUNCATE);

			// Зчитування Ціни
			token = strtok_s(NULL, ";", &next_token);
			current->price = atof(token);

			// Зчитування Постачальника
			token = strtok_s(NULL, ";", &next_token);
			strncpy_s(current->from, SIZE, token, _TRUNCATE);

			// Зчитування Флагу Видалення
			token = strtok_s(NULL, ";", &next_token);
			current->delstat = atoi(token);

			//перехід на наступний вузел
			current->next = NULL;

			//якщо зв'язний список не має вузлів, то поточний вузел, стане першим
			if (*arr == NULL) {
				*arr = current;
			}
			//перехід на наступний вузел
			*lastNextPtr = current;
			lastNextPtr = &(current->next);
		}
	}
	//завершення задачі
	return 0;
}

PUBLIC int CountOfWork(struct Stuff** arr) {		/* рахує скільки товарів вже існує */

	//поточний вузел
	struct Stuff* current = *arr;

	//кількість товарів
	int count = 0;
	while (current != NULL) {
		count++;
		current = current->next;
	}
	//повертаємо кількість товарів
	return count;
}

PUBLIC int menu(struct Stuff** arr) {		/* головне меню */

	while (true) {		/* цикл на виконання програми */

		//оголошення змінних
		int choise;
		char continum = ' ';

		//виведення інформації до користувача
		printf("\tВизвана функція меню.\n");
		printf("\tНатисніть:\n");
		printf(
			"\t\t1. Створити новий товар\n"
			"\t\t2. Налаштування товару за Id\n"
			"\t\t3. Видалення товару за Id\n"
			"\t\t4. Переглянути товар за Id\n"
			"\t\t5. Переглянути всі товари\n"
			"\t\t6. Виведення усіх товарів за постачальником\n"
			"\t\t7. Виведення усіх товарів за групою, в яких ціна нижче за заднау\n"
			"\t\t8. Збереження списку до CSV файлу\n"
			"\t\t0. Завершити програму\n"
		);

		//введення данних
		fflush(stdin);
		scanf_s("%i", &choise);

		//вибір символу до операції
		switch (choise) {
		case 1:		/* Створення товару */
			system("cls");
			printf("\tСтворюємо новий товар...\n");
			AddStuff(arr);
			break;
		case 2:		/* Змінити товар */
			system("cls");
			printf("\tЗмінюємо товар за Id...\n");
			ChangeSet(*arr);
			break;
		case 3:		/* Видалити товар */
			system("cls");
			printf("\tВидаляємо товар за Id...\n");
			DeleteStuff(arr);
			break;
		case 4:		/* Виведення товар за Id */
			system("cls");
			printf("\tВиводимо товар за Id...\n");
			PrintId(*arr);
			break;
		case 5:		/* Вивести всі відомі товари */
			system("cls");
			printf("\tВиводимо відомі товари...\n");
			PrintAll(arr);
			break;
		case 6:		/* Вивести знайдені товари за постачальником */
			system("cls");
			printf("\tВиводимо товари за постачальником...\n");
			PrintFrom(*arr);
			break;
		case 7:		/* Виведення усіх товарів заданої групи, ціна яких нижче за задану. */
			system("cls");
			printf("\tВиводимо товари за группою з фільтром на ціну...\n");
			GroupPriceFall(*arr);
			break;
		case 8:		/* Збереження даних до бд */
			system("cls");
			printf("\tЗберігаємо данні...\n");
			writeDataToFile(arr);
			break;
		case 0:		/* Завершити програму */
			system("cls");
			printf("\tЗавершення програми...\n");
			return 0;
		default:	/* Дія не була знайдена */
#ifdef DEF
			printf("err: menu choice is wrong");
#endif
			return ERROR_TYPE;
		}
	}
}

PRIVATE int writeDataToFile(struct Stuff** arr) {		/* Записує дані із зв'язного списку до бд */

	//відкриваємо файл бд
	FILE* fcsv;
	if (fopen_s(&fcsv, "mybd.csv", "w+")) {
		puts("\n Помилка відкриття файлу mybd.csv");
		return ERROR_TYPE;
	}

	//поточний вузел зв'язного списку
	struct Stuff* current = *arr;

	//запис першої строки
	fprintf(fcsv, "ID;Name;Group;Price;From;Del. Stat.\n");

	//цикл на запис данних із зв'язного списку
	while (current != NULL) {

		//запис
		fprintf(fcsv, "%d;%s;%s;%.2lf;%s;%i\n"
			, current->id
			, current->name
			, current->group
			, current->price
			, current->from
			, current->delstat
		);

		//перехід на наступний вузел зв'язного списку
		current = current->next;
	}
	//закриття файлу та заверешння задачі
	fclose(fcsv);
	return 0;
}

PRIVATE char getsymb() {		/* бітовий запис символу */
	char Csymb = ' ';
	do {
		scanf_s("%c", &Csymb);
	} while (Csymb == '\n');
	return Csymb;
}

PRIVATE int read_line(char* str, int n) {		/* побітовий запис строки */
	int ch, i = 0;
	while (getchar() != '\n');  // зачистка stdin
	while ((ch = getchar()) != '\n' && i < n - 1)
		str[i++] = ch;
	str[i] = '\0';
	return i;
}

PRIVATE bool TheDogma(struct Stuff* ptr) {		/* Створює товар на видаленних ділянках */

	//ініціалізація зв'язного вузла новими данними
	AddHelper(ptr);
	
	//зміна видаленого статусу
	ptr->delstat = false;

	//налаштування зв'язного вузла
	SetStuff(ptr);

	//повертає true, як правильно виконану роботу
	return true;
}

PRIVATE int AddStuff(struct Stuff** arr) {		/* створення нового вузла */

	//оголошення визову створення
	printf("Створення нового товару...\n");

	//ініціалізуємо new_node, який буде шукати місце для роташування нового товара
	struct Stuff* new_node = *arr;
	//перевірка на те, чи була дія виконана на видаленому місці, чи буде відбуватись пошук нового місця
	bool dogmaticKnowlege = false;

	//пошук місця під новий товар
	while (new_node != NULL) {
		if (new_node->delstat == 1) {
			dogmaticKnowlege = TheDogma(new_node);
			break;
		}
		new_node = new_node->next;
	}

	//якщо видалених вузлів знайдено не було
	if (!dogmaticKnowlege) {
		//ініціалізація останнього вузла
		new_node = (Stuff*)malloc(SIZE * sizeof(Stuff));
		if (new_node == NULL) {
#ifdef DEF
			printf("err: adding new stuff is failed");
#endif
			return ERROR_TYPE;
		}

		//виклик помічника
		AddHelper(new_node);

		//виклик налаштування товару
		new_node->id = CountOfWork(arr) + 1;
		SetStuff(new_node);

		//ініціалізація наступного вузла нулем
		new_node->next = NULL;

		//присвоювання вузла
		struct Stuff* last = *arr;
		while (last->next != NULL) {
			last = last->next;
		}

		//за для корректного переходу та збереження цілостності
		last->next = new_node;
	}

	//завершення задачі
	return 0;
}

PRIVATE int AddHelper(struct Stuff* help_new_stuff) {		/* допоміжна функція додавання товару */
	
	//ініціалізація товару
	help_new_stuff->name = (char*)malloc(SIZE * sizeof(char));
	if (help_new_stuff->name == NULL) {
#ifdef DEF
		printf("err: helping_adding stuff is failed");
#endif
		return ERROR_TYPE;
	}
	help_new_stuff->group = (char*)malloc(SIZE * sizeof(char));
	if (help_new_stuff->group == NULL) {
#ifdef DEF
		printf("err: helping_adding stuff is failed");
#endif
		return ERROR_TYPE;
	}
	help_new_stuff->from = (char*)malloc(SIZE * sizeof(char));
	if (help_new_stuff->from == NULL) {
#ifdef DEF
		printf("err: helping_adding stuff is failed");
#endif
		return ERROR_TYPE;
	}
	
	//заповнення товару базовими данними
	strcpy_s(help_new_stuff->name, SIZE, "zero");
	strcpy_s(help_new_stuff->group, SIZE, "zero");
	help_new_stuff->price = 0;
	strcpy_s(help_new_stuff->from, SIZE, "zero");
	help_new_stuff->delstat = 0;

	//завершення задачі
	return 0;
}

PRIVATE int SetStuff(struct Stuff* ptr) {		/* заповнення структур */
	
	//створення основних змінних
	int choise;
	char continum = ' ';

	//цикл на змінення товару
	while (true) {
		
		//виведення твоару на екран
		PrintStuff(ptr);
		
		//вибор дії
		printf("\tНатисніть:\n"
			"\t\t1. Змінити ім'я\n"
			"\t\t2. Змінити групу\n"
			"\t\t3. Змінити ціну товару\n"
			"\t\t4. Змінити постачальника\n"
			"\t\t0. Вийти із редактора\n"
		);

		//введення данних
		scanf_s("%i", &choise);
		
		//дії над товаром
		switch (choise) {
		case 1:		/* Задати ім'я */
			printf("Введіть нове ім'я товару: ");
			read_line(ptr->name, SIZE);
			break;
		case 2:		/* Задати групу */
			printf("Введіть нову групу товару: ");
			read_line(ptr->group, SIZE);
			break;
		case 3:		/* Задати ціну */
			printf("Введіть нову ціну для вашого товару: ");
			scanf_s("%lg", &ptr->price);
			break;
		case 4:		/* Задати постачальника */
			printf("Введіть нового постачальника товару: ");
			read_line(ptr->from, SIZE);
			break;
		case 0:		/* Закрити редактор */
			system("cls");
			printf("Редактор був закрит.");
			return 0;
		default:	/* Дія не була знайдена */
			printf("Некоректний ввід\n");
#ifdef DEF
			printf("err: set stuff char break");
#endif
			return ERROR_TYPE;
		}
		system("cls");
	}
}

PRIVATE void ChangeSet(struct Stuff* ptr) {		/* Змінити товар за Id */
	
	//ініціалізація поточного вузла
	struct Stuff* current = ptr;
	
	//оголошення та запит Id товару, який треба змінити
	int setId;
	printf("Вкажіть Id товару, який треба змінити: ");
	scanf_s("%i", &setId);

	// Знаходження вузла
	while (current != NULL && current->id != setId) {
		current = current->next;
	}
	// Налаштування вузла за Id
	if (current != NULL && current->delstat == 0) {
		SetStuff(current);
	}
	// Якщо Id не знайдено
	else {
		printf("Товар за Id %i не знайдено.\n", setId);
	}
}

PRIVATE int DeleteStuff(struct Stuff** arr) {		/* Видалення товару */
	
	// Оголошення та введення Id
	printf("Який товар потрібно видалити? Введіть id товару:\n");
	int d;
	scanf_s("%i", &d);
	
	// Ініціалізація зв'язного вузла поточного, та минулого
	struct Stuff* prev = NULL;
	struct Stuff* current = *arr;
	
	// Пошук товару за Id
	while (current != NULL && current->id != d) {
		prev = current;
		current = current->next;
	}
	// Якщо намає товару за Id
	if (current == NULL) {
		printf("Товар за Id %i не знайден\n", d);
		return ERROR_TYPE;
	}
	// Зміна флагу на видалення 
	if (prev != NULL) {
		current->delstat = 1;
	}
	// Якщо остання умова не
	else {
		*arr = current->next;
	}
	//завершення задачі
	return 0;
}

PRIVATE void PrintStuff(struct Stuff* ptr) {		/* виведення структури */
	if (ptr->delstat == 1) { return; }		/* перевірка на видалення */
	else
		printf(
			"\t\t+--------------------------------------------------+\n"
			"\t\t| Id вашого товару: %i\n"
			"\t\t+--------------------------------------------------+\n"
			"\t\t| Ім'я вашого товару: %s\n"
			"\t\t+--------------------------------------------------+\n"
			"\t\t| Группа вашого товару: %s\n"
			"\t\t+--------------------------------------------------+\n"
			"\t\t| Ціна вашого товару: %.2f грн\n"
			"\t\t+--------------------------------------------------+\n"
			"\t\t| Постачальник вашого товару: %s\n"
			"\t\t+--------------------------------------------------+\n\n"

			, ptr->id
			, ptr->name
			, ptr->group
			, ptr->price
			, ptr->from
		);
}

PRIVATE void PrintAll(struct Stuff** arr) {		/* Виведення всіх товарів */
	
	//ініціалізація поточного вузла
	struct Stuff* current = *arr;
	
	//оголошення про виведення
	printf("\tСписок ваших товарів:\n");
	while (current != NULL) {
		PrintStuff(current);
		current = current->next;
		printf("\n");
	}
	printf("\n");
}

PRIVATE void PrintId(struct Stuff* ptr) {		/* Виведення товару за Id */
	
	// ініціалізація поточного вузла
	struct Stuff* current = ptr;
	// Оголошення та запит Id
	int setId;
	printf("Вкажіть Id товару, який треба знайти: ");
	scanf_s("%i", &setId);
	
	// Знайти вузел за заданим Id
	while (current != NULL && current->id != setId) {
		current = current->next;
	}
	// Змінення вузла за заданим Id
	if (current != NULL && current->delstat == 0) {
		PrintStuff(current);
	}
	// Якщо вузел не знайден
	else {
		printf("Товар за Id %i не знайдено.\n", setId);
	}
}

PRIVATE int PrintFrom(struct Stuff* ptr) {		/* Виводить товари від одного постачальника */
	
	// Допоміжний структурний тип
	struct Stuff* current = ptr;
	
	// Оголошення та запит постачальника
	char* from = (char*)malloc(SIZE * sizeof(char));
	if (from == NULL) {
#ifdef DEF
		printf("err: print from stuff is failed");
#endif
		return ERROR_TYPE;
	}
	printf("Вкажіть постачальника товару, товари якого треба знайти: ");
	read_line(from, SIZE);
	
	//цикл на пошук та виведення
	while (current != NULL) {
		if (strcmp(current->from, from) == 0) {
			PrintStuff(current);
		}
		current = current->next;
	}

	//завершення задачі
	return 0;
}

PRIVATE int GroupPriceFall(struct Stuff* ptr) {		/* Виводить товари за группою, але тількі ті, які нижчі за ціною */
	
	// ініціалізація поточного вузла
	struct Stuff* current = ptr;
	
	// Оголошення та запит групи, ціни
	double price;
	char* group = (char*)malloc(SIZE * sizeof(char));
	if (group == NULL) {
#ifdef DEF
		printf("err: group price fall stuff is failed");
#endif
		return ERROR_TYPE;
	
	}
	printf("Вкажіть групу товару: ");
	read_line(group, SIZE);
	printf("Вкажіть ціну товару: ");
	scanf_s("%lg", &price);

	//пошук задовільних умов
	while (current != NULL) {
		if (strcmp(current->group, group) == 0 && current->price < price) {
			PrintStuff(current);
		}
		current = current->next;
	}

	//завершення задачі
	return 0;
}