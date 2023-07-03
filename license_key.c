#include "license_key.h"

int key_generate() {
    time_t currentTime = time(NULL); // Отримати поточний час в секундах
    struct tm* localTime = localtime(&currentTime); // Конвертувати в місцевий час
    // рік від 1900 -100 та домножимо на 3
    int currentYear = (((localTime->tm_year - 100) * 3));
    // місяць ділимо на два
    int month = (((localTime->tm_mon) / 2));
    // день від початку року ділимо на 100
    int day_year = (localTime->tm_yday / 100) * 1;

    return((currentYear * 100 + month * 10 + day_year) * 1000 + (currentYear + month + day_year) * 4);
}


int key_valid(int key) {
    int year = (key / 100000);
    int month = (key / 10000) - year * 10;
    int day_year = (key / 1000) - year * 100 - month * 10;
    int summa = (key - ((year * 100000) + month * 10000 + day_year * 1000)) / 4;
    // тільки 23 та 24 рік          місяць тільки від 0 до 5
    if ((year == 69 || year == 72) && (month >= 0 && month <= 5) && (day_year >= 0 && day_year <= 3) && (year + month + day_year == summa)) {
        return 0;
    }
    return 1;
}