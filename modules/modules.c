#include "..\FNCTS\FNCTS.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define scanf scanf_s

#define CONFIG_FILE "RGR.cfg"

// Функція для генерації унікального ідентифікатора
int generateUniqueId() {
    static int id = 0; // Статична змінна для збереження останнього використаного ідентифікатора
    if (id >= 999) { // Перевірка чи досягнуто максимальної кількості оголошень
        printf("Помилка: досягнуто максимальної кількості оголошень.\n");
        return -1; // Повертаємо -1 у випадку помилки
    }
    id++; // Збільшуємо ідентифікатор на 1

    int randId = rand() % 1000; // Генеруємо випадковий ідентифікатор
    printf("Випадковий ID: %d\n", randId);
    printf("Послідовний порядковий номер: %d\n", id);

    return randId; // Повертаємо випадковий ідентифікатор
}

// Функція для очищення буфера вводу
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Читаємо символи з буфера доки не зустрінемо символ нового рядка або кінець файлу
}

// Структура для збереження інформації про оголошення
typedef struct {
    int id; // Ідентифікатор оголошення
    char title[50]; // Заголовок оголошення
    float price; // Ціна оголошення
    char city[50]; // Місто оголошення
    char phone[20]; // Номер телефону для зв'язку
} Announcement;

// Структура для збереження вузлів списку оголошень
typedef struct Node {
    Announcement data; // Дані про оголошення
    struct Node* next; // Вказівник на наступний вузол у списку
} Node;
Node* head = NULL; // Вказівник на голову списку

// Функція для додавання нового оголошення до списку
void addAnnouncement() {
    Announcement data; // Створюємо нове оголошення
    data.id = generateUniqueId(); // Генеруємо унікальний ідентифікатор для оголошення
    printf("\n");
    printf("Введіть назву: ");
    clearInputBuffer(); // Очищуємо буфер вводу перед читанням даних
    fgets(data.title, sizeof(data.title), stdin); // Читаємо назву оголошення з консолі
    // видалення символу нового рядка з кінця рядка
    data.title[strcspn(data.title, "\n")] = 0;
    printf("\n");
    printf("Введіть ціну: ");
    scanf("%f", &data.price); // Читаємо ціну оголошення з консолі
    clearInputBuffer(); // Очищуємо буфер вводу перед читанням даних
    printf("\n");
    printf("Введіть місто: ");
    fgets(data.city, sizeof(data.city), stdin); // Читаємо місто оголошення з консолі
    // видалення символу нового рядка з кінця рядка
    data.city[strcspn(data.city, "\n")] = 0;
    printf("\n");
    printf("Введіть телефон: ");
    fgets(data.phone, sizeof(data.phone), stdin); // Читаємо номер телефону з консолі
    // видалення символу нового рядка з кінця рядка
    data.phone[strcspn(data.phone, "\n")] = 0;

    Node* newNode = (Node*)malloc(sizeof(Node)); // Створюємо новий вузол для списку
    newNode->data = data; // Збереження даних про оголошення у вузлі
    newNode->next = NULL; // Встановлення наступного вузла як NULL

    if (head == NULL) { // Якщо список порожній
        head = newNode; // Встановлюємо новий вузол як голову списку
        return;
    }

    Node* temp = head; // Починаємо пошук з голови списку
    while (temp->next != NULL) { // Продовжуємо пошук доки не дійдемо до кінця списку
        temp = temp->next;
    }
    temp->next = newNode; // Додаємо новий вузол до кінця списку
}
//1

