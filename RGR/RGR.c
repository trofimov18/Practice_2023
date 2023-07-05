/**
* @file RGR.C
* @author Латишев Я.М., гр. 515а, варіант 29
* @date 26 квітня 2023
* @brief Розрахункова робота
*
* База даних студентів
*/
#define _CRT_SECURE_NO_WARNINGS
#include "windows.h";
#include <stdio.h>
#include "..\FNCTS\FNCTS.h"
#include "..\modules\modules.c"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define scanf scanf_s

#define CONFIG_FILE "RGR.cfg"

// Головна функція програми
int main() {
    SetConsoleCP(1251); // Встановлення кодування консолі для коректного виводу символів кирилиці
    SetConsoleOutputCP(1251); // Встановлення кодування виводу консолі для коректного виводу символів кирилиці
    // Перевірка наявності ліцензійного ключа
    int configFileCreated = createConfigFile();
    printf("------------------------------------------------\n");
    if (configFileCreated == 1) {
        printf("Конфігураційний файл створений.\n");
    }
    else if (configFileCreated == 0) {
        printf("Конфігураційний файл вже існує.\n");
    }
    else {
        printf("Помилка створення конфігураційного файлу.\n");
    }

    FILE* file = fopen(CONFIG_FILE, "r"); // Відкриваємо файл конфігурації для читання
    if (file == NULL) { // Якщо не вдалося відкрити файл
        printf("Помилка при відкритті файлу.\n"); // Виводимо повідомлення про помилку
        return 0; // Завершуємо роботу програми з кодом помилки 0
    }
    printf("------------------------------------------------\n");

    char line[100];
    int found = 0; // Змінна для збереження інформації про те, чи знайдено ключ у файлі
    int isAdmin = 0; // Змінна для збереження інформації про те, чи користувач є адміністратором
    while (fgets(line, sizeof(line), file)) { // Читаємо рядки з файлу доки не дійдемо до кінця файлу
        if (strncmp(line, "KEY", strlen("KEY")) == 0 && line[strlen("KEY")] == '=') { // Якщо знайдено рядок з ключем KEY
            found = 1; // Встановлюємо змінну found у 1
        }
        else if (strncmp(line, "login", strlen("login")) == 0 && line[strlen("login")] == '=') { // Якщо знайдено рядок з ключем login
            char* login = line + strlen("login") + 1; // Отримуємо значення ключа login
            login[strcspn(login, "\n")] = 0; // Видалення символу нового рядка з кінця рядка
            if (strcmp(login, "admin") == 0) { // Якщо значення ключа login дорівнює "admin"
                isAdmin = 1; // Встановлюємо змінну isAdmin у 1
            }
        }
    }
    fclose(file); // Закриваємо файл після читання

    int choice; // Змінна для збереження вибору користувача

    while (1) { // Початок безкінечного циклу меню програми
        printf("1. Додати оголошення\n"); // Виводимо пункти меню
        printf("2. Видалити оголошення\n");
        printf("3. Переглянути оголошення\n");
        printf("4. Оновити оголошення\n");
        printf("5. Зберегти базу даних\n");
        printf("6. Завантажити базу даних\n");
        printf("7. Експортувати базу даних\n");
        printf("8. Оновити конфігурацію\n");
        if (found) { // Якщо ліцензійний ключ знайдено у файлі конфігурації
            printf("9. Переглянути оголошення за містом\n");
            printf("10. Переглянути оголошення за ціною\n");
            printf("11. Надрукувати опис даних\n"); // новий пункт меню
            if (isAdmin) {
                printf("12. Вихід\n"); // оновлений пункт меню
                printf("13. Згенерувати новий ліцензійний ключ\n"); // новий пункт меню для адміністратора
            }
            else {
                printf("12. Вихід\n"); // оновлений пункт меню
            }
        }
        else {
            printf("\nЛіцензійний ключ не знайдено або недійсний. Деякі функції недоступні.\n");
            if (isAdmin) {
                printf("\n11. Згенерувати новий ліцензійний ключ\n"); // новий пункт меню для адміністратора
                printf("12. Вихід\n"); // оновлений пункт меню
            }
            else {
                printf("\n11. Надрукувати опис даних\n"); // новий пункт меню
                printf("12. Вихід\n"); // оновлений пункт меню
            }
        }

        printf("\n");
        printf("Введіть свій вибір:");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("\n");
            addAnnouncement();
            printf("\n");
            break;
        case 2: {
            int id;
            printf("\n");
            printf("Введіть ID для видалення: ");
            scanf("%d", &id);
            deleteAnnouncement(id);
            break;
        }
        case 3:
            viewAnnouncements();
            printf("\n");
            break;
        case 4: {
            int id;
            printf("\n");
            printf("Введіть ID для оновлення: ");
            scanf("%d", &id);
            updateAnnouncement(id);
            break;
        }
        case 5:

            if (!saveDatabase()) {
                printf("Сталася помилка при збереженні бази даних.\n");

            }
            break;
        case 6:
            loadDatabase();
            break;
        case 7:
            if (!exportDatabaseCSV()) {
                printf("Сталася помилка при експортуванні бази даних.\n");
            }
            break;
        case 8: {
            char key[50];
            char value[50];
            printf("\n");
            printf("Введіть ключ для оновлення: ");
            clearInputBuffer();
            fgets(key, sizeof(key), stdin);
            key[strcspn(key, "\n")] = 0;
            printf("Введіть значення: ");    
            fgets(value, sizeof(value), stdin);
            value[strcspn(value, "\n")] = 0;
            updateConfig(key, value);
            break;
        }
        case 9:
            if (found) {
                char city[50];
                printf("\n");
                printf("Введіть місто: ");
                clearInputBuffer();
                fgets(city, sizeof(city), stdin);
                // видалення символу нового рядка з кінця рядка
                city[strcspn(city, "\n")] = 0;
                viewAnnouncementsByCity(city);
            }
            else {
                printf("\nЛіцензійний ключ не знайдено або недійсний. Ця функція недоступна.\n");
            }
            break;
        case 10:
            if (found) {
                char price[50];
                printf("\n");
                printf("Введіть максимальну ціну: ");
                clearInputBuffer();
                fgets(price, sizeof(price), stdin);
                // видалення символу нового рядка з кінця рядка
                price[strcspn(price, "\n")] = 0;
                float maxPrice = atof(price);
                viewAnnouncementsByPrice(maxPrice);
            }
            else {
                printf("\nЛіцензійний ключ не знайдено або недійсний. Ця функція недоступна.\n");
            }
            break;
        case 11:
            printDataDescription();
            printf("\n");
            break;
        case 12:
            return 0;
        default:
            break;
        case 13:
            if (isAdmin) {
                char licenseKey[17];
                generateLicenseKey(licenseKey);
            }
            else {
                return 0;
            }
            break;

        }
    }
    return 0;
}
