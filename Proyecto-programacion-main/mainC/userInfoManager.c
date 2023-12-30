/*
 *  Name Student 1: Juan Alfonso Arribas
 *  Name Student 2: Fernando Azlor Hostaled
 *  Name Student 3: Tomas Juan Uson
 *  Project: Programming Project
 *  Date of Creation: 27 / 12 / 2023
 *  Objective: Library that manages the dynamic memory allocation of the data structures that have
 *             to be defined and to store the information of each account in the structs.
 */

#include "fileManager.h"
#include "userInfoManager.h"

// Probablemente tenemos que volverlo int por si los datos no se han asignado correctamente
void createUserInfo(int numAccounts, Accounts** account, int firstTime) {
    if (firstTime) {
        *account = (Accounts*)malloc(numAccounts * sizeof(Accounts));

    }
    else {
        *account = (Accounts*)realloc(*account, numAccounts * sizeof(Accounts));
    }
}

//===================================================================================

int fillUserInfo(Accounts* account) {

    char username[5] = {0};
    char password[5] = {0};

    printf("Enter the name of your new account:");
    scanf("%s", username);

    printf("Enter the password of your new account:");
    scanf("%s", password);

    account -> userNamelenght = (int)strlen(username);
    account -> passwordlenght = (int)strlen(password);

    account -> userName = malloc(account -> userNamelenght + 1);
    if (account -> userName == NULL) {
        fprintf(stderr, "There is not enough memory space");
        return 1;
    }
    account -> password = malloc(account -> passwordlenght + 1);
    if (account -> password == NULL) {
        fprintf(stderr, "There is not enough memory space");
        return 1;
    }

    strcpy(account -> userName, username);
    strcpy(account -> password, password);

    // DIFFICULTY
    //account -> userName = username;
    //account -> password = password;

    printf("%s %s", account -> userName, account -> password);


    account -> checksum = checksum(account -> userName, account -> userNamelenght);
    account -> checksum += checksum(account -> password, account -> passwordlenght);

    // Return 0 if Everything Went Alright
    return 0;
}

void deleteUser(int numAccounts, int index, Accounts** accounts)
{

    for(int i = index - 1; i < numAccounts; i++)
    {

        accounts[i]->userNamelenght = accounts[i + 1]->userNamelenght;
        accounts[i]->passwordlenght = accounts[i + 1]->passwordlenght;

        (*accounts)[i].userName = realloc((*accounts)[i].userName, accounts[i]->userNamelenght+1);
        (*accounts)[i].password = realloc((*accounts)[i].password, accounts[i]->passwordlenght+1);

        accounts[i]->userName = accounts[i + 1]->userName;
        accounts[i]->password = accounts[i + 1]->password;

    }

    printf("Deleted succesfuly\n");

}