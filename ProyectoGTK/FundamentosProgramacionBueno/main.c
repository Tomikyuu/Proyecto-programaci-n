/*
 *  Name Student 1: Juan Alfonso Arribas
 *  Name Student 2: Fernando Azlor Hostaled
 *  Name Student 3: Tomas Juan Uson
 *  Project: Programming Project
 *  Date of Creation: 27 / 12 / 2023
 *  Objective: Create an Account Manager that first ask the user for the username and password of the
 *             master account. Afterward, creates the text file where the information will be stored
 *             and gives the user the chance to pick between the 4 operations:
 *             1) See Accounts
 *             2) Add Accounts
 *             3) Delete Accounts
 *             4) Exit
 *             The operation do as the names suggest. Once the user picks 4 the program will end, until
 *             it will continue in a loop.
 *
 */

/// LIBRARIES

// Include Libraries
// Library needed to print the date
#include <time.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include "fileManager.h"
#include "userInfoManager.h"

#define SEE_ACCOUNTS 1
#define ADD_ACCOUNT 2
#define DELETE_ACCOUNT 3
#define SAVE_AND_EXIT 4

#define SIZE 100
#define SIZE_PATH 200
#define SIZE_FORMAT 5

// Global variables to handle the data transfer from the GUI to the variables on the code
//The first char, has to be big enough to store all the accounts of a user in any given moment
char text1[10000] = {0}, text2[SIZE] = {0};
//Numerical variables for the different modes
int numerical_button = 0;

// Struct to store the GTK Widgets of user and password
typedef struct {
    GtkWidget *box1;
    GtkWidget *box2;
} UserData;

// Gets the time in an array format to be used by the login window
char* date_GTK() {
    static char time_string[128];
    time_t currentTime = time(NULL);
    if (currentTime != (time_t)-1) {
        strftime(time_string, sizeof(time_string), "| Date and Time: %Y-%m-%d %H:%M:%S |", localtime(&currentTime));
        return time_string;
    }
    return "Failure to obtain the current time.";
}

///HEADERS OF ALL THE DIFFERENT FUNCTIONS USED BY THE GUI

//Opens the welcome window
static void welcome_window(GtkApplication *app, gpointer user_data);
//Handles the close input from the welcome window, and sends the signal to open the login window
static void welcome_button(GtkWidget *widget, gpointer data);
//Opens the login window
static void login_window(GtkWidget *widget, gpointer *args);

//Opens the program instructions window
void instructionsProgram_window();
//Handles the close input from the instructions window, and stores the password confirmation.
void instructionsProgramButton(GtkWidget *window, gpointer data);

//Opens the operation window
void selectOperation_window();
//Handles the close input from the instructions window, and stores the password confirmation.
void selectOperation_button(GtkWidget *widget, gpointer data);

//Opens the deleting account window
void indexAccount_window();
//Handles the close input from the operation window, and stores the value of the operation to make.
static void indexAccount_button(GtkButton *button, gpointer user_data);

//Opens the accounts window
void showAccounts_window();
//Handles the close input from the accounts window.
void showAccounts_button(GtkWidget *widget, gpointer window);

//Opens the window of re-enterig the password after a fail of an already existing account
void wrong_Password();
//Handles the close input from the wrong_Password window, and stores the value of new try.
void wrong_Password_Button(GtkWidget *window, gpointer data);

//Opens the window of re-enterig the password after a creating a new account with different passwords
void passwordChange();
//Handles the close input from the passwordChange window, and stores the value of the new password.
void password_Button(GtkWidget *widget, gpointer data);

///WELCOME AND START

