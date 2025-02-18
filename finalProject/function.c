#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatype.h"
#include <ctype.h>

struct User users[100];
int userCount = 0;


//ham chuyen tien
void transferMoney(struct User *sender) {
    char receiverId[10]; //id nguoi nhan 
    double amount;
    char transferId[10]; //id giao dich
    
    printf("\nEnter transaction ID: ");
    scanf("%s", transferId);
    
    printf("Enter receiver's User ID: ");
    scanf("%s", receiverId);

    // duyet qua ds user tim ID trung ID nguoi nhan 
    struct User *receiver = NULL;
	// gan ptr receiver tro den tai khoan nguoi nhan neu tim thay
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].userId, receiverId) == 0) {
            receiver = &users[i];
            break;
        }
    }

    if (receiver == NULL) {
        printf("Error: Receiver's account does not exist.\n");
        return;
    }

    printf("Enter the amount to transfer: ");
    scanf("%lf", &amount);
    
    if (amount <= 0) {
        printf("Amount must be greater than zero.\n");
        return;
    }

    if (amount > sender->balance) {
        printf("Insufficient funds.\n");
        return;
    }

    // Giảm số dư tài khoản người gửi
    sender->balance -= amount;

    // Tăng số dư tài khoản người nhận
    receiver->balance += amount;

    // Cập nhật giao dịch cho người gửi
    struct Transaction senderTransaction;
    strcpy(senderTransaction.transferId, transferId);
    strcpy(senderTransaction.type, "transfer");
    senderTransaction.amount = amount;
    senderTransaction.transactionDate = (struct Date){ 18, 2, 2025 };  // Set the current date, can be dynamic
    strcpy(senderTransaction.message, "Transferred to: ");
    strcat(senderTransaction.message, receiverId);

    // Thêm giao dịch vào lịch sử của người gửi
    for (int i = 0; i < 100; i++) {
        if (sender->transactionHistory[i].amount == 0) {
            sender->transactionHistory[i] = senderTransaction;
            break;
        }
    }

    // Cập nhật giao dịch cho người nhận
    struct Transaction receiverTransaction;
    strcpy(receiverTransaction.transferId, transferId);
    strcpy(receiverTransaction.type, "transfer");
    receiverTransaction.amount = amount;
    receiverTransaction.transactionDate = (struct Date){ 18, 2, 2025 };  // Set the current date, can be dynamic
    strcpy(receiverTransaction.message, "Received from: ");
    strcat(receiverTransaction.message, sender->userId);

    // Thêm giao dịch vào lịch sử của người nhận
    for (int i = 0; i < 100; i++) {
        if (receiver->transactionHistory[i].amount == 0) {
            receiver->transactionHistory[i] = receiverTransaction;
            break;
        }
    }

    printf("Transfer successful. Your new balance is: %.2f\n", sender->balance);
    printf("Receiver's new balance is: %.2f\n", receiver->balance);
    
    // Lưu lại dữ liệu người dùng
    saveUserData();
}


void depositMoney(struct User *user) {
    double amount;
    char transferId[10];
    printf("\nEnter transaction ID: ");
    scanf("%s", transferId);
    
    printf("Enter the amount to deposit: ");
    scanf("%lf", &amount);
    
    if (amount <= 0) {
        printf("Amount must be greater than zero.\n");
        return;
    }

    user->balance += amount;

    struct Transaction newTransaction;
    strcpy(newTransaction.transferId, transferId);
    strcpy(newTransaction.type, "deposit");
    newTransaction.amount = amount;
    newTransaction.transactionDate = (struct Date){ 18, 2, 2025 }; 
    strcpy(newTransaction.message, "Deposit transaction successful");

    for (int i = 0; i < 100; i++) {
        if (user->transactionHistory[i].amount == 0) {
            user->transactionHistory[i] = newTransaction;
            break;
        }
    }

    printf("Deposit successful. Your new balance is: %.2f\n", user->balance);
}


