//
// Created by tomas on 27/12/2023.
//

#ifndef MAINC_FILEMANAGER_H
#define MAINC_FILEMANAGER_H

#include <string.h>
#include "userInfoManager.h"

int checksum(char arrayChar[], int numChar);

void xorCipher(char* arrayData, int numChar, int pwd[]);



//Leera segun la estructura del fichero que esta definida en este documento, y
// devolvera una lista de cuentas (nombre de usuario - contrasena), y el
//numero de cuentas que se han le´ıdo del fichero.
void readUserInfo(char ruta, const int claveCifrado);

// Si el fichero se ha podido crear y escribir correctamente, la funcion devolvera el valor 0, y si no deolvera el valor -1.
int writeUserInfo(char* path, Accounts account[], const char* pwd);

#endif //MAINC_FILEMANAGER_H

