#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "userInfoManager.h"
#include "fileManager.h"

//TIME AND OPENING INTERFACE
//internet
void Time()
{
    time_t current_time;
    char* c_time_string;

    // Obtain current time
    current_time = time(NULL);

    if (current_time == ((time_t)-1))
    {
        (void) fprintf(stderr, "Failure to obtain the current time.\n");
        exit(EXIT_FAILURE);
    }

    // Convert to local time format
    c_time_string = ctime(&current_time);
    c_time_string[24] = ' ' ;

    /*
    if (c_time_string == NULL)
    {
        (void) fprintf(stderr, "Failure to convert the current time.\n");
        exit(EXIT_FAILURE);
    }
    */
    // Print to stdout. ctime() has already added a terminating newline character
    (void) printf("%c Date and Time: %s%c", 186, c_time_string, 186);


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
    Time();
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
    int pwd[10] = {0};
    int pwd2[10] = {0};
    int mode = 0;

    //Variable that states the existance of a file: (0 = didn't exist; 1 = existed) -->default: exists
    int fileExists = 1;

    FILE * fp;

    printf("Username:");
    scanf("%s", user);
    fflush(stdin);
//============================================================================
    char filePath[20] = ".\\";
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
    scanf("%d", pwd);
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
                scanf("%d", pwd);
            }

            printf("Write your password again:");
            scanf("%d", pwd2);
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


                //fclose(fp);

                break;
            default:

                fprintf(stderr, "That is not an option, try again \n ");

                break;
        }
    }while ((mode != 4));


    return 0;

}
