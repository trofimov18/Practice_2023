#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "fyncc.h"
#include <stdlib.h>
#include <locale.h>


int main() {
    setlocale(LC_ALL, "rus");
    struct Payment* payments = NULL;
    int numPayments = 0;
    int choice, id, account, mfo;
    char date[20];
    float amount;


    loadPaymentsFromFile(&payments, &numPayments);

    while (1) {
        printf("1. Додати платіж\n");
        printf("2. Видалити платіж\n");
        printf("3. Змінити платіж\n");
        printf("4. Показати всі платежі\n");
        printf("5. Показати платежі за рахунком та МФО\n");
        printf("6. Показати платежі за датою та сумою\n");
        printf("0. Вийти\n");
        printf("Виберіть дію: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addPayment(&payments, &numPayments);
            break;
        case 2:
            printf("Введіть ID платежу, який потрібно видалити: ");
            scanf("%d", &id);
            deletePayment(&payments, &numPayments, id);
            break;
        case 3:
            printf("Введіть ID платежу, який потрібно змінити: ");
            scanf("%d", &id);
            modifyPayment(payments, numPayments, id);
            break;
        case 4:
            displayPayments(payments, numPayments);
            break;
        case 5:
            printf("Введіть розрахунковий рахунок: ");
            scanf("%d", &account);
            printf("Введіть МФО банку: ");
            scanf("%d", &mfo);
            displayPaymentsByAccountAndMFO(payments, numPayments, account, mfo);
            break;
        case 6:
            printf("Введіть дату: ");
            scanf(" %[^\n]", date);
            printf("Введіть суму: ");
            scanf("%f", &amount);
            displayPaymentsByDateAndAmount(payments, numPayments, date, amount);
            break;
        case 0:
            savePaymentsToFile(payments, numPayments);
            free(payments);
            printf("До побачення!\n");
            return 0;
        default:
            printf("Невірний вибір. Спробуйте ще раз.\n");
            break;
        }
    }

    return 0;
}
