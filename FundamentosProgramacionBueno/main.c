/*
 *  Name Student 1: Juan Alfonso Arribas
 *  Name Student 2: Fernando Azlor Hostaled
 *  Name Student 3: Tomas Juan Uson
 *  Project: Programming Project
 *  Date of Creation: 27 / 12 / 2023
 *  Objective: Main function that does the following:
 *
 */

/// LIBRARIES

// Include Libraries
// Library needed to print the date
#include <time.h>
#include <stdio.h>
#include "fileManager.h"
#include "userInfoManager.h"

#define SEE_ACCOUNTS 1
#define ADD_ACCOUNT 2
#define DELETE_ACCOUNT 3
#define SAVE_AND_EXIT 4

#define SIZE 50
#define SIZE_PATH 70
#define SIZE_FORMAT 5

#define NUMBER_BARS 50
#define DOUBLE_BARS 186
#define BARS_INTERFACE 205

/// WELCOMING INTERFACE FUNCTIONS

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
    // DOUBLE_BARS --> 186 --> ║ (Symbol that our computer keyboards can´t write)
    printf("%c     Date and Time: %s   %c", DOUBLE_BARS , dateString, DOUBLE_BARS);
    return 0;
}

/*
 * Argument:
 *      No parameters
 * Function:
 *      printBars() prints 43 == to create a box
 * Return:
 *      It's a void, so it doesn't return anything
 */
void printBars() {
    // Prints == 43 times to create a box
    // BARS_INTERFACE --> 205 --> ASCII Code for a Symbol our computer keyboards can't write
    for(int i = 0; i < NUMBER_BARS; i++)
    {
        printf("%c", BARS_INTERFACE);
    }
    printf("\n");
}

/*
 * Argument:
 *      No argument
 * Function:
 *      interface() prints an interface for the program
 * Return:
 *      It's a void, so it doesn't return anything
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
    printf("%c       Welcome to heaven's account Manager      %c\n", DOUBLE_BARS, DOUBLE_BARS);
    // Introduce Developers
    printf("%c    V1.0 Copyright @Tomas @JuanAlf @Fernando    %c\n", DOUBLE_BARS, DOUBLE_BARS);
    // Print date
    date();
    printf("\n");

    // Prints box down bars
    printBars();
    printf("\n");
}

/*
 * Argument:
 *      No argument
 * Function:
 *      Prints the Instructions of the Program
 * Return:
 *      It's a void, so it doesn't return anything
 */
void instructionsProgram() {
    // Prints Instructions of the Program
    printf("\nYou are a new user, so we will explain how to use the program:\n"
           "This program stores user accounts encrypted with the password\n"
           "that you have entered, Once you have finished the initial creation of your profile\n"
           "you will be asked to enter the username/e-mail of the account first\n"
           "to store, and then the password. Once you have finished adding\n"
           "accounts, the manager will encrypt and store your information.\n\n"

           "As you are creating a new profile, let's make sure that the\n"
           "the master password you have entered is the correct one.\n\n");
}

/// FILE CHECKS FUNCTIONS

/*
 * Argument:
 *      char firstPassword[]  --> Master Password that the user Entered
 *      char secondPassword[] --> Master Password that the user Entered to Check If he had Written the Correct One
 * Function:
 *      Checks if the Passwords are Equal
 * Return:
 *      1 (True)  --> If the Passwords are Equal
 *      0 (False) --> If the Password are Different
 */
int equalPassword(const char firstPassword[], const char secondPassword[]) {
    // Comparison of Passwords
    return strcmp(firstPassword, secondPassword) == 0;
}


/*
 * Argument:
 *      char firstPassword[]  --> Master Password that the user Entered
 *      char secondPassword[] --> Master Password that the user Entered to Check If he had Written the Correct One
 * Function:
 *      Asks the User to Introduce the Password Again to Check If the User Didn't Introduce the Wrong Password.
 *      If they aren't the Same, then Ask For a New Password, and repeat the Process.
 * Return:
 *      It's a void, so it doesn't return anything (masterPassword goes through Reference)
 */
