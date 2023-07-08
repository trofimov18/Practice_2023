#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "contacts.h"

#define MAX_ACCESS_KEY_LENGTH 50

int main() {
    setlocale(LC_ALL, "Ukr");
    char accessKey[MAX_ACCESS_KEY_LENGTH];

    getAccessKey(accessKey);

    // Перевірка ключа доступу
    if (!checkAccessKey(accessKey, "access_key.txt")) {
        printf("Невiрний ключ доступу. Програма завершується.\n");
        return 0;
    }
    Contact* contacts = NULL;
    int numContacts = 0;
    int choice;

    do {
        printf("Меню:\n");
        printf("1. Додати контакт\n");
        printf("2. Видалити контакт\n");
        printf("3. Вивести всi контакти\n");
        printf("4. Редагувати контакт\n");
        printf("5. Вивести контакти з месенджером\n");
        printf("6. Вивести контакти, що починаються з пiдрядка\n");
        printf("7. Зберегти контакти у файл(та вийти)\n");
        printf("8. Завантажити контакти з файлу\n");
        printf("Ваш вибiр: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addContact(&contacts, &numContacts);
            break;
        case 2: {
            int index;
            printf("Введіть iндекс контакту для видалення: ");
            scanf("%d", &index);
            deleteContact(&contacts, &numContacts, index);
            break;
        }
        case 3:
            displayContacts(contacts, numContacts);
            break;
        case 4: {
            int index;
            printf("Введiть iндекс контакту для редагування: ");
            scanf("%d", &index);
            editContact(contacts, numContacts, index);
            break;
        }
        case 5:
            displayContactsByMessenger(contacts, numContacts);
            break;
        case 6: {
            char substring[50];
            printf("Введiть підрядок: ");
            scanf("%s", substring);
            displayContactsBySubstring(contacts, numContacts, substring);
            break;
        }
        case 7: {
            char filename[50];
            printf("Введiть назву файлу для збереження: ");
            scanf("%s", filename);
            saveContactsToFile(contacts, numContacts, filename);
            printf("До побачення");
            break;
        }
        case 8: {
            char filename[50];
            printf("Введiть назву файлу для завантаження: ");
            scanf("%s", filename);
            loadContactsFromFile(&contacts, &numContacts, filename);
            break;
        }
        default:
            printf("Невiрний вибiр. Спробуйте ще раз.\n");
            break;
        }
    } while (choice != 7);

    return 0;
}