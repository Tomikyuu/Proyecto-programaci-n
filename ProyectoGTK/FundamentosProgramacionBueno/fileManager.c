/*
 *  Name Student 1: Juan Alfonso Arribas
 *  Name Student 2: Fernando Azlor Hostaled
 *  Name Student 3: Tomas Juan Uson
 *  Project: Programming Project
 *  Date of Creation: 27 / 12 / 2023
 *  Objective: Library that manages the creation, writing and reading of the files.
 */

#include "fileManager.h"

/*
 * Argument:
 *      int numChar      --> Number of characters of arrayChar[]
 *      char arrayChar[] --> Array of character (We will be calculating its checksum)
 * Function:
 *      calculateChecksum() calculates the checksum of an array of characters (arrayChar) through an algorithm.
 * Return:
 *      checksum --> Returns the checksum that correspond to the arrayChar[]
 */
int calculateChecksum(const char arrayData[], const int numChar) {
    // Create and Initialize Checksum
    int checksum = 0;
    // For loop that repeats as many times as characters are in arrayChar[]
    for (int i = 0; i < numChar; i++) {
        // Calculates checksum and store it in result
        // Algorithm: Add the ASCII value of every character of the array to result
        checksum = checksum + (int)arrayData[i];
    }
    // Return checksum
    return checksum;
}

/*
 * Argument:
 *      int numChar      --> nº of characters arrayData has
 *      char arrayData[] --> Array of character that we will be ciphering or deciphering
 *      char password[]  --> Key to cipher and decipher arrayData[]
 * Function:
 *      xorCipher(), ciphers or deciphers with an XOR bit to bit cipher the array of characters
 *                   in arrayData[] with the key password. And stores the result in arrayData[]
 * Return:
 *      Nothing is a void. (But arrayChar goes through reference and "stores" the ciphered text)
 */
void cipherXOR(char arrayData[], int numChar, const char password[]) {
    // Store the Lenght of the Master Password
    int passwordLenght = (int)strlen(password);
    // Cipher/Decipher arrayData() (For Loop that repeats as many times as Characters are in arrayData)
    for (int i = 0; i < numChar; i++) {
        // Algorithm that Ciphers/Deciphers arrayData[] bit to bit
        arrayData[i] = (char)(arrayData[i] ^ password[i % passwordLenght]);
    }
}

