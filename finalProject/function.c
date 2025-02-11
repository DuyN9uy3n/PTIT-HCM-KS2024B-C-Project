#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

struct User users[100];
int userCount = 0;

void loadUserData() {
    FILE *file = fopen("data/user.bin", "rb");
    if (file) {
        fread(&users, sizeof(struct User), 100, file);
        fclose(file);
        userCount = 100;
    }
}

bool validateUserInput(struct User user) {
 
    if (strlen(user.userId) == 0 || strlen(user.phone) == 0 || strlen(user.email) == 0 || strlen(user.name) == 0) {
        return false; 
    }
    return true;
}

void saveUserData() {
    FILE *file = fopen("data/user.bin", "wb");
    fwrite(&users, sizeof(struct User), userCount, file);
    fclose(file);
}

void displayUserList() {
    printf("\n*** User List ***\n");
    printf("=======================================================================================\n");
    printf("| %-10s | %-20s | %-25s | %-12s | %-6s |\n", "ID", "Name", "Email", "Phone", "Status");
    printf("---------------------------------------------------------------------------------------\n");

    for (int i = 0; i < userCount; i++) {
        printf("| %-10s | %-20s | %-25s | %-12s | %-6s |\n",
               users[i].userId,
               users[i].name,
               users[i].email,
               users[i].phone,
               users[i].status ? "Locked" : "Open");
    }

    printf("========================================================================================\n");
}

bool isValidLength(const char *input, int maxLength) {
    return strlen(input) > 0 && strlen(input) <= maxLength;
}

void searchUserByName(char *name) {
    printf("Searching for '%s'...\n", name);
    int found = 0;
    printf("========================================================================================\n");
    printf("| %-10s | %-20s | %-25s | %-12s | %-6s |\n", "ID", "Name", "Email", "Phone", "Status");
    printf("----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < userCount; i++) {
        if (strstr(users[i].name, name) != NULL) {
            printf("| %-10s | %-20s | %-25s | %-12s | %-6s |\n",
                   users[i].userId,
                   users[i].name,
                   users[i].email,
                   users[i].phone,
                   users[i].status ? "Locked" : "Open");
            found = 1;
        }
    }
    if (!found) {
        printf("No users found matching '%s'.\n", name);
    }
    printf("========================================================================================\n");
}

bool isDuplicateUser(struct User user) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].userId, user.userId) == 0 || 
            strcmp(users[i].phone, user.phone) == 0 || 
            strcmp(users[i].email, user.email) == 0 || 
            strcmp(users[i].name, user.name) == 0) {
            return true;
        }
    }
    return false;
}

void addUser() {
    if (userCount >= 100) {
        printf("Maximum user limit reached.\n");
        return;
    }

    struct User newUser;

    printf("Enter Name: ");
    getchar();
    fgets(newUser.name, sizeof(newUser.name), stdin);
    newUser.name[strcspn(newUser.name, "\n")] = 0;
    if (strlen(newUser.name) == 0) {
        printf("Name cannot be empty!\n");
        return;
    }

    printf("Enter User ID: ");
    fgets(newUser.userId, sizeof(newUser.userId), stdin);
    newUser.userId[strcspn(newUser.userId, "\n")] = 0;
    if (strlen(newUser.userId) == 0) {
        printf("User ID cannot be empty!\n");
        return;
    }

    printf("Enter Phone: ");
    fgets(newUser.phone, sizeof(newUser.phone), stdin);
    newUser.phone[strcspn(newUser.phone, "\n")] = 0;
    if (strlen(newUser.phone) == 0) {
        printf("Phone cannot be empty!\n");
        return;
    }

    printf("Enter Email: ");
    fgets(newUser.email, sizeof(newUser.email), stdin);
    newUser.email[strcspn(newUser.email, "\n")] = 0;
    if (strlen(newUser.email) == 0) {
        printf("Email cannot be empty!\n");
        return;
    }

    newUser.status = 0; 
    strcpy(newUser.password, newUser.phone); // Đặt mặc định password là số điện thoại

    if (!isValidLength(newUser.userId, 10) || 
        !isValidLength(newUser.phone, 12) || 
        !isValidLength(newUser.email, 30) || 
        !isValidLength(newUser.name, 50)) {
        printf("Invalid input length!\n");
        return;
    }

    if (isDuplicateUser(newUser)) {
        printf("User ID, phone number, or email is already taken!\n");
        return;
    }
    users[userCount++] = newUser;
    saveUserData();
    printf("User added successfully!\n");
}


void toggleUserStatus() {
    char userId[10];
    printf("\n*** Lock (Unlock) an user ***\n");
    printf("Enter an user id: ");
    scanf("%s", userId);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].userId, userId) == 0) {
            printf("User found: %s\n", userId);
            printf("Current status: %s. Change status? (y/n): ", users[i].status ? "Locked" : "Open");

            char confirm;
            scanf(" %c", &confirm);
            if (confirm == 'y' || confirm == 'Y') {
                users[i].status = !users[i].status;
                saveUserData();
                printf("Status changed successfully!\n");
            }
            return;
        }
    }
    printf("No user found for ID: %s\n", userId);
}
