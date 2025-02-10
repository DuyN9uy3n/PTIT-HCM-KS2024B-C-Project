#include <stdio.h>  
#include <string.h>  
#include "function.h"  

struct User users[100];  
int userCount = 0;  

void loadUserData() {  
    FILE *file = fopen("data/user.bin", "rb");  
    if (file) {  
        fread(&users, sizeof(struct User), 100, file);  
        fclose(file);  
        userCount = 100; // gs co 100 nguoi dung 
    }  
}  

void saveUserData() {  
    FILE *file = fopen("data/user.bin", "wb");  
    fwrite(&users, sizeof(struct User), userCount, file);  
    fclose(file);  
}  

void displayMainMenu() {  
    printf("=== Menu Quan Ly Nguoi Dung ===\n");  
    printf("1. Hien thi danh sach nguoi dung\n");  
    printf("2. Them nguoi dung\n");  
    printf("3. Khoa/Mo khoa nguoi dung\n");  
    printf("4. Xem chi tiet nguoi dung\n");  
    printf("5. Sap xep danh sach nguoi dung\n");  
    printf("6. Tim kiem nguoi dung\n");  
    printf("0. Thoat\n");  
    printf("Vui long chon chuc nang: ");  
}  

void displayUserList() {  
    printf("Danh sach nguoi dung:\n");  
    for (int i = 0; i < userCount; i++) {  
        printf("%s - %s\n", users[i].userId, users[i].name);  
    }  
}  

void addUser() {  
    if (userCount >= 100) {  
        printf("Da dat toi da so nguoi dung.\n");  
        return;  
    }  
    
    struct User newUser;  
    printf("Nhap ten nguoi dung: ");  
    scanf("%s", newUser.name);  
    printf("Nhap ID nguoi dung: ");  
    scanf("%s", newUser.userId);  
    
    // Mời người dùng nhập ngày sinh  
    printf("Nhap ngay sinh (dd mm yyyy): ");  
    scanf("%d %d %d", &newUser.dateOfBirth.day, &newUser.dateOfBirth.month, &newUser.dateOfBirth.year);  
    
    printf("Nhap gioi tinh (1 - Nam, 0 - Nu): ");  
    scanf("%d", &newUser.gender);  
    
    printf("Nhap so dien thoai: ");  
    scanf("%s", newUser.phone);  
    printf("Nhap email: ");  
    scanf("%s", newUser.email);  

    if (validateUserInput(newUser)) {  
        users[userCount++] = newUser;  
        saveUserData();  
        printf("Them nguoi dung thanh cong!\n");  
    } else {  
        printf("Du lieu khong hop le!\n");  
    }  
}  

bool validateUserInput(struct User user) {  
    // Kt du lieu dau vao
    if (strlen(user.userId) == 0 || strlen(user.phone) == 0 || strlen(user.email) == 0) {  
        return false;  
    }  
    for (int i = 0; i < userCount; i++) {  
        if (strcmp(users[i].userId, user.userId) == 0 || strcmp(users[i].phone, user.phone) == 0 || strcmp(users[i].email, user.email) == 0) {  
            return false; // ID, sdt, va email phai khac nhau  
        }  
    }  
    return true;  
}  

void toggleUserStatus() {  
    char userId[10];  
    printf("Nhap ID nguoi dung muon khoa/mo khoa: ");  
    scanf("%s", userId);  
    
    for (int i = 0; i < userCount; i++) {  
        if (strcmp(users[i].userId, userId) == 0) {  
            users[i].status = !users[i].status; // dao nguoc tt 
            saveUserData();  
            printf("Trang thai nguoi dung da duoc thay doi.\n");  
            return;  
        }  
    }  
    printf("Khong tim thay nguoi dung voi ID %s.\n", userId);  
}  

void displayUserDetails(char *userId) {  
    for (int i = 0; i < userCount; i++) {  
        if (strcmp(users[i].userId, userId) == 0) {  
            printf("Ten: %s\n", users[i].name);  
            printf("ID: %s\n", users[i].userId);  
            printf("Ngay sinh: %02d/%02d/%04d\n", users[i].dateOfBirth.day, users[i].dateOfBirth.month, users[i].dateOfBirth.year);  
            printf("Gioi tinh: %s\n", users[i].gender ? "Nam" : "Nu");  
            printf("So dien thoai: %s\n", users[i].phone);  
            printf("Email: %s\n", users[i].email);  
            return;  
        }  
    }  
    printf("Khong tim thay nguoi dung voi ID %s.\n", userId);  
}  

void sortUserList() {  
    // Sap xep nguoi dung theo ten
    for (int i = 0; i < userCount - 1; i++) {  
        for (int j = i + 1; j < userCount; j++) {  
            if (strcmp(users[i].name, users[j].name) > 0) {  
                struct User temp = users[i];  
                users[i] = users[j];  
                users[j] = temp;  
            }  
        }  
    }  
    printf("Danh sach nguoi dung da duoc sap xep theo ten.\n");  
}  

void searchUserByName(char *name) {  
    printf("Ket qua tim kiem theo ten \"%s\":\n", name);  
    for (int i = 0; i < userCount; i++) {  
        if (strstr(users[i].name, name) != NULL) {  
            printf("%s - %s\n", users[i].userId, users[i].name);  
        }  
    }  
}