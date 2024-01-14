/*
 *  Name Student 1: Juan Alfonso Arribas
 *  Name Student 2: Fernando Azlor Hostaled
 *  Name Student 3: Tomas Juan Uson
 *  Project: Programming Project
 *  Date of Creation: 27 / 12 / 2023
 *  Objective: Define the headers of the userInfoManager.c functions.
 */

#ifndef FUNDAMENTOSPROGRAMACIONBUENO_USERINFOMANAGER_H
#define FUNDAMENTOSPROGRAMACIONBUENO_USERINFOMANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a type of struct called Account
typedef struct {
    // Number of characters in the username
    int usernameLenght;
    // Number of characters in the password
    int passwordLenght;
    // Username of the account
    char* username;
    // Password of the account
    char* password;
}Account;

/*
 * Argument:
 *      int numAccounts --> Number of Accounts of the User.
 * Function:
 *      Reserve enough dynamic memory to hold as many account structs as deemed necessary
 *      according to the numAccounts parameter.
 *      (It also initialises the values of the structures for better understanding while debugging)
 * Return:
 *      userAccountArray --> Address where the dynamic memory was reserved.
 */
Account* createUserInfo(int numAccounts);

/*
 * Argument:
 *      Account* user --> Address reserved for the data of the new account
 * Function:
 *      fillUserInfo() will store the struct account with the username, the password, the length in characters
 *      of the username, the length in characters of the password and the checksum of the account.
 * Return:
 *      It is a void, so it doesn't return anything (user goes through reference)
 */
void fillUserInfo(Account* user);

/*
 * Argument:
 *      int index        --> Number of the account that we need to delete
 *      Account** user   --> Address of the Pointer that has the Address of the Accounts (Pointer to Pointer)
 *      int* numAccounts --> Number of Accounts of the user
 * Function:
 *      Erases the account in the position index
 * Return:
 *      Nothing is a void. (But *user and *numAccounts goes through reference)
 */
void deleteUser(Account** user, int index, int* numAccounts);

/*
 * Argument:
 *      Account* user    --> List of all the accounts the user has
 *      int* numAccounts --> Number of Accounts of the user
 * Function:
 *      Free the dynamic memory that was reserved at createUserInfo.
 * Return:
 *      It is a void, so it doesn't return anything (*user goes through reference)
 */
void freeAllUserInfo(Account* user, int numAccounts);

#endif //FUNDAMENTOSPROGRAMACIONBUENO_USERINFOMANAGER_H
