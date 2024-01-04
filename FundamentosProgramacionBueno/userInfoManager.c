/*
 *  Name Student 1: Juan Alfonso Arribas
 *  Name Student 2: Fernando Azlor Hostaled
 *  Name Student 3: Tomas Juan Uson
 *  Project: Programming Project
 *  Date of Creation: 27 / 12 / 2023
 *  Objective: Library that manages the dynamic memory allocation of the data structures that have
 *             to be defined and to store the information of each account in the structs.
 */

#include "userInfoManager.h"

#define SIZE 20

Account* createUserInfo(int numAccounts) {

    // Assign memory for an array of accounts (Array of structs)
    Account* userAccountArray = malloc(numAccounts * sizeof(Account));

    // Check if the allocation was successful
    if (userAccountArray == NULL) {
        // Inform of an ERROR
        fprintf(stderr, "ERROR: Memory Assignment of the Accounts Failed");
        // Terminate Abruptly the Program (We found exit(EXIT_FAILURE) through the Internet)
        exit(EXIT_FAILURE);
    }

    // Initialize each account of the user (For Loop that runs through all the accounts)
    for (int i = 0; i < numAccounts; i++) {
        // Initialize username
        userAccountArray[i].username = 0;
        // Initialize password
        userAccountArray[i].password = 0;
        // Initialize usernameLenght
        userAccountArray[i].usernameLenght = 0;
        // Initialize passwordLenght
        userAccountArray[i].passwordLenght = 0;
    }
    // Return the List of Accounts
    return userAccountArray;
}

void fillUserInfo(Account* user) {
    // Character Arrays to store momentarily the username and password of the new account
    // Character Array to store the username
    char username[SIZE] = {0};
    // Character Array to store the password
    char password[SIZE] = {0};

    // Ask the user for the username of his new account
    printf("\nEnter the name of your new account:");
    // Store the username in username
    scanf("%s", username);
    // Empty Buffer
    fflush(stdin);

    // Ask the user for the password of his new account
    printf("Enter the password of your new account:");
    // Store the password in password
    scanf("%s", password);
    // Empty Buffer
    fflush(stdin);

    // Store the number of character os the username in usernameLenght
    user -> usernameLenght = (int)strlen(username);
    // Store the number of character os the username in usernameLenght
    user -> passwordLenght = (int)strlen(password);

    // Assign memory for an array of characters, the username of the new account
    user -> username = malloc(user -> usernameLenght + 1);
    // Check if the allocation was successful
    if (user -> username == NULL) {
        // Inform of an ERROR
        fprintf(stderr, "ERROR: Memory Assignment of the Username Failed (Add Account) ");
        // Terminate Abruptly the Program (We found exit(EXIT_FAILURE) through the Internet)
        exit(EXIT_FAILURE);
    }
    // Assign memory for an array of characters, the password of the new account
    user -> password = malloc(user -> passwordLenght + 1);
    // Check if the allocation was successful
    if (user -> password == NULL) {
        // Inform of an ERROR
        fprintf(stderr, "ERROR: Memory Assignment of the Password Failed (Add Account) ");
        // Terminate Abruptly the Program (We found exit(EXIT_FAILURE) through the Internet)
        exit(EXIT_FAILURE);
    }

    // Store the username of the new account in username
    strcpy(user -> username, username);
    // Store the password of the new account in password
    strcpy(user -> password, password);

    // Add '\0' to the End of the username
    user -> username[user -> usernameLenght] = '\0';
    // Add '\0' to the End of the password
    user -> password[user -> passwordLenght] = '\0';
}

void deleteUser(Account** user, const int index, int* numAccounts) {
    // Free the Memory of the username of the account we are erasing
    free((*user)[index].username);
    // Free the Memory of the password of the account we are erasing
    free((*user)[index].password);

    // Resize the Number of Accounts
    (*numAccounts)--;

    // Adjust Array of Account to Delete the Index Account
    // (For Loop that runs through the accounts from Index to the End)
    for (int i = index; i < *numAccounts ; i++) {
        // Move Account One Less Position
        (*user)[i] = (*user)[i+1];
    }

    // Resize the Memory Space Assigned to the Accounts of the user
    *user = realloc(*user, *numAccounts * sizeof(Account));
    // Check if the allocation was successful
    if (*user == NULL) {
        // Inform of an ERROR
        fprintf(stderr, "Error: Memory ReAssignment of the Accounts Failed (Delete Account Function)");
        // Terminate Abruptly the Program (We found exit(EXIT_FAILURE) through the Internet)
        exit(EXIT_FAILURE);
    }
}

void freeAllUserInfo(Account* user, const int numAccounts) {
    // If the Number of Accounts Is 0 There is No Memory Space to Free
    if (numAccounts != 0) {
        // For Loop that Goes Through All the Accounts Created at the Moment
        for (int i = 0; i < numAccounts; i++) {
            // Free Memory Space where the Username was Stored
            free(user[i].username);
            // Free Memory Space where the Password was Stored
            free(user[i].password);
        }
        // Free Memory Space where the Array of Accounts was
        free(user);
    }
}
