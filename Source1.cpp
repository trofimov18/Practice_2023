/**
* @file practice3.cpp
* @author Ткаченко Є.С., гр. 515і, варіант 7
* @date 3 липня 2023
* @brief Навчальна практика
*
* База даних потягів
*/

#pragma warning(disable : 4996)
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "locale.h"
// Структура для потягів//
typedef struct tagITEM
{
    int tr_num;
    char dis_po[20];
    char arr_po[20];
    char dep_ti[6];
} ITEM;

//Масив (макс. 20)
ITEM Train[20];

//Кількість занятих потягів
int lock;

//Функція виводу інформації
void print(void)
{
    int i;
    printf("|№ | Номер потягу | Пункт вiдправлення | Пункт призначення | Час призначення|\n");
    for (i = 0; i < lock; i++)
        printf("%2i   %i               %-20s  %-20s %s\n", i+1, Train[i].tr_num, Train[i].dis_po, Train[i].arr_po, Train[i].dep_ti);
}

//Функція додавання інформації про потяг
void add(void)
{
    printf("Введiть номер потягу: ");
    scanf_s("%i", &Train[lock].tr_num);
    printf("Введiть пункт вiдправки: ");
    scanf_s("%19s", Train[lock].dis_po, sizeof(Train[lock].dis_po));
    printf("Введiть пункт прибуття: ");
    scanf_s("%19s", Train[lock].arr_po, sizeof(Train[lock].arr_po));
    printf("Введiть час вiдправки(у форматi HH:MM): ");
    scanf_s("%5s", &Train[lock].dep_ti, sizeof(Train[lock].dep_ti));

    lock++;
}

//Функція видалення потягу
void deleting(void)
{
    int i;

    print();
    printf("Введiть номер маршруту: ");
    scanf_s("%i", &i);
    if (i < 1 || i > lock)
    {
        fprintf(stderr, " %i такого номеру не iснує\n", i);
        return;
    }

    for (i--; i < lock - 1; i++)
        Train[i] = Train[i + 1];

    lock--;
}

//Функція збереження інформації у файлі
void save(void)
{
    FILE* TRAIN;
    int i;

    if ((TRAIN = fopen("train.dat", "wt")) == NULL)
    {
        fprintf(stderr, "Неможливо вiдкрити\n");
        return;
    }

    fprintf(TRAIN, "%i\n", lock);
    for (i = 0; i < lock; i++)
        fprintf(TRAIN, "%i\n%s\n%s\n%s\n",Train[i].tr_num, Train[i].dis_po, Train[i].arr_po, Train[i].dep_ti);

    fclose(TRAIN);
}

//Функція завантаження файлу
void load(void)
{
    FILE* TRAIN;
    int i;

    if ((TRAIN = fopen("train.dat", "rt")) == NULL)
    {
        fprintf(stderr, "Неможливо завантажити файл\n");
        return;
    }

    fscanf_s(TRAIN, "%i", &lock);
    for (i = 0; i < lock; i++)
        fscanf_s(TRAIN, "%i%19s%19s%19s", &Train[i].tr_num, Train[i].dis_po, sizeof(Train[lock].dis_po), Train[i].arr_po, sizeof(Train[lock].arr_po), Train[i].dep_ti, sizeof(Train[lock].dep_ti));

    fclose(TRAIN);
    fclose(TRAIN);
} 
//Меню для вибору дій
int menu(void)
{
    int c = 0;

    while ((c < '0' || c > '5') )
    {
        printf("0 : Вихiд\n"
            "1 : додати\n"
            "2 : зберегти\n"
            "3 : завантижити\n"
            "4 : вивести\n"
            "5 : видалити\n");
        c = _getch();
        printf("%c\n", c);
    }
    return c;
}

//Основна функція
void main(int) {
    int Selection;
    setlocale(LC_ALL, "Ukr");
    lock = 0;
    while ((Selection = menu()) != '0' )
        switch (Selection)
        {
        case '1':
            add();
            break;
        case '2':
            save();
            break;
        case '3':
            load();
            break;
        case '4':
            print();
            break;
        case '5':
            deleting();
            break;
        }
}