void withdrawMoney(struct User *user) {
    double amount;
    char transferId[10];
    
    printf("\nEnter transaction ID: ");
    scanf("%s", transferId);

    printf("Enter the amount to withdraw: ");
    scanf("%lf", &amount);
    
    if (amount <= 0) {
        printf("Amount must be greater than zero.\n");
        return;
    }

    if (amount > user->balance) {
        printf("Insufficient funds.\n");
        return;
    }

    user->balance -= amount;

    struct Transaction newTransaction;
    strcpy(newTransaction.transferId, transferId);
    strcpy(newTransaction.type, "withdraw");
    newTransaction.amount = amount;
    newTransaction.transactionDate = (struct Date){ };  
    strcpy(newTransaction.message, "Withdrawal transaction successful");

    for (int i = 0; i < 100; i++) {
        if (user->transactionHistory[i].amount == 0) {
            user->transactionHistory[i] = newTransaction;
            break;
        }
    }

    printf("Withdrawal successful. Your new balance is: %.2f\n", user->balance);
}



void displayAccountMenu(struct User *loggedInUser) {
    int choice;
    do {
        printf("\n*** ACCOUNT MANAGEMENT MENU ***\n");
        printf("===================================\n");
        printf("[1] View Account Details\n");
        printf("[2] Deposit Money\n");
        printf("[3] Withdraw Money\n");
        printf("[4] Transfer Money\n");  // Thêm chức năng chuyển tiền
        printf("[5] Edit Personal Information\n");
        printf("[6] Exit\n");
        printf("===================================\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                system("cls");
                displayAccountDetails(loggedInUser);
                break;
            case 2:
                system("cls");
                depositMoney(loggedInUser);
                break;
            case 3:
                system("cls");
                withdrawMoney(loggedInUser);
                break;
            case 4:
                system("cls");
                transferMoney(loggedInUser);  // Thực hiện chuyển tiền
                break;
            case 5:
                system("cls");
                editUserInfo(loggedInUser);
                break;
            case 6:
                printf("Exiting Account Management...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 6);
}



void displayAccountDetails(struct User *user) {
    printf("\n================ Account Details ================\n");
    printf("User ID      : %s\n", user->userId);
    printf("Name         : %s\n", user->name);
    printf("Email        : %s\n", user->email);
    printf("Phone        : %s\n", user->phone);
    printf("Status       : %s\n", user->status ? "Locked" : "Open");
    printf("Balance      : %.2f\n", user->balance);
    printf("Username     : %s\n", user->username);

    printf("\n--- Transaction History ---\n");
    printf("===============================================\n");
    
    int hasTransaction = 0;
//    for (int i = 0; i < 100; i++) {
//        if (user->transactionHistory[i].amount > 0) {
//            printf("Transaction ID: %s | To: %s | Amount: %.2f | Type: %s | Date: %02d-%02d-%04d\n",
//                   user->transactionHistory[i].transferId,
//                   user->transactionHistory[i].receivingId,
//                   user->transactionHistory[i].amount,
//                   user->transactionHistory[i].type,
//                   user->transactionHistory[i].transactionDate.day,
//                   user->transactionHistory[i].transactionDate.month,
//                   user->transactionHistory[i].transactionDate.year);
//            hasTransaction = 1;
//        }
//    }

    if (!hasTransaction) {
        printf("No transaction history found.\n");
    }

    printf("===============================================\n");
}



void editUserInfo(struct User *user) {  
    int choice;  
    do {  
        printf("\n*** Edit Account Information ***\n");  
        printf("===================================\n");  
        printf("[1] Change Password\n");  
        printf("[2] Update Personal Information\n");  
        printf("[3] Exit\n");  
        printf("===================================\n");  
        printf("Enter Your Choice: ");  
        
        scanf("%d", &choice);  
        getchar(); 

        switch (choice) {
            case 1: {
                char oldPassword[20], newPassword[20], confirmPassword[20];
                int passwordMatched = 0;

                printf("\nYour current password is your phone number.\n");

                while (!passwordMatched) {
                    printf("\nEnter your current password: ");
                    scanf("%s", oldPassword);

                    if (strcmp(oldPassword, user->password) != 0) {
                        printf("Incorrect password! Please try again.\n");
                    } else {
                        passwordMatched = 1;
                    }
                }

                int passwordConfirmed = 0;
                while (!passwordConfirmed) {
                    printf("\nEnter new password (at least 6 characters): ");
                    scanf("%s", newPassword);
                    if (strlen(newPassword) < 6) {
                        printf("Password must be at least 6 characters long!\n");
                        continue;
                    }
                    printf("Re-enter new password: ");
                    scanf("%s", confirmPassword);

                    if (strcmp(newPassword, confirmPassword) != 0) {
                        printf("Passwords do not match! Please try again.\n");
                    } else {
                        strcpy(user->password, newPassword);
                        saveUserData();
                        passwordConfirmed = 1;
                    }
                }

                printf("Password updated successfully!\n");
                break;
            }

            case 2: {
                char temp[100];  
                printf("\nCurrent Information:\n");  
                printf("Name: %s\n", user->name);  
                printf("Email: %s\n", user->email);  
                printf("Phone: %s\n", user->phone);  
                printf("(Your current password is your phone number)\n");  
 
                do {  
                    printf("\nEnter new Name (or press Enter to keep current): ");  
                    fgets(temp, sizeof(temp), stdin);  
                    temp[strcspn(temp, "\n")] = 0;  
                    if (strlen(temp) > 0) { 
                        if (!isValidName(temp)) {  
                            printf("Name cannot contain numbers!\n");  
                            continue;  
                        }  
                        strcpy(user->name, temp);  
                    }  
                } while (strlen(temp) == 0 && printf("Name cannot be empty! Please enter again.\n"));  

                do {  
                    printf("Enter new Email (or press Enter to keep current): ");  
                    fgets(temp, sizeof(temp), stdin);  
                    temp[strcspn(temp, "\n")] = 0;
                    if (strlen(temp) > 0) {  
                        if (strchr(temp, '@') != NULL && strchr(temp, '.') != NULL) {  
                            strcpy(user->email, temp);  
                        } else {  
                            printf("Invalid email format! Please enter again.\n");  
                        }  
                    }  
                } while (strlen(temp) == 0 || (strchr(temp, '@') == NULL || strchr(temp, '.') == NULL));  

                do {  
                    printf("Enter new Phone (or press Enter to keep current): ");  
                    fgets(temp, sizeof(temp), stdin);  
                    temp[strcspn(temp, "\n")] = 0;  
                    if (strlen(temp) > 0) {  
                        if (isValidPhone(temp)) {  
                            strcpy(user->phone, temp);  
                        } else {  
                            printf("Phone number must be a valid number and less than or equal to 12 digits!\n");  
                        }  
                    }  
                } while (strlen(temp) > 0 && !isValidPhone(temp));  
 
                saveUserData();  
                printf("Information updated successfully!\n");  
                break;  
            }  

            case 3:  
                printf("Exiting Edit Menu...\n");  
                break;  

            default:  
                printf("Invalid choice! Please try again.\n");  
        }  
    } while (choice != 3);  
}  



int isValidUserId(const char *userId) {
    for (int i = 0; i < strlen(userId); i++) {
        if (isalpha(userId[i])) { 
            return 0;
        }
    }
    return 1;
}

int isValidName(const char *name) {
    for (int i = 0; i < strlen(name); i++) {
        if (isdigit(name[i])) {
            return 0;
        }
    }
    return 1;
}

int isValidPhone(const char *phone) {
    if (strlen(phone) > 12) return 0;
    for (int i = 0; i < strlen(phone); i++) {
        if (!isdigit(phone[i])) {
            return 0; 
        }
    }
    return 1; 
}


void cleanString(char *str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] == '|') {
            str[i] = '_';
        }
    }
}

