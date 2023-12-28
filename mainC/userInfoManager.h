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
#include <stdlib.h>
#include <string.h>


typedef struct
{
    char* userName;
    char* password;

    int userNamelenght;
    int passwordlenght;

    int checksum;

}Accounts;

/*
 * Argument:
 *
 * Function:
 *
 * Return:
 *      Nothing is a void. (But arrayChar goes through reference and "stores" the ciphered text)
 */
void createUserInfo(int numAccounts, Accounts** account, int firstTime);

/*
 * Argument:
 *      account* --> pointer struct that contains the credentials of an account
 * Function:
 *      fillUserInfo() will store the struct account with the username, the password, the length in characters
 *      of the username, the length in characters of the password and the checksum of the account.
 * Return:
 *      Nothing is a void. (But arrayChar goes through reference and "stores" the ciphered text)
 */
void fillUserInfo(Accounts* account);

/*
 * Argument:
 *
 * Function:
 *
 * Return:
 *      Nothing is a void. (But arrayChar goes through reference and "stores" the ciphered text)
 */
void deleteUser(int numAccounts, int index);

/*
 * Argument:
 *
 * Function:
 *
 * Return:
 *      Nothing is a void. (But arrayChar goes through reference and "stores" the ciphered text)
 */
void freeAllUserInfo(int numAccount);

#endif //MAINC_USERINFOMANAGER_H
