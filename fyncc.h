#define _CRT_SECURE_NO_WARNINGS
#ifndef FYNC_H
#define FYNC_H

#include "stdio.h"

struct Payment {
    int id;
    char surname[100];
    int account;
    int mfo;
    char date[20];
    float amount;
};

void savePaymentsToFile(struct Payment* payments, int numPayments);
void loadPaymentsFromFile(struct Payment** payments, int* numPayments);
void addPayment(struct Payment** payments, int* numPayments);
void deletePayment(struct Payment** payments, int* numPayments, int id);
void modifyPayment(struct Payment* payments, int numPayments, int id);
void displayPayments(struct Payment* payments, int numPayments);
void displayPaymentsByAccountAndMFO(struct Payment* payments, int numPayments, int account, int mfo);
void displayPaymentsByDateAndAmount(struct Payment* payments, int numPayments, char* date, float amount);

#endif