void saveUserData() {
    FILE *file = fopen("data/user.txt", "w");
    if (!file) {
        printf("Error: Could not open file for writing.\n");
        return;
    }

    for (int i = 0; i < userCount; i++) {
        fprintf(file, "USER|%s|%s|%02d-%02d-%04d|%d|%s|%s|%d|%s|%.2f|\n",
                users[i].userId, users[i].name,
                users[i].dateOfBirth.day, users[i].dateOfBirth.month, users[i].dateOfBirth.year,
                users[i].gender, users[i].phone, users[i].email,
                users[i].status, users[i].password,
                users[i].balance);

        for (int j = 0; j < 100; j++) {
            if (users[i].transactionHistory[j].amount > 0) {
                fprintf(file, "TRANSACTION|%s|%s|%.2f|%s|%s|%02d-%02d-%04d\n",
                        users[i].transactionHistory[j].transferId,
                        users[i].transactionHistory[j].receivingId,
                        users[i].transactionHistory[j].amount,
                        users[i].transactionHistory[j].type,
                        users[i].transactionHistory[j].message,
                        users[i].transactionHistory[j].transactionDate.day,
                        users[i].transactionHistory[j].transactionDate.month,
                        users[i].transactionHistory[j].transactionDate.year);
            }
        }
    }

    fclose(file);
    printf("User data saved successfully!\n");
}





