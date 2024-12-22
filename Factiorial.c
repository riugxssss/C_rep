//Factiorial
#include <stdio.h>

int main(){

    int number_user;
    int factioria = 1;

    printf("Enter the number: ");
    scanf("%d", &number_user);

    for (int i=1; i<= number_user; printf("[%i]\t%d\n", i, factioria*=i), i++);

    return 0;
}
