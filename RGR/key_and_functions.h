#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <cstdlib>
#include <windows.h>
#include <time.h>

#define _CRT_SECURE_NO_WARNINGS

#define CONFIG_FILE_NAME "config.txt"
#define DATA_FILE_NAME "mybd.dat"
const char DEFAULT_DB_FILE_NAME[] = "default_db_file.dat";
const char DEFAULT_LICENSE_KEY[] = "default_license_key";

typedef struct {
    int id;
    char name[50];
    float price;
    int quantity;
    int is_deleted;
} Product;

void save_license_key_to_config_file(const char* license_key);
void generate_license_key(char* license_key);
int check_license_key(const char* license_key);
int read_config_file(char* db_file_name, char* license_key, unsigned int license_key_size);


void generate_license_key(char* license_key) {
    srand(time(NULL));  // Початок генератора випадкових чисел.

    // Генерируем лицензионный ключ
    snprintf(license_key, 25, "%04X-%04X-%04X-%04X",
        rand() % 0xFFFF, rand() % 0xFFFF, rand() % 0xFFFF, rand() % 0xFFFF);
}

int check_license_key(const char* license_key) {
    // Перевіряємо, чи ліцензійний ключ відповідає потрібному формату.
    // Формат повинен бути XXXX-XXXX-XXXX-XXXX, де X - шістнадцяткова цифра (0-9, A-F).

    // Перевіряємо довжину ліцензійного ключа.
    if (strlen(license_key) != 19)
        return 0;

    // Перевіряємо, чи є кожен символ допустимою шістнадцятковою цифрою чи тире.
    for (int i = 0; i < 19; i++) {
        char c = license_key[i];
        if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c == '-')))
            return 0;
    }

    // Перевіряэмо правильне розташування тире
    if (license_key[4] != '-' || license_key[9] != '-' || license_key[14] != '-')
        return 0;

    return 1;
}


int read_config_file(char* db_file_name, char* license_key, unsigned int license_key_size) {
    FILE* file;
    if (fopen_s(&file, CONFIG_FILE_NAME, "r") == 0) {
        // Читання ліцензійного ключа з файлу
        if (fscanf_s(file, "KEY = %s", license_key, license_key_size) != 1) {
            fclose(file);
            return 0;
        }
        fclose(file);
        return check_license_key(license_key);
    }
    else {
        // Файл не існує, створення нового ліцензійного ключа і збереження його у config.txt
        generate_license_key(license_key);
        save_license_key_to_config_file(license_key);
        return 1; // Припустимо, що згенерований ліцензійний ключ дійсний.
    }
}

void save_license_key_to_config_file(const char* license_key) {
    FILE* file;
    if (fopen_s(&file, CONFIG_FILE_NAME, "w") == 0) {
        fprintf(file, "KEY = %s\n", license_key);
        fclose(file);
        printf("License key saved to %s.\n", CONFIG_FILE_NAME);
    }
    else {
        printf("Failed to save the license key to %s.\n", CONFIG_FILE_NAME);
    }
}



void print_menu();
int read_menu_option();
void save_config_file(const char* db_file_name, const char* license_key);
int read_data_file(Product** products);
void save_data_file(Product* products, int num_products);
void add_product(Product** products, int* num_products);
void delete_product(Product* products, int* num_products);
void edit_product(Product* products, int num_products);
void find_product_by_name(Product* products, int num_products);
void find_product_by_code(Product* products, int num_products);
void export_to_csv(Product* products, int num_products);
void print_low_quantity_high_price_products(Product* products, int num_products);
void print_all_products(Product* products, int num_products);
void open_csv_file(Product** products, int* num_products);



void print_menu() {
    printf("\n--- MENU ---\n");
    printf("Select an option:\n");
    printf("1. Add a new product\n");
    printf("2. Delete a product\n");
    printf("3. Edit a product\n");
    printf("4. Find a product by name\n");
    printf("5. Find a product by code\n");
    printf("6. Export to CSV file\n");
    printf("7. Open and edit A CVS file\n");
    printf("8. Print products with low quantity and high price\n");
    printf("9. Print all products\n");
    printf("10. Exit\n");
    printf("--------------\n");

}

int read_menu_option() {
    int option;
    printf("Enter option number: ");
    scanf_s("%d", &option);
    return option;
}

void save_config_file(const char* db_file_name, const char* license_key) {
    FILE* config_file;
    if (fopen_s(&config_file, CONFIG_FILE_NAME, "w") != 0) {
        printf("Could not save config file.\n");
        return;
    }

    fprintf(config_file, "DB = %s\n", db_file_name);
    fprintf(config_file, "KEY = %s\n", license_key);

    fclose(config_file);
}