static void welcome_window(GtkApplication *app, gpointer user_data) {

    // Create a new window for the application
    GtkWidget *window = gtk_application_window_new(app);

    // Set the title of the window
    gtk_window_set_title(GTK_WINDOW(window), "Welcome to Heaven's Account Manager");

    // Set the default size of the window to 300x200 pixels
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    // Create a vertical box container with a spacing of 5 pixels between children
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    // Add the vertical box to the window
    gtk_container_add(GTK_CONTAINER(window), vbox);

    ///PLEASE CHANGE THE ROUTE TO YOUR CURRENT ONE
    // Create an image widget from a file
    GtkWidget *image = gtk_image_new_from_file("INSERT YOUR ROUTE");

    // Add the image widget to the vertical box, allowing it to expand and fill space
    gtk_box_pack_start(GTK_BOX(vbox), image, TRUE, TRUE, 0);

    // Create a button with the label "Next"
    GtkWidget *button = gtk_button_new_with_label("Next");

    // Create an argument array to store the window and app pointers
    gpointer *args = g_new0(gpointer, 2);
    args[0] = window;
    args[1] = app;

    // Connect the "clicked" signal of the button to the login_window function
    g_signal_connect_data(button, "clicked", G_CALLBACK(login_window), args, (GClosureNotify)g_free, 0);

    // Add the button to the vertical box, without expanding or filling space
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

    // Make the window and all its children visible
    gtk_widget_show_all(window);
}
static void welcome_button(GtkWidget *widget, gpointer data) {
    // Cast the user data and retrieve username and password from the entry fields
    UserData *user_data = (UserData *)data;
    const char *username = gtk_entry_get_text(GTK_ENTRY(user_data->box1));
    const char *password = gtk_entry_get_text(GTK_ENTRY(user_data->box2));

    // Copy username and password to global variables for later use
    strncpy(text1, username, sizeof(text1) - 1);
    strncpy(text2, password, sizeof(text2) - 1);

    // Close the current window
    gtk_widget_destroy(gtk_widget_get_toplevel(widget));
}
static void login_window(GtkWidget *widget, gpointer *args) {
    // Retrieve the welcome window and application object passed as arguments
    GtkWidget *welcome_window = GTK_WIDGET(args[0]);
    GtkApplication *app = GTK_APPLICATION(args[1]);

    // Destroy the welcome window
    gtk_widget_destroy(welcome_window);

    // Declare widgets needed for the login window
    GtkWidget *window, *vbox, *hbox_user, *hbox_pass, *submit_button;
    UserData *user_data_local = g_new0(UserData, 1);

    // Create a new window for the application
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Can't believe it's working");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 300);

    // Create a vertical box to organize widgets vertically
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create and add labels to the vertical box
    GtkWidget *label1 = gtk_label_new("Welcome to Heaven's Account Manager");
    GtkWidget *label2 = gtk_label_new("V1.0 Copyright @Tomas @JuanAlf @Fernando");
    GtkWidget *label3 = gtk_label_new(date_GTK());

    // Create username entry field with placeholder text
    user_data_local->box1 = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(user_data_local->box1), "User Here, don't leave it empty");

    // Create password entry field with placeholder text and hidden visibility
    user_data_local->box2 = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(user_data_local->box2), "Password Here, don't leave it empty");
    gtk_entry_set_visibility(GTK_ENTRY(user_data_local->box2), FALSE);

    // Create a submit button and connect its "clicked" signal to the welcome_button callback
    submit_button = gtk_button_new_with_label("Submit");
    g_signal_connect(submit_button, "clicked", G_CALLBACK(welcome_button), user_data_local);

// Create horizontal boxes for user and password fields
    hbox_user = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    hbox_pass = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

// Add user label and entry field to the user horizontal box
    gtk_box_pack_start(GTK_BOX(hbox_user), gtk_label_new("USER: "), FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox_user), user_data_local->box1, TRUE, TRUE, 5);

// Add password label and entry field to the password horizontal box
    gtk_box_pack_start(GTK_BOX(hbox_pass), gtk_label_new("PASSWORD: "), FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox_pass), user_data_local->box2, TRUE, TRUE, 5);

// Add labels and horizontal boxes to the vertical box
    gtk_box_pack_start(GTK_BOX(vbox), label1, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), label2, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), label3, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox_user, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox_pass, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), submit_button, FALSE, FALSE, 0);

// Make the window and all its components visible
    gtk_widget_show_all(window);

}

// Prints Instructions of the Program
void instructionsProgram() {
    printf("\nYou are a new user, so we will explain how to use the program:\n"
           "This program stores user accounts encrypted with the password\n"
           "that you have entered, Once you have finished the initial creation of your profile\n"
           "you will be asked to enter the username/e-mail of the account first\n"
           "to store, and then the password. Once you have finished adding\n"
           "accounts, the manager will encrypt and store your information.\n\n"

           "As you are creating a new profile, let's make sure that the\n"
           "the master password you have entered is the correct one.\n\n");
}

