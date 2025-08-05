#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){

   int a = 2 /*00000010*/, b = 3; /*00000011*/

   a ^= b; //a = 00000001 = 1
   b ^= a; //b = 00000010 = 2
   a ^= b; //a = 00000011 = 3

   printf("%d : %d\n", a, b);

   int s = 4, g = 5;

   s >> 1;
   g >> 1;

   printf("%d : %d", s >> 1, g >> 1); //output 2 : 2
    return 0;
}