int read_data_file(Product** products) {
    FILE* data_file;
    fopen_s(&data_file, DATA_FILE_NAME, "rb");
    if (data_file == NULL) {
        return 0;
    }
    int num_products;
    fread(&num_products, sizeof(int), 1, data_file);

    *products = (Product*)malloc(num_products * sizeof(Product));
    if (*products == NULL) {
        fclose(data_file);
        return 0;
    }
    fread(*products, sizeof(Product), num_products, data_file);

    fclose(data_file);
    return num_products;
}

void save_data_file(Product* products, int num_products) {
    FILE* file;
    fopen_s(&file, DATA_FILE_NAME, "wb");
    if (file == NULL) {
        printf("Error opening data file.\n");
        return;
    }
    fwrite(products, sizeof(Product), num_products, file);
    fclose(file);
}

void add_product(Product** products, int* num_products) {
    Product new_product;
    printf("\nEnter product details:\n");
    printf("Name: ");
    scanf_s("%49s", new_product.name, (unsigned int)sizeof(new_product.name));
    printf("Price: ");
    scanf_s("%f", &new_product.price);
    printf("Quantity: ");
    scanf_s("%d", &new_product.quantity);
    new_product.is_deleted = 0;

    if (*num_products == 0) {
        new_product.id = 1;
        *products = (Product*)malloc(sizeof(Product));
    }
    else {
        new_product.id = (*products)[*num_products - 1].id + 1;
        Product* new_products = (Product*)realloc(*products, (*num_products + 1) * sizeof(Product));
        if (new_products == NULL) {
            printf("Memory allocation failed. Product could not be added.\n");
            return;
        }
        *products = new_products;
    }

    if (*products != NULL) {   // Перевірка, чи *products не є null перед розіменуванням.
        (*products)[*num_products] = new_product;
        (*num_products)++;
        save_data_file(*products, *num_products);  // Оновити файл даних після додавання продукту.
    }
}

void delete_product(Product* products, int* num_products) {
    int id;
    printf("\nEnter product ID to delete: ");
    scanf_s("%d", &id);
    for (int i = 0; i < *num_products; i++) {
        if (products[i].id == id && products[i].is_deleted == 0) {
            products[i].is_deleted = 1;
            printf("Product with ID %d has been deleted.\n", id);
            // Оновити ідентифікатори решти продуктів.
            for (int j = i + 1; j < *num_products; j++) {
                products[j - 1] = products[j];
                products[j - 1].id = j;
            }
            (*num_products)--;
            save_data_file(products, *num_products);  // Оновити файл даних після видалення продукту.
            return;
        }
    }
    printf("Product with ID %d not found.\n", id);
}

void edit_product(Product* products, int num_products) {
    int id;
    printf("\nEnter product ID to edit: ");
    scanf_s("%d", &id);
    for (int i = 0; i < num_products; i++) {
        if (products[i].id == id && products[i].is_deleted == 0) {
            printf("\nEditing product with ID %d:\n", id);
            printf("Name: %s\n", products[i].name);
            printf("Price: %.2f\n", products[i].price);
            printf("Quantity: %d\n", products[i].quantity);

            // Запитувати користувача щодо нових значень.
            printf("\nEnter new product details:\n");
            printf("Name: ");
            scanf_s("%49s", products[i].name, (unsigned int)sizeof(products[i].name));
            printf("Price: ");
            scanf_s("%f", &products[i].price);
            printf("Quantity: ");
            scanf_s("%d", &products[i].quantity);

            printf("Product with ID %d has been edited.\n", id);
            save_data_file(products, num_products);  // Оновити файл даних після редагування продукту.
            return;
        }
    }
    printf("Product with ID %d not found.\n", id);
}
// Функція пошуку товару за його назвою.
void find_product_by_name(Product* products, int num_products) {
    char search_name[50];
    printf("Enter the name of the product to search for: ");
    scanf_s("%49s", search_name, (unsigned int)sizeof(search_name) - 1);
    search_name[sizeof(search_name) - 1] = '\0';
    int found = 0;
    for (int i = 0; i < num_products; i++) {
        if (!products[i].is_deleted && strcmp(search_name, products[i].name) == 0) {
            printf("ID: %d\nName: %s\nPrice: %.2f\nQuantity: %d\n\n", products[i].id, products[i].name, products[i].price, products[i].quantity);
            found = 1;
        }
    }
    if (!found) {
        printf("No product found with name %s\n", search_name);
    }
}

// Функція пошуку товару за його кодом (id).
void find_product_by_code(Product* products, int num_products) {
    int search_id;
    printf("Enter the ID of the product to search for: ");
    scanf_s("%d", &search_id);
    int found = 0;
    for (int i = 0; i < num_products; i++) {
        if (!products[i].is_deleted && search_id == products[i].id) {
            printf("ID: %d\nName: %s\nPrice: %.2f\nQuantity: %d\n\n", products[i].id, products[i].name, products[i].price, products[i].quantity);
            found = 1;
        }
    }
    if (!found) {
        printf("No product found with ID %d\n", search_id);
    }
}

