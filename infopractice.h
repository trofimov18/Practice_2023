#ifndef INFOPRACTICE_H
#define INFOPRACTICE_H
#define PUBLIC
#define PRIVATE static
#define MAX 100
#define KEY_LENGTH 10
#define MAX_FILENAME_LENGTH 20
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>


PUBLIC void change(const char* CurfileName);
PUBLIC void delet(const char* CurfileName);
PUBLIC void print(const char* CurfileName);
PUBLIC void input(const char* CurfileName);
PUBLIC int menu();
PUBLIC void search_by_supplier(const char* CurfileName);
PUBLIC void low_prices(const char* CurfileName);
PRIVATE int code_exists(int code_num, const char* CurfileName);
PUBLIC bool is_valid_key();
PUBLIC int menu_settings();
PUBLIC void file_change_name(const char* CurfileName);
PUBLIC void generation_key();
PUBLIC void exportCSV(const char* CurfileName);
#endif
