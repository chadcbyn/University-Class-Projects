#include <stdio.h>
#include <math.h>

int main() {
    
    int b20s;
    int b10s;
    int b5s;
    int b1s;
    int quarters;
    int dimes;
    int nickels;
    int pennies;
    int dollars;
    int cents;
    int length;

    printf("Enter the number of $20s: ");
    scanf("%d", &b20s);
    printf("\nEnter the number of $10s: ");
    scanf("%d", &b10s);
    printf("\nEnter the number of $5s: ");
    scanf("%d", &b5s);
    printf("\nEnter the number of $1s: ");
    scanf("%d", &b1s);
    printf("\nEnter the number of quarters: ");
    scanf("%d", &quarters);
    printf("\nEnter the number of dimes: ");
    scanf("%d", &dimes);
    printf("\nEnter the number of nickels ");
    scanf("%d", &nickels);
    printf("\nEnter the number of pennies ");
    scanf("%d", &pennies);

    dollars = (b20s * 20) + (b10s * 10) + (b5s * 5) + b1s + ((quarters * 25) / 100) + ((dimes * 10) / 100) + ((nickels * 5) / 100) + (pennies / 100);
    cents = ((quarters % 4) * 25) + ((dimes % 10) * 10) + ((nickels % 20) * 5) + (pennies % 100);
    if (cents >= 100){
        dollars += (cents / 100);
        cents = cents % 100;
    }
    printf("You have %d dollars and %d cents\n", dollars, cents);

    length = round(((b20s + b10s + b5s + b1s) * 6.14) + (quarters * 0.955) + (dimes * 0.705) + (nickels * 0.835) + (pennies * 0.75));
    printf("The length of your money is roughly %d inches", length);


    return 0;
}