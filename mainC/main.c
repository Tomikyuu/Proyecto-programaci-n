/*
 *  Name Student 1: Juan Alfonso Arribas
 *  Name Student 2: Fernando Azlor Hostaled
 *  Name Student 3: Tomas Juan Uson
 *  Project: Programming Project
 *  Date of Creation: 27 / 12 / 2023
 *  Objective: Main function that does the following:
 *
 */

// Include libraries
#include <stdio.h>
#include <time.h>
#include <string.h>

// Include .h files
#include "fileManager.h"
#include "userInfoManager.h"

// Define the different modes of the program for better understanding
#define SEE_ACCOUNTS 1
#define CREATE_ACCOUNT 2
#define DELETE_ACCOUNT 3
#define SAFE_AND_EXIT 4

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
        printf("Failure to obtain the current time.\n");
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

/*
 * Argument:
 *      No argument
 * Function:
 *      printBars() prints 43 == to create a box
 * Return:
 *      It's a void, so it doesn't print anything
 */
void printBars() {
    // Prints == 43 times to create a box
    // 205 --> ASCII Code for a Symbol our computer keyboards can't write
    for(int i = 0; i < 43; i++)
    {
        printf("%c", 205);
    }
    printf("\n");
}

/*
 * Argument:
 *      No argument
 * Function:
 *      interface() prints an interface for the program
 * Return:
 *      It's a void, so it doesn't print anything
 */
void interface() {
    //ASCII ART saying WELCOME
    printf(" __      __        __\n");
    printf("/  \\    /  \\ ____ |  |   ____  ____   _____   ____\n");
    printf("\\   \\/\\/   // __ \\|  | _/ ___\\/    \\ /     \\ / __ \\\n");
    printf(" \\        /\\  ___/|  |_\\  \\__(  <_> )  y y  \\  ___/\n");
    printf("  \\__/\\__/  \\____ |____/\\___/ \\____/|__|_|__/\\____\n");

    // Prints box top bars
    printBars();

    // Welcome the user, Introduce Developers and Print Date
    // 186 --> ║ (Symbol that our computer keyboards can´t write)
    printf("%c Welcome to heaven's account Manager     %c\n", 186, 186);
    printf("%c Creators: @Tomas @JuanAlf @Fernando     %c\n", 186, 186);
    date();
    printf("\n");

    // Prints box down bars
    printBars();
    printf("\n");
}

int main() {

    setbuf(stdout, NULL);

    interface();

    // Declare Variables
    char user[10] = {0};
    char pwd[10] = {0};
    char pwd2[10] = {0};
    int mode = 0;

    //Variable that states the existence of a file: (0 = didn't exist; 1 = existed) -->default: exists
    int fileExists = 1;

    printf("Username:");
    scanf("%s", user);
    fflush(stdin);

    // name change(?)
    printf("Password:");
    scanf("%s", pwd);
    printf("\n");

//============================================================================

    int firstTime = 1;
    int numAccounts = 0;

    Accounts* account;

    char filePath[20] = "./";
    char fileFormat[5] = ".txt";

    strcat(user, fileFormat);
    strcat(filePath, user);

    FILE * fp;
    fp = fopen(filePath, "r");

    if (fp == NULL) //protección para el caso que no exista el fichero
    {
        fp = fopen(filePath, "w"); //se crea el fichero si no existe
        fclose(fp);

        fileExists = 0;
    }
    else {
        fclose(fp);
        // Variable counter that stores the amount of chances the user has to write the correct password
        int counter = 3;
        do {
            createUserInfo(1, &account, 1);
            numAccounts = readUserInfo(filePath, account, pwd);
            counter--;
            // If the file could not be open:
            if (numAccounts == -1) {
                printf("File could not be open");
                return 0;
            }
            // If the password is incorrect (after checking with the checksums)
            else if(numAccounts == -2) {

                printf("Wrong Password, Try Again (You have %d Tries left):", counter);
                scanf("%s", pwd);

                if (counter == 0) {

                    printf("\nNo More Chances Left .... ENTRY BLOCKED .... Closing the Program\n");
                    // Return 0 --> No more chances left, Invalid Password
                    return 0;
                }
            }
        // While the passwords are incorrect --> the while loop will not end
        } while(numAccounts == -2);
    }
//============================================================================

    if(fileExists == 0)
    {
        printBars();

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

            printf("%s -> %s\n", pwd, pwd2);


            if(strcmp(pwd, pwd2) != 0)
            {
                samePwd = 0;
                printf("Passwords are not equal\n\n");

            }

        }while (!samePwd);

    }

    //strlen(user) - 4 is used to not print the ".txt" at the end of the name
    printf("\nWelcome ");
    for(int i =0; i < strlen(user) - 4; i++)
    {
        printf("%c", user[i]);
    }

    do {

        printf("\nSelect what you want to do:\n");
        printf("\t 1) See saved accounts \n"
                      "\t 2) Add a new account \n"
                      "\t 3) Delete account \n"
                      "\t 4) Save and quit \n");

        scanf("%d", &mode);

        //#define **
        switch (mode) {
            case SEE_ACCOUNTS:

                if(numAccounts == 0)
                {
                    printf("You have no accounts, create a new one");
                }
                else
                {
                    for(int i = 0; i < numAccounts; i++)
                    {
                        printf("\nAccount number %d:\n", i + 1);
                        printf("\tUsername: %s\n", account[i].userName);
                        printf("\tPassword: %s\n", account[i].password);
                    }
                }

                break;
            case CREATE_ACCOUNT:
                if (numAccounts == 0) {
                    // malloc
                    createUserInfo(numAccounts + 1, &account, 1);
                }
                else {
                    // realloc
                    createUserInfo(numAccounts + 1, &account, 0);
                }
                fillUserInfo(&account[numAccounts]);
                numAccounts++;
                break;
            case DELETE_ACCOUNT:



                break;
            case SAFE_AND_EXIT:

                writeUserInfo(filePath, account, pwd, numAccounts);

                break;
            default:

                fprintf(stderr, "That is not an option, try again \n ");

                break;
        }
    }while ((mode != 4));


    return 0;

}
