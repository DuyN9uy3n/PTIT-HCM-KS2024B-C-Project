#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"
#include <conio.h>

void inputPassword(char* password, int maxLength) {
    char ch;
    int i = 0;
    
    while (1) {
        ch = getch();  
        if (ch == '\r') 
            break;
        else if (ch == '\b') {   
            if (i > 0) {  
                i--;  
                printf("\b \b");   
            }  
        } else if (i < maxLength - 1) {  
            password[i++] = ch;  
            printf("*");  
        }  
    }  
    password[i] = '\0';
}  

int main() {  
    loadUserData();   

    int role, choice;  
    while (1) {  
        printf("\n*** BANK MANAGEMENT SYSTEM ***\n");  
        printf("============================\n");  
        printf("[1] Admin\n");  
        printf("[2] User\n");  
        printf("[0] Exit\n");  
        printf("============================\n");  
        printf("Enter Your Choice: ");  
        scanf("%d", &role);  
        
        while (getchar() != '\n');  

        if (role == 1) {  // Admin login  
            char email[50], password[20];  
            printf("\nEmail: ");  
            scanf("%s", email);  
            printf("Password: ");  
            inputPassword(password, sizeof(password));  

            if (strcmp(email, "admin@gmail.com") != 0 || strcmp(password, "admin123") != 0) {  
                printf("Login failed! Please try again.\n");  
                continue;  
            }  
            system("cls");
            do {  
                printf("\n*** ADMIN MENU ***\n");  
                printf("============================\n");  
                printf("[1] Add A New User\n");  
                printf("[2] Show All Users\n");  
                printf("[3] Lock (Unlock) A User\n");  
                printf("[4] Search User By Name\n");  
                printf("[5] View User Details By ID\n");  
                printf("[6] Sort User List\n");  
                printf("[7] Exit\n");  
                printf("============================\n");  
                printf("Enter Your Choice: ");  
                scanf("%d", &choice);  
                switch (choice) {  
                    case 1:  
                        system("cls");  
                        addUser();  
                        saveUserData();  
                        break;  
                    case 2:  
                        system("cls");  
                        displayUserList();  
                        break;  
                    case 3:  
                        system("cls");  
                        toggleUserStatus();  
                        break;  
                    case 4:  
                        system("cls");  
                        char searchName[50];  
                        printf("Enter name to search: ");  
                        scanf("%s", searchName);  
                        searchUserByName(searchName);  
                        break;  
                    case 5:  
                        system("cls");  
                        char userId[10];  
                        printf("Enter User ID: ");  
                        scanf("%s", userId);  
                        displayUserDetails(userId);  
                        break;  
                    case 6:  
                        system("cls");  
                        sortUserList();  
                        break;  
                    case 7:  
                        system("cls");   
                        printf("Exiting Admin Menu...\n");  
                        return 0;  
                    default:  
                        printf("Invalid choice! Please try again.\n");  
                }  
            } while (choice != 7);  
        } else if (role == 2) {  // User login
            char email[50], password[20];
            printf("\nEnter Email: ");
            scanf("%s", email);
            printf("Enter Pass: ");
            scanf("%s", password);

            struct User *loggedInUser = NULL;
            for (int i = 0; i < userCount; i++) {
                if (strcmp(users[i].email, email) == 0 && strcmp(users[i].password, password) == 0) {
                    loggedInUser = &users[i];
                    printf("\nLogin Successful!\n");
                    break;
                }
            }

            if (loggedInUser == NULL) {
                printf("Invalid login. Please check your email and phone number.\n");
            } else if (loggedInUser->status) {
                printf("Your account is locked.\n");
            } else {
                displayAccountMenu(loggedInUser);
            }
        } else if (role == 0) {
            printf("Exiting system...\n");
            break;
        } else {
            printf("Invalid choice! Please try again.\n");
        }
    }  
    return 0;
}
