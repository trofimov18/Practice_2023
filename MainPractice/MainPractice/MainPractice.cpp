#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "Functions.h"

int main() {
    setlocale(LC_ALL, "Ukr");
    int choice;
    openFile(); // Зчитування даних з файлу

    while (1) {
        printf("\n");
        printf("Функції керування базою даних рейсів\n");
        printf("-------------------------------------\n");
        printf("1. Додати рейс\n");
        printf("2. Видалити рейс\n");
        printf("3. Показати рейси\n");
        printf("4. Редагувати рейс\n");
        printf("5. Пошук рейсів за пунктом призначення\n");
        printf("6. Пошук рейсів за типом літака\n");
        printf("0. Вихід\n");
        printf("-------------------------------------\n");
        printf("Введіть номер команди: ");
        scanf("%d", &choice);

        switch (choice) {
        case 0:
            printf("Вихід з програми...\n");
            exit(0);
        case 1:
            addFlight();
            break;
        case 2:
            deleteFlight();
            break;
        case 3:
            displayFlights();
            break;
        case 4:
            modifyFlight();
            break;
        case 5:
            searchByDestination();
            break;
        case 6:
            searchByAircraftType();
            break;
        default:
            printf("Неправильні введені дані. Введіть номер з запропонованих команд.\n");
            break;
        }
    }

    return 0;
}