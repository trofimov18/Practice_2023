
//////////|
//define//|
//////////|

//керуючи дефайни
#define PRIVATE static
#define PUBLIC
//відлагодження
/*#define DEF*/
//побічні дефайни
#define ERROR_TYPE 1
#define SIZE 246

/////////////////////////////////////|
// структури баз даних, та їх листи//|
/////////////////////////////////////|

/**
* Зв'язний список товарів
*
* @type id		, номер товару
* @type name	, назва товару
* @type	groupe	, группа товару
* @type	price	, ціна товару
* @type	from	, постачальник товару
* @type delstat	, флаг видалення(0 - не видалено, 1 - видалено)
* @type * next	, наступний вузол структурного списку
*/
struct Stuff {			/* визначення зв'зного списку товарів */
	int id;				/* номер товару */
	char* name;			/* назва товару */
	char* group;		/* группа товару */
	double price;		/* ціна товару */
	char* from;			/* постачальник товару */
	int delstat = 0;	/* змінна флагу видаленого файлу */
	struct Stuff* next;	/* наступний вузол */
};

/////////////////////////////////////////////////////////////////////|
// прототипи основних функцій, та їх функціонально залежені функції//|
/////////////////////////////////////////////////////////////////////|

/**
* Головне меню керування
*
* @param arr, вказівник на зв'язний список
* @return 0, за нормальних умов
*/
int menu(struct Stuff** arr);
/**
* Конструктор структур
*
* @param ptr, вузол зв'язного списку
* @return 0
*/
int SetStuff(struct Stuff* ptr);
/**
* Виведення вузла
*
* @param ptr, вузол зв'язного списку
* @return void
*/
void PrintStuff(struct Stuff* ptr);
/**
* Створення нового товару
*
* @param arr, вказівник на зв'язний список
* @return 0, за задовільних умов
*/
int AddStuff(struct Stuff** arr);
/**
* Ініціалізація нового вузла товару
*
* @param help_new_stuff, вказівник на вузол, який треба ініціалізувати
* @return 0, за задовільних умов
*/
int AddHelper(struct Stuff* help_new_stuff);
/**
* Побітовий запис строки
*
* @param str, строка
* @param n, кількість символів
* @return i, кількість записаних символів
*/
int read_line(char* str, int n);
/**
* Бітовий запис символу
*
* @param NULL
* @return Csymb, повертає символ
*/
char getsymb();
/**
* Видалення вузла
*
* @param arr, вказівник на зв'язний список
* @return 0, за задовільних умов
*/
int DeleteStuff(struct Stuff** arr);
/**
* Виведення всіх вузлів
*
* @param arr, вказівник на зв'язний список
* @return void
*/
void PrintAll(struct Stuff** arr);
/**
* Зміна вузла за його Id
*
* @param ptr, вузел зв'язного списку
* @return void
*/
void ChangeSet(struct Stuff* ptr);
/**
* Пошук вузла за його Id
*
* @param ptr, вузел зв'язного списку
* @return void
*/
void PrintId(struct Stuff* ptr);
/**
* Виведення усіх товарів, що постачаються заданим постачальником.
*
* @param ptr, вузел зв'язного списку
* @return 0, за задовільних умов
*/
int PrintFrom(struct Stuff* ptr);
/**
* Виведення усіх товарів заданої групи, ціна яких нижче за задану.
*
* @param ptr, вузел зв'язного списку
* @return 0, за задовільних умов
*/
int GroupPriceFall(struct Stuff* ptr);
/**
* Зчитує інформацію з бд, та заносить її в зв'язний список
*
* @param arr, вказівник на зв'язний список
* @param pcsv, вказівник на файл
* @return 0, за задовільних умов
*/
int readDataFromFile(struct Stuff** arr, FILE* pcsv);
/**
* Зчитує інформацію із структури, та заносить її в бд
*
* @param arr, вказівник на зв'язний список
* @param pcsv, вказівник на файл
* @return 0, за задовільних умов
*/
int writeDataToFile(struct Stuff** arr);
/**
* Зчитує інформацію із зв'зного списку, та заносить її в бд
*
* @param arr, вказівник на зв'язний список
* @return count, кількість роботи
*/
int CountOfWork(struct Stuff** arr);
/**
* AddStuff але створює нові товари замість старих
*
* @param ptr, вузел зв'язного списку
* @return true, за задовільних умов
*/
bool TheDogma(struct Stuff* ptr);