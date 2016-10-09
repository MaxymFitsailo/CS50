#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main()
{
    float changeAmountInDollars;
    int changeAmountInCents, coinsCount=0;
    int coins[4]={25,10,5,1}; //coins available

    //waiting for a valid input...
    do {
        printf("How much change is owed?\n");
        changeAmountInDollars=GetFloat();
    }
    while (changeAmountInDollars<0);

    changeAmountInCents=round(changeAmountInDollars*100);

    //Coins counting...
    for(int i=0; i<4; i++){
            coinsCount+=changeAmountInCents/coins[i];
            changeAmountInCents=changeAmountInCents%coins[i];
    }

    //result showing...
    printf("You need %d coins.\n",coinsCount);
}
