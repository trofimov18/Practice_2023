/*
Файл: MainPract.cpp
Автор: Трофімов Дмитро Романович
Дата создания: 01.07.2023
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Header.h"

#define MAX_RECORDS 100
int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "rus");
    int specialAccess = 0;
    // Визначення імені конфігураційного файлу
    char configFileName[100];
    strncpy(configFileName, argv[0], 100);
    char* dot = strchr(configFileName, '.');
    if (dot != NULL) {
        strncpy(dot, ".cfg", 5);
    }
    else {
        strncat(configFileName, ".cfg", 5);
    }

    // Читання конфігураційного файлу
    char databaseFile[100] = "routes.dat";
    char licenseKey[maxlandkey + 1];
    generateLicenseKey(licenseKey);

    readConfigurationFile(configFileName, databaseFile, licenseKey);

    // Перевірка наявності бази даних
    FILE* database;
    fopen_s(&database, databaseFile, "rb");
    if (database == NULL) {
        createEmptyDatabaseFile();
        createConfigurationFile(configFileName, licenseKey);
    }
    else {
        fclose(database);
    }

    // Перевірка наявності ліцензійного ключа
    if (strlen(licenseKey) == 0 || strcmp(licenseKey, "") == 0) {
        printf("Лицензионный ключ отсутствует, или же не корректный. \n");
        return 0;
    }
    char userLicenseKey[maxlandkey + 1];
    readLicenseKeyFromUser(userLicenseKey);

    // Перевірка совпадіння лицензійних ключів
    if (strcmp(licenseKey, userLicenseKey) == 0) {
        printf("Лицензионный ключ принят. Получен доступ к специальным функциям.\n");
        specialAccess = 1;
    }
    else {
        printf("Неверный лицензионный ключ. Доступ к специальным функциям ограничен.\n");
    }
    int choice;
    printf("_____ Меню действий _____    \n");
    printf("( 1 ) Добавить маршрут \n");
    printf("( 2 ) Удалить маршрут \n");
    printf("( 3 ) Просмотреть все маршруты \n");
    printf("( 4 ) Изменить данные маршрута\n");
    printf("( 5 ) Сохранить маршруты в файл \n");
    printf("( 6 ) Выход \n");
    printf("Доп. Функции (необходим лицензионный ключ): \n");
    printf("( 7 ) Вывод всех маршрутов по заданному начальному пункту \n");
    printf("( 8 ) Вывод всех маршрутов по заданному конечному пункту и диапазону сложности \n");

    do {
        printf("Выберете действие: ");
        scanf_s("%d", &choice);
        switch (choice) {
        case 1: {
            printf("Введите данные нового маршрута:\n");
            char Sp[50], Ep[50];
            int routeLvl, RouteNum;
            struct route newRoute = { "", "", 0, 0 };
            printf("Введите начальный пункт маршрута: ");
            scanf("%s", newRoute.Sp);
            printf("Введите конечный пункт маршрута: ");
            scanf("%s", newRoute.Ep);
            printf("Введите уровень сложности маршрута: ");
            scanf("%d", &newRoute.routeLvl);
            printf("Введите номер маршрута: ");
            scanf("%d", &newRoute.RouteNum);
            addRoute(newRoute.Sp, newRoute.Ep, newRoute.routeLvl, newRoute.RouteNum);
            break;
        }
        case 2: {
            printf("Введите номер маршрута, который необходимо удалить: ");
            int routeNum;
            scanf_s("%d", &routeNum);
            deleteRoute(routeNum);
        }
              break;
        case 3: {
            printAllRoutes();
            break;
        }
        case 4: {
            int routeNum;
            int ch;
            printf("Введите номер маршрута для изменения данных: \n");
            scanf("%d", &routeNum);
            getchar();

            if (routeNum >= 1 && routeNum <= count) {
                struct route* object = &routes[routeNum - 1];
                printf("Укажите параметр, который хотите изменить: \n");
                printf("( 1 ) Изменить начальный пункт маршрута \n");
                printf("( 2 ) Изменить конечный пункт маршрута \n");
                printf("( 3 ) Изменить сложность маршрута \n");
                printf("( 4 ) Изменить номер маршрута \n");
                scanf("%d", &ch);
                getchar();

                switch (ch) {
                case 1: {
                    printf("Введите новый начальный пункт маршрута: \n");
                    fgets(object->Sp, sizeof(object->Sp), stdin);
                    object->Sp[strcspn(object->Sp, "\n")] = '\0';
                    printf("Данные маршрута успешно изменены.\n");
                    break;
                }
                case 2: {
                    printf("Введите новый конечный пункт маршрута: \n");
                    fgets(object->Ep, sizeof(object->Ep), stdin);
                    object->Ep[strcspn(object->Ep, "\n")] = '\0';
                    printf("Данные маршрута успешно изменены.\n");
                    break;
                }
                case 3: {
                    printf("Укажите новую сложность маршрута от 1 до 10: \n");
                    scanf("%d", &object->routeLvl);
                    getchar();
                    printf("Данные маршрута успешно изменены.\n");
                    break;
                }
                case 4: {
                    printf("Введите новый номер данному маршруту: \n");
                    scanf("%d", &object->RouteNum);
                    getchar();
                    printf("Данные маршрута успешно изменены.\n");
                    break;
                }
                }

                // Обновление данных маршрута в связанном списке
                struct route* current = head;
                int i = 1;
                while (current != NULL) {
                    if (i == routeNum) {
                        strncpy(current->Sp, object->Sp, 50);
                        strncpy(current->Ep, object->Ep, 50);
                        current->routeLvl = object->routeLvl;
                        current->RouteNum = object->RouteNum;
                        break;
                    }
                    current = current->next;
                    i++;
                }

                // Обновление данных маршрута в массиве routes[]
                routes[routeNum - 1] = *object;
            }
            else {
                printf("Некорректный номер маршрута.\n");
            }
        }
              break;
        case 5: {
            FILE* file;
            fopen_s(&file, "routes.dat", "wb");
            if (file != NULL) {
                for (int i = 0; i < count; i++) {
                    fprintf(file, "Маршрут %d:\n", i + 1);
                    fprintf(file, "Начальный пункт: %s\n", routes[i].Sp);
                    fprintf(file, "Конечный пункт: %s\n", routes[i].Ep);
                    fprintf(file, "Сложность: %d\n", routes[i].routeLvl);
                    fprintf(file, "Номер маршрута: %d\n", routes[i].RouteNum);
                    fprintf(file, "\n");
                }
                fclose(file);
                printf("Маршруты успешно сохранены в файл.\n");
            }
            else {
                printf("Ошибка при открытии файла для сохранения маршрутов.\n");
            }
        }
              break;
        case 6:
            printf("Программа успешно закрыта. \n");
            break;
        case 7: {
            if (specialAccess == 1) {
                char startPoint[50];
                printf("Введите начальный пункт для поиска маршрутов: ");
                scanf("%s", startPoint);
                printRoutesByStartPoint(startPoint);

            }
            else {
                printf("У вас нет доступа к данной функции, так как лицензионный ключ не был предоставлен, пожалуста, перезапустите программу и введите лицензионный ключ для доступа к данной функции. \n");
            }
        }break;
        case 8: {
            if (specialAccess == 1) {
                char endPoint[50];
                int minDifficulty, maxDifficulty;
                printf("Введите конечный пункт для поиска маршрутов: ");
                scanf("%s", endPoint);
                printf("Введите минимальную сложность маршрутов: ");
                scanf("%d", &minDifficulty);
                printf("Введите максимальную сложность маршрутов: ");
                scanf("%d", &maxDifficulty);
                printRoutesByEndPointAndDifficulty(endPoint, minDifficulty, maxDifficulty);
            }
            else {
                printf("У вас нет доступа к данной функции, так как лицензионный ключ не был предоставлен, пожалуста, перезапустите программу и введите лицензионный ключ для доступа к данной функции. \n");
            }
        }break;

        default:
            printf("Неверный ввод. Попробуйте снова.\n");
        }
    } while (choice != 6);

    freeMemory();
    return 0;
}
