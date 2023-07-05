#ifndef FNCTS_H
#define FNCTS_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define scanf scanf_s

#define CONFIG_FILE "RGR.cfg"

int generateUniqueId();
void clearInputBuffer();



void addAnnouncement();
void deleteAnnouncement(int id);
void viewAnnouncements();
void updateAnnouncement(int id);
int saveDatabase();
void loadDatabase();
int exportDatabaseCSV();
void updateConfig(char* key, char* value);
void viewAnnouncementsByCity(char* city);
void viewAnnouncementsByPrice(float maxPrice);
void printDataDescription();
void generateLicenseKey(char* licenseKey);
#endif