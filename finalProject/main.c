#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include "function.h"  
#include <conio.h>  

// Function to input password while displaying asterisks  
void inputPassword(char* password, int maxLength) {  
    char ch;  
    int i = 0;  
    
    while (1) {  
        ch = getch();  // Đọc ký tự mà không hiển thị  
        if (ch == '\r')  // Nhấn Enter (mã ASCII 13)  
            break;  
        else if (ch == '\b') {  // Nếu nhấn Backspace  
            if (i > 0) {  
                i--;  
                printf("\b \b");  // Xóa dấu * vừa in  
            }  
        } else if (i < maxLength - 1) {  
            password[i++] = ch;  
            printf("*");  // Hiển thị dấu *  
        }  
    }  
    password[i] = '\0';  // Kết thúc chuỗi  
}  

int main() {  
    loadUserData();  // Load dữ liệu người dùng từ file  

    int role, choice;  
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
        
        // Clear the input buffer to avoid reading leftover characters  
        while (getchar() != '\n');  

        // Kiểm tra quyền truy cập  
        if (role == 1) {  // Admin login  
            char email[50], password[20];  
            printf("\nEmail: ");  
            scanf("%s", email);  // Để tránh lỗi khoảng trắng, có thể thay bằng fgets  
            printf("Password: ");  
            inputPassword(password, sizeof(password));  // Gọi hàm nhập mật khẩu  

            // Kiểm tra thông tin đăng nhập của Admin  
            if (strcmp(email, "admin@gmail.com") != 0 || strcmp(password, "admin123") != 0) {  
                printf("Login failed! Please try again.\n");  
                continue;  // Quay lại vòng lặp login  
            }  
            system("cls"); // Clear screen  

            // Menu Admin  
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
                
                // Xử lý nhập liệu và kiểm tra  
                if (scanf("%d", &choice) != 1) {  
                    while (getchar() != '\n');  // Xử lý ký tự không hợp lệ trong bộ đệm  
                    printf("Invalid input! Please enter a valid number.\n");  
                    continue;  // Quay lại vòng lặp menu  
                }  

                // Tái sử dụng menu admin  
                switch (choice) {  
                    case 1:  
                        system("cls");  
                        addUser();  
                        saveUserData(); // Thêm người dùng  
                        break;  
                    case 2:  
                        system("cls");  
                        displayUserList();  // Hiển thị danh sách người dùng  
                        break;  
                    case 3:  
                        system("cls");  
                        toggleUserStatus();  // Khóa/Mở khóa người dùng  
                        break;  
                    case 4: {  
                        char searchName[50];  
                        printf("Enter name to search: ");  
                        scanf("%s", searchName);  
                        system("cls");  
                        searchUserByName(searchName);  // Tìm kiếm người dùng theo tên  
                        break;  
                    }  
                    case 5: {  
                        char userId[10];  
                        printf("Enter User ID: ");  
                        scanf("%s", userId);  
                        system("cls");  
                        displayUserDetails(userId);  // Hiển thị chi tiết người dùng theo ID  
                        break;  
                    }  
                    case 6:  
                        system("cls");  
                        sortUserList();  // Sắp xếp danh sách người dùng theo ID  
                        break;  
                    case 7:  
                        system("cls");  
                        saveUserData();  // Lưu dữ liệu người dùng  
                        printf("Exiting Admin Menu...\n");  
                        return 0;  // Thoát chương trình  
                    default:  
                        printf("Invalid choice! Please try again.\n");  
                }  

                // Quay lại menu chính hoặc thoát chương trình  
                printf("\n[1] Return to Admin Menu\n");  
                printf("[0] Exit\n");  
                int exitChoice;  
                printf("Enter choice: ");  
                if (scanf("%d", &exitChoice) != 1) {  
                    while (getchar() != '\n');  // Clear invalid input  
                    printf("Invalid input! Please enter a valid number.\n");  
                    continue;  
                }  

                if (exitChoice == 0) {  
                    saveUserData();  
                    return 0;  // Exit the program  
                } else {  
                    system("cls");  // Clear màn hình và quay lại menu Admin  
                }  

            } while (choice != 7); // Lặp lại menu cho đến khi chọn thoát  
        } else if (role == 2) {  // User login  
            char email[50], phone[12];  
            printf("\nEnter Email: ");  
            scanf("%s", email);  // Để tránh lỗi khoảng trắng, có thể thay bằng fgets  
            printf("Enter Pass: ");  
            inputPassword(phone, sizeof(phone));  // Gọi hàm nhập mật khẩu  

            // Kiểm tra thông tin đăng nhập của User  
            int found = 0;  
            for (int i = 0; i < userCount; i++) {  
                if (strcmp(users[i].email, email) == 0 && strcmp(users[i].phone, phone) == 0) {  
                    found = 1;  
                    printf("\nLogin Successful!\n");  
                    // Kiểm tra trạng thái khóa tài khoản  
                    if (users[i].status) {  
                        printf("Your account is locked.\n");  
                    } else {  
                        printf("Your account is open.\n");  
                    }  
                    break;  
                }  
            }  

            if (!found) {  
                printf("Invalid login. Please check your email and phone number.\n");  
            }
        }
    }
}