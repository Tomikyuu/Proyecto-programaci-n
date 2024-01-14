# Proyecto-programacion

**Componentes del Equipo:**
Juan Alfonso_ID: 161014 
Fernando Azlor_ID: 166054 
Tomás Juan_ID: 156527

Bienvenidos a nuestra lista de Schneider, esta lista de Schneider es un gestor de cuentas desarrollado en C que utiliza el clásico cifrado XOR bit a bit para encriptar la información de sus cuentas. Creamos el gestor de cuentas como proyecto para la asignatura de Fundametos de Programción para la Universidad de San Jorge. A continuación, comenzaremos a describir la estructura del repositorio y sus componentes. Después podrá encontrar el tiempo invertido en el proyecto por cada uno de los miembros del equipo.

En este repositorio de GitHub podrán encontrar de forma totalmente gratuita el código base de nuestro gestor de cuentas para que puedan utilizar sus servicios sin ningun tipo de problema. Como podrán observar, el repositorio esta formado por varias carpetas, cada una de ellas con un código distinto:

**Memoria Técnica:** Documento PDF donde se describe el comportamiento del programa junto a las decisiones de implementación. Recomendamos encarecidamente que lea primero la memoria técnica antes de ejecutar el Código Base para conseguir un mayor entendimiento del gestor de cuentas.

**Carpeta FundamentosProgramaciónBueno:** Código base del Gestor de Cuentas tal y como se define en el PDF del Proyecto. Es decir, sin ningun tipo de modificación extra para conseguir una mayor puntuación.

**Carpeta GTK:** El Código del Gestor de Cuentas + Interfaz Gráfica (GTK)

**ARCHIVO EJECUTABLE:** Archivo Ejecutable del Gestor de Cuentas con la Interfaz Gráfica. Utilizar en caso de que no se pueda compilar el código en **Carpeta GTK**.

En el interior del propio Código, podemos encontrar implementadas varias funciones que fueron usadas para realizar la práctica de manera más ordenada y mantener el código más limpio y legible.
*Funciones:
**int calculateChecksum:** Argument:
                               int numChar      --> Number of characters of arrayChar[]
                               char arrayChar[] --> Array of character (We will be calculating its checksum)
                          Function:
                               calculateChecksum() calculates the checksum of an array of characters (arrayChar) through an algorithm.
                          Return:
                               checksum --> Returns the checksum that correspond to the arrayChar[]

 **void cipherXOR:** Argument:
                         int numChar      --> nº of characters arrayData has
                         char arrayData[] --> Array of character that we will be ciphering or deciphering
                         char password[]  --> Key to cipher and decipher arrayData[]
                    Function:
                         xorCipher(), ciphers or deciphers with an XOR bit to bit cipher the array of characters
                                      in arrayData[] with the key password. And stores the result in arrayData[]
                    Return:
                         Nothing is a void. (But arrayChar goes through reference and "stores" the ciphered text)

**Account* readUserInfo:** Argument:
                               char filePath*   --> Data path where the file is
                               int numAccounts  --> Number of Accounts the User Has
                               char key[]       --> Array of characters that form the password to decipher the data
                          Function:
                               The function reads the information of the file and decipher it's with the password[].
                               Then, it will store the information in the structs and compare the checksums to
                               check if the password is the correct one.
                               The file will follow this structure:
                               numAccounts (Exm: 3)
                               NºChar username0   NºChar password0   username0   password0   checksum0
                               NºChar username1   NºChar password1   username1   password1   checksum1
                               NºChar username2   NºChar password2   username2   password2   checksum2
                          Return:
                              Account* user --> An Array of Structures that Have all the Information of the Accounts on the File

**int writeUserInfo:**  Argument:
                             char* path       --> Data path of the file
                             Account* user    --> List of accounts (struct) that have all the variables that an account needs
                             char key[]       --> Array of characters that form the password to cipher the data
                             int numAccounts  --> Number of Accounts the User Has
                        Function:
                             Will write in the file that the *path points to the information in account[] once it have
                             been ciphered with the password[].
                             The file will follow this structure:
                             numAccounts (Exm: 3)
                             NºChar username0   NºChar password0   username0   password0   checksum0
                             NºChar username1   NºChar password1   username1   password1   checksum1
                             NºChar username2   NºChar password2   username2   password2   checksum2
                        Return:
                              0 --> If everything went as it should
                             -1 --> If the file could not be opened
 
 **Account* createUserInfo:** Argument:
                                   int numAccounts --> Number of Accounts of the User.
                              Function:
                                   Reserve enough dynamic memory to hold as many account structs as deemed necessary
                                   according to the numAccounts parameter.
                                   (It also initialises the values of the structures for better understanding while debugging)
                              Return:
                                   userAccountArray --> Address where the dynamic memory was reserved.

**void fillUserInfo:** Argument:
                           Account* user --> Address reserved for the data of the new account
                      Function:
                           fillUserInfo() will store the struct account with the username, the password, the length in characters
                           of the username, the length in characters of the password and the checksum of the account.
                      Return:
                          It is a void, so it doesn't return anything (user goes through reference)

**void deleteUser:** Argument:
                           int index        --> Number of the account that we need to delete
                           Account** user   --> Address of the Pointer that has the Address of the Accounts (Pointer to Pointer)
                           int* numAccounts --> Number of Accounts of the user
                     Function:
                          Erases the account in the position index
                     Return:
                          Nothing is a void. (But *user and *numAccounts goes through reference)

**void freeAllUserInfo:** Argument:
                               Account* user    --> List of all the accounts the user has
                               int* numAccounts --> Number of Accounts of the user
                          Function:
                               Free the dynamic memory that was reserved at createUserInfo.
                          Return:
                               It is a void, so it doesn't return anything (*user goes through reference)

**int main:** Argument:
                    Sin argumentos, 
              Function:
                    Poner en funcionamiento todas las funciones, pues es la función en la que se ejecuta el programa que se muestra al usuario. Muestra el inicio de sesión y los modos disponibles para el usuario
              Return:
                    0 --> acaba el programa

Cuando comenzamos a hablar por primera vez sobre el proyecto, decidimos que unicamente trabajaríamos en el cuando todos los integrantes del equipo estuviesen juntos. De esta modo, todos los miembros conseguirían la misma nota al haber participado de manera equitativa. Sin embargo, también llegamos a la conclusión que si alguno de los miembros del equipo decidia "abandonar" a sus compañeros este sería exiliado del proyecto y por tanto, perdería la posiblidad de formar parte del proyecto.

Para que no hubiese problemas decidimos trabajar en el proyecto siguiendo el horario de la universidad, es decir, de 9:00 a 14:00, una parada para comer y continuar de 17:00 a 20:00. Horario que cumplimos desde el 28 de Diciembre hasta el 30 de Diciembre y continuamos desde el 2 de Enero hasta el 5 de Enero. Por tanto, podemos decir con total seguridad que los miembros del equipo invirtieron 56 horas en total. A continuación mostraremos el reparto de tareas:

**Trabajo Realizado en Conjunto:** fileManager.c / userInfoManager.c 

**Tomás/Fernando:** main.c y Memoria Técnica

**Juan:** Interfaz Gráfica (Incluida la parte de GTK en la Memoria Técnica)


