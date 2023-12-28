/*
 *  Name Student 1: Juan Alfonso Arribas
 *  Name Student 2: Fernando Azlor Hostaled
 *  Name Student 3: Tomas Juan Uson
 *  Project: Programming Project
 *  Date of Creation: 27 / 12 / 2023
 *  Objective: Library that manages the creation, writing and reading.
 */

#include "fileManager.h"

int checksum(char arrayChar[], int numChar) {
    // Declare variable result where we will store the value of the checksum and initialise it to 0 so
    // when we add to it, it will not give us any problem.
    int result = 0;
    // For loop that goes through the array of characters arrayChar[] one character at the time
    for (int i = 0; i < numChar; i++) {
        // Add the ASCII value of every character of the array to result
        result = result + (int)arrayChar[i];
    }
    // Return result (checksum of arrayChar)
    return result;
}

void xorCipher(char arrayData[], int numChar, const char password[]) {
    int passwordLenght = (int)strlen(arrayData);
    for (int i = 0; i < numChar; i++)
    {
        arrayData[i] = arrayData[i] ^ password[i % passwordLenght];
    }
}

int writeUserInfo(char* path, Accounts account[], const char password[], const int numAccounts)
{
    // Cipher usernames and passwords in
    for (int i = 0; i < numAccounts; i++) {
        xorCipher(account[i].userName, account[i].userNamelenght, password);
        xorCipher(account[i].password, account[i].passwordlenght, password);
    }

    FILE * fp;
    fp = fopen(path, "wb");

    if(fp == NULL)
    {
        fprintf(stderr, "The file could not be open");
        return -1;
    }

    fprintf(fp, "%d\n", numAccounts);

    for (int i = 0; i < numAccounts; i++) {
        fprintf(fp, "%d ", account[i].userNamelenght);
        fprintf(fp, "%d ", account[i].passwordlenght);
        fprintf(fp, "%s ", account[i].userName);
        fprintf(fp, "%s ", account[i].password);
        fprintf(fp, "%d\n", account[i].checksum);
    }

    fclose(fp);
    return 0;
}


