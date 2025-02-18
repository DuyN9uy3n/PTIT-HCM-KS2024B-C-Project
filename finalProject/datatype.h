#ifndef DATATYPE_H
#define DATATYPE_H

#include <stdbool.h>

struct Date {
    int month, day, year;
};

struct Transaction {
    char transferId[10];
    char receivingId[10];
    double amount;
    char type[10];
    char message[50];
    struct Date transactionDate;
};

struct User {
    char userId[10];
    char name[20];
    struct Date dateOfBirth;
    bool gender;
    char phone[12];
    char email[20];
    bool status;
    char password[20];
    float balance;
    char username[10];
    struct Transaction transactionHistory[100];
};

extern struct User users[100];
extern int userCount;

#endif
