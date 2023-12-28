/*
 *  Name Student 1: Juan Alfonso Arribas
 *  Name Student 2: Fernando Azlor Hostaled
 *  Name Student 3: Tomas Juan Uson
 *  Project: Programming Project
 *  Date of Creation: 27 / 12 / 2023
 *  Objective: Define the headers of the userInfoManager.c functions.
 */

#ifndef MAINC_USERINFOMANAGER_H
#define MAINC_USERINFOMANAGER_H

#include <stdio.h>
#include <string.h>


typedef struct
{
    char* userName;
    char* password;

    int userNamelenght;
    int passwordlenght;

    int checksum;

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
