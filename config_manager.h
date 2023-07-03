#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <stdio.h>
#include <String.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

// Оголошення функції зчитування назви бази данних
int read_pathDB(char* cfg_path, char* out_path);

// Оголошення функції зчитування ключа з конфігураційного файлу
int read_key(char* cfg_path, int* key);

// Редагування назви БД в конфігураційному файлі
int edit_pathDB(char* cfg_path, char* DB_name);

// Редагування ключу в конфігураційному файлі
int edit_key(char* cfg_path, int key);

// створення .cfg файлу
int make_cfg_file(char* cfg_path);


#endif