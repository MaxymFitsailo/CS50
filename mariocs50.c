#include <stdio.h>
#include <cs50.h>


int main()
{
    int numberOfRows; // Height of the pyramid.

    // Entering the valid number of rows of the pyramid.
    do {

        printf(" Enter height of pyramid, please: ");
        numberOfRows=GetInt();
    }
    while(n<0 || n>23);

    //Drawing the pyramid...
    for (int row = 1; row <= numberOfRows; row++){
        for (int spaces = numberOfRows-row; spaces>0; spaces--){
            printf(" ");
        }
        for (int bricks = 1; bricks <= row+1; bricks++) {
            printf("#");
        }
        printf("\n");
    }
}
