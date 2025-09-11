#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isPositiveInteger(char token[]) {
   int x;
   for(int i = 0; i < strlen(token); ++i) {
      if(isdigit(token[i])) x = 1;
      else {
         x = 0;
         break;
      }
   }
   return x;
}
int isNegativeInteger(char token[]) {
   int x;
   if(token[0] == '-') {
      for(int i = 1; i < strlen(token); ++i) {
         if(isdigit(token[i])) x = 1;
         else {
            x = 0;
            break;
         }
      }
   }
   return x;
}
int isBinaryNumber(char token[]) {
   int x;
   if(token[0] == '0' && token[1] == 'b') {
      for(int i = 2; i < strlen(token); ++i) {
         if(token[i] == '0' || token[i] == '1') x = 1;
         else {
            x = 0;
            break;
         }
      }
   }
   return x;
}
int isGuid(char token[]) {
   int x = 0;
   if(token[8] == '-' && token[13] == '-' && token[18] == '-' && token[23] == '-' && strlen(token) == 36) {
      for(int i = 0; i < 8; ++i) {
         if(isxdigit(token[i])) {
            x = 1;
         }
         else {
            x = 0;
            return x;
         }
      }
      for(int i = 9; i < 13; ++i) {
         if(isxdigit(token[i])) x = 1;
         else {
            x = 0;
            return x;
         }
      }
      for(int i = 14; i < 18; ++i) {
         if(isxdigit(token[i])) x = 1;
         else {
            x = 0;
            return x;
         }
      }
      for(int i = 19; i < 23; ++i) {
         if(isxdigit(token[i])) x = 1;
         else {
            x = 0;
            return x;
         }
      }
      for(int i = 24; i <= 35; ++i) {
         if(isxdigit(token[i])) x = 1;
         else {
            x = 0;
            return x;
         }
      }
   }
   else x = 0;

   return x;
}
int isPositiveFloatingPoint(char token[]) {
   int x;
   int dec = 0;
   for(int i = 0; i < strlen(token); ++i) {
      if(token[i] == '.') {
         dec++;
      }
   }
   if(dec == 1 && isdigit(token[0]) && isdigit(token[strlen(token) - 1])) {
      for(int i = 0; i < strlen(token); ++i) {
         if(token[i] == '.' || isdigit(token[i])) x = 1;
         else {
            x = 0;
            break;
         }
      }
   }
   else x = 0;

   return x;
}
int isNegativeFloatingPoint(char token[]) {
   int x;
   int dec = 0;
   for(int i = 0; i < strlen(token); ++i) {
      if(token[i] == '.') {
         dec++;
      }
   }
   if(dec == 1 && isdigit(token[1]) && isdigit(token[strlen(token) - 1]) && token[0] == '-') {
      for(int i = 1; i < strlen(token); ++i) {
         if(token[i] == '.' || isdigit(token[i])) x = 1;
         else {
            x = 0;
            break;
         }
      }
   }
   else x = 0;

   return x;
}

int main() {

   char input[100];
   printf("Enter a token to identify, EOF to stop:\n");
   while(scanf("%s", input) != EOF) {
      if(isPositiveInteger(input)) printf("The token is a positive integer\n");
      else if(isNegativeInteger(input)) printf("The token is a negative integer\n");
      else if(isBinaryNumber(input)) printf("The token is a binary number\n");
      else if(isGuid(input)) printf("The token is a guid\n");
      else if(isPositiveFloatingPoint(input)) printf("The token is a positive floating-point number\n");
      else if(isNegativeFloatingPoint(input)) printf("The token is a negative floating-point number\n");
      else printf("The token cannot be identified\n");
      printf("Enter a token to identify, EOF to stop:\n");
   }
   return 0;
}