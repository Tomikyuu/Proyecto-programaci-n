//27/12/2023.

#include "fileManager.h"

int checksum(char arrayChar[], int numChar)
{
    int result = 0;
    for (int i = 0; i < numChar; i++)
    {
        result = result + (int)arrayChar[i];
    }

    return result;
}

void xorCipher(char* arrayData, int numChar, int pwd[])
{
    int pwdLenght = strlen(arrayData);
    for (int i = 0; i < numChar; i++)
    {
        arrayData[i] = arrayData[i] ^ pwd[i % pwdLenght];
    }

}

int writeUserInfo(char* path, Accounts account[], const char* pwd)
{
    FILE * fp;
    fp = fopen(path, "wb");

    if(fp == NULL)
    {
        fprintf(stderr, "The file could not be open");
        return -1;
    }

    fprintf(fp, "");

    return 0;
}


