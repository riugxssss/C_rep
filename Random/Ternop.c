
#include <stdio.h>

int main(){

    int t1; 
    int sum = 0;
    printf("Enter the number: ");
    scanf("%d", &t1);
    //Sum of numbers 
    for (int i=0; i<=t1; printf("%d\n", sum+=i), i++);
    //Ternary operator to simulate an if-else in a fast and smart way
    printf("%s", sum > 15 ? "Sum is more than 15" : "Sum is less than or equal to 15");
    return 0;
}
