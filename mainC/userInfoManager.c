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


void createUserInfo(int numAccounts)
{

}

//===================================================================================

void fillUserInfo(Accounts account)
{
    printf("Enter the name of your new account: ");
    scanf("%s", account.userName);

    printf("Enter the password of your new account: ");
    scanf("%s", account.password);

    account.userNamelenght = (int)strlen(account.userName);
    account.passwordlenght = (int)strlen(account.password);

    // We declare checksum 0 so that it can add correctly
    account.checksum = 0;
    account.checksum = checksum(account.userName, account.userNamelenght);
    account.checksum += checksum(account.password, account.passwordlenght);

    //index may be needed
}

