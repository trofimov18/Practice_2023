/**
* @file Practice2023.cpp
* @author Приліпко, гр. 515-i, варіант 11
* @date 3 липня 2023
* @brief Практика
*
* База даних студентів
*/

#include "infopractice.h"
#include <locale.h>


int main() {

    setlocale(LC_CTYPE, "ukr");
   
    char dbFilename[MAX_FILENAME_LENGTH];
    char licenseKey[KEY_LENGTH];
    char currentNameFile[MAX_FILENAME_LENGTH];
    printf("Введіть назву файлу: Приклад 'data.txt' -  ");
    fgets(currentNameFile, MAX_FILENAME_LENGTH, stdin);
    currentNameFile[strcspn(currentNameFile, "\n")] = '\0';



    // Зчитування конфігураційного файлу
    FILE* configFile = fopen("infopractice.cfg", "r");
    if (configFile == NULL) {
        // Конфігураційний файл відсутній, створюємо його та пусту базу даних

        printf("Створено конфігураційний файл та пусту базу даних.\n");
        generation_key();
        strcpy(dbFilename, "new_base.dat");
    }

    else {
        // Зчитування імені бази даних та ліцензійного ключа з конфігураційного файлу
        char line[100];
        while (fgets(line, sizeof(line), configFile) != NULL) {
            if (strstr(line, "DB") != NULL) {
                sscanf(line, "DB = %s", dbFilename);
            }
            else if (strstr(line, "KEY") != NULL) {
                sscanf(line, "KEY = %s", licenseKey);
            }
        }
        fclose(configFile);
    }
start:
    // Перевірка ліцензійного ключа
    if (is_valid_key() == true) {
        printf("Некоректний ліцензійний ключ. Деякі функції можуть бути недоступні.\n");
        printf("Доступні дії з даними"
            "\n1. Для додавання запису введіть - input"
            "\n2. Для видалення запису введіть - delete"
            "\n3. Для пепегляду записів введіть - print"
            "\n4. Для змінювання запису введіть - change"
            "\n5. Для завершення програми введіть - exit"
            "\n Оберіть дію - ");
        while (1) {
            switch (menu()) {
            case 1:
                input(currentNameFile);

                break;
            case 2:
                delet(currentNameFile);
                goto start;
                break;
            case 3:
                print(currentNameFile);
                goto start;
                break;
            case 4:
                change(currentNameFile);
                goto start;
                break;
            case 0:
                printf("THE END");
                return 0;
            }
        }

    }

    else {
        printf("Доступні дії з даними"
            "\n1. Для додавання запису, введіть - input"
            "\n2. Для видалення запису, введіть - delete"
            "\n3. Для перегляду записів, введіть - print"
            "\n4. Для змінювання запису, введіть - change"
            "\n5. Для пошуку за постачальником, введіть - search"
            "\n6. Для пошуку товару за ціною,введіть - price"
            "\n7. Для налаштування файлу, введіть - settings "
            "\n8. Для завершення програми введіть - exit"
            "\n Оберіть дію - ");
        while (1) {
            switch (menu()) {
            case 1:
                input(currentNameFile);
                goto start;
                break;
            case 2:
                delet(currentNameFile);
                goto start;
                break;
            case 3:
                print(currentNameFile);
                goto start;
                break;
            case 4:
                change(currentNameFile);
                goto start;
                break;
            case 5:
                search_by_supplier(currentNameFile);
                goto start;
                break;
            case 6:
                low_prices(currentNameFile);
                goto start;
                break;
            case 7:
                printf("Налаштування:"
                    "\n Для замінення назви файлу, введіть - name "
                    "\n Для експорту у файл csv, введіть - csv "
                    "\n Оберіть дію - ");
                switch (menu_settings()) {
                case 1:
                    printf("Після зміни назви файлу програма завершить роботу.\n");
                    file_change_name(currentNameFile);
                    printf("Назву файла успішно змінено. \n");
                    return 0;
                    break;
                case 2:
                    exportCSV(currentNameFile);
                    goto start;
                    break;

                default:
                    printf("\nНе вірна операція. Повернення на головну сторінку.\n");
                    goto start;
                    break;
                }

                break;

            case 0:
                printf("Кінець.");
                return 0;
            }
        }
    }
    return 0;
}