void loadUserData() {
    FILE *file = fopen("data/user.txt", "r");
    if (!file) {
        printf("Error: Could not open file for reading.\n");
        return;
    }

    char line[512];
    userCount = 0;
    struct User tempUser;
    int transactionIndex = 0;

    while (fgets(line, sizeof(line), file)) {
        char type[20];
        sscanf(line, "%[^|]", type);

        if (strcmp(type, "USER") == 0) {
            sscanf(line, "USER|%[^|]|%[^|]|%d-%d-%d|%d|%[^|]|%[^|]|%d|%[^|]|%f|",
                   tempUser.userId, tempUser.name,
                   &tempUser.dateOfBirth.day, &tempUser.dateOfBirth.month, &tempUser.dateOfBirth.year,
                   &tempUser.gender, tempUser.phone, tempUser.email,
                   &tempUser.status, tempUser.password,
                   &tempUser.balance);

            users[userCount] = tempUser;
            transactionIndex = 0;
            userCount++;
        } else if (strcmp(type, "TRANSACTION") == 0) {
            struct Transaction transaction;
            sscanf(line, "TRANSACTION|%[^|]|%[^|]|%lf|%[^|]|%[^|]|%d-%d-%d",
                   transaction.transferId, transaction.receivingId,
                   &transaction.amount, transaction.type, transaction.message,
                   &transaction.transactionDate.day, &transaction.transactionDate.month, &transaction.transactionDate.year);

            if (transactionIndex < 100) {
                users[userCount - 1].transactionHistory[transactionIndex] = transaction;
                transactionIndex++;
            }
        }
    }

    fclose(file);
    printf("User data loaded successfully! Found %d users.\n", userCount);
}



