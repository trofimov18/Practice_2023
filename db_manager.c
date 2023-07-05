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

	// Запис структури в файл
	fwrite(person, sizeof(struct Person), 1, file);

	// Закриття файлу
	fclose(file);
}


// функція зміни будь якого поля в базі данних
void update_contact(const char* filename, unsigned int id, struct Person* new_person) {
	// відкриваємо файл для читання/запису в бінарному режимі
	FILE* file = fopen(filename, "r+b");

	struct Person person;

	// читаємо структуру
	while (fread(&person, sizeof(struct Person), 1, file) == 1) {
		// як індефікатор співпав то заміняємо на нашу структуру
		if (person.id == id) {
			// змінна для зміщення курсору по байтам файлу
			long offset = sizeof(struct Person) * (-1);
			// виставляємо куди
			fseek(file, offset, SEEK_CUR);
			// заміняємо на нашу структуру
			fwrite(new_person, sizeof(struct Person), 1, file);
			// прапорець що все добре
			break;
		}
	}
	// закриваємо файл
	fclose(file);
}