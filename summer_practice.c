/** 
* @file main.c
 * @author Косінов І.С., гр. 515-i, варіант 17 
* @date 28 червня 2023 
* @brief Навчальна практика 
* 
* База даних 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Структура для хранения информации о товаре
struct Product {
    int code;
    char name[100];
    float price;
    int quantity;
};

// Функция для добавления записи о товаре
void addProduct(struct Product *database, int *numProducts) {
    struct Product newProduct;
    
    printf("Enter product code: ");
    scanf("%d", &newProduct.code);
    
    printf("Enter product name: ");
    scanf("%s", newProduct.name);
    
    printf("Enter product price: ");
    scanf("%f", &newProduct.price);
    
    printf("Enter product quantity: ");
    scanf("%d", &newProduct.quantity);
    
    database[*numProducts] = newProduct;
    (*numProducts)++;
    
    printf("Product added successfully!\n");
}

// Функция для удаления записи о товаре по коду
void removeProduct(struct Product *database, int *numProducts) {
    int code;
    int i, found = 0;
    
    printf("Enter product code to remove: ");
    scanf("%d", &code);
    
    for (i = 0; i < *numProducts; i++) {
        if (database[i].code == code) {
            found = 1;
            break;
        }
    }
    
    if (found) {
        // Сдвигаем элементы массива для удаления записи
        for (; i < *numProducts - 1; i++) {
            database[i] = database[i + 1];
        }
        
        (*numProducts)--;
        printf("Product removed successfully!\n");
    } else {
        printf("Product with the specified code not found!\n");
    }
}

// Функция для вывода всех записей о товарах
void displayProducts(const struct Product *database, int numProducts) {
    if (numProducts > 0) {
        printf("Product List:\n");
        printf("-------------------------------\n");
        
        for (int i = 0; i < numProducts; i++) {
            printf("Code: %d\n", database[i].code);
            printf("Name: %s\n", database[i].name);
            printf("Price: %.2f\n", database[i].price);
            printf("Quantity: %d\n", database[i].quantity);
            printf("-------------------------------\n");
        }
    } else {
        printf("No products found!\n");
    }
}

// Функция для изменения записи о товаре по коду
void modifyProduct(struct Product *database, int numProducts) {
    int code;
    int i, found = 0;
    
    printf("Enter product code to modify: ");
    scanf("%d", &code);
    
    for (i = 0; i < numProducts; i++) {
        if (database[i].code == code) {
            found = 1;
            break;
        }
    }
    
    if (found) {
        printf("Enter new product name: ");
        scanf("%s", database[i].name);
        
        printf("Enter new product price: ");
        scanf("%f", &database[i].price);
        
        printf("Enter new product quantity: ");
        scanf("%d", &database[i].quantity);
        
        printf("Product modified successfully!\n");
    } else {
        printf("Product with the specified code not found!\n");
    }
}

// Функция для вывода количества товара по названию или коду
void displayQuantityByCriteria(const struct Product *database, int numProducts) {
    int choice;
    printf("Choose criteria:\n");
    printf("1. By name\n");
    printf("2. By code\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        char name[100];
        int totalQuantity = 0;
        
        printf("Enter product name: ");
        scanf("%s", name);
        
        for (int i = 0; i < numProducts; i++) {
            if (strcmp(database[i].name, name) == 0) {
                totalQuantity += database[i].quantity;
            }
        }
        
        printf("Total quantity for product '%s': %d\n", name, totalQuantity);
    } else if (choice == 2) {
        int code;
        int totalQuantity = 0;
        
        printf("Enter product code: ");
        scanf("%d", &code);
        
        for (int i = 0; i < numProducts; i++) {
            if (database[i].code == code) {
                totalQuantity = database[i].quantity;
                break;
            }
        }
        
        printf("Total quantity for product with code %d: %d\n", code, totalQuantity);
    } else {
        printf("Invalid choice!\n");
    }
}

// Функция для вывода товаров с количеством 1 и ценой выше заданной
void displayProductsByCriteria(const struct Product *database, int numProducts) {
    float minPrice;
    
    printf("Enter minimum price: ");
    scanf("%f", &minPrice);
    
    printf("Products with quantity 1 and price higher than %.2f:\n", minPrice);
    printf("-------------------------------\n");
    
    int found = 0;
    for (int i = 0; i < numProducts; i++) {
        if (database[i].quantity == 1 && database[i].price > minPrice) {
            printf("Code: %d\n", database[i].code);
            printf("Name: %s\n", database[i].name);
            printf("Price: %.2f\n", database[i].price);
            printf("Quantity: %d\n", database[i].quantity);
            printf("-------------------------------\n");
            found = 1;
        }
    }
    
    if (!found) {
        printf("No products found!\n");
    }
}

int main() {
    struct Product database[100];
    int numProducts = 0;
    int choice;
    
    do {
        printf("\nProduct Database\n");
        printf("1. Add product\n");
        printf("2. Remove product\n");
        printf("3. Display all products\n");
        printf("4. Modify product\n");
        printf("5. Display quantity by criteria\n");
        printf("6. Display products by criteria\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addProduct(database, &numProducts);
                break;
            case 2:
                removeProduct(database, &numProducts);
                break;
            case 3:
                displayProducts(database, numProducts);
                break;
            case 4:
                modifyProduct(database, numProducts);
                break;
            case 5:
                displayQuantityByCriteria(database, numProducts);
                break;
            case 6:
                displayProductsByCriteria(database, numProducts);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 0);
    
    return 0;
}