void instructionsProgramButton(GtkWidget *window, gpointer data) {
    // Retrieve a GtkWidget pointer (entry widget) stored in the window object
    GtkWidget *entry = g_object_get_data(G_OBJECT(window), "entry");

    // Get the text entered in the entry widget
    const gchar *entry_text = gtk_entry_get_text(GTK_ENTRY(entry));

    // Copy the text from the entry widget to a global or static buffer 'text1'
    strncpy(text1, entry_text, sizeof(text1) - 1);

    // Ensure the string is null-terminated to prevent buffer overrun
    text1[sizeof(text1) - 1] = '\0';

    // Destroy the window containing the entry widget
    gtk_widget_destroy(window);
}
void instructionsProgram_window() {
    GtkWidget *window, *button, *label, *vbox, *entry;

    // Create a new top-level window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Program Instructions");
    gtk_window_set_default_size(GTK_WINDOW(window), 550, 200);

    // Create a vertical box container to organize widgets
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create an entry widget (text input field)
    entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Please enter the password again");
    gtk_box_pack_start(GTK_BOX(vbox), entry, TRUE, TRUE, 0);

    // Create a label with instructional text
    label = gtk_label_new("You have created a new account. Use this box to confirm password\n"
                          "\n"
                          "Since you are a new user, will explain how to use the program, please pay close attention:\n"
                          "           This program stores user accounts encrypted with the password\n"
                          "           that you have entered, Once you have finished the initial creation of your profile\n"
                          "           you will be asked to enter the username/e-mail of the account first\n"
                          "           to store, and then the password. Once you have finished adding\n"
                          "           accounts, the manager will encrypt and store your information.\n"

                          "           As you are creating a new profile, let's make sure that the\n"
                          "           the master password you have entered is the correct one.\n"
                          "\n"
                          "PLEASE GE GENTLE WITH THE PROGRAM AND DONT TRY TO TRY AND BREAK IT, THO ITS PRETTY ROBUST\n"
                          "IT MAY CAUSE SOME MALFUNCTIONS, BUT NOT TO THE POINT OF CAUSING DAMAGE TO THE PROGRAM OR COMPUTER\n"
                          " Also, please notice that all the possible error message will be displayed in the terminal.\n"
                          " They wont be visible on the windows, so if something goes wrong, please check in there");
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);

    // Create a button with the label "I understand"
    button = gtk_button_new_with_label("I understand");
    gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);

    // Connect the button's "clicked" signal to the instructionsProgramButton function
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(instructionsProgramButton), window);

    // Store the entry widget in the window object for later retrieval
    g_object_set_data(G_OBJECT(window), "entry", entry);

    // Display all widgets in the window
    gtk_widget_show_all(window);

    // Connect the window's "destroy" signal to exit the GTK main loop
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
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
    strncpy(auxiliaryPassword, text1, sizeof(auxiliaryPassword) - 1);

    // If the Passwords aren't Equal Ask Again Until They Are
    while(!equalPassword(masterPassword, auxiliaryPassword)) {
        //Call the window
        passwordChange();
        //Change the values from the window
        strncpy(masterPassword, text1, sizeof(masterPassword) - 1);
        strncpy(auxiliaryPassword, text2, sizeof(auxiliaryPassword) - 1);
        //OLD CODE COMPARISON
       /* // Inform the User that the Password Entered weren't the Same
        printf("\nThe Password aren't equal.\n");
        // Ask the User to Enter a New Master Password
        printf("\nIntroduce a new Password:");
        // Store the New Master Password in masterPassword
        scanf("%s", masterPassword);

        // Ask the User to Enter the New Master Password Again
        printf("Introduce the Password Again:");
        // Store the Password in auxiliaryPassword
        scanf("%s", auxiliaryPassword);*/

    }
    // Prints End Of Line
    printf("\n");
}

void wrong_Password_Button(GtkWidget *window, gpointer data) {
    // Retrieve the entry widget stored in the window object
    GtkWidget *entry = g_object_get_data(G_OBJECT(window), "entry");

    // Get the text entered in the entry widget
    const gchar *entry_text = gtk_entry_get_text(GTK_ENTRY(entry));

    // Copy the text from the entry widget to a global or static buffer 'text1'
    strncpy(text1, entry_text, sizeof(text1) - 1);

    // Ensure the string is null-terminated to prevent buffer overrun
    text1[sizeof(text1) - 1] = '\0';

    // Destroy the window containing the entry widget
    gtk_widget_destroy(window);
}
void wrong_Password() {
    GtkWidget *window, *button, *label, *vbox, *entry;

    // Create a new top-level window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Wrong password");
    gtk_window_set_default_size(GTK_WINDOW(window), 550, 200);

    // Create a vertical box container for organizing widgets
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create an entry widget (text input field) for password re-entry
    entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Please enter the password again");
    gtk_box_pack_start(GTK_BOX(vbox), entry, TRUE, TRUE, 0);

    // Create a label with a message about the wrong password attempt
    label = gtk_label_new("The password you have tried is not correct\n"
                          "you have 3 chances, (I will not count them), else the program will finish");
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);

    // Create a button with the label "I understand"
    button = gtk_button_new_with_label("I understand");
    gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);

    // Connect the button's "clicked" signal to the wrong_Password_Button function
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(wrong_Password_Button), window);

    // Associate the entry widget with the window for later access
    g_object_set_data(G_OBJECT(window), "entry", entry);

