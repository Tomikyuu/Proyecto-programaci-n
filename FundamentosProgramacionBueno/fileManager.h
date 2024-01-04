/*
 *  Name Student 1: Juan Alfonso Arribas
 *  Name Student 2: Fernando Azlor Hostaled
 *  Name Student 3: Tomas Juan Uson
 *  Project: Programming Project
 *  Date of Creation: 27 / 12 / 2023
 *  Objective: Define the headers of the fileManager.c functions.
 */

#ifndef FUNDAMENTOSPROGRAMACIONBUENO_FILEMANAGER_H
#define FUNDAMENTOSPROGRAMACIONBUENO_FILEMANAGER_H

#include "userInfoManager.h"

/*
 * Argument:
 *      char filePath*   --> Data path where the file is
 *      int numAccounts  --> Number of Accounts the User Has
 *      char key[]       --> Array of characters that form the password to decipher the data
 * Function:
 *      The function reads the information of the file and decipher it's with the password[].
 *      Then, it will store the information in the structs and compare the checksums to
 *      check if the password is the correct one.
 *      The file will follow this structure:
 *      numAccounts (Exm: 3)
 *      NºChar username0   NºChar password0   username0   password0   checksum0
 *      NºChar username1   NºChar password1   username1   password1   checksum1
 *      NºChar username2   NºChar password2   username2   password2   checksum2
 * Return:
 *       Account* user --> An Array of Structures that Have all the Information of the Accounts on the File
 */
Account* readUserInfo(const char filePath[], const char key[], int* numAccounts);

/*
 * Argument:
 *      char* path       --> Data path of the file
 *      Account* user    --> List of accounts (struct) that have all the variables that an account needs
 *      char key[]       --> Array of characters that form the password to cipher the data
 *      int numAccounts  --> Number of Accounts the User Has
 *
 * Function:
 *      Will write in the file that the *path points to the information in account[] once it have
 *      been ciphered with the password[].
 *      The file will follow this structure:
 *      numAccounts (Exm: 3)
 *      NºChar username0   NºChar password0   username0   password0   checksum0
 *      NºChar username1   NºChar password1   username1   password1   checksum1
 *      NºChar username2   NºChar password2   username2   password2   checksum2
 * Return:
 *       0 --> If everything went as it should
 *      -1 --> If the file could not be opened
 */
int writeUserInfo(char* filePath, Account* user, const char key[], int numAccounts);

#endif //FUNDAMENTOSPROGRAMACIONBUENO_FILEMANAGER_H
