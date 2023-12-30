/*
 *  Name Student 1: Juan Alfonso Arribas
 *  Name Student 2: Fernando Azlor Hostaled
 *  Name Student 3: Tomas Juan Uson
 *  Project: Programming Project
 *  Date of Creation: 27 / 12 / 2023
 *  Objective: Define the headers of the fileManager.c functions.
 */

#ifndef PROYECTOFUNDAMENTOS_FILEMANAGER_H
#define PROYECTOFUNDAMENTOS_FILEMANAGER_H

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
int checksum(const char arrayChar[], int numChar);

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
 *      path*      --> Data path where the file is
 *      account**  --> Pointer to array(pointer) of structs where we need to store the data
 *      password[] --> Array of characters that form the password to decipher the data
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
 *       0 --> If everything went as it should
 *      -1 --> If it could not open the file or assign the memory space needed
 *      -2 --> If the master password[] is not the correct one, if the checksum don't add up
 */
int readUserInfo(char* path, Accounts** account, const char password[]);

/*
 * Argument:
 *      path*      --> Data path where the file is
 *      account[]  --> List of accounts (struct) that have all the variables that an account needs
 *      password[] --> Array of characters that form the password to cipher the data
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
int writeUserInfo(char* path, Accounts account[], const char password[], int numAccounts);

#endif //PROYECTOFUNDAMENTOS_FILEMANAGER_H