// Display all the widgets in the window
    gtk_widget_show_all(window);

// Set up the window to exit the GTK main loop when it's closed
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

}
void password_Button(GtkWidget *widget, gpointer data) {
    // Assign text from the two text entry widgets to global variables text1 and text2
    strcpy(text1, gtk_entry_get_text(GTK_ENTRY(((GtkWidget **)data)[0])));
    strcpy(text2, gtk_entry_get_text(GTK_ENTRY(((GtkWidget **)data)[1])));

    //Print the texts to verify (useful for debugging)
    g_print("Text1: %s\n", text1);
    g_print("Text2: %s\n", text2);

    // Close the window containing the button
    gtk_widget_destroy(gtk_widget_get_toplevel(widget));
}
void passwordChange() {
    GtkWidget *window, *button, *entry1, *entry2, *label, *vbox;

    // Initialize GTK
    gtk_init(NULL, NULL);

    // Create the main window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Password Change");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a vertical box to contain the widgets
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create and add a label
    label = gtk_label_new("                 Ups...\n"
                          "It seems like the passwords are different\n"
                          "Let's change it, and remember the correct one");
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

    // Create and add text entry boxes
    entry1 = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), entry1, FALSE, FALSE, 0);
    entry2 = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), entry2, FALSE, FALSE, 0);

    // Create and add a button
    button = gtk_button_new_with_label("Submit");
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

    // Connect the "clicked" signal of the button to the callback function
    GtkWidget *entries[] = {entry1, entry2};
    g_signal_connect(button, "clicked", G_CALLBACK(password_Button), entries);

    // Show all widgets
    gtk_widget_show_all(window);

    // Start the main GTK loop
    gtk_main();
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
    //OLD CODE FOR COMPARISON
    //scanf("%d", &mode);
    mode = numerical_button;
    // Empty Buffer
    fflush(stdin);
    return mode;
}

void selectOperation_button(GtkWidget *widget, gpointer data) {
    // Convert the data pointer to an integer and assign it to the global variable 'numerical_button'
    numerical_button = GPOINTER_TO_INT(data);

    // Destroy the top-level window that contains the widget
    gtk_widget_destroy(gtk_widget_get_toplevel(widget));
}
void selectOperation_window() {
    GtkWidget *window, *label, *button1, *button2, *button3, *button4, *vbox, *hbox;

    // Create a new top-level window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "What do you want to do");
    gtk_window_set_default_size(GTK_WINDOW(window), 475, 200);

    // Connect the window's "destroy" event to exit the GTK main loop
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a label with the operation options
    label = gtk_label_new("1) See saved accounts\n"
                          "2) Add a new account\n"
                          "3) Delete account\n"
                          "4) Save and quit\n");

    // Create buttons for each operation
    button1 = gtk_button_new_with_label("1");
    button2 = gtk_button_new_with_label("2");
    button3 = gtk_button_new_with_label("3");
    button4 = gtk_button_new_with_label("4");

    // Connect each button's "clicked" signal to the selectOperation_button callback
    // The button number is passed as data to the callback
    g_signal_connect(button1, "clicked", G_CALLBACK(selectOperation_button), GINT_TO_POINTER(1));
    g_signal_connect(button2, "clicked", G_CALLBACK(selectOperation_button), GINT_TO_POINTER(2));
    g_signal_connect(button3, "clicked", G_CALLBACK(selectOperation_button), GINT_TO_POINTER(3));
    g_signal_connect(button4, "clicked", G_CALLBACK(selectOperation_button), GINT_TO_POINTER(4));

    // Create a vertical box to contain the label and buttons
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);

    // Create a horizontal box to arrange the buttons
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(hbox), button1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), button2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), button3, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), button4, TRUE, TRUE, 0);

    // Add the horizontal box containing buttons to the vertical box
    gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 0);

    // Add the vertical box to the window
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Show all widgets in the window
    gtk_widget_show_all(window);
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

            //Use the for loop to write the accounts in the general char text1
            snprintf(text1 + strlen(text1), 10000 - strlen(text1), "\nAccount Number %d:\n", i + 1);
            snprintf(text1 + strlen(text1), 10000 - strlen(text1), "\tUsername: %s\n", user[i].username);
            snprintf(text1 + strlen(text1), 10000 - strlen(text1), "\tPassword: %s\n", user[i].password);

        }
    }
}

