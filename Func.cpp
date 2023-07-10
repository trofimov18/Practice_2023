/*
Файл: Func.cpp
Автор: Трофімов Дмитро Романович
Дата создания: 01.07.2023
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Header.h"

struct route* head = NULL;
struct route routes[MAX_RECORDS];
int count = 0;
void createEmptyDatabaseFile() {
    FILE* file;
    fopen_s(&file, "routes.dat", "wb");
    if (file != NULL) {
        fclose(file);
        printf("Створено пусту базу даних з іменем routes.dat.\n");
    }
    else {
        printf("Помилка при створенні файлу бази даних.\n");
    }
}
void generateLicenseKey(char* licenseKey) {
    srand(time(NULL));

    // Генерация случайного ключа состоящего из цифр
    for (int i = 0; i < 8; i++) {
        licenseKey[i] = '0' + rand() % 10;
    }
    licenseKey[8] = '\0';
}

void createConfigurationFile(const char* filename, const char* licenseKey) {
    FILE* file;
    fopen_s(&file, filename, "w");
    if (file != NULL) {
        fprintf(file, "# Ім’я файлу бази даних\n");
        fprintf(file, "database_file=routes.dat\n");
        fprintf(file, "# Ліцензійний ключ\n");
        fprintf(file, "license_key=%.*s\n", maxlandkey, licenseKey);
        fclose(file);
        printf("Створено конфігураційний файл: %s\n", filename);
    }
    else {
        printf("Помилка при створенні конфігураційного файлу: %s\n", filename);
    }
}


void readConfigurationFile(const char* filename, char* databaseFile, char* licenseKey) {
    FILE* file;
    fopen_s(&file, filename, "r");
    if (file != NULL) {
        char line[100];
        while (fgets(line, sizeof(line), file)) {
            // Ігноруємо рядки з коментарями
            if (line[0] != '#') {
                char* delimiter = strchr(line, '=');
                if (delimiter != NULL) {
                    char* key = strtok(line, "=");
                    char* value = strtok(NULL, "=");
                    if (strcmp(key, "database_file") == 0) {
                        strncpy(databaseFile, value, 100);
                        databaseFile[strcspn(databaseFile, "\n")] = '\0'; // Remove newline if present
                    }
                    else if (strcmp(key, "license_key") == 0) {
                        strncpy(licenseKey, value, maxlandkey + 1);
                        licenseKey[strcspn(licenseKey, "\n")] = '\0'; // Remove newline if present
                    }
                }
            }
        }
        fclose(file);
    }
}
void freeMemory() {
    struct route* current = head;
    while (current != NULL) {
        struct route* next = current->next;
        free(current);
        current = next;
    }
}
void addRoute(const char* Sp, const char* Ep, int routeLvl, int RouteNum) {
    struct route* newRoute = (struct route*)malloc(sizeof(struct route));
    if (newRoute != NULL) {
        strncpy(newRoute->Sp, Sp, 50);
        strncpy(newRoute->Ep, Ep, 50);
        newRoute->routeLvl = routeLvl;
        newRoute->RouteNum = RouteNum;
        newRoute->next = NULL;

        if (head == NULL) {
            head = newRoute;
        }
        else {
            struct route* current = head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newRoute;
        }

        routes[count] = *newRoute; // Добавлено для сохранения маршрута в массиве routes

        count++;
        printf("Маршрут успешно добавлен.\n");
    }
    else {
        printf("Ошибка при выделении памяти для нового маршрута.\n");
    }
}


void printAllRoutes() {
    for (int i = 0; i < count; i++) {
        printf("Маршрут %d:\n", i + 1);
        printf("Начальный пункт: %s\n", routes[i].Sp);
        printf("Конечный пункт: %s\n", routes[i].Ep);
        printf("Сложность: %d\n", routes[i].routeLvl);
        printf("Номер маршрута: %d\n", routes[i].RouteNum);
        printf("\n");
    }

}
void deleteRoute(int routeNum) {
    if (routeNum >= 1 && routeNum <= count) {
        struct route* current = head;
        struct route* previous = NULL;
        int i = 1;
        while (i < routeNum) {
            previous = current;
            current = current->next;
            i++;
        }

        if (previous == NULL) {
            head = current->next;
        }
        else {
            previous->next = current->next;
        }
        for (int i = routeNum - 1; i < count - 1; i++) {
            routes[i] = routes[i + 1];
        }

        free(current);
        count--;
        printf("Маршрут успішно видалений.\n");
    }
    else {
        printf("Некоректний номер маршруту.\n");
    }
}
void readLicenseKeyFromUser(char* userLicenseKey) {
    printf("Введите лицензионный ключ: ");
    scanf_s("%17s", userLicenseKey, maxlandkey + 1);
    userLicenseKey[strcspn(userLicenseKey, "\n")] = '\0'; // Удаление символа новой строки

    // Проверка на переполнение
    if (strlen(userLicenseKey) >= maxlandkey + 1) {
        printf("Ошибка: превышена длина лицензионного ключа.\n");
    }
}
void printRoutesByStartPoint(const char* startPoint) {
    int i = 0;
    int foundRoutes = 0;
    struct route* current = head;
    while (current != NULL) {
        if (strcmp(current->Sp, startPoint) == 0) {
            printf("Маршрут %d:\n", i + 1);
            printf("Начальный пункт: %s\n", current->Sp);
            printf("Конечный пункт: %s\n", current->Ep);
            printf("Сложность: %d\n", current->routeLvl);
            printf("Номер маршрута: %d\n", current->RouteNum);
            printf("\n");
            foundRoutes++;
        }
        current = current->next;
        i++;
    }

    if (foundRoutes == 0) {
        printf("Маршруты с заданным начальным пунктом не найдены.\n");
    }
}
void printRoutesByEndPointAndDifficulty(const char* endPoint, int minDifficulty, int maxDifficulty) {
    if (count > 0) {
        struct route* current = head;
        int routeCount = 1;  // Переменная для отслеживания номера текущего маршрута
        while (current != NULL) {
            if (strcmp(current->Ep, endPoint) == 0 && current->routeLvl >= minDifficulty && current->routeLvl <= maxDifficulty) {
                printf("Маршрут %d:\n", current->RouteNum);  // Выводим номер маршрута, а не порядковый номер
                printf("Начальный пункт: %s\n", current->Sp);
                printf("Конечный пункт: %s\n", current->Ep);
                printf("Сложность: %d\n", current->routeLvl);
                printf("Номер маршрута: %d\n", current->RouteNum);
                printf("\n");
                routeCount++;
            }
            current = current->next;
        }
        if (routeCount == 1) {
            printf("Маршруты с заданным конечным пунктом и диапазоном сложности не найдены.\n");
        }
    }
    else {
        printf("База данных пуста.\n");
    }
}


