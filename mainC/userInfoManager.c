/*
 *  Name Student 1: Juan Alfonso Arribas
 *  Name Student 2: Fernando Azlor Hostaled
 *  Name Student 3: Tomas Juan Uson
 *  Project: Programming Project
 *  Date of Creation: 27 / 12 / 2023
 *  Objective: Library that manages the dynamic memory allocation of the data structures that have
 *             to be defined, to store the information of each account.
 */

#include "fileManager.h"
#include "userInfoManager.h"

void createUserInfo(int numAccounts, Accounts** account, int firstTime) {
    if (firstTime) {
        *account = (Accounts*)malloc(numAccounts * sizeof(Accounts));
    }
    else {
        *account = (Accounts*)realloc(*account, numAccounts * sizeof(Accounts));
    }
}

//===================================================================================

void fillUserInfo(Accounts* account) {

    char username[5] = {0};
    char password[5] = {0};

    printf("Enter the name of your new account:");
    scanf("%s", username);

    printf("Enter the password of your new account:");
    scanf("%s", password);

    account -> userNamelenght = (int)strlen(username);
    account -> passwordlenght = (int)strlen(password);

    //account -> userNamelenght += 1;
    //account -> passwordlenght += 1;

    account -> userName = malloc(account -> userNamelenght + 1);
    if (account -> userName == NULL) {
        fprintf(stderr, "There is not enough memory space");
    }
    account -> password = malloc(account -> passwordlenght + 1);
    if (account -> password == NULL) {
        fprintf(stderr, "There is not enough memory space");
    }

    strcpy(account -> userName, username);
    strcpy(account -> password, password);

    // DIFFICULTY
    //account -> userName = username;
    //account -> password = password;

    printf("%s %s", account -> userName, account -> password);

    // We declare checksum 0 so that it can add correctly
    account -> checksum = checksum(account -> userName, account -> userNamelenght);
    account -> checksum += checksum(account -> password, account -> passwordlenght);
}

