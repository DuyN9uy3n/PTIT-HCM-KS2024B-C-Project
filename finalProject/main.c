#include <stdlib.h>
#include <stdio.h>  
#include <string.h>  
#include "function.h"  

int main() {  
    int choice;  
    
    loadUserData(); // Tai du lieu khi chay chuong trinh 

    while (1) {  
        displayMainMenu();  
        scanf("%d", &choice);  
        switch (choice) {  
            case 1:  
                displayUserList();  
                break;  
            case 2:  
                addUser();  
                break;  
            case 3:  
                toggleUserStatus();  
                break;  
            case 4: {  
                char userId[10];  
                printf("Nhap ID nguoi dung muon xem tt: ");  
                scanf("%s", userId);  
                displayUserDetails(userId);  
                break;  
            }  
            case 5:  
                sortUserList();  
                break;  
            case 6: {  
                char searchName[20];  
                printf("Nhap ten nguoi dung de tim kiem: ");  
                scanf("%s", searchName);  
                searchUserByName(searchName);  
                break;  
            }  
            case 0:  
                saveUserData(); // luu khi thoat
                return 0;  
            default:  
                printf("Lua chon khong hop le!\n");  
        }  
    }  
}