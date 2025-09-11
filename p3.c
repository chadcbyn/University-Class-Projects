#include <stdio.h> //allow printf() and scanf()
#include <string.h>


int main() {
   
    char input[50];
    int i;
    int num;
    int len;
    int lineLen = 0;


    scanf("%d", &num);
    char line[num];
    line[0] = '\0';


    while(scanf("%s", input) != EOF) {
        len = strlen(input);
        if(len + lineLen == num) { //add input to line
            strcat(line, input);
            for(i = 0; i < strlen(input); ++i) lineLen++;
        }
        else if(len + lineLen < num) { //add input to line
            strcat(line, input);
            strcat(line, " ");
            for(i = 0; i <= strlen(input); ++i) lineLen++;
        }
        else { //print the line flipped
            int spaces = num - strlen(line);
            for(i = 0; i < spaces; ++i) {
                printf(" ");
            }
            for(i = strlen(line) - 1; i >= 0; i--) {
                printf("%c",line[i]);
            }
            printf("\n");
            //line[0] = '\0';
            strcpy(line, input);
            lineLen = strlen(input);
            if(lineLen != num) {
                strcat(line, " ");
                lineLen++;
            }
        }
       
    }
    if(lineLen > 0) {
        int spaces = num - strlen(line);
        for(i = 0; i < spaces; ++i) {
            printf(" ");
        }
        for(i = strlen(line) - 1; i >= 0; i--) {
            printf("%c",line[i]);
        }
        lineLen = 0;
        printf("\n");
    }

    for(int a = 1; a <= num; ++a) {
        if(a <= 9) {
            printf("%d", a);
        }
        else printf("%d", a % 10);
    }
    printf("\n");
   
    return 0;
}