void showAccounts_button(GtkWidget *widget, gpointer window) {
    // Destroy the window passed as the gpointer argument
    gtk_widget_destroy(GTK_WIDGET(window));
}
void showAccounts_window() {
    GtkWidget *window, *label, *button, *vbox;

    // Initialize GTK
    gtk_init(NULL, NULL);

    // Create a new top-level window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Accounts");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

    // Create a vertical box container
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create a label with the text from the global variable text1
    label = gtk_label_new(text1);
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);

    // Create a "Close" button
    button = gtk_button_new_with_label("Close");
    gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);

    // Connect the "Close" button to the showAccounts_button function
    g_signal_connect(button, "clicked", G_CALLBACK(showAccounts_button), window);

    // Show all widgets in the window
    gtk_widget_show_all(window);
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
        index = numerical_button;
        indexAccount_window();
        gtk_main();
        //scanf("%d", &index);
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

static void indexAccount_button(GtkButton *button, gpointer user_data) {
    // Cast user_data to GtkEntry* to access the entry widget
    GtkEntry *entry = (GtkEntry *)user_data;

    // Retrieve the text entered in the entry widget
    const char *text = gtk_entry_get_text(entry);

    // Convert the text to an integer and store it in the global variable 'numerical_button'
    numerical_button = atoi(text);
}
void indexAccount_window() {
    GtkWidget *window, *button, *entry, *label, *vbox;

    // Create the main window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Deleting account");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a VBox for vertical organization of widgets
    vbox = gtk_vbox_new(FALSE, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create and add a label
    label = gtk_label_new("Which Account Would you like to Delete?\n"
                          "Please enter the number of the account\n"
                          "You will be asked to confirm the number");
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

    // Create and add an entry widget
    entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);

    // Create and add a submit button
    button = gtk_button_new_with_label("Submit");
    // Connect the button's "clicked" signal to the indexAccount_button function
    g_signal_connect(button, "clicked", G_CALLBACK(indexAccount_button), entry);
    // Connect the button's "clicked" signal to also destroy the window
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), window);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

    // Show all widgets
    gtk_widget_show_all(window);
}

/// MAIN
int main(int argc, char **argv) {

    /// INTERFACE AND ASK FOR THE FIRST VALUES (USERNAME AND PASSWORD)


        GtkApplication *app = gtk_application_new("org.example.myapp", G_APPLICATION_FLAGS_NONE);
        g_signal_connect(app, "activate", G_CALLBACK(welcome_window), NULL);
        int status = g_application_run(G_APPLICATION(app), argc, argv);
        g_object_unref(app);

        char masterUsername[SIZE] = {0}, masterPassword[SIZE] = {0};
        strncpy(masterUsername, text1, sizeof(masterUsername) - 1);
        strncpy(masterPassword, text2, sizeof(masterPassword) - 1);


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
        instructionsProgram_window();
        gtk_main();
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
                wrong_Password();
                gtk_main();
                // Inform the User of the Situation and Ask for the Correct Master Password
                printf("\nWrong Password, Try Again (You have %d Tries left):", attemptsPassword);
                // Store the New Password on masterPassword
                strncpy(masterPassword, text1, sizeof(masterPassword) - 1);
                //scanf("%s", masterPassword);
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
        selectOperation_window();
        gtk_main();
        operation = selectOperation();

        // Each Operation:
        switch (operation) {
            // Operation 1: Show through the Console All the Accounts of the User
            case SEE_ACCOUNTS:

                //Resetting the array so the changes in the accounts don't overlap
                memset(text1, 0, sizeof(text1));
                // Show the Accounts
                showAccounts(user, numAccounts);
                showAccounts_window();

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
                    indexAccount_window();
                    gtk_main();
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