// Функція для видалення оголошення зі списку за ідентифікатором
void deleteAnnouncement(int id) {
    if (head == NULL) { // Якщо список порожній
        printf("\n");
        printf("Оголошення не знайдено.\n"); // Виводимо повідомлення про помилку
        printf("\n");
        return;
    }

    if (head->data.id == id) { // Якщо ідентифікатор співпадає з ідентифікатором голови списку
        Node* temp = head; // Збереження вказівника на голову списку
        head = head->next; // Зміна голови списку на наступний вузол
        free(temp); // Звільнення пам'яті виділеної для вузла
        printf("\n");
        printf("Оголошення видалено.\n"); // Виводимо повідомлення про успішне видалення
        printf("\n");
        return;
    }

    Node* temp = head; // Починаємо пошук з голови списку
    while (temp->next != NULL && temp->next->data.id != id) { // Продовжуємо пошук доки не дійдемо до кінця списку або не знайдемо вузол з потрібним ідентифікатором
        temp = temp->next;
    }

    if (temp->next == NULL) { // Якщо досягли кінця списку і не знайшли потрібний вузол
        printf("\n");
        printf("Оголошення не знайдено.\n"); // Виводимо повідомлення про помилку
        printf("\n");
        return;
    }

    Node* nodeToDelete = temp->next; // Збереження вказівника на вузол для видалення
    temp->next = nodeToDelete->next; // Зміна наступного вузла у поточного вузла на наступний вузол після того, що буде видалено
    free(nodeToDelete); // Звільнення пам'яті виділеної для вузла
    printf("Оголошення видалено.\n"); // Виводимо повідомлення про успішне видалення
    printf("\n");
}
//2


// Функція для перегляду всіх оголошень у списку
void viewAnnouncements() {
    if (head == NULL) { // Якщо список порожній
        printf("Оголошення не знайдено.\n"); // Виводимо повідомлення про помилку
        return;
    }

    Node* temp = head; // Починаємо перегляд з голови списку
    while (temp != NULL) { // Продовжуємо перегляд доки не дійдемо до кінця списку
        printf("ID: %d\n", temp->data.id); // Виводимо інформацію про оголошення
        printf("Назва: %s\n", temp->data.title);
        printf("Ціна: %.2f\n", temp->data.price);
        printf("Місто: %s\n", temp->data.city);
        printf("Телефон: %s\n", temp->data.phone);
        printf("\n");
        temp = temp->next; // Переходимо до наступного вузла у списку
    }
}
//3

// Функція для оновлення інформації про оголошення за ідентифікатором
void updateAnnouncement(int id) {
    if (head == NULL) { // Якщо список порожній
        printf("Оголошення не знайдено.\n"); // Виводимо повідомлення про помилку
        return;
    }

    Node* temp = head; // Починаємо пошук з голови списку
    while (temp != NULL && temp->data.id != id) { // Продовжуємо пошук доки не дійдемо до кінця списку або не знайдемо вузол з потрібним ідентифікатором
        temp = temp->next;
    }

    if (temp == NULL) { // Якщо досягли кінця списку і не знайшли потрібний вузол
        printf("Оголошення не знайдено.\n"); // Виводимо повідомлення про помилку
        return;
    }

    printf("Виберіть опцію:\n"); // Виводимо меню для вибору опції оновлення
    printf("1. Змінити назву\n");
    printf("2. Змінити ціну\n");
    printf("3. Змінити місто\n");
    printf("4. Змінити телефон\n");
    printf("5. Скасувати\n");
    printf("\n");

    clearInputBuffer(); // Очищуємо буфер вводу перед читанням даних
    char choice[10];
    fgets(choice, sizeof(choice), stdin); // Читаємо вибір користувача з консолі
    int choiceInt = atoi(choice); // Перетворюємо рядок у число

    switch (choiceInt) { // Обробка вибору користувача
    case 1: // Зміна назви оголошення
        printf("\n");
        printf("Введіть нову назву: ");
        char title[50];

        fgets(title, sizeof(title), stdin); // Читаємо нову назву з консолі
        title[strcspn(title, "\n")] = 0; // Видалення символу нового рядка з кінця рядка
        strcpy(temp->data.title, title); // Збереження нової назви у вузлі списку
        break;
    case 2: // Зміна ціни оголошення
        printf("\n");
        printf("Введіть нову ціну: ");
        char price[50];

        fgets(price, sizeof(price), stdin); // Читаємо нову ціну з консолі
        temp->data.price = atof(price); // Збереження нової цени у вузлі списку
        break;
    case 3: // Зміна міста оголошення
        printf("\n");
        printf("Введіть нове місто: ");
        char city[50];

        fgets(city, sizeof(city), stdin); // Читаємо нове місто з консолі
        city[strcspn(city, "\n")] = 0; // Видалення символу нового рядка з кінця рядка
        strcpy(temp->data.city, city); // Збереження нового міста у вузлі списку
        break;
    case 4: // Зміна номера телефону оголошення
        printf("\n");
        printf("Введіть новий телефон: ");
        char phone[20];

        fgets(phone, sizeof(phone), stdin); // Читаємо новий номер телефону з консолі
        phone[strcspn(phone, "\n")] = 0; // Видалення символу нового рядка з кінця рядка
        strcpy(temp->data.phone, phone); // Збереження нового номера телефону у вузлі списку
        break;
    case 5: // Скасування оновлення
        return;
        break;
    case 6:
        printf("\n");
        printf("Неправильний вибір.\n"); // Виводимо повідомлення про помилку у випадку неправильного вибору користувачем
        printf("\n");
        return;
        break;
    }
    printf("\n");
    printf("Оголошення оновлено.\n"); // Виводимо повідомлення про успышне оновлення інформацыї про оголошення
    printf("\n");
}
//4

