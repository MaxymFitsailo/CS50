# include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


int main (int argc, char* argv[]){

    //Verification the number of arguments.
    if (argc != 2) {
        printf("Wrong arguments\n");
        return 1;
    }

    // Reception of the string to encrypt and the key.
    int key = (atoi(argv[1]))%26;
    string stringToEncrypt = GetString();

    //Encryption
    for (int i=0, n=strlen(stringToEncrypt); i<n; i++ ){
        if (islower(stringToEncrypt[i])) stringToEncrypt[i]=(char)(96+((int)stringToEncrypt[i]-96+key)%26);
        if (isupper(stringToEncrypt[i])) stringToEncrypt[i]=(char)(64+((int)stringToEncrypt[i]-64+key)%26);
    }

    //Result
    printf("%s\n",stringToEncrypt);
}
