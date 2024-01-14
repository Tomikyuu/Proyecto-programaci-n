# Proyecto-programacion

**Componentes del Equipo:**
Juan Alfonso_ID: 161014 
Fernando Azlor_ID: 166054 
Tomás Juan_ID: 156527

Bienvenidos a nuestra lista de Schneider, esta lista de Schneider es un gestor de cuentas desarrollado en C que utiliza el clásico cifrado XOR bit a bit para encriptar la información de sus cuentas. Creamos el gestor de cuentas como proyecto para la asignatura de Fundametos de Programción para la Universidad de San Jorge. A continuación, comenzaremos a describir la estructura del repositorio y sus componentes. Después podrá encontrar el tiempo invertido en el proyecto por cada uno de los miembros del equipo.

En este repositorio de GitHub podrán encontrar de forma totalmente gratuita el código base de nuestro gestor de cuentas para que puedan utilizar sus servicios sin ningun tipo de problema. Como podrán observar, el repositorio esta formado por varias carpetas, cada una de ellas con un código distinto:

**Memoria Técnica:** Documento PDF donde se describe el comportamiento del programa junto a las decisiones de implementación. Recomendamos encarecidamente que lea primero la memoria técnica antes de ejecutar el Código Base para conseguir un mayor entendimiento del gestor de cuentas.

**Carpeta GTK:** El Código del Gestor de Cuentas + Interfaz Gráfica (GTK)

**ARCHIVO EJECUTABLE: FundamentosProgramacionBueno.exe:** Archivo Ejecutable del Gestor de Cuentas con la Interfaz Gráfica. Utilizar en caso de que no se pueda compilar el código en **Proyecto GTK**.

**CARPETA Extra:**
    1) **Carpeta FundamentosProgramacionBueno:** Código base del Gestor de Cuentas tal y como se define en el PDF del Proyecto. Es decir, sin ningun tipo de modificación extra para conseguir una mayor puntuación.
    2) **Vídeo:** Video mostrando y describiendo los resultados del programa.
    
En el interior del propio Código, podemos encontrar implementadas varias funciones que fueron usadas para realizar la práctica de manera más ordenada y mantener el código más limpio y legible.

*Funciones:

**int calculateChecksum:** 

                          Argument:
                               int numChar      --> Nº de caracteres de arrayChar[]
                               char arrayChar[] --> el array (calcularemos su checksum)
                          
                          Function:
                               calculateChecksum() calcula el checksum del array (arrayChar) por medio de un algoritmo.
                          
                          Return:
                               checksum --> devuelve el checksum del correspondiente arrayChar[]

 **void cipherXOR:** 
                     
                     Argument:
                         int numChar      --> nº de caracteres que tiene arrayData
                         char arrayData[] --> array que vamos a cifrar o descifrar
                         char password[]  --> clave para cifrar y descifrar arrayData[]
                    
                    Function:
                         xorCipher(), cifrado o descifrado XOR bit a bit cifra el array de caracteres
                                      en arrayData[] con la contraseña. almacena el resultado en arrayData[]
                    
                    Return:
                         Nada, es void. (pero arrayChar pasa por referencia y "almacena" el texto cifrado)

**Account* readUserInfo:** 
  
                          Argument:
                               char filePath*   --> ruta de datos
                               int numAccounts  --> numero de cuentas que tiene el usuario almacenadas
                               char key[]       --> array de caracteres que forman la contraseña
                          
                          Function:
                               la funcion lee la informacion del fichero y la descifra con la password[].
                               Luego, almacena la info en los structs y compara los checksums para
                               comprobar que la contraseña es correcta.
                               sigue esta estructura:
                               numAccounts (Exm: 3)
                               NºChar username0   NºChar password0   username0   password0   checksum0
                               NºChar username1   NºChar password1   username1   password1   checksum1
                               NºChar username2   NºChar password2   username2   password2   checksum2
                          
                          Return:
                              Account* user --> un Array de Structures que tienen toda la informacion de las cuentas del fichero

