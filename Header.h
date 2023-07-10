/*
Файл: Header.h
Автор: Трофімов Дмитро Романович
Дата создания: 01.07.2023
*/
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define MAX_RECORDS 100
#define maxlandkey 17
struct route {
    char Sp[50];
    char Ep[50];
    int routeLvl;
    int RouteNum;
    struct route* next;
};
extern struct route* head;
extern struct route routes[MAX_RECORDS];
extern int count;
void generateLicenseKey(char* licenseKey);
void createEmptyDatabaseFile();
void createConfigurationFile(const char* filename, const char* licenseKey);
void readConfigurationFile(const char* filename, char* databaseFile, char* licenseKey);
void freeMemory();
void addRoute(const char* Sp, const char* Ep, int routeLvl, int RouteNum);
void printAllRoutes();
void deleteRoute(int routeNum);
void readLicenseKeyFromUser(char* userLicenseKey);
void printRoutesByStartPoint(const char* startPoint);
void printRoutesByEndPointAndDifficulty(const char* endPoint, int minDifficulty, int maxDifficulty);

#endif  // FUNCTIONS_H
