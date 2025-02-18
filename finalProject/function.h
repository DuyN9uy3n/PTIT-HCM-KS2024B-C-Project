// function.h
#ifndef FUNCTION_H
#define FUNCTION_H

#include "datatype.h"

// Menu chính
void displayMainMenu();
void displayAccountMenu(); // Thêm menu quản lý tài khoản

// Hiển thị danh sách người dùng
void displayUserList();

// Thêm người dùng
void addUser();

// Khóa/Mở khóa người dùng
void toggleUserStatus();

// Hiển thị thông tin người dùng theo ID
void displayUserDetails(char *userId);
void displayAccountDetails(char *userId); // Thêm hiển thị chi tiết tài khoản

// Sắp xếp danh sách người dùng
void sortUserList();

// Tìm kiếm người dùng theo tên
void searchUserByName(char *name);

// Chỉnh sửa thông tin cá nhân
void editUserInfo(char *userId);

// Kiểm tra dữ liệu người dùng
bool validateUserInput(struct User user);

// Lưu dữ liệu người dùng
void saveUserData();

// Đọc dữ liệu người dùng
void loadUserData();

#endif // FUNCTION_H