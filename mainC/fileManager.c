/*
 *  Name Student 1: Juan Alfonso Arribas
 *  Name Student 2: Fernando Azlor Hostaled
 *  Name Student 3: Tomas Juan Uson
 *  Project: Programming Project
 *  Date of Creation: 27 / 12 / 2023
 *  Objective: Library that manages the creation, writing and reading.
 */

#include "fileManager.h"

int checksum(const char arrayChar[], int numChar) {
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
    // Stores lenght of the password
    int passwordLenght = (int)strlen(password);
    // For loop repeats as many times as characters are in arrayData
    for (int i = 0; i < numChar; i++) {
        // Algorithm that encrypts arrayData by the XOR bit by bit Cipher
        arrayData[i] = arrayData[i] ^ password[i % passwordLenght];
    }
}

int readUserInfo(char* path, Accounts* account, const char password[]) {
    int checksumAux;
    int numAccounts = 0;

    // Open file
    FILE * fp;
    // Read a binary file
    fp = fopen(path, "rb");

    // If the file could not be open
    if(fp == NULL) {
        fprintf(stderr, "The file could not be open");
        return -1;
    }

    // Read number of accounts and store it in numAccounts
    fscanf(fp, "%d", &numAccounts);

    // Assign Memory Space to the Struct
    createUserInfo(numAccounts, &account, 0);

    // For loop that goes through all the accounts of the user
    for (int i = 0; i < numAccounts; i++) {
        // Store the data of the file in the variables of the struct
        fscanf(fp, "%d", &account[i].userNamelenght);
        fscanf(fp, "%d", &account[i].passwordlenght);

        // Assign Memory Space to the Pointers of the username and password
        account[i].userName = malloc(account[i].userNamelenght);
        account[i].password = malloc(account[i].passwordlenght);

        fscanf(fp, "%s", account[i].userName);
        fscanf(fp, "%s", account[i].password);
        fscanf(fp, "%d", &account[i].checksum);

        // Decipher username and password
        xorCipher(account[i].userName, account[i].userNamelenght, password);
        xorCipher(account[i].password, account[i].passwordlenght, password);

        // Calculate checksum of username and password
        checksumAux  = checksum(account[i].userName, account[i].userNamelenght);
        checksumAux += checksum(account[i].password, account[i].passwordlenght);

        // If the checksums are different
        if (account[i].checksum != checksumAux) {
            // Close file
            fclose(fp);
            // Free memory space of account, password and username
            free(account);
            for (int j = 0; j <= i; j++) {
                free(account[i].userName);
                free(account[i].password);
            }
            // Return -2
            return -2;
        }
    }

    // Close file
    fclose(fp);
    // Return numAccounts
    return numAccounts;
}


int writeUserInfo(char* path, Accounts account[], const char password[], const int numAccounts)
{
    // Cipher usernames and passwords in
    for (int i = 0; i < numAccounts; i++) {
        xorCipher(account[i].userName, account[i].userNamelenght, password);
        printf("%s", account[i].userName);
        xorCipher(account[i].password, account[i].passwordlenght, password);
        printf("%s", account[i].password);
    }

    FILE * fp;
    fp = fopen(path, "wb");

    if(fp == NULL) {
        printf("The file could not be open");
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