**int writeUserInfo:**  

                        Argument:
                             char* path       --> rucha del fichero
                             Account* user    --> lista de cuentas (struct) que tienen las variables que las cuentas necesitan
                             char key[]       --> Array de caracteres que forman la contraseña para descifrar los datos
                             int numAccounts  --> número de cuentas
                        
                        Function:
                             escribirá en el fichero al que *path apunte la información de account[] una vez sea
                             cifrado con la password[].
                             sigue esta estructura:
                             numAccounts (Exm: 3)
                             NºChar username0   NºChar password0   username0   password0   checksum0
                             NºChar username1   NºChar password1   username1   password1   checksum1
                             NºChar username2   NºChar password2   username2   password2   checksum2
                        
                        Return:
                              0 --> todo ha ido bien
                             -1 --> el fichero no pudo abrirse
 
 **Account* createUserInfo:** 
 
                             Argument:
                                   int numAccounts --> numero de cuentas.
                              
                              Function:
                                   reserva tabta memoria como los structs necesiten, no menos,
                                   dependiendo del numAccounts.
                                   (tambien inicializa el valor de los structures para mayor claridad en el debbugging)
                              
                              Return:
                                   userAccountArray --> direccion donde se reserva la memoria.

**void fillUserInfo:** 

                      Argument:
                           Account* user --> direccion reservada para las nuevas cuentas
                      
                      Function:
                           fillUserInfo() almacenará las cuentas struct con su usuario, contraseña, tamaño de caracteres
                           del usuario y contraseña, y el checksum de la cuenta.
                      
                      Return:
                          es un void, asi que no devuelve nada (usuario pasa por referencia)

**void deleteUser:** 

                    Argument:
                           int index        --> numero de la cuenta que se quiere eliminar
                           Account** user   --> direccion del puntero que tiene la direccion de las cuentas (puntero a puntero)
                           int* numAccounts --> numero de cuentas
                     
                     Function:
                          vorra la cuenta indicada por el usuario
                     
                     Return:
                          nada, es void. (pero *user y *numAccounts pasan por referencia)

**void freeAllUserInfo:** 

                          Argument:
                               Account* user    --> lista de todas las cuentas
                               int* numAccounts --> numero de cuentas
                          Function:
                               libera la memoria dinamica reservada en createUserInfo.
                          Return:
                               es un void, no devuelve nada (*user pasa por referencia)

**int main:** 

              Argument:
                    Sin argumentos, 
              
              Function:
                    Poner en funcionamiento todas las funciones, pues es la función en la que se 
                    ejecuta el programa que se muestra al usuario. Muestra el inicio de sesión y 
                    los modos disponibles para el usuario
              
              Return:
                    0 --> acaba el programa

Obviamente estas funciones han sido distribuidas por distintos archivos .c y.h, estos son tales ficheros:

**fileManager.c:** Objective: librería que organiza la creación, escritura and lectura de ficheros.

**userInfoManager.c:** Objective: libreria que maneja la memoria dinámica que necesitan las estructuras de datos que han
                                de ser definidos y almacenados en los structs.

**fileManager.h:** Objective: definir la cabezera de las funciones de fileManager.c

**userInfoManager.h:** Objective: definir la cabezera de las funciones de userInfoManager.c

**main.c:** Objective: ejecutar y mostrar el programa al usuario.


Cuando comenzamos a hablar por primera vez sobre el proyecto, decidimos que unicamente trabajaríamos en el cuando todos los integrantes del equipo estuviesen juntos. De esta modo, todos los miembros conseguirían la misma nota al haber participado de manera equitativa. Sin embargo, también llegamos a la conclusión que si alguno de los miembros del equipo decidia "abandonar" a sus compañeros este sería exiliado del proyecto y por tanto, perdería la posiblidad de formar parte del proyecto.

Para que no hubiese problemas decidimos trabajar en el proyecto siguiendo el horario de la universidad, es decir, de 9:00 a 14:00, una parada para comer y continuar de 17:00 a 20:00. Horario que cumplimos desde el 28 de Diciembre hasta el 30 de Diciembre y continuamos desde el 2 de Enero hasta el 5 de Enero. Por tanto, podemos decir con total seguridad que los miembros del equipo invirtieron 56 horas en total. A continuación mostraremos el reparto de tareas:

**Trabajo Realizado en Conjunto:** fileManager.c / userInfoManager.c 

**Tomás/Fernando:** main.c y Memoria Técnica

**Juan:** Interfaz Gráfica (Incluida la parte de GTK en la Memoria Técnica)


