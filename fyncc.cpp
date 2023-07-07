#define _CRT_SECURE_NO_WARNINGS
#include "fyncc.h"
#include "stdlib.h"
#include "string.h"

void savePaymentsToFile(struct Payment* payments, int numPayments) {
    FILE* file = fopen("payments.txt", "w");
    if (file == NULL) {
        printf("Не вдалося відкрити файл бази даних.\n");
        return;
    }
    for (int i = 0; i < numPayments; i++) {
        fprintf(file, "%d;%s;%d;%d;%s;%.2f\n",
            payments[i].id,
            payments[i].surname,
            payments[i].account,
            payments[i].mfo,
            payments[i].date,
            payments[i].amount);
    }
    fclose(file);
}

void loadPaymentsFromFile(struct Payment** payments, int* numPayments) {
    FILE* file = fopen("payments.txt", "r");
    if (file == NULL) {
        printf("Не вдалося відкрити файл бази даних.\n");
        return;
    }
    int count = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            count++;
        }
    }
    rewind(file);
    struct Payment* temp = (struct Payment*)malloc(count * sizeof(struct Payment));
    if (temp == NULL) {
        printf("Помилка виділення пам'яті.\n");
        fclose(file);
        return;
    }
    int i = 0;
    while (fscanf(file, "%d;%[^;];%d;%d;%[^;];%f\n",
        &temp[i].id,
        temp[i].surname,
        &temp[i].account,
        &temp[i].mfo,
        temp[i].date,
        &temp[i].amount) == 6) {
        i++;
    }
    fclose(file);
    *payments = temp;
    *numPayments = count;
}

void addPayment(struct Payment** payments, int* numPayments) {
    struct Payment newPayment;
    printf("Введіть прізвище замовника: ");
    scanf(" %[^\n]", newPayment.surname);
    printf("Введіть розрахунковий рахунок: ");
    scanf("%d", &newPayment.account);
    printf("Введіть МФО банку: ");
    scanf("%d", &newPayment.mfo);
    printf("Введіть дату: ");
    scanf(" %[^\n]", newPayment.date);
    printf("Введіть суму: ");
    scanf("%f", &newPayment.amount);
    newPayment.id = *numPayments + 1;
    (*numPayments)++;
    *payments = (struct Payment*)realloc(*payments, (*numPayments) * sizeof(struct Payment));
    (*payments)[*numPayments - 1] = newPayment;
}

void deletePayment(struct Payment** payments, int* numPayments, int id) {
    int index = -1;
    for (int i = 0; i < *numPayments; i++) {
        if ((*payments)[i].id == id) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Платіж з таким ID не знайдено.\n");
        return;
    }
    for (int i = index; i < *numPayments - 1; i++) {
        (*payments)[i] = (*payments)[i + 1];
    }
    (*numPayments)--;
    *payments = (struct Payment*)realloc(*payments, (*numPayments) * sizeof(struct Payment));
    printf("Платіж з ID %d успішно видалено.\n", id);
}

void modifyPayment(struct Payment* payments, int numPayments, int id) {
    int index = -1;
    for (int i = 0; i < numPayments; i++) {
        if (payments[i].id == id) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Платіж з таким ID не знайдено.\n");
        return;
    }
    struct Payment modifiedPayment;
    modifiedPayment.id = id;
    printf("Введіть нове прізвище замовника: ");
    scanf(" %[^\n]", modifiedPayment.surname);
    printf("Введіть новий розрахунковий рахунок: ");
    scanf("%d", &modifiedPayment.account);
    printf("Введіть нову МФО банку: ");
    scanf("%d", &modifiedPayment.mfo);
    printf("Введіть нову дату: ");
    scanf(" %[^\n]", modifiedPayment.date);
    printf("Введіть нову суму: ");
    scanf("%f", &modifiedPayment.amount);
    payments[index] = modifiedPayment;
    printf("Платіж з ID %d успішно змінено.\n", id);
}

void displayPayments(struct Payment* payments, int numPayments) {
    if (numPayments == 0) {
        printf("Немає жодного платежу.\n");
        return;
    }
    printf("Інформація про платежі:\n");
    printf("--------------------------------------------------------\n");
    printf("| ID | Прізвище замовника | Рахунок | МФО | Дата | Сума |\n");
    printf("--------------------------------------------------------\n");
    for (int i = 0; i < numPayments; i++) {
        printf("| %2d | %-21s | %7d | %6d | %-6s | %.2f |\n",
            payments[i].id,
            payments[i].surname,
            payments[i].account,
            payments[i].mfo,
            payments[i].date,
            payments[i].amount);
    }
    printf("--------------------------------------------------------\n");
}

void displayPaymentsByAccountAndMFO(struct Payment* payments, int numPayments, int
    account, int mfo) {
    int count = 0;
   
    printf("Платежі за рахунком %d та МФО %d:\n", account, mfo);
    printf("--------------------------------------------------------\n");
    printf("| ID | Прізвище замовника | Рахунок | МФО | Дата | Сума \n");
        printf("--------------------------------------------------------\n");
    for (int i = 0; i < numPayments; i++) {
        if (payments[i].account == account && payments[i].mfo == mfo) {
            printf("| %2d | %-21s | %7d | %6d | %-6s | %.2f |\n",
                payments[i].id,
                payments[i].surname,
                payments[i].account,
                payments[i].mfo,
                payments[i].date,
                payments[i].amount);
            count++;
        }
    }
    printf("--------------------------------------------------------\n");
    if (count == 0) {
        printf("Немає платежів за заданими рахунком %d та МФО %d.\n", account, mfo);
    }
}

void displayPaymentsByDateAndAmount(struct Payment* payments, int numPayments, char*
    date, float amount) {
    int count = 0;
    printf("Платежі на дату %s з сумою меншою за %.2f:\n", date, amount);
    printf("--------------------------------------------------------\n");
    printf("| ID | Прізвище замовника | Рахунок | МФО | Дата | Сума \n");
        printf("--------------------------------------------------------\n");
    for (int i = 0; i < numPayments; i++) {
        if (strcmp(payments[i].date, date) == 0 && payments[i].amount < amount) {
            printf("| %2d | %-21s | %7d | %6d | %-6s | %.2f |\n",
                
                payments[i].id,
                payments[i].surname,
                payments[i].account,
                payments[i].mfo,
                payments[i].date,
                payments[i].amount);
            count++;
        }
    }
    printf("--------------------------------------------------------\n");
    if (count == 0) {
        printf("Немає платежів на дату %s з сумою меншою за %.2f.\n", date, amount);
    }
}
