#ifndef FUNCTION_H  
#define FUNCTION_H  

#include "datatype.h"  

// menu chinh 
void displayMainMenu();  

// hien thi ds user
void displayUserList();  

// them user
void addUser();  

// khoa user
void toggleUserStatus();  

// hien thi user theo id
void displayUserDetails(char *userId);  

// sap xep ds user
void sortUserList();  

// Htim kiem user theo ten
void searchUserByName(char *name);  

// kt du lieu 
bool validateUserInput(struct User user);  

// luu tep du lieu
void saveUserData();  

// doc du lieu 
void loadUserData();  

#endif // FUNCTION_H