// Функція для збереження бази даних у файл
int saveDatabase() {
    char filename[50];
    printf("Введіть ім'я файлу для збереження:\n ");

    clearInputBuffer(); // Очищуємо буфер вводу перед читанням даних
    fgets(filename, sizeof(filename), stdin); // Читаємо ім'я файлу з консолі
    // видалення символу нового рядка з кінця рядка
    filename[strcspn(filename, "\n")] = 0;
    printf("\n");
    FILE* file = fopen(filename, "wb"); // Відкриваємо файл для запису у двійковому режимі
    if (file == NULL) { // Якщо не вдалося відкрити файл
        printf("Помилка відкриття файлу.\n"); // Виводимо повідомлення про помилку
        return 0; // Повертаємо 0 у випадку помилки
    }

    Node* temp = head; // Починаємо запис з голови списку
    while (temp != NULL) { // Продовжуємо запис доки не дійдемо до кінця списку
        fwrite(&temp->data, sizeof(Announcement), 1, file); // Записуємо дані про оголошення у файл
        temp = temp->next; // Переходимо до наступного вузла у списку
    }

    fclose(file); // Закриваємо файл після запису
    return 1; // Повертаємо 1 у випадку успішного запису
}//5

// Функція для завантаження бази даних з файлу
void loadDatabase() {
    char filename[50];
    printf("Введіть ім'я файлу для завантаження: ");
    clearInputBuffer(); // Очищуємо буфер вводу перед читанням даних
    fgets(filename, sizeof(filename), stdin); // Читаємо ім'я файлу з консолі
    // видалення символу нового рядка з кінця рядка
    filename[strcspn(filename, "\n")] = 0;

    FILE* file = fopen(filename, "rb"); // Відкриваємо файл для читання у двійковому режимі
    if (file == NULL) { // Якщо не вдалося відкрити файл
        printf("Помилка відкриття файлу.\n"); // Виводимо повідомлення про помилку
        return;
    }

    // звільнення будь-яких існуючих даних у зв'язному списку
    Node* temp = head;
    while (temp != NULL) { // Продовжуємо звільнення доки не дійдемо до кінця списку
        Node* next = temp->next;
        free(temp); // Звільнення пам'яті виділеної для вузла
        temp = next;
    }
    head = NULL; // Встановлюємо голову списку як NULL

    Announcement data;
    while (fread(&data, sizeof(Announcement), 1, file) == 1) { // Читаємо дані про оголошення з файлу доки не дійдемо до кінця файлу
        Node* newNode = (Node*)malloc(sizeof(Node)); // Створюємо новий вузол для списку
        newNode->data = data; // Збереження даних про оголошення у вузлі
        newNode->next = NULL;

        if (head == NULL) { // Якщо список порожній
            head = newNode; // Встановлюємо новий вузол як голову списку
        }
        else {
            Node* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
    fclose(file);
}
//6


// Функція для експорту бази даних у файл у форматі CSV
int exportDatabaseCSV() {
    char filename[50];
    printf("Введіть ім'я файлу для експорту: ");
    clearInputBuffer(); // Очищуємо буфер вводу перед читанням даних
    fgets(filename, sizeof(filename), stdin); // Читаємо ім'я файлу з консолі
    // видалення символу нового рядка з кінця рядка
    filename[strcspn(filename, "\n")] = 0;

    FILE* file = fopen(filename, "w"); // Відкриваємо файл для запису у текстовому режимі
    if (file == NULL) { // Якщо не вдалося відкрити файл
        printf("Помилка відкриття файлу.\n"); // Виводимо повідомлення про помилку
        return 0; // Повертаємо 0 у випадку помилки
    }

    // Додати рядок заголовка
    fprintf(file, "ID;Назва;Ціна;Місто;Телефон\n");

    Node* temp = head; // Починаємо запис з голови списку
    while (temp != NULL) { // Продовжуємо запис доки не дійдемо до кінця списку
        fprintf(file, "%d;%s;%.2f;%s;%s\n", temp->data.id, temp->data.title, temp->data.price, temp->data.city, temp->data.phone); // Записуємо дані про оголошення у файл у форматі CSV
        temp = temp->next; // Переходимо до наступного вузла у списку
    }

    fclose(file); // Закриваємо файл після запису
    return 1; // Повертаємо 1 у випадку успішного запису
}



//7

// Функція для оновлення налаштувань у файлі конфігурації
void updateConfig(char* key, char* value) {
    printf("Результат оновлення: ключ: %s, значення: %s\n", key, value); // Виводимо інформацію про оновлення
    FILE* file = fopen(CONFIG_FILE, "r"); // Відкриваємо файл конфігурації для читання
    if (file == NULL) { // Якщо не вдалося відкрити файл
        printf("Помилка відкриття файлу.\n"); // Виводимо повідомлення про помилку
        return;
    }

    char line[100];
    int found = 0; // Змінна для збереження інформації про те, чи знайдено ключ у файлі
    char buffer[1000] = ""; // Буфер для збереження нового вмісту файлу
    while (fgets(line, sizeof(line), file)) { // Читаємо рядки з файлу доки не дійдемо до кінця файлу
        if (strncmp(line, key, strlen(key)) == 0 && line[strlen(key)] == '=') { // Якщо знайдено рядок з потрібним ключем
            found = 1; // Встановлюємо змінну found у 1
            sprintf(buffer + strlen(buffer), "%s=%s\n", key, value); // Додаємо новий рядок з оновленим значенням до буфера
        }
        else {
            sprintf(buffer + strlen(buffer), "%s", line); // Додаємо рядок без змін до буфера
        }
    }

    if (!found) { // Якщо ключ не знайдено у файлі
        sprintf(buffer + strlen(buffer), "%s=%s\n", key, value); // Додаємо новий рядок з ключем та значенням до буфера
    }

    fclose(file); // Закриваємо файл після читання

    file = fopen(CONFIG_FILE, "w"); // Відкриваємо файл конфігурації для запису
    if (file == NULL) { // Якщо не вдалося відкрити файл
        printf("Помилка відкриття файлу.\n"); // Виводимо повідомлення про помилку
        return;
    }
    fprintf(file, "%s", buffer); // Записуємо новий вміст файлу з буфера
    fclose(file); // Закриваємо файл після запису
}
//8

// Функція для перегляду оголошень у списку за містом
void viewAnnouncementsByCity(char* city) {
    if (head == NULL) { // Якщо список порожній
        printf("Оголошення не знайдено.\n"); // Виводимо повідомлення про помилку
        return;
    }

    Node* temp = head; // Починаємо перегляд з голови списку
    while (temp != NULL) { // Продовжуємо перегляд доки не дійдемо до кінця списку
        if (strcmp(temp->data.city, city) == 0) { // Якщо місто оголошення співпадає з заданим містом
            printf("ID: %d\n", temp->data.id); // Виводимо інформацію про оголошення
            printf("Назва: %s\n", temp->data.title);
            printf("Ціна: %.2f\n", temp->data.price);
            printf("Місто: %s\n", temp->data.city);
            printf("Телефон: %s\n", temp->data.phone);
            printf("\n");
        }
        temp = temp->next; // Переходимо до наступного вузла у списку
    }
}//9

// Функція для перегляду оголошень у списку за максимальною ціною
void viewAnnouncementsByPrice(float maxPrice) {
    if (head == NULL) { // Якщо список порожній
        printf("Оголошення не знайдено.\n"); // Виводимо повідомлення про помилку
        return;
    }

    Node* temp = head; // Починаємо перегляд з голови списку
    while (temp != NULL) { // Продовжуємо перегляд доки не дійдемо до кінця списку
        if (temp->data.price <= maxPrice) { // Якщо ціна оголошення менша або рівна заданій максимальній ціні
            printf("ID: %d\n", temp->data.id); // Виводимо інформацію про оголошення
            printf("Назва: %s\n", temp->data.title);
            printf("Ціна: %.2f\n", temp->data.price);
            printf("Місто: %s\n", temp->data.city);
            printf("Телефон: %s\n", temp->data.phone);
            printf("\n");
        }
        temp = temp->next; // Переходимо до наступного вузла у списку
    }
}
//10

// Функція для виводу опису даних про оголошення
void printDataDescription() {
    printf("Інформація про оголошення:\n"); // Виводимо заголовок
    printf("- ID оголошення (ціле число)\n"); // Виводимо інформацію про кожне поле структури
    printf("- Назва (рядок)\n");
    printf("- Ціна (число з плаваючою комою)\n");
    printf("- Місто (рядок)\n");
    printf("- Телефон (рядок)\n");
}//11

// Функція для генерації ліцензійного ключа
void generateLicenseKey(char* licenseKey) {
    const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; // Набір символів для генерації ключа
    srand(time(NULL)); // Ініціалізація генератора випадкових чисел
    for (int i = 0; i < 16; i++) { // Генерація 16 символів ключа
        licenseKey[i] = charset[rand() % (sizeof(charset) - 1)]; // Вибираємо випадковий символ з набору символів
    }
    licenseKey[16] = '\0'; // Додаємо символ кінця рядка до ключа

    updateConfig("KEY", licenseKey); // Оновлюємо значення ключа у файлі конфігурації
}


int createConfigFile() {
    // Отримання імені виконуваного файлу
    char* executableName = "RGR";

    // Формування імені конфігураційного файлу
    char configFileName[256];
    sprintf(configFileName, "%s.cfg", executableName);

    // Перевірка наявності конфігураційного файлу
    FILE* configFile = fopen(configFileName, "r");
    if (configFile != NULL) {
        fclose(configFile);
        return 0; // Конфігураційний файл вже існує
    }

    // Створення нового конфігураційного файлу
    configFile = fopen(configFileName, "w");
    if (configFile == NULL) {
        return 2; // Помилка створення конфігураційного файлу
    }

    // Запис інформації в конфігураційний файл
    fprintf(configFile, "; Файл бази даних\n");
    fprintf(configFile, "DB = mybd.dat\n");
    fprintf(configFile, "; Ліцензійний ключ\n");
    char licenseKey[17];
    generateLicenseKey(licenseKey);
    fprintf(configFile, "KEY=%s\n", licenseKey);

    fprintf(configFile, "; Логин\n");
    fprintf(configFile, "login=\n");

    fclose(configFile);
    return 1; // Конфігураційний файл успішно створений
}