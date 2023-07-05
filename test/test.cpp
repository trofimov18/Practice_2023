#include "gtest/gtest.h"
#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "..\FNCTS\FNCTS.h"
#include "..\modules\modules.c"

TEST(AnnouncementTest, AddAnnouncement) {
    // Налаштування тестових даних
    Announcement data;
    data.id = 1;
    strcpy(data.title, "Тестова назва");
    data.price = 100.0;
    strcpy(data.city, "Тестове місто");
    strcpy(data.phone, "1234567890");

    // Виклик функції для тестування
    addAnnouncement();

    // Перевірка результатів
    Node* temp = head;
    while (temp != NULL) {
        if (temp->data.id == data.id) {
            EXPECT_STREQ(temp->data.title, data.title);
            EXPECT_FLOAT_EQ(temp->data.price, data.price);
            EXPECT_STREQ(temp->data.city, data.city);
            EXPECT_STREQ(temp->data.phone, data.phone);
            break;
        }
        temp = temp->next;
    }
}
TEST(AnnouncementTest, DeleteAnnouncement) {
    // Налаштування тестових даних
    Announcement data;
    data.id = 1;
    strcpy(data.title, "Тестова назва");
    data.price = 100.0;
    strcpy(data.city, "Тестове місто");
    strcpy(data.phone, "1234567890");

    // Додавання тестових даних до зв'язного списку
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = head;
    head = newNode;

    // Виклик функції для тестування
    deleteAnnouncement(data.id);

    // Перевірка результатів
    Node* temp = head;
    while (temp != NULL) {
        EXPECT_NE(temp->data.id, data.id);
        temp = temp->next;
    }
}

TEST(AnnouncementTest, ViewAnnouncementsByCity) {
    // Налаштування тестових даних
    Announcement data1;
    data1.id = 1;
    strcpy(data1.title, "Назва1");
    data1.price = 100.0;
    strcpy(data1.city, "Місто1");
    strcpy(data1.phone, "Телефон1");

    Announcement data2;
    data2.id = 2;
    strcpy(data2.title, "Назва2");
    data2.price = 200.0;
    strcpy(data2.city, "Місто2");
    strcpy(data2.phone, "Телефон2");

    // Додавання тестових даних до зв'язного списку
    Node* newNode1 = (Node*)malloc(sizeof(Node));
    newNode1->data = data1;
    newNode1->next = head;
    head = newNode1;

    Node* newNode2 = (Node*)malloc(sizeof(Node));
    newNode2->data = data2;
    newNode2->next = head;
    head = newNode2;

    // Виклик функції для тестування
    viewAnnouncementsByCity("Місто1");

    // Перевірка виводу
    // Ви можете захопити stdout та порівняти його з очікуваним виводом, якщо хочете автоматизувати цю перевірку

    // Очищення тестових даних
    head = NULL; // Скидання зв'язного списку
    free(newNode1);
    free(newNode2);
}

TEST(AnnouncementTest, ViewAnnouncementsByPrice) {
    // Задання тестових даних
    Announcement data1;
    data1.id = 1;
    strcpy(data1.title, "Назва1");
    data1.price = 100.0;
    strcpy(data1.city, "Місто1");
    strcpy(data1.phone, "Телефон1");

    Announcement data2;
    data2.id = 2;
    strcpy(data2.title, "Назва2");
    data2.price = 200.0;
    strcpy(data2.city, "Місто2");
    strcpy(data2.phone, "Телефон2");

    Announcement data3;
    data3.id = 3;
    strcpy(data3.title, "Назва3");
    data3.price = 50.0;
    strcpy(data3.city, "Місто3");
    strcpy(data3.phone, "Телефон3");

    // Додайте тестові дані до зв'язаного списку
    Node* newNode1 = (Node*)malloc(sizeof(Node));
    newNode1->data = data1;
    newNode1->next = head;
    head = newNode1;

    Node* newNode2 = (Node*)malloc(sizeof(Node));
    newNode2->data = data2;
    newNode2->next = head;
    head = newNode2;

    Node* newNode3 = (Node*)malloc(sizeof(Node));
    newNode3->data = data3;
    newNode3->next = head;
    head = newNode3;

    // Виклик функції для тестування
    viewAnnouncementsByPrice(150.0);
    // Очистка даних тесту
    head = NULL; // Скидання зв'язаних списків
    free(newNode1);
    free(newNode2);
    free(newNode3);
}