void checkSamePassword(char* masterPassword) {
    // Store the Second Time the Password was Used
    char auxiliaryPassword[SIZE] = {0};
    // Ask the user to Enter the Password Again
    printf("Introduce Again the Password:");
    // Store the Password in auxiliaryPassword
    scanf("%s", auxiliaryPassword);

    // If the Passwords aren't Equal Ask Again Until They Are
    while(!equalPassword(masterPassword, auxiliaryPassword)) {
        // Inform the User that the Password Entered weren't the Same
        printf("\nThe Password aren't equal.\n");
        // Ask the User to Enter a New Master Password
        printf("\nIntroduce a new Password:");
        // Store the New Master Password in masterPassword
        scanf("%s", masterPassword);

        // Ask the User to Enter the New Master Password Again
        printf("Introduce the Password Again:");
        // Store the Password in auxiliaryPassword
        scanf("%s", auxiliaryPassword);
    }
    // Prints End Of Line
    printf("\n");
}

/*
 * Argument:
 *      char* filePath --> Address of the Character Array where we Store the Data Path of the File
 * Function:
 *      First it creates the Data Path to the File.
 *      Then, Checks if the File Already Existed and if not, Create It
 * Return:
 *      0 --> If the File didn't Exist and Had to be Created
 *      1 --> If the File Already Existed
 */
int fileExists(char* filePath, const char* masterUsername) {
    // Variable to Store the Name of the File (Username) and Initialize it to 0 (NULL)
    // Note: We do it to not lose the Username
    char fileName[SIZE];

    // Copy the masterUsername on to fileName
    strcpy(fileName, masterUsername);

    // Format of the File
    char fileFormat[SIZE_FORMAT] = ".txt";

    // Piece Together the Data Path of the File.
    // File = Username + Format
    strcat(fileName, fileFormat);
    // Data Path = Path + File
    strcat(filePath, fileName);

    // Pointer that Points to Files
    FILE * fp;
    // Open Binary File
    fp = fopen(filePath, "rb");

    // Check if the File Exist
    // If it Does Not Exist
    if (fp == NULL) {
        // Then We Create It
        fp = fopen(filePath, "wb");
        // Check if the File Was Created
        if (fp == NULL) {
            // Inform of an ERROR
            fprintf(stderr, "ERROR: File Could not be Created");
            // Terminate Abruptly the Program (We found exit(EXIT_FAILURE) through the Internet)
            exit(EXIT_FAILURE);
        }
        // Close File
        fclose(fp);
        // Return 0 --> File Had to Be Created Because It Did Not Exist
        return 0;
    }
    // If the File Does Exist
    else {
        // Then we Close It
        fclose(fp);
        // Return 1 --> File Did Exist
        return 1;
    }
}

/// PROGRAM OPERATIONS FUNCTIONS

/*
 * Argument:
 *      No argument
 * Function:
 *      Ask the User which Operation would he Like To Pick and Return It
 * Return:
 *      mode --> Operation the user has picked
 */
int selectOperation() {
    // Variable to Store the Mode of the Program
    int mode = 0;
    // Inform User of the Different Functions of the Program
    printf("\nWhat would you like to do?\n");
    printf("\t 1) See saved accounts \n"
           "\t 2) Add a new account \n"
           "\t 3) Delete account \n"
           "\t 4) Save and quit \n");
    // Ask the User to Pick Between One of Them
    printf("Select an option:");
    // Store the Function on Mode
    scanf("%d", &mode);
    // Empty Buffer
    fflush(stdin);
    return mode;
}

/*
 * Argument:
 *      Account* user   --> Array Of Structures with the Information of All the Accounts
 *      int numAccounts --> Number of Accounts the User Has Created
 * Function:
 *      Prints the Information of the Accounts following the next structure:
 *      Account number x:
 *          Username:
 *          Password:
 * Return:
 *      It's Void so Nothing
 */
