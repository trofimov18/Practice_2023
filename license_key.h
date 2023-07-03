#ifndef LICENSE_KEY_H
#define LICENSE_KEY_H

#include <time.h>
#pragma warning(disable : 4996)

// Оголошення функції генерації ліцензійного ключу
int key_generate();

// функція перевірки ключу
int key_valid(int key);

#endif