#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

int main() {
    int role, choice;
    loadUserData();

    while (1) {
        // Màn hình login
        printf("\n*** BANK MANAGEMENT SYSTEM ***\n");
        printf("============================\n");
        printf("[1] Admin\n");
        printf("[2] User\n");
        printf("[0] Exit\n");
        printf("============================\n");
        printf("Enter Your Choice: ");
        scanf("%d", &role);

        if (role == 1) {
            char email[50], password[20];
            printf("\nEmail: ");
            scanf("%s", email);
            printf("Password: ");
            scanf("%s", password);

            if (strcmp(email, "admin@gmail.com") != 0 || strcmp(password, "admin123") != 0) {
                printf("Login failed!\n");
                continue;
            }
            system("cls");

            while (1) {
                printf("\n*** ADMIN MENU ***\n");
                printf("============================\n");
                printf("[1] Add A New User\n");
                printf("[2] Show All Users\n");
                printf("[3] Lock (Unlock) A User\n");
                printf("[4] Search User By Name\n");
                printf("[5] View User Details By ID\n");
                printf("[6] Exit\n");
                printf("============================\n");
                printf("Enter Your Choice: ");
                scanf("%d", &choice);

                switch (choice) {
                    case 1:
                        system("cls");
                        addUser();
                        break;
                    case 2:
                        system("cls");
                        displayUserList();
                        break;
                    case 3:
                        system("cls");
                        toggleUserStatus();
                        break;
                    case 4: {
                        char searchName[50];
                        printf("Enter name to search: ");
                        scanf("%s", searchName);
                        system("cls");
                        searchUserByName(searchName);
                        break;
                    }
                    case 5: {
                        char userId[10];
                        printf("Enter User ID: ");
                        scanf("%s", userId);
                        system("cls");
                        displayUserDetails(userId);
                        break;
                    }
                    case 6:
                        system("cls");
                        saveUserData();
                        printf("Exiting Admin Menu...\n");
                        return 0;
                    default:
                        printf("Invalid choice! Returning to Admin Menu...\n");
                }

                printf("\n[1] Return to Admin Menu\n");
                printf("[0] Exit\n");
                int exitChoice;
                printf("Enter choice: ");
                scanf("%d", &exitChoice);
                if (exitChoice == 0) {
                    saveUserData();
                    return 0; 
                } else {
                    system("cls"); 
            }
        }
    }
}
}
