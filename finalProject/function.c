#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatype.h"
#include <ctype.h>

struct User users[100];
int userCount = 0;



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

// Hàm kiểm tra số điện thoại có hợp lệ không (chỉ chứa số và không dài quá 12 ký tự)
int isValidPhone(const char *phone) {
    if (strlen(phone) > 12) return 0;  // Kiểm tra chiều dài
    for (int i = 0; i < strlen(phone); i++) {
        if (!isdigit(phone[i])) {
            return 0;  // Nếu có ký tự không phải số, trả về false
        }
    }
    return 1;  // Nếu tất cả các ký tự đều là số, trả về true
}
// Định nghĩa mảng users và biến userCount


void cleanString(char *str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] == '|') {
            str[i] = '_';  // Thay thế ký tự '|' bằng '_'
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
        fprintf(file, "USER|%s|%s|%02d-%02d-%04d|%d|%s|%s|%d|%s|%.2f|%s\n",
                users[i].userId, users[i].name,
                users[i].dateOfBirth.day, users[i].dateOfBirth.month, users[i].dateOfBirth.year,
                users[i].gender, users[i].phone, users[i].email,
                users[i].status, users[i].password,
                users[i].balance, users[i].username);

        for (int j = 0; j < 100; j++) {
            if (users[i].transactionHistory[j].amount > 0) {
                cleanString(users[i].transactionHistory[j].type);
                cleanString(users[i].transactionHistory[j].message);
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

    char line[256];
    userCount = 0;
    struct User tempUser;
    int transactionIndex = 0;

    while (fgets(line, sizeof(line), file)) {
        char type[20];
        sscanf(line, "%[^|]", type);

        if (strcmp(type, "USER") == 0) {
            sscanf(line, "USER|%[^|]|%[^|]|%d-%d-%d|%d|%[^|]|%[^|]|%d|%[^|]|%f|%[^|]",
                   tempUser.userId, tempUser.name,
                   &tempUser.dateOfBirth.day, &tempUser.dateOfBirth.month, &tempUser.dateOfBirth.year,
                   &tempUser.gender, tempUser.phone, tempUser.email,
                   &tempUser.status, tempUser.password,
                   &tempUser.balance, tempUser.username);

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
                   users[i].dateOfBirth.day,  
                   users[i].dateOfBirth.month,  
                   users[i].dateOfBirth.year);  

            printf("\n--- Account Information ---\n");  
            printf("Balance      : %.2f\n", users[i].balance);  
            printf("Username     : %s\n", users[i].username);  

            // Removed Transaction History section  

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
    
    while (!valid) {  // Tiếp tục yêu cầu nhập nếu dữ liệu không hợp lệ
        printf("Enter Name: ");
        getchar();  // Để bỏ qua ký tự thừa
        fgets(newUser.name, sizeof(newUser.name), stdin);
        newUser.name[strcspn(newUser.name, "\n")] = 0;  // Loại bỏ ký tự newline

        // Kiểm tra tên có chứa số không
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

        // Kiểm tra User ID không chứa chữ
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
        // Kiểm tra số điện thoại có hợp lệ không
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

        // Nhập ngày sinh
        printf("Enter Date of Birth (DD MM YYYY): ");
        scanf("%d %d %d", &newUser.dateOfBirth.day, &newUser.dateOfBirth.month, &newUser.dateOfBirth.year);
        
        if (newUser.dateOfBirth.year < 1900 || newUser.dateOfBirth.year > 2025 || 
            newUser.dateOfBirth.month < 1 || newUser.dateOfBirth.month > 12 || 
            newUser.dateOfBirth.day < 1 || newUser.dateOfBirth.day > 31) {
            printf("Invalid date of birth!\n");
            continue;
        }

        // Kiểm tra dữ liệu người dùng đã hợp lệ, thoát khỏi vòng lặp
        valid = 1;
    }

    newUser.status = 0;  // Mặc định người dùng mới có trạng thái "Mở"
    strcpy(newUser.password, newUser.phone);  // Mật khẩu mặc định là số điện thoại

    if (isDuplicateUser(newUser)) {
        printf("User ID, phone number, or email is already taken!\n");
        return;
    }
    
    users[userCount++] = newUser;  // Thêm người dùng vào danh sách
    saveUserData();  // Lưu dữ liệu vào file
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