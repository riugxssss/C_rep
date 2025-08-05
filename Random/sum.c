//Sum
#include <stdio.h>

int main(){

    int number_user;
    int sum_numbers = 0;

    printf("Enter the number: ");
    scanf("%d", &number_user);

    for (int i=1; i<= number_user; printf("[%i]\t%d\n", i, sum_numbers+=i), i++);

    return 0;
}
