#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

int main() {
    int role, choice;
    loadUserData();

    while (1) {
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

            while (1) {
                printf("\n*** ADMIN MENU ***\n");
                printf("============================\n");
                printf("[1] Add A New User\n");
                printf("[2] Show All Users\n");
                printf("[3] Lock (Unlock) A User\n");
                printf("[4] Search User By Name\n");
                printf("[5] Exit\n");
                printf("============================\n");
                printf("Enter Your Choice: ");
                scanf("%d", &choice);
                
                switch (choice) {
                    case 1: addUser(); break;
                    case 2: displayUserList(); break;
                    case 3: toggleUserStatus(); break;
                    case 4: {
                        char searchName[50];
                        printf("Enter name to search: ");
                        scanf("%s", searchName);
                        searchUserByName(searchName);
                        break;
                    }
                    case 5:
                        saveUserData();
                        return 0;
                    default:
                        printf("Invalid choice!\n");
                }
            }
        }
    }
}
