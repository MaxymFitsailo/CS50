# include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


int main (int argc, char* argv[]) {

    //Verification of the number of arguments.
    if (argc != 2) {
        printf("Wrong  number of args.\n");
        return 1;
    }

    int keyWordLength=strlen(argv[1]);

    //Verification the correction of the key word.
    for (int i=0; i<keyWordLength; i++) {
        if (!(isalpha(argv[1][i]))) {
            printf("Incorrect key word!!!\n");
            return 1;
        }
    }

    int keys[keyWordLength]; //a set of keys.

    //Initializing the set of keys
    for(int i=0; i<keyWordLength; i++) {
        argv[1][i]=tolower(argv[1][i]);
        keys[i]=argv[1][i]-97;
    }

    string stringToEncrypt=GetString();
    int useKey=0; //indicates which key to use

    //Encryption...
    for (int i=0, k=strlen(stringToEncrypt); i<k; i++) {
        if (islower(stringToEncrypt[i])) {
            stringToEncrypt[i]=(char)(96+ ((int)stringToEncrypt[i]-96+keys[useKey%keyWordLength])%26);
            useKey++;
        }
        if (isupper(stringToEncrypt[i])) {
            stringToEncrypt[i]=(char)(64+ ((int)stringToEncrypt[i]-94+keys[useKey%keyWordLength])%26);
            useKey++;
        }

    }
    //Result
    printf("%s\n",stringToEncrypt);
}
