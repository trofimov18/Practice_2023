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