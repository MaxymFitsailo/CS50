#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>


int main(){

    string name=GetString();

    if (name != NULL) {
        if (((name[0]>='a')&& (name[0]<='z')) || ((name[0]>='A')&& (name[0]<='Z'))) printf ("%c", toupper(name[0]));

        for (int i=1, n=strlen(name); i<n; i++) {
            if ((name[i]>='a'&& name[i]<='z') || (name[i]>='A'&& name[i]<='Z')) {
                if (name[i-1]==' ') printf("%c",toupper(name[i]));
            }
        }
        printf("\n");
    }
}