void showAccounts(Account* user, const int numAccounts) {
    // If the User Has No Accounts, Inform the User
    if(numAccounts == 0) {
        // Inform the User
        printf("\nYou have No Accounts, Create a New One\n");
    }
    // If the Use Has Accounts, Print the Data of Them
    else {
        // Loop that goes through all the accounts of the user
        for(int i = 0; i < numAccounts; i++) {
            // Print Number of the Account
            printf("\nAccount Number %d:\n", i + 1);
            // Print Username of the Account
            printf("\tUsername: %s\n", user[i].username);
            // Print Password of the Account
            printf("\tPassword: %s\n", user[i].password);
        }
    }
}

/*
 * Argument:
 *      Account** user  --> Array Of Structures with the Address of All the Accounts
 *      int numAccounts --> Number of Accounts the User Has Created
 * Function:
 *      First, Add One more Account to numAccounts
 *      Then, Allocates Memory Space in the Array of Structures for the New Account.
 *      Finally, Add the Information of the New Account
 * Return:
 *      It's Void so Nothing
 */
void addAccount(Account** user, int* numAccounts) {
    // Add One More Account to numAccount
    (*numAccounts)++;
    // If the Number of Accounts is 1 now, it Means there was No Account Before
    // So we have to allocate some memory for the information to Fit
    if (*numAccounts == 1) {
        // Allocate Memory to Fit the Information of the New Account
        *user = createUserInfo(*numAccounts);
    }
    // If the Number of Account is More than 1, Then we Add one More Memory Space to Fit the New Account
    else {
        // Add more Memory Space to Fit the Information of the New Account
        *user = realloc(*user, *numAccounts * sizeof(Account));
        // Check if the allocation was successful
        if (*user == NULL) {
            // Inform of an ERROR
            fprintf(stderr, "ERROR: Memory ReAssignment of the Accounts Failed (Operation 2)");
            // Terminate Abruptly the Program (We found exit(EXIT_FAILURE) through the Internet)
            exit(EXIT_FAILURE);
        }
    }
    // Add the New Account to the Array of Structs
    fillUserInfo(&((*user)[*numAccounts - 1]));
}

/*
 * Argument:
 *      int numAccount --> Number of Accounts of the User
 * Function:
 *      Ask the User which Account would he like to Delete
 * Return:
 *      index - 1 --> Real Index (Index on the Array) of the Account we will be Erasing
 */
int indexAccount(const int numAccounts) {
    // Variable to Store the Index of the Account
    int index;
    // Do at least Once:
    do{
        // Ask the User to Pick the Account to Delete
        printf("\nWhich Account Would you like to Delete? (1 - %d):", numAccounts);
        // Store the Index of the Account on index
        scanf("%d", &index);
        // Empty Buffer
        fflush(stdin);

        // If the Index is Out of Limits
        if (index < 1 || index > numAccounts) {
            printf("That Account doesn't Exist, Please Pick Another One\n");
        }

        // The Loop Will Repeat Until the User Gives a Valid Index
    }while (index < 1 || index > numAccounts) ;
    // Return the Index of the Account on the Array
    return index - 1;
}

/// MAIN

