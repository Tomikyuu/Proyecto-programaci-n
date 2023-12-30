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

// Define a type of struct
typedef struct {
    // Int to store the nº of characters in the username
    int userNamelenght;
    // Int to store the nº of characters in the password
    int passwordlenght;

    // Pointer (array) to store the username of the account
    char* userName;
    // Pointer (array) to store the password of the account
    char* password;

    // Int to store the checksum of the username and password
    int checksum;

// Name this type of struct as Accounts
}Accounts;

/*
 * Argument:
 *      numAccounts --> Nº of accounts the user has
 *      account**   --> Pointer that points to the pointer that points to the struct (To assign memory space)
 *      firstTime   --> Boolean Variable:
 *                          1 --> First time assigning memory so malloc
 *                          0 --> Already assigned memory so we realloc
 * Function:
 *      It assigns the memory space needed to the struct account:
 *                      If it's the first time we use malloc to assign
 *                      If it's not then we realloc the memory to add or subtract
 * Return:
 *      void... for now....
 *       0 --> If everything went as it should
 *      -1 --> If the memory was not assigned correctly
 */
void createUserInfo(int numAccounts, Accounts** account, int firstTime);

/*
 * Argument:
 *      account* --> pointer struct that contains the credentials of an account
 * Function:
 *      fillUserInfo() will store the struct account with the username, the password, the length in characters
 *      of the username, the length in characters of the password and the checksum of the account.
 * Return:
 *       0 --> If everything went as it should
 *      -1 --> If the memory was not assigned correctly
 */
int fillUserInfo(Accounts* account);

/*
 * Argument:
 *      numAccount --> Nº of accounts the user has created (Nº of structs)
 *      index      --> Number of the account that we need to delete
 *      *Probablemente tenemos que añadir Account*
 * Function:
 *      Erases the account in the position index
 * Return:
 *      Nothing is a void. (But arrayChar goes through reference and "stores" the ciphered text)
 */
void deleteUser(int numAccounts, int index);

/*
 * Argument:
 *      numAccount --> Nº of accounts the user has created (Nº of structs)
 * Function:
 *      Frees all the memory spaces allocated during the execution of the program.
 * Return:
 *      Nothing is a void.
 */
void freeAllUserInfo(int numAccount);

#endif //MAINC_USERINFOMANAGER_H
