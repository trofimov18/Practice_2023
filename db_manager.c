#include "db_manager.h"

// створення файлу
int make_database_file(char* db_name) {
	// .dat файл
	FILE* dbfile;

	if ((dbfile = fopen(db_name, "wb+")) == NULL) {
		// файл не створено повертаємо 1
		return 1;
	}
	fclose(dbfile);

	return 0;
}

// зчитування файлу
int read_database_file(char* db_name, struct node** head) {
	// .dat файл
	FILE* dbfile;

	if ((dbfile = fopen(db_name, "rb")) == NULL) {
		// файл не створено повертаємо 1
		return -1;
	}

	// для повертаного значення (кількість записів)
	int for_id = 0;
	// Зчитування структур з файлу та додавання їх у список
	while (1) {
		// нова структура розміром з нашу структуру
		struct Person* new_person = (struct Person*)malloc(sizeof(struct Person));
		// якщо прочиталося не успішно (цикл завершиться коли нічого буде читати)
		if (fread(new_person, sizeof(struct Person), 1, dbfile) != 1) {
			free(new_person);
			break;
		}
		// зв'язуємо список
		new_person->next = *head;
		*head = new_person;
		// рахуємо скільки контактів
		for_id++;
	}
	// Закриття файлу
	fclose(dbfile);
	// повертаємо кількість записів
	return for_id;
}


// Функція для додавання нових записів структури в файл
void add_to_db(const char* filename, const struct Person* person) {
	// Відкриття файлу для додавання у режимі бінарного запису
	FILE* file = fopen(filename, "ab");
	if (file == NULL) {
		printf("\n!WRN File open error!\n");
		// виходимо з функції
		return;
	}

	// Запис структури в файл
	fwrite(person, sizeof(struct Person), 1, file);

	// Закриття файлу
	fclose(file);
}