Account* readUserInfo(const char filePath[], const char key[], int* numAccounts) {
    // Pointer to store the Address of the File
    FILE* fp;
    // Open Binary File in Read Mode
    fp = fopen(filePath, "rb");
    // Check if the File Was Opened (or Exists)
    if (fp == NULL) {
        // Inform of an ERROR
        fprintf(stderr, "ERROR: File Could not be Opened on Read Mode");
        // Terminate Abruptly the Program (We found exit(EXIT_FAILURE) through the Internet)
        exit(EXIT_FAILURE);
    }

    // Read (on the File) the Number of Accounts and store it on numAccounts
    fread(numAccounts, sizeof(int), 1, fp);

    // Array of (Account) Structs to store the Accounts
    // Assign Memory Space
    Account* user = createUserInfo(*numAccounts);

    // Store the Checksum Calculated from the Password and Username
    int checksumNew;
    // Store the Checksum Written on the File
    int checksumFile = 0;

    // Read the Information on the File and Store it on the Account (Array of structs)
    // (For Loop that Repeats as many times as Accounts are)
    for (int i = 0; i < *numAccounts; i++) {
        // Read (on the File) the Number of Characters of the Username and store it on usernameLenght
        fread(&user[i].usernameLenght, sizeof(int), 1, fp);
        // Read (on the File) the Number of Characters of the Password and store it on passwordLenght
        fread(&user[i].passwordLenght, sizeof(int), 1, fp);

        // Allocate Memory Space for the Username of each Account
        user[i].username = malloc(user[i].usernameLenght + 1);
        // Check if the allocation was successful
        if (user[i].username == NULL) {
            // Inform of an ERROR
            fprintf(stderr, "ERROR: Memory Assignment of the Username Failed (Read File) ");
            // Terminate Abruptly the Program (We found exit(EXIT_FAILURE) through the Internet)
            exit(EXIT_FAILURE);
        }
        // Allocate Memory Space for the Password of each Account
        user[i].password = malloc(user[i].passwordLenght + 1);
        // Check if the allocation was successful
        if (user[i].password == NULL) {
            // Inform of an ERROR
            fprintf(stderr, "ERROR: Memory Assignment of the Password Failed (Read File) ");
            // Terminate Abruptly the Program (We found exit(EXIT_FAILURE) through the Internet)
            exit(EXIT_FAILURE);
        }

        // Read (on the file) the Username of the Account and store it on username
        fread(user[i].username, sizeof(char), user[i].usernameLenght, fp);
        // Read (on the file) the Password of the Account and store it on password
        fread(user[i].password, sizeof(char), user[i].passwordLenght, fp);

        // Add '\0' to the End of the username
        user[i].username[user[i].usernameLenght] = '\0';
        // Add '\0' to the End of the password
        user[i].password[user[i].passwordLenght] = '\0';

        // Read (on the file) the Checksum of the Account and store it on checksum
        fread(&checksumFile, sizeof(int), 1, fp);

        // Decipher username
        cipherXOR(user[i].username, user[i].usernameLenght, key);
        // Decipher password
        cipherXOR(user[i].password, user[i].passwordLenght, key);

        // Calculate Checksum of the username
        checksumNew = calculateChecksum(user[i].username, user[i].usernameLenght);
        // Calculate Checksum of the password and Add it to the Checksum of the username
        checksumNew += calculateChecksum(user[i].password, user[i].passwordLenght);

        // Check if the Checksum from the File and the Recently Calculated Checksum are Equal
        if (checksumFile != checksumNew) {
            // Close File
            fclose(fp);
            // Free Memory Allocated
            freeAllUserInfo(user, i + 1);
            // Inform of the Issue
            printf("Wrong Password\n");
            // Return NULL
            return NULL;
        }
    }
    // Close File
    fclose(fp);
    // Return the List Of Accounts
    return user;
}

int writeUserInfo(char* filePath, Account* user, const char key[], const int numAccounts) {
    // Pointer to store the Address of the File
    FILE* fp;
    // Open Binary File in Write Mode
    fp = fopen(filePath, "wb");
    // Check if the File Was Opened
    if (fp == NULL) {
        // Inform of an ERROR
        fprintf(stderr, "ERROR: File Could not be Opened on Write Mode");
        // Return -1 If the File could not be opened
        return -1;
    }

    // Variable to store the Checksum of the Username and Password of each Account
    int checksum;

    // Write on the File the Number of Accounts
    fwrite(&numAccounts, sizeof(int), 1, fp);

    // If numAccounts == 0 we don't wrote anymore and delete the file
    if (numAccounts == 0) {
        // Close File
        fclose(fp);
        // Remove File
        remove(filePath);
    }
    // If not, then we write the information of the accounts on the file
    else {
        // Write the Information of All the Accounts (For Loop that Repeats as many times as Accounts are)
        for (int i = 0; i < numAccounts; i++) {
            // Write the Number of Characters on the username on the File
            fwrite(&user[i].usernameLenght, sizeof(int), 1, fp);
            // Write the Number of Characters on the password on the File
            fwrite(&user[i].passwordLenght, sizeof(int), 1, fp);

            // Calculate Checksum Username
            checksum = calculateChecksum(user[i].username, user[i].usernameLenght);
            // Calculate Checksum Password and Add it to the Checksum
            checksum += calculateChecksum(user[i].password, user[i].passwordLenght);

            // Cipher username
            cipherXOR(user[i].username, user[i].usernameLenght, key);
            // Cipher password
            cipherXOR(user[i].password, user[i].passwordLenght, key);

            // Write the username on the File
            fwrite(user[i].username, sizeof(char), user[i].usernameLenght, fp);
            // Write the password on the File
            fwrite(user[i].password, sizeof(char), user[i].passwordLenght, fp);

            // Write on the File the Checksum
            fwrite(&checksum, sizeof(int), 1, fp);
        }
    }
    // Close File
    fclose(fp);
    // Return 0 if Everything went Alright
    return 0;
}
