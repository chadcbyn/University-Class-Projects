#include <stdio.h> 
#include <math.h>

int main() {
    
    double operand1;
    double operand2;
    int num1;
    int num2;
    char operator;
    double dubResult = 0;

    printf("Enter the ops:\n");
    scanf("%lf %c %lf", &operand1, &operator, &operand2);


    if ((operand1 == (int)operand1) && (operand2 == (int)operand2)) {
        num1 = (int)operand1;
        num2 = (int)operand2;
        int intResult = 0;
        if (operator == '+') {
            intResult = num1 + num2;
            printf("%d\n", intResult);
        }
        else if (operator == '-') {
            intResult = num1 - num2;
            printf("%d\n", intResult);
        }
        else if (operator == '*') {
            intResult = num1 * num2;
            printf("%d\n", intResult);
        }
        else if (operator == '/') {
            if (num2 != 0) {
                intResult = num1 / num2;
                printf("%d\n", intResult);
            }
            else printf("Cannot divide by zero\n");
        }
        else if (operator == '^') {
            if (num2 >= 0) {
                intResult = pow(num1, num2);
                printf("%d", intResult);
            }
            else printf("Exponent cannot be negative\n");
        }
        else if (operator == '%') {
            if (num2 != 0) {
                intResult = num1 % num2;
                printf("%d\n", intResult);
            }
            else printf("Cannot modulo by zero\n");
        }
        else printf("Unknown operator\n");

        if (intResult > 1000) printf("Large number\n");
        else if (intResult < -1000) printf("Small number\n");
    }
    else if (operator == '+') {
        dubResult = operand1 + operand2;
        printf("%lf\n", dubResult);
    }
    else if (operator == '-') {
        dubResult = operand1 - operand2;
        printf("%lf\n", dubResult);
    }
    else if (operator == '*') {
        dubResult = operand1 * operand2;
        printf("%lf\n", dubResult);
    }
    else if (operator == '/') {
        if (operand2 != 0) {
            dubResult = operand1 / operand2;
            printf("%lf\n", dubResult);
        }
        else printf("Cannot divide by zero\n");
    }
    else if (operator == '%') {
        printf("Modulo requires integers\n");
        if (operand2 == 0) printf("Cannot modulo by zero\n");
    }
    else if(operator == '^') {
        if (operand2 < 0) {
            printf("Exponent cannot be negative\n");
            if ((operand1 < 0) && (operand2 != (int)(operand2))) printf("With a negative base, exponent must be an int\n");
        }
        else if ((operand1 < 0) && (operand2 != (int)(operand2))) printf("With a negative base, exponent must be an int\n");
        else {
            dubResult = pow(operand1, operand2);
            printf("%lf\n", dubResult);
        }

    }
    else printf("Unknown operator\n");

    if (dubResult < -1000) printf("Small number\n");
    if (dubResult > 1000) printf("Large number\n");


    
    return 0;
}