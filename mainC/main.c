/*
 *  Name Student 1: Juan Alfonso Arribas
 *  Name Student 2: Fernando Azlor Hostaled
 *  Name Student 3: Tomas Juan Uson
 *  Project: Programming Project
 *  Date of Creation: 27 / 12 / 2023
 *  Objective: Main function that does the following:
 *
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "fileManager.h"
#include "userInfoManager.h"

/*
 * Argument:
 *      No argument
 * Function:
 *      date() prints the current time on a string format.
 * Return:
 *       0 --> If we were able to print the current date
 *      -1 --> If we weren't successful obtaining the current time
 */
int date() {
    // time_t variable where we will store the current time
    time_t currentTime;
    // Char pointer where we will store the formatted date string
    char* dateString;

    // Obtain the current time
    currentTime = time(NULL);

    // We check if we were successful obtaining the current time
    if (currentTime == ((time_t)-1)) {
        // We print an ERROR message informing that we couldn't obtain the current time
        fprintf(stderr, "Failure to obtain the current time.\n");
        return -1;
    }

    // Convert currentTime into a string representation
    dateString = ctime(&currentTime);
    // Replace '\n' at index 24 with a space (Remove the newline)
    dateString[24] = ' ' ;

    // Print the date in a string format
    // 186 --> ║ (Symbol that our computer keyboards can´t write)
    printf("%c Date and Time: %s%c", 186, dateString, 186);
    return 0;
}

void interface()
{
    //ASCII ART
    printf(" __      __        __\n");
    printf("/  \\    /  \\ ____ |  |   ____  ____   _____   ____\n");
    printf("\\   \\/\\/   // __ \\|  | _/ ___\\/    \\ /     \\ / __ \\\n");
    printf(" \\        /\\  ___/|  |_\\  \\__(  <_> )  y y  \\  ___/\n");
    printf("  \\__/\\__/  \\____ |____/\\___/ \\____/|__|_|__/\\____\n");

    //write style interface
    for(int i = 0; i < 43; i++)
    {
        printf("%c", 205);
    }
    printf("\n");


    printf("%c Welcome to heaven's account gestor      %c\n", 186, 186);
    printf("%c creators: @Tomas @JuanAlf @Fernando     %c\n", 186, 186);
    date();
    printf("\n");

    //write style interface
    for(int j = 0; j < 43; j++)
    {
        printf("%c", 205);
    }
    printf("\n\n");
}

int main() {

    interface();

    MasterAccount master;

    //dinamico **
    char user[10] = {0};
    char pwd[10] = {0};
    char pwd2[10] = {0};
    int mode = 0;

    //Variable that states the existance of a file: (0 = didn't exist; 1 = existed) -->default: exists
    int fileExists = 1;

    FILE * fp;

    printf("Username:");
    scanf("%s", user);
    fflush(stdin);
//============================================================================
    char filePath[20] = "./";
    char fileFormat[5] = ".txt";

    strcat(user, fileFormat);
    strcat(filePath, user);

    fp = fopen(filePath, "r");

    if (fp == NULL) //protección para el caso que no exista el fichero
    {
        fp = fopen(filePath, "w"); //se crea el fichero si no existe
        fclose(fp);

        fileExists = 0;
    }
    else
    {
        fclose(fp);
    }
//============================================================================

    // name change(?)
    printf("Password:");
    scanf("%s", pwd);
    printf("\n");

    if(fileExists == 0)
    {
        for(int j = 0; j < 43; j++)
        {
            printf("%c", 205);
        }


        printf("\nWelcome, I see that your account is a new one, so let me explain how the program works:\n"
               "You will be asked to write accounts you want to store and its password. Then these data\n"
               "will be ciphered with the password you entered, and finally you'll be able to safely quit\n"
               "the program by selecting the fourth option.\n"
               "lets see if you password is right:\n\n");


        // 0 = false; 1 = true
        int samePwd = 1;
        do
        {
            if(!samePwd)
            {
                printf("Write your new password:");
                scanf("%s", pwd);
            }

            printf("Write your password again:");
            scanf("%s", pwd2);
            samePwd = 1;

            for(int i = 0; i < 10; i++)
            {
                if(pwd[i] != pwd2[i])
                {
                    samePwd = 0;
                    fprintf(stderr, "Passwords are not equal\n\n");
                }
            }
        }while (!samePwd);

    }

    int numAccounts = 0;
    Accounts account[numAccounts];

    do
    {
        //strlen(user) - 4 is used to not print the ".txt" at the end of the name
        printf("\nWelcome ");
        for(int i =0; i < strlen(user) - 4; i++)
        {
            printf("%c", user[i]);
        }
        printf("\nSelect what you want to do:\n");

        printf("\t 1) See saved accounts \n"
                      "\t 2) Add a new account \n"
                      "\t 3) Delete account \n"
                      "\t 4) Save and quit \n");

        scanf("%d", &mode);

        //#define **
        switch (mode)
        {
            case 1:



                break;
            case 2:

                //podriamos poner numAccounts++ despues de la funcion
                numAccounts++;
                fillUserInfo(account[numAccounts - 1]);

                break;
            case 3:



                break;
            case 4:

                writeUserInfo(filePath, account, pwd, numAccounts);

                break;
            default:

                fprintf(stderr, "That is not an option, try again \n ");

                break;
        }
    }while ((mode != 4));


    return 0;

}