void displayUserList() {  
    printf("\n*** User List ***\n");  
    printf("===============================================================================================================\n");  
    printf("| %-10s | %-20s | %-25s | %-12s | %-14s | %-6s |\n", "ID", "Name", "Email", "Phone", "Date of Birth", "Status");  
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
    do {  
        printf("[1] Return to Admin Menu\n");  
        printf("[0] Exit\n");  
        printf("Enter choice: ");  
        scanf("%d", &choice);  

        if (choice == 0) {  
            printf("Exiting...\n");  
            exit(0);
        } else if (choice == 1) {  
            break;
        } else {  
            printf("Invalid choice! Please try again.\n");  
        }  
    } while (choice != 0); 
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
                   users[i].dateOfBirth.day,  
                   users[i].dateOfBirth.month,  
                   users[i].dateOfBirth.year);  

            printf("\n--- Account Information ---\n");  
            printf("Balance      : %.2f\n", users[i].balance);  
            printf("Username     : %s\n", users[i].username);  

            found = 1;  
            break;  
        }  
    }  

    if (!found) {  
        printf("No user found with ID: %s\n", userId);  
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
    struct User newUser;  
    int valid = 0;  
    
    while (!valid) {  
        printf("Enter Name: ");  
        getchar(); 
        fgets(newUser.name, sizeof(newUser.name), stdin);  
        newUser.name[strcspn(newUser.name, "\n")] = 0;  

        if (strlen(newUser.name) == 0) {  
            printf("Name cannot be empty!\n");  
            continue;  
        }  
        if (!isValidName(newUser.name)) {  
            printf("Name cannot contain numbers!\n");  
            continue;  
        }  

        printf("Enter User ID: ");  
        fgets(newUser.userId, sizeof(newUser.userId), stdin);  
        newUser.userId[strcspn(newUser.userId, "\n")] = 0;  

        if (strlen(newUser.userId) == 0) {  
            printf("User ID cannot be empty!\n");  
            continue;  
        }  
        if (!isValidUserId(newUser.userId)) {  
            printf("User ID cannot contain letters!\n");  
            continue;  
        }  

        printf("Enter Phone: ");  
        fgets(newUser.phone, sizeof(newUser.phone), stdin);  
        newUser.phone[strcspn(newUser.phone, "\n")] = 0;  

        if (strlen(newUser.phone) == 0 || !isValidPhone(newUser.phone)) {  
            printf("Phone number must be a valid number and less than or equal to 12 digits!\n");  
            continue;  
        }  

        printf("Enter Email: ");  
        fgets(newUser.email, sizeof(newUser.email), stdin);  
        newUser.email[strcspn(newUser.email, "\n")] = 0;  
        if (strlen(newUser.email) == 0) {  
            printf("Email cannot be empty!\n");  
            continue;  
        }  
 
        printf("Enter Date of Birth (DD MM YYYY): ");  
        scanf("%d %d %d", &newUser.dateOfBirth.day, &newUser.dateOfBirth.month, &newUser.dateOfBirth.year);  
        
        if (newUser.dateOfBirth.year < 1900 || newUser.dateOfBirth.year > 2025 ||   
            newUser.dateOfBirth.month < 1 || newUser.dateOfBirth.month > 12 ||   
            newUser.dateOfBirth.day < 1 || newUser.dateOfBirth.day > 31) {  
            printf("Invalid date of birth!\n");  
            continue;  
        }  

        valid = 1;
    }  

    newUser.status = 0;
    strcpy(newUser.password, newUser.phone);   

    if (isDuplicateUser(newUser)) {  
        printf("User ID, phone number, or email is already taken!\n");  
        return;  
    }  
    
    users[userCount++] = newUser; 
    saveUserData();  
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

void sortUserList() {
    int choice;
    printf("\n*** Sort User List ***\n");
    printf("============================\n");
    printf("[1] Sort by ID Ascending\n");
    printf("[2] Sort by ID Descending\n");
    printf("============================\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        for (int i = 0; i < userCount - 1; i++) {
            for (int j = i + 1; j < userCount; j++) {
                if (strcmp(users[i].userId, users[j].userId) > 0) {
                    struct User temp = users[i];
                    users[i] = users[j];
                    users[j] = temp;
                }
            }
        }
        printf("User list sorted by ID in ascending order.\n");
    } else if (choice == 2) {
        for (int i = 0; i < userCount - 1; i++) {
            for (int j = i + 1; j < userCount; j++) {
                if (strcmp(users[i].userId, users[j].userId) < 0) {
                    struct User temp = users[i];
                    users[i] = users[j];
                    users[j] = temp;
                }
            }
        }
        printf("User list sorted by ID in descending order.\n");
    } else {
        printf("Invalid choice.\n");
        return;
    }

    displayUserList();
}