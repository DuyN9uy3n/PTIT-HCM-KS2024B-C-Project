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
    printf("===============================================================================================================\n");
    printf("| %-10s | %-20s | %-25s | %-12s | %-14s | %-6s |\n", "ID", "Name", "Email", "Phone", "Date of Birth", "Status" );
    printf("---------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < userCount; i++) {
        printf("| %-10s | %-20s | %-25s | %-12s | %02d-%02d-%04d | %-10s |\n",
               users[i].userId,
               users[i].name,
               users[i].email,
               users[i].phone,
               users[i].dateOfBirth.day, users[i].dateOfBirth.month, users[i].dateOfBirth.year,
               users[i].status ? "Locked" : "Open");
    }

    printf("===============================================================================================================\n");

    int choice;
    printf("\n[1] Return to Admin Menu\n");
    printf("[0] Exit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    
    if (choice == 0) {
        saveUserData();
        exit(0);
    } else {
        system("cls");
    }
}




void displayUserDetails(char *userId) {
    int found = 0;
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].userId, userId) == 0) {
            printf("\n================ User Details ================\n");
            printf("User ID      : %s\n", users[i].userId);
            printf("Name         : %s\n", users[i].name);
            printf("Email        : %s\n", users[i].email);
            printf("Phone        : %s\n", users[i].phone);
            printf("Status       : %s\n", users[i].status ? "Locked" : "Open");
            printf("Date of Birth: %02d-%02d-%04d\n",
                   users[i].dateOfBirth.day, users[i].dateOfBirth.month, users[i].dateOfBirth.year);

            printf("\n--- Account Information ---\n");

            struct AccountInfo account;
            FILE *file = fopen("data/account.bin", "rb");
            if (file) {
                int accountFound = 0;
                while (fread(&account, sizeof(struct AccountInfo), 1, file)) {
                    if (strcmp(account.userId, userId) == 0) {
                        printf("Balance      : %.2f\n", account.balance);
                        printf("Status       : %s\n", account.status ? "Locked" : "Open");
                        accountFound = 1;
                        break;
                    }
                }
                fclose(file);
                
                if (!accountFound) {
                    printf("No account data found for user ID: %s\n", userId);
                }
            } else {
                printf("Error: Unable to access account data. Please ensure the account data file exists and is accessible.\n");
            }

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No user found with ID: %s\n", userId);
    }

    printf("\n[1] Return to Main Menu\n");
    printf("[0] Exit\n");

    int choice;
    printf("Enter choice: ");
    scanf("%d", &choice);
    if (choice == 1) {
        return;
    } else {
        exit(0);
    }
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

    // Nhập ngày sinh
    printf("Enter Date of Birth (DD MM YYYY): ");
    scanf("%d %d %d", &newUser.dateOfBirth.day, &newUser.dateOfBirth.month, &newUser.dateOfBirth.year);

    newUser.status = 0; 
    strcpy(newUser.password, newUser.phone);

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
    printf("\n*** Lock (Unlock) a User ***\n");
    printf("Enter User ID: ");
    scanf("%s", userId);

    int found = 0;
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].userId, userId) == 0) {
            found = 1;
            printf("User found: %s\n", userId);
            printf("Current Status: %s. Do you want to change the status? (y/n): ", users[i].status ? "Locked" : "Open");

            char confirm;
            scanf(" %c", &confirm);
            if (confirm == 'y' || confirm == 'Y') {
                users[i].status = !users[i].status;
                saveUserData();
                printf("User status changed successfully!\n");
            } else {
                printf("Status change canceled.\n");
            }
            break;
        }
    }

    if (!found) {
        printf("No user found with ID: %s\n", userId);
    }
}