// Функція для експорту продуктів у файл CSV.
void export_to_csv(Product* products, int num_products) {
    char csv_file_name[50];
    printf("Enter the name of the CSV file to export to: ");
    scanf_s("%49s", csv_file_name, (unsigned int)sizeof(csv_file_name) - 1);
    strcat_s(csv_file_name, sizeof(csv_file_name), ".csv"); // Додавання росширення .csv.
    FILE* csv_file;
    if (fopen_s(&csv_file, csv_file_name, "w") != 0) {
        printf("Error opening CSV file.\n");
        return;
    }

    fprintf(csv_file, "ID;Name;Price;Quantity\n"); // Використовуємо точку із запятой в якості розділител.

    for (int i = 0; i < num_products; i++) {
        if (!products[i].is_deleted) {
            fprintf(csv_file, "%d;%s;%.2f;%d\n", products[i].id, products[i].name, products[i].price, products[i].quantity);
        }
    }

    fclose(csv_file);
    printf("Products exported to %s successfully.\n", csv_file_name);
}

// Функція друку продукції з низькою кількістю та високою ціною.
void print_low_quantity_high_price_products(Product* products, int num_products) {
    printf("Products with low quantity and high price:\n");
    for (int i = 0; i < num_products; i++) {
        if (!products[i].is_deleted && products[i].quantity < 10 && products[i].price > 100.0) {
            printf("ID: %d\nName: %s\nPrice: %.2f\nQuantity: %d\n\n", products[i].id, products[i].name, products[i].price, products[i].quantity);
        }
    }
}
// Функція виведення усіх продуктів.
void print_all_products(Product* products, int num_products) {
    if (num_products == 0) {
        printf("No products found.\n");
        return;
    }
    printf("\nAll Products\n");
    printf("------------\n");
    printf("ID | Name | Price | Quantity\n");
    printf("-------------------------------------------\n");
    for (int i = 0; i < num_products; i++) {
        if (products[i].is_deleted == 0) {
            printf("%-3d | %-16s | %-7.2f      | %-8d\n",
                products[i].id, products[i].name, products[i].price, products[i].quantity);
        }
    }
}

void open_csv_file(Product** products, int* num_products) {
    char csv_file_name[50];
    printf("Enter the name of the CSV file to open: ");
    scanf_s("%49s", csv_file_name, (unsigned int)sizeof(csv_file_name) - 1);
    strcat_s(csv_file_name, sizeof(csv_file_name), ".csv"); // // Додавання розширення .csv.

    FILE* csv_file;
    if (fopen_s(&csv_file, csv_file_name, "r") != 0) {
        printf("Error opening CSV file.\n");
        return;
    }

    // Читання вмісту файлу CSV.
    char buffer[256];
    int count = 0;
    while (fgets(buffer, sizeof(buffer), csv_file) != NULL) {
        count++;
    }

    // Оновити кількість товарів.
    *num_products = count - 1; // Віднімання 1, щоб виключити рядок заголовка.

    // Виділити пам'ять для продуктів.
    Product* temp = (Product*)realloc(*products, (*num_products) * sizeof(Product));
    if (temp == NULL) {
        printf("Memory allocation failed.\n");
        fclose(csv_file);
        free(*products); // Free the original memory block
        *products = NULL; // Set the pointer to null
        return;
    }
    *products = temp;

    // Перемотати покажчик файлу на початок файлу.
    rewind(csv_file);

    // Пропустити рядок заголовка.
    fgets(buffer, sizeof(buffer), csv_file);

    // Читання кожного рядка файлу CSV і аналіз даних.
    int i = 0;
    while (fgets(buffer, sizeof(buffer), csv_file) != NULL) {
        // Розділити рядок на поля за допомогою strtok_s.
        char* token = NULL;
        char* next_token = NULL;

        token = strtok_s(buffer, ";", &next_token);
        if (token != NULL) {
            // Читання ID.
            (*products)[i].id = atoi(token);

            // Читання назви.
            token = strtok_s(NULL, ";", &next_token);
            strncpy_s((*products)[i].name, sizeof((*products)[i].name), token, _TRUNCATE);

            // Читання ціни.
            token = strtok_s(NULL, ";", &next_token);
            (*products)[i].price = atof(token);

            // Читання кількості.
            token = strtok_s(NULL, ";", &next_token);
            (*products)[i].quantity = atoi(token);

            // Встановити is_deleted на 0
            (*products)[i].is_deleted = 0;

            i++;
        }
    }

    fclose(csv_file);

    printf("CSV file %s opened successfully.\n", csv_file_name);
}