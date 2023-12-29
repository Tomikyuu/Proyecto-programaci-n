/*
 *  Name Student 1: Juan Alfonso Arribas
 *  Name Student 2: Fernando Azlor Hostaled
 *  Name Student 3: Tomas Juan Uson
 *  Project: Programming Project
 *  Date of Creation: 27 / 12 / 2023
 *  Objective: Define the headers of the fileManager.c functions.
 */

#ifndef MAINC_FILEMANAGER_H
#define MAINC_FILEMANAGER_H

#include <string.h>
#include "userInfoManager.h"

/*
 * Argument:
 *      numChar     --> nº of characters arrayChar[] has
 *      arrayChar[] --> Array of character that we will be calculating its checksum
 * Function:
 *      checksum() calculates the checksum of an array of characters (arrayChar) through an algorithm.
 * Return:
 *      result --> Returns the checksum that correspond to the arrayChar[]
 */
int checksum(char arrayChar[], int numChar);

/*
 * Argument:
 *      numChar     --> nº of characters arrayData has
 *      arrayData[] --> Array of character that we will be ciphering or deciphering
 *      password[]  --> Key to cipher and decipher arrayData[]
 * Function:
 *      xorCipher(), ciphers or deciphers with an XOR bit to bit cipher the array of characters
 *                   in arrayData[] with the key password. And stores the result in arrayData[]
 * Return:
 *      Nothing is a void. (But arrayChar goes through reference and "stores" the ciphered text)
 */
void xorCipher(char arrayData[], int numChar, const char password[]);

/*
 * Argument:
 *
 * Function:
 *
 * Return:
 *      Nothing is a void. (But arrayChar goes through reference and "stores" the ciphered text)
 */
int readUserInfo(char* path, Accounts* account, const char password[]);

/*
 * Argument:
 *      path*      --> Data path where the file is
 *      account[]  --> List of accounts (struct) that have all the variables that an account needs
 *      password[] --> Array of characters that form the password
 *
 * Function:
 *
 * Return:
 *      Nothing is a void. (But arrayChar goes through reference and "stores" the ciphered text)
 */
int writeUserInfo(char* path, Accounts account[], const char password[], int numAccounts);

#endif //MAINC_FILEMANAGER_H