int main() {

    /// INTERFACE AND ASK FOR THE FIRST VALUES (USERNAME AND PASSWORD)

    // Print Interface welcoming the user
    interface();

    // Variable to Store the Master Username (Initialized to 0)
    char masterUsername[SIZE] = {0};
    // Ask User for the Master Username
    printf("Please User, Introduce your Username:");
    // Store Username on masterUsername
    scanf("%s", masterUsername);
    // Empty Buffer
    fflush(stdin);

    // Variable to Store the Master Password (Initialized to 0)
    char masterPassword[SIZE] = {0};
    // Ask the user for the Master Password
    printf("Please User, Introduce your Password:");
    // Store the Password in the masterPassword
    scanf("%s", masterPassword);
    // Empty Buffer
    fflush(stdin);

    /// CHECK IF THE FILE EXISTS

    // Data Path to the File
    char filePath[SIZE_PATH] = "./";

    // Data Structure Where the Data of the Accounts Will Be Stored
    Account* user;

    // Variable to Store the Number of Accounts
    int numAccounts = 0;

    // If the File didn't Exist, Create One and Print the Instructions of the Program
    if (!fileExists(filePath, masterUsername)) {
        // Prints Instructions of the Program
        instructionsProgram();
        // Check if the Passwords are Equal
        checkSamePassword(masterPassword);
    }
    // If the File Exist, Read the File and Check if the Master Password is the Correct One
    else {
        // Number of Chances the User has to Give the Program the Correct Master Password
        int attemptsPassword = 3;
        // While ( the Checksums don't Add up then --> Account* user == NULL ) the Loop will Continue:
        // Which means the User entered the Wrong Password
        while ((user = readUserInfo(filePath, masterPassword, &numAccounts)) == NULL) {
            // If the User has no More Attempts Then the Program Closes
            if (attemptsPassword == 0) {
                // Inform the User
                printf("\nNo More Chances Left .... ENTRY BLOCKED .... Closing the Program\n");
                // Free Allocated Memory
                free(user);
                // Return 0 --> No more chances left, Invalid Password
                return 0;
            }
            // If the user has more Chances
            else {
                // Inform the User of the Situation and Ask for the Correct Master Password
                printf("\nWrong Password, Try Again (You have %d Tries left):", attemptsPassword);
                // Store the New Password on masterPassword
                scanf("%s", masterPassword);
                // One Less Attempt for the User to Guess the Correct Password
                attemptsPassword--;
            }
        }
    }

    /// OPERATIONS OF THE PROGRAM {SHOW - ADD - DELETE - SAVE&EXIT}

    // Variable to Store the Mode the User Picked
    int operation;

    // Welcome the User to the Program
    printf("\nWelcome, %s!", masterUsername);

    // Operation of the Program
    do {
        // The User Selects the Operation
        operation = selectOperation();
        // Each Operation:
        switch (operation) {
            // Operation 1: Show through the Console All the Accounts of the User
            case SEE_ACCOUNTS:
                // Show the Accounts
                showAccounts(user, numAccounts);
                break;

            // Operation 2: Add a New Account
            case ADD_ACCOUNT:
                // Add the Account
                addAccount(&user, &numAccounts);
                // Inform the User
                printf("\nThe New Account Has Been Added Successfully\n");
                break;

            // Operation 3: Delete an Account
            case DELETE_ACCOUNT:
                // If There are Accounts, Delete One
                if (numAccounts != 0) {
                    // Delete the Account
                    deleteUser(&user, indexAccount(numAccounts), &numAccounts);
                    // Inform the User
                    printf("\nThe New Accounts Has Been Deleted Successfully\n");
                }
                // If there Aren't Inform the User
                else {
                    // Inform the User
                    printf("\nYou have No Accounts, Create a New One\n");
                }
                break;

            // Operation 4: Save the Information of the Accounts on a File and Exit the Program
            case SAVE_AND_EXIT:
                // Write on a File the Information of the Accounts to Save It
                writeUserInfo(filePath, user, masterPassword, numAccounts);
                // Free the Memory Allocated During the Program
                freeAllUserInfo(user, numAccounts);
                // Wish Farewell the User
                printf("\nFarewell %s, Have a Nice Day!!\n", masterUsername);
                break;

            // If the User picks An Non-Existent Mode
            default:
                // Inform of his Choice and Ask the User To Pick Another Mode
                printf("\nThis Operation Doesn't Exist, Please Pick Another One\n");
                break;
        }
    // Until the User Picks Mode Nº4 The Loop will Continue
    } while (operation != SAVE_AND_EXIT);

    // Return 0 --> Exit the Program (Everything Went Alright)
    return 0;
}

