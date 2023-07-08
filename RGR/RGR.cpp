/**
* @file RGR.cpp
* @author Гесс.Є.В, гр. 515б
* @date 3 липня 2023
* @brief Практична робота.
* Структури. Зв'язані списки. Файли.
*/


#include "key_and_functions.h"

int main() {
    char db_file_name[50];
    char license_key[50];
    int num_products = 0;
    Product* products = NULL;
    int license_check = 0;

    // Read config file and check the license key
    int success = read_config_file(db_file_name, license_key, sizeof(license_key));
 
    if (!success) {
        printf("Invalid or missing license key. Some functions may not work.\n");
        return 1;
    }

    printf("License key from file config.txt: %s\n", license_key);

    printf("Enter license key: ");
    scanf_s("%s", license_key, (unsigned int)sizeof(license_key));

    // Check the entered license key
    if (!check_license_key(license_key)) {
        printf("Invalid license key. Some functions may not work.\n");
        license_check = 0;
    }
    else {
        license_check = 1;
    }
    while (1) {
        // Print menu
        print_menu();

        // Read menu option from user
        int option = read_menu_option();

        // Perform action based on menu option
        switch (option) {
        case 1:
            add_product(&products, &num_products);
            save_data_file(products, num_products);
            break;
        case 2:
            delete_product(products, &num_products);
            save_data_file(products, num_products);
            break;
        case 3:
            edit_product(products, num_products);
            save_data_file(products, num_products);
            break;
        case 4: //need key
            if (license_check) {
                find_product_by_name(products, num_products);
            }
            else {
                printf("Special function disabled. Invalid license key.\n");
            }
            break;
        case 5: //need key
            if (license_check) {
                find_product_by_code(products, num_products);
            }
            else {
                printf("Special function disabled. Invalid license key.\n");
            }
            break;
        case 6: //need key
            if (license_check) {
                export_to_csv(products, num_products);
            }
            else {
                printf("Special function disabled. Invalid license key.\n");
            }
            break;
        case 7:
            // Îòêðûòü è ðåäàêòèðîâàòü ðàíåå ñîõðàíåííûé ôàéë CSV
            open_csv_file(&products, &num_products);
            save_data_file(products, num_products);
            break;
        case 8: //need key
            if (license_check) {
                print_low_quantity_high_price_products(products, num_products);
            }
            else {
                printf("Special function disabled. Invalid license key.\n");
            }
            break;
        case 9: //need key
            if (license_check) {
                print_all_products(products, num_products);
            }
            else {
                printf("Special function disabled. Invalid license key.\n");
            }
            break;
        case 10:
            // Quit program
            printf("Exiting program.\n");
            save_data_file(products, num_products);
            free(products);
            return 0;
        default:
            printf("Invalid option. Please try again.\n");
            break;
        }
    }
}
