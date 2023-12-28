//
// Created by tomas on 27/12/2023.
//

#ifndef MAINC_USERINFOMANAGER_H
#define MAINC_USERINFOMANAGER_H

#include <string.h>
#include <stdio.h>

typedef struct
{
    char* userName;
    char* password;

    int userNamelenght;
    int passwordlenght;

}Accounts;

typedef struct
{
    //puede que no hagan falta user y pwd
    char* userName;
    char* password;

    int numAccounts;
    int checkSum;
}MasterAccount;

void createUserInfo(int numAccounts);

void fillUserInfo(Accounts account);

void deleteUser(int numAccounts, int index);

void freeAllUserInfo(int numAccount);

#endif //MAINC_USERINFOMANAGER_H
