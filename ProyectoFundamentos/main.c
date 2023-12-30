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
 *      No parameters
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

    // Check if we were successful obtaining the current time
    if (currentTime == ((time_t)-1)) {
        // Print an ERROR message informing that we couldn't obtain the current time
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
 *      No parameters
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
    //ASCII ART to WELCOME the user
    printf(" __      __        __\n");
    printf("/  \\    /  \\ ____ |  |   ____  ____   _____   ____\n");
    printf("\\   \\/\\/   // __ \\|  | _/ ___\\/    \\ /     \\ / __ \\\n");
    printf(" \\        /\\  ___/|  |_\\  \\__(  <_> )  y y  \\  ___/\n");
    printf("  \\__/\\__/  \\____ |____/\\___/ \\____/|__|_|__/\\____\n");

    // Prints box top bars
    printBars();

    // Welcome the user, Introduce Developers and Print Date
    // 186 --> ║ (Symbol that our computer keyboards can´t write)
    // Welcome user
    printf("%c Welcome to heaven's account Manager     %c\n", 186, 186);
    // Introduce Developers
    printf("%c Creators: @Tomas @JuanAlf @Fernando     %c\n", 186, 186);
    // Print date
    date();
    printf("\n");

    // Prints box down bars
    printBars();
    printf("\n");
}

int main() {

    // RECORDATORIO:
    // TENEMOS QUE BORRAR ESTE CÓDIGO YA QUE SOLO SIRVE PARA HACER DEBBUGING
    // (OCUPA ESPACIO Y ES MALA PRAXIS DEJARLO)
    setbuf(stdout, NULL);

    // Print Interface welcoming the user
    interface();

    // Declare Variables ESCRIIBR ESTO ADECUADAMENTE
    char user[10] = {0};
    char pwd[10] = {0};
    char pwd2[10] = {0};
    int mode = 0;

    // Boolean variable that states the existence of a file:
    //      0 --> File does not exist (It means it's the first time the user uses the program)
    //      1 --> File exists (Default state)
    int fileExists = 1;

    // Ask the user for the username of the account
    printf("Username:");
    // Store username in user
    scanf("%s", user);
    // Empty the buffer
    fflush(stdin);

    // Ask the user for the password of the account
    printf("Password:");
    // Store password in pwd
    scanf("%s", pwd);
    printf("\n");
    // Empty the buffer
    fflush(stdin);

//============================================================================

    // Variable to store the nº of accounts
    int numAccounts = 0;
    // Create pointer that points to a type Accounts struct
    Accounts* account;

    // Array of character that stores the path to the file
    char filePath[20] = "./";
    // Array of Characters that stores the file format
    char fileFormat[5] = ".txt";

    // Link together the path, username and file format, to create the complete path to the file
    // Concatenate the username and the file format
    strcat(user, fileFormat);
    // Concatenate the path and the file (username + file format)
    strcat(filePath, user);

    // Create pointer to file
    FILE * fp;
    // Try to open the file, so we can know if it exists
    fp = fopen(filePath, "rb");
    // If the file does not exist, or we cannot access to it
    if (fp == NULL) {
        // We create the file (By opening the file in writing mode)
        fp = fopen(filePath, "wb");
        // Close the file we just created
        fclose(fp);
        // The file didn't exist so 0 (It means it's the first time the user uses the program)
        fileExists = 0;
    }
        // If not then the file already exists
    else {
        // Close the file we just opened AÑADIR LA LÍNEA ESTARÍA BIEN
        fclose(fp);
        // Stores the amount of chances the user has to write the correct password
        int counter = 3;
        // Do the next piece of code at least once
        do {
            //
            createUserInfo(1, &account, 1);
            numAccounts = readUserInfo(filePath, &account, pwd);
            counter--;
            // If the file could not be open:
            if (numAccounts == -1) {
                printf("File could not be open");
                return 0;
            }
                // If the password is incorrect (after checking with the checksums)
            else if(numAccounts == -2) {
                free(account);
                if (counter == 0) {
                    printf("\nNo More Chances Left .... ENTRY BLOCKED .... Closing the Program\n");
                    // Return 0 --> No more chances left, Invalid Password
                    return 0;
                }
                else {
                    printf("Wrong Password, Try Again (You have %d Tries left):", counter);
                    scanf("%s", pwd);
                }
            }
            // While the passwords are incorrect --> The while loop will not end
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
    for(int i = 0; i < strlen(user) - 4; i++)
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
        int index;

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

                printf("Which account do you want to delete:");
                scanf("%d", &index);

                if(index > numAccounts || index < 1)
                {
                    printf("There is no account in this slot\n");
                }
                else
                {
                    deleteUser(numAccounts, index, account);
                    numAccounts--;
                    createUserInfo(numAccounts, &account, 0);
                }

                break;
            case SAFE_AND_EXIT:


                writeUserInfo(filePath, account, pwd, numAccounts);

                break;
            default:

                fprintf(stderr, "That is not an option, try again \n ");

                break;
        }
    }while ((mode != 4));

    // Return 0 (Everything Went Alright)
    return 0;

}

