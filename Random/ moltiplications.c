//Tabels Moltiplication
#include <stdio.h>

int main(){

    int number_user;
    int x_point = 10;

    printf("Enter the number: ");
    scanf("%d", &number_user);

    for (int i=1; i<= x_point; printf("[%i]\t%d\n", i, number_user*i), i++);

    return 0;
}
