#ifndef FUNCTION_H
#define FUNCTION_H

#include "datatype.h"

// Menu chính
void displayMainMenu();

// Hiển thị danh sách user
void displayUserList();

// Thêm user
void addUser();

// Khóa/Mở khóa user
void toggleUserStatus();

// Hiển thị user theo ID
void displayUserDetails(char *userId);

// Sắp xếp danh sách user
 void sortUserList();

// Tìm kiếm user theo tên
void searchUserByName(char *name);

// Kiểm tra dữ liệu user
bool validateUserInput(struct User user);


// Lưu dữ liệu user
void saveUserData();

// Đọc dữ liệu user
void loadUserData();

void displayUserDetails(char *userId);


#endif // FUNCTION_H