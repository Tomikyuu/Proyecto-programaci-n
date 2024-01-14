/*
 *  Name Student 1: Juan Alfonso Arribas
 *  Name Student 2: Fernando Azlor Hostaled
 *  Name Student 3: Tomas Juan Uson
 *  Project: Programming Project
 *  Date of Creation: 27 / 12 / 2023
 *  Objective: Library that manages the dynamic memory allocation of the data structures that have
 *             to be defined and to store the information of each account in the structs.
 */

#include "userInfoManager.h"
#include <gtk/gtk.h>

#define SIZE 100

char text3[SIZE] = {0}, text4[SIZE] = {0};

Account* createUserInfo(int numAccounts) {

    // Assign memory for an array of accounts (Array of structs)
    Account* userAccountArray = malloc(numAccounts * sizeof(Account));

    // Check if the allocation was successful
    if (userAccountArray == NULL) {
        // Inform of an ERROR
        fprintf(stderr, "ERROR: Memory Assignment of the Accounts Failed");
        // Terminate Abruptly the Program (We found exit(EXIT_FAILURE) through the Internet)
        exit(EXIT_FAILURE);
    }

    // Initialize each account of the user (For Loop that runs through all the accounts)
    for (int i = 0; i < numAccounts; i++) {
        // Initialize username
        userAccountArray[i].username = 0;
        // Initialize password
        userAccountArray[i].password = 0;
        // Initialize usernameLenght
        userAccountArray[i].usernameLenght = 0;
        // Initialize passwordLenght
        userAccountArray[i].passwordLenght = 0;
    }
    // Return the List of Accounts
    return userAccountArray;
}

void fillUserInfo_window();
void fillUserInfo(Account* user) {
    fillUserInfo_window();
    gtk_main();

    // Character Arrays to store momentarily the username and password of the new account
    // Character Array to store the username
    char username[SIZE] = {0};
    // Character Array to store the password
    char password[SIZE] = {0};

    // Ask the user for the username of his new account
    //printf("\nEnter the name of your new account:");
    // Store the username in username
    //scanf("%s", username);
    strncpy(username, text3, sizeof(username) - 1);
    // Empty Buffer
    fflush(stdin);

    // Ask the user for the password of his new account
    //printf("Enter the password of your new account:");
    // Store the password in password
    //scanf("%s", password);
    strncpy(password, text4, sizeof(password) - 1);
    // Empty Buffer
    fflush(stdin);

    // Store the number of character os the username in usernameLenght
    user -> usernameLenght = (int)strlen(username);
    // Store the number of character os the username in usernameLenght
    user -> passwordLenght = (int)strlen(password);

    // Assign memory for an array of characters, the username of the new account
    user -> username = malloc(user -> usernameLenght + 1);
    // Check if the allocation was successful
    if (user -> username == NULL) {
        // Inform of an ERROR
        fprintf(stderr, "ERROR: Memory Assignment of the Username Failed (Add Account) ");
        // Terminate Abruptly the Program (We found exit(EXIT_FAILURE) through the Internet)
        exit(EXIT_FAILURE);
    }
    // Assign memory for an array of characters, the password of the new account
    user -> password = malloc(user -> passwordLenght + 1);
    // Check if the allocation was successful
    if (user -> password == NULL) {
        // Inform of an ERROR
        fprintf(stderr, "ERROR: Memory Assignment of the Password Failed (Add Account) ");
        // Terminate Abruptly the Program (We found exit(EXIT_FAILURE) through the Internet)
        exit(EXIT_FAILURE);
    }

    // Store the username of the new account in username
    strcpy(user -> username, username);
    // Store the password of the new account in password
    strcpy(user -> password, password);

    // Add '\0' to the End of the username
    user -> username[user -> usernameLenght] = '\0';
    // Add '\0' to the End of the password
    user -> password[user -> passwordLenght] = '\0';
}
static void fillUserInfo_button(GtkButton *button, gpointer user_data) {
    // user_data apunta a un arreglo de GtkEntry
    GtkEntry **entries = (GtkEntry **)user_data;

    // Obtener texto de los campos 'User' y 'Password'
    strcpy(text3, gtk_entry_get_text(entries[0]));
    strcpy(text4, gtk_entry_get_text(entries[1]));

    ///ACUERDATE QUITAR

    g_print("Username: %s\n", text3);
    g_print("Password: %s\n", text4);

    // Obtener la ventana y cerrarla
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    if (gtk_widget_is_toplevel(window)) {
        gtk_widget_destroy(window);
    }
}
void fillUserInfo_window() {
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *user_entry;
    GtkWidget *password_entry;
    GtkWidget *label_user;
    GtkWidget *label_password;
    GtkWidget *vbox;
    GtkEntry *entries[2];

    // Crear la ventana
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Add new account");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Crear un VBox para organizar los widgets
    vbox = gtk_vbox_new(FALSE, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Crear y agregar el label y entry para 'User'
    label_user = gtk_label_new("Username");
    gtk_box_pack_start(GTK_BOX(vbox), label_user, FALSE, FALSE, 0);
    user_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), user_entry, FALSE, FALSE, 0);
    entries[0] = GTK_ENTRY(user_entry);

    // Crear y agregar el label y entry para 'Password'
    label_password = gtk_label_new("Password");
    gtk_box_pack_start(GTK_BOX(vbox), label_password, FALSE, FALSE, 0);
    password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE); // Oculta la contraseña
    gtk_box_pack_start(GTK_BOX(vbox), password_entry, FALSE, FALSE, 0);
    entries[1] = GTK_ENTRY(password_entry);

    // Crear y agregar el botón
    button = gtk_button_new_with_label("Submit");
    g_signal_connect(button, "clicked", G_CALLBACK(fillUserInfo_button), entries);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

    // Mostrar todos los widgets
    gtk_widget_show_all(window);
}


void deleteUser(Account** user, const int index, int* numAccounts) {
    // Free the Memory of the username of the account we are erasing
    free((*user)[index].username);
    // Free the Memory of the password of the account we are erasing
    free((*user)[index].password);

    // Resize the Number of Accounts
    (*numAccounts)--;

    // Adjust Array of Account to Delete the Index Account
    // (For Loop that runs through the accounts from Index to the End)
    for (int i = index; i < *numAccounts ; i++) {
        // Move Account One Less Position
        (*user)[i] = (*user)[i+1];
    }
}

void freeAllUserInfo(Account* user, const int numAccounts) {
    // If the Number of Accounts Is 0 There is No Memory Space to Free
    if (numAccounts != 0) {
        // For Loop that Goes Through All the Accounts Created at the Moment
        for (int i = 0; i < numAccounts; i++) {
            // Free Memory Space where the Username was Stored
            free(user[i].username);
            // Free Memory Space where the Password was Stored
            free(user[i].password);
        }
        // Free Memory Space where the Array of Accounts was
        free(user);
    }
}
