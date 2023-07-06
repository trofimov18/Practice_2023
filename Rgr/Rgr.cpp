/**
* @file Rgr.cpp
* @author Романцев Ростислав., гр. 515б, варіант 28
* @date 21 травня 2023
* @brief Розрахункова робота
*
* База даних студентів
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define CONFIG_FILE "config.txt"
#define MAX_KEY_LENGTH 10

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    float cost;
    int date[6];
    int isDeleted;
} AuctionLot;

typedef struct {
    char dbFile[MAX_NAME_LENGTH];
    char key[MAX_KEY_LENGTH];
} Config;

// Функція для отримання налаштувань з конфігураційного файлу
Config getConfig() {

    Config config = { 0 };;
    FILE* configFile = fopen(CONFIG_FILE, "r");
    if (configFile == NULL) {
        // Создание нового конфигурационного файла, если он не существует
        configFile = fopen(CONFIG_FILE, "w");
        if (configFile == NULL) {
            perror("Config file creation failed");
            exit(EXIT_FAILURE);
        }
        fprintf(configFile, "DB = database.db\n");
        fprintf(configFile, "KEY = secret_key\n");
        fclose(configFile);

        // Повторное открытие только что созданного файла
        configFile = fopen(CONFIG_FILE, "r");
        if (configFile == NULL) {
            perror("Config file opening failed");
            exit(EXIT_FAILURE);
        }
    }

    char line[100];
    while (fgets(line, sizeof(line), configFile)) {
        if (strncmp(line, "DB =", 4) == 0) {
            int result = sscanf(line, "DB = %s", config.dbFile);
            if (result != 1) {
                // Обработка ошибки при разборе строки
            }
        }
        else if (strncmp(line, "KEY =", 5) == 0) {
            int result = sscanf(line, "KEY = %s", config.key);
            if (result != 1) {

            }
        }
    }

    fclose(configFile);
    return config;
}

// Функція для додавання запису до бази даних
AuctionLot* addRecord(AuctionLot** lots, int* count) {
    AuctionLot lot;

    printf("Enter lot name: ");
    fgets(lot.name, sizeof(lot.name), stdin);
    lot.name[strcspn(lot.name, "\n")] = '\0'; // Видалення символу нового рядка

    printf("Enter lot cost: ");
    int result = scanf("%f", &lot.cost);
    if (result != 1) {
        printf("Error reading lot cost\n");
        exit(EXIT_FAILURE);
    }
    int c = getchar(); // Считывание символа новой строки и игнорирование его
    printf("Enter lot date and time (YYYY MM DD HH MM SS): ");
    scanf_s("%d %d %d %d %d %d", &lot.date[0], &lot.date[1], &lot.date[2], &lot.date[3], &lot.date[4], &lot.date[5]);

    lot.isDeleted = 0;

    lot.id = *count;
    AuctionLot* newLots = (AuctionLot*)realloc(*lots, (*count + 1) * sizeof(AuctionLot));
    if (newLots == NULL) {
        perror("Memory reallocation failed");
        exit(EXIT_FAILURE);
    }
    else {
        if (newLots != *lots) {
            *lots = newLots;
        }
        (*lots)[*count] = lot;
        (*count)++;
    }

    return *lots;
}




// Функція для видалення запису з бази даних
void deleteRecord(AuctionLot* lots, int* count, int id) {
    if (id < 0 || id >= *count) {
        printf("Invalid record ID\n");
        return;
    }

    if (lots[id].isDeleted) {
        printf("Record has already been deleted\n");
        return;
    }

    lots[id].isDeleted = 1;
    printf("Record with ID %d has been deleted\n", id);

    // Сдвигаем лоты после удаленного элемента
    for (int i = id + 1; i < *count; i++) {
        lots[i - 1] = lots[i];
        lots[i - 1].id = i - 1;
    }

    (*count)--;
}

// Функція для перегляду записів бази даних
void viewRecords(AuctionLot* lots, int count) {
    printf("ID\tName\tCost\tDate\n");
    for (int i = 0; i < count; i++) {
        if (!lots[i].isDeleted) {
            printf("%d\t%s\t%.2f\t%.2d/%.2d/%.2d %.2d:%.2d:%.2d\n",
                lots[i].id, lots[i].name, lots[i].cost,
                lots[i].date[0], lots[i].date[1], lots[i].date[2],
                lots[i].date[3], lots[i].date[4], lots[i].date[5]);
        }
    }
}



// Функція для зміни запису в базі даних
void modifyRecord(AuctionLot* lots, int count, int id) {
    if (id < 0 || id >= count) {
        printf("Invalid record ID\n");
        return;
    }

    if (lots[id].isDeleted) {
        printf("Record has been deleted\n");
        return;
    }

    AuctionLot modifiedLot = lots[id];

    printf("Enter new lot name (leave blank to keep the same): ");
    int c;
    

    fgets(modifiedLot.name, sizeof(modifiedLot.name), stdin);
    modifiedLot.name[strcspn(modifiedLot.name, "\n")] = '\0'; // Удаляем символ новой строки

    printf("Enter new lot cost (leave blank to keep the same): ");
    char costInput[10];
    fgets(costInput, sizeof(costInput), stdin);
    if (costInput[0] != '\n') {
        sscanf_s(costInput, "%f", &modifiedLot.cost);
    }

    printf("Enter new lot date and time (YYYY MM DD HH MM SS, leave blank to keep the same): ");
    char dateInput[50];
    fgets(dateInput, sizeof(dateInput), stdin);
    if (dateInput[0] != '\n') {
        sscanf_s(dateInput, "%d %d %d %d %d %d",
            &modifiedLot.date[0], &modifiedLot.date[1], &modifiedLot.date[2],
            &modifiedLot.date[3], &modifiedLot.date[4], &modifiedLot.date[5]);
    }

    lots[id] = modifiedLot;
}

// Функція для виведення інформації про лоти, вартість яких попадає у заданий діапазон
void printLotsInRange(AuctionLot* lots, int count, float minCost, float maxCost) {
    printf("Lots within the specified cost range:\n");
    printf("ID\tName\tCost\n");
    for (int i = 0; i < count; i++) {
        if (!lots[i].isDeleted && lots[i].cost >= minCost && lots[i].cost <= maxCost) {
            printf("%d\t%s\t%.2f\n", lots[i].id, lots[i].name, lots[i].cost);
        }
    }
}
// Функція для виведення інформації про лоти, що закінчуються у задану дату
void printLotsByDate(AuctionLot* lots, int count, int year, int month, int day) {
    printf("Lots ending on the specified date:\n");
    printf("ID\tName\tCost\tDate\n");
    for (int i = 0; i < count; i++) {
        if (!lots[i].isDeleted && lots[i].date[0] == year && lots[i].date[1] == month && lots[i].date[2] == day) {
            printf("%d\t%s\t%.2f\t%d/%d/%d %02d:%02d:%02d\n",
                lots[i].id, lots[i].name, lots[i].cost,
                lots[i].date[0], lots[i].date[1], lots[i].date[2],
                lots[i].date[3], lots[i].date[4], lots[i].date[5]);
        }
    }
}

// Функція для збереження бази даних у файлі
void saveDatabase(AuctionLot* lots, int count) {
    char dbFileName[MAX_NAME_LENGTH];

    printf("Enter the name of the database file: ");
    fgets(dbFileName, sizeof(dbFileName), stdin);
    dbFileName[strcspn(dbFileName, "\n")] = '\0'; // Удаление символа новой строки

    FILE* file = fopen(dbFileName, "wb");
    if (file == NULL) {
        perror("File opening failed");
        exit(EXIT_FAILURE);
    }

    fwrite(lots, sizeof(AuctionLot), count, file);

    fclose(file);

    printf("Database saved successfully as %s\n", dbFileName);
}

// Функція для експорту бази даних у текстовий файл формату CSV

void exportCSV(AuctionLot* lots, int count, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("File opening failed");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "ID;Name;Cost;Date\n");
    for (int i = 0; i < count; i++) {
        if (!lots[i].isDeleted) {
            fprintf(file, "%d;%s;%.2f; %d.%d.%d %02d:%02d:%02d\n",
                lots[i].id, lots[i].name, lots[i].cost,
                lots[i].date[0], lots[i].date[1], lots[i].date[2],
                lots[i].date[3], lots[i].date[4], lots[i].date[5]);
        }
    }
    fclose(file);
}




void open_input_database(AuctionLot** lots, int* count) {
    if (*lots != NULL) {
        free(*lots);
        *lots = NULL;
        *count = 0;
    }

    char db_file_name[MAX_NAME_LENGTH];
    printf("Enter the name of the database file to open: ");
    fgets(db_file_name, sizeof(db_file_name), stdin);
    db_file_name[strcspn(db_file_name, "\n")] = '\0'; // Удаление символа новой строки

    FILE* db_file;
    if (fopen_s(&db_file, db_file_name, "rb") != 0) {
        printf("Error opening the database file.\n");
        return;
    }

    AuctionLot lot;
    while (fread(&lot, sizeof(AuctionLot), 1, db_file)) {
        AuctionLot* temp = (AuctionLot*)realloc(*lots, (*count + 1) * sizeof(AuctionLot));
        if (temp == NULL) {
            perror("Memory reallocation failed");
            fclose(db_file);
            exit(EXIT_FAILURE);
        }
        *lots = temp;
        (*lots)[*count] = lot;
        (*count)++;
    }

    fclose(db_file);

    printf("Database file %s opened successfully.\n", db_file_name);
}


void createDatabaseFile(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        file = fopen(filename, "wb");
        if (file == NULL) {
            perror("Database file creation failed");
            exit(EXIT_FAILURE);
        }
        fclose(file);
        printf("Database file created: %s\n", filename);
    }
    else {
        fclose(file);
    }
}

int main() {
    Config config = getConfig();
    // Запрос лицензионного ключа у пользователя
    char licenseKey[MAX_KEY_LENGTH];
    printf("Enter license key: ");
    fgets(licenseKey, sizeof(licenseKey), stdin);
    licenseKey[strcspn(licenseKey, "\n")] = '\0'; // Удаление символа новой строки

    // Проверка лицензионного ключа
    int isValidKey = 0;
    if (atoi(licenseKey) % 1024 == 0) {
        isValidKey = 1;
    }

    // Проверка доступа к функциям
    if (isValidKey) {
        printf("License key is valid. Access granted to all functions.\n");
    }
    else {
        printf("Invalid license key. Access restricted.\n");
    }

    AuctionLot* lots = NULL;
    int count = 0;

    FILE* file = fopen(config.dbFile, "rb");
    if (file != NULL) {
        AuctionLot lot;
        while (fread(&lot, sizeof(AuctionLot), 1, file)) {

            AuctionLot* temp = (AuctionLot*)realloc(lots, (count + 1) * sizeof(AuctionLot));
            if (temp == NULL) {
                perror("Memory reallocation failed");
                free(lots); // Освобождаем память, выделенную до этого
                exit(EXIT_FAILURE);
            }
            lots = temp;
            lots[count] = lot;
            count++;
        }

        fclose(file);
    }


    int choice;
    do {
        printf("Menu:\n");
        printf("1. Add record\n");
        printf("2. Delete record\n");
        printf("3. View records\n");
        printf("4. Modify record\n");
        printf("5. Print lots within cost range\n");
        printf("6. Print lots ending on date\n");
        printf("7. Save database\n");
        printf("8. Export database to CSV\n");
        printf("9. Input database\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf_s("%d", &choice);
        (void)getchar(); // Читання символу нового рядка після введення вибору

        switch (choice) {
        case 1:
            if (isValidKey) {
                lots = addRecord(&lots, &count);
            }
            else {
                printf("Access denied. Invalid license key.\n");
            }
            break;
        case 2:
            if (isValidKey) {
                int id;
                printf("Enter the ID of the record to delete: ");
                scanf_s("%d", &id);
                deleteRecord(lots, &count, id);
            }
            else {
                printf("Access denied. Invalid license key.\n");
            }
            break;
        case 3:
            viewRecords(lots, count);
            break;
        case 4: {
            if (isValidKey) {
                int id;
                printf("Enter the ID of the record to modify: ");
                scanf_s("%d", &id);
                (void)getchar(); // Читання символу нового рядка після введення ID
                modifyRecord(lots, count, id);
                break;
            }
            else {
                printf("Access denied. Invalid license key.\n");
            }
            break;
        }

        case 5: {
            if (isValidKey) {
                float minCost, maxCost;
                printf("Enter the minimum cost: ");
                scanf_s("%f", &minCost);
                (void)getchar(); // Читання символу нового рядка після введення мінімальної вартості
                printf("Enter the maximum cost: ");
                scanf_s("%f", &maxCost);
                (void)getchar(); // Читання символу нового рядка після введення максимальної вартості
                printLotsInRange(lots, count, minCost, maxCost);
                break;
            }
            else {
                printf("Access denied. Invalid license key.\n");
            }
            break;
        }
        case 6: {

            if (isValidKey) {
                int year, month, day;
                printf("Enter the date (YYYY MM DD): ");
                scanf_s("%d %d %d", &year, &month, &day);
                (void)getchar(); // Читання символу нового рядка після введення дати
                printLotsByDate(lots, count, year, month, day);
                break;
            }
            else {
                printf("Access denied. Invalid license key.\n");
            }
            break;

        }
        case 7:
        {if (isValidKey) {
            saveDatabase(lots, count);
            break;
        }
        else {
            printf("Access denied. Invalid license key.\n");
        }
        break;
           
        }

        case 8: if (isValidKey) {
            exportCSV(lots, count, "database.csv");
            printf("Database exported to 'database.csv'\n");
        }
              else {
            printf("Access denied. Invalid license key.\n");
        }
              break;
           
        
        case 9:
            open_input_database(&lots, &count);
            break;
        case 0:
            printf("Goodbye!\n");
            break;
        default:
            printf("Invalid choice\n");
            break;
        }
    } while (choice != 0);

    free(lots);

    return EXIT_SUCCESS;
} 