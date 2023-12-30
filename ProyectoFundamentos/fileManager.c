/*
 *  Name Student 1: Juan Alfonso Arribas
 *  Name Student 2: Fernando Azlor Hostaled
 *  Name Student 3: Tomas Juan Uson
 *  Project: Programming Project
 *  Date of Creation: 27 / 12 / 2023
 *  Objective: Library that manages the creation, writing and reading of the files.
 */

#include "fileManager.h"

int checksum(const char arrayChar[], int numChar) {
    // Variable that stores the value of the checksum and initialise it to 0 so
    // when used to add to it, it will not give us any problem.
    int result = 0;
    // For loop that repeats as many times as characters are in arrayChar[]
    for (int i = 0; i < numChar; i++) {
        // Calculates checksum and store it in result
        // Algorithm: Add the ASCII value of every character of the array to result
        result = result + (int)arrayChar[i];
    }
    // Return result (checksum of arrayChar[])
    return result;
}

void xorCipher(char arrayData[], int numChar, const char password[]) {
    // Stores lenght of the password
    int passwordLenght = (int)strlen(password);
    // For loop that repeats as many times as characters are in arrayData[]
    for (int i = 0; i < numChar; i++) {
        // Algorithm that encrypts arrayData by the bit by bit XOR Cipher
        arrayData[i] = arrayData[i] ^ password[i % passwordLenght];
    }
}

int readUserInfo(char* path, Accounts account[], const char password[]) {
    // Auxiliary Variable to store the checksum of the account and compare it after
    int checksumAux;
    // Variable to store the number of accounts the user created
    int numAccounts = 0;

    // Create pointer to file
    FILE * fp;
    // Open and read a binary file
    fp = fopen(path, "rb");
    // If the file could not be open, tell the user and return -1
    if(fp == NULL) {
        fprintf(stderr, "The file could not be open");
        return -1;
    }

    // Read number of accounts and store it in numAccounts
    fscanf(fp, "%d", &numAccounts);

    // Assign Memory Space to the Struct so that it can store all the accounts
    createUserInfo(numAccounts, account, 0);

    // For loop that goes through all the accounts of the user
    for (int i = 0; i < numAccounts; i++) {
        // Store the data of the file (N� of characters in the password and username) in the variables of the struct
        // Store n� of characters in the username in .userNamelenght
        fscanf(fp, "%d", &(*account)[i].userNamelenght);
        // Store n� of characters in the password in .passwordlenght
        fscanf(fp, "%d", &(*account)[i].passwordlenght);

        // Assign Memory Space to the Pointers of the username
        (*account)[i].userName = malloc((*account)[i].userNamelenght + 1);
        // If it can be assigned, tell the user and return -1
        if((*account)[i].userName == NULL) {
            fprintf(stderr, "We could not assign the memory space");
            return -1;
        }
        // Assign Memory Space to the Pointers of the password
        (*account)[i].password = malloc((*account)[i].passwordlenght + 1);
        // If it can be assigned, tell the user and return -1
        if((*account)[i].password == NULL) {
            fprintf(stderr, "We could not assign the memory space");
            return -1;
        }

        // Store the information (username, password and checksum) in the variables of the struct
        // Store username in .userName
        fscanf(fp, "%s", (*account)[i].userName);
        // Store password in .password
        fscanf(fp, "%s", (*account)[i].password);
        // Store checksum in .checksum
        fscanf(fp, "%d", &(*account)[i].checksum);

        // Decipher username and password (XOR Cipher) with the master password (password[])
        // Decipher username and store it in .userName
        xorCipher((*account)[i].userName, (*account)[i].userNamelenght, password);
        // Decipher password and store it in .password
        xorCipher((*account)[i].password, (*account)[i].passwordlenght, password);

        // Calculate checksum of username and password
        // Calculate checksum of the username
        checksumAux  = checksum((*account)[i].userName, (*account)[i].userNamelenght);
        // Calculate checksum of the password and add it to the total checksum
        checksumAux += checksum((*account)[i].password, (*account)[i].passwordlenght);

        // If the checksums are different, then the master password (password[]) is wrong
        if ((*account)[i].checksum != checksumAux) {
            // Close file
            fclose(fp);
            // Free memory space passwords and usernames
            // For loop that goes through the accounts that have been read at the moment
            for (int j = 0; j < i; j++) {
                // Free the memory of the username
                free((*account)[i].userName);
                // Free the memory of the password
                free((*account)[i].password);
            }
            // Return -2
            return -2;
        }
    }

    // Close file
    fclose(fp);
    // Return numAccounts (Everything Went Alright)
    return numAccounts;
}

int writeUserInfo(char* path, Accounts account[], const char password[], const int numAccounts) {
    // Cipher the usernames and passwords of all the accounts (XOR Cipher)
    // For loop that goes through all the accounts (structs) of the user
    for (int i = 0; i < numAccounts; i++) {
        // Cipher Username
        xorCipher(account[i].userName, account[i].userNamelenght, password);
        // Cipher Password
        xorCipher(account[i].password, account[i].passwordlenght, password);
    }

    // Create pointer to file
    FILE * fp;
    // Open and write in a binary file
    fp = fopen(path, "wb");
    // If the file could not be open, tell the user and return -1
    if(fp == NULL) {
        printf("The file could not be open");
        return -1;
    }

    // Write in the file the n� of accounts (n� of structs) the user has created
    fprintf(fp, "%d\n", numAccounts);

    // Write in the file the rest of the information.
    // Information:
    // N� characters username | N� characters password | username (ciphered) | password (ciphered) | checksum
    // For loop that goes through all the accounts (structs) of the user
    for (int i = 0; i < numAccounts; i++) {
        // Prints in file the n� character in the username
        fprintf(fp, "%d ", account[i].userNamelenght);
        // Prints in file the n� character in the password
        fprintf(fp, "%d ", account[i].passwordlenght);
        // Prints in file the ciphered username
        fprintf(fp, "%s ", account[i].userName);
        // Prints in file the ciphered password
        fprintf(fp, "%s ", account[i].password);
        // Prints in file the checksum
        fprintf(fp, "%d\n", account[i].checksum);
    }

    // Close file
    fclose(fp);
    // Return 0 (Everything Went Alright)
    return 0;
}
