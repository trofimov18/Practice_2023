#include "db_pretty_output.h"

// функція дл виводу всіх контактів в табличці
void pretty_output_base(struct node** head) {
	// хоча і локально але всеодно треба підчищати зв'язний список
	struct Person* current = *head;
	// виводимо заголовок таблиці
	printf("\n+----+--------------------------------------------------+---------------+-------------+----------+\n");
	printf("| id |                       Name                       |     Phone     |   Birtday   | Telegram |\n");
	// поки є елементи виводимо всі поля
	while (current != NULL) {
		// виводимо якщо контакт не видалено
		if (current->deleted == 0) {
			// тут форматований вивід та розбиття дати народження для більш красивого виводу
			printf("|%4u|%-50s|%-15s| %02d.%02d.%4d  |", current->id, current->name_lastname,
				current->phone, current->birtday / 1000000, ((current->birtday - (current->birtday / 1000000) * 1000000) - current->birtday % 10000) / 10000,
				current->birtday % 10000);
			current->telegram == 1 ? printf("     +    |\n") : printf("     -    |\n");
		}
		// наступний контакт
		current = current->next;
	}
	// закриваємо табличку
	printf("+----+--------------------------------------------------+---------------+-------------+----------+\n");
}