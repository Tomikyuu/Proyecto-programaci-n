//27/12/2023.


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



    //index may be needed
}

