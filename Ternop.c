
#include <stdio.h>

int main(){

    int t1; 
    int somma = 0;
    printf("Enter the number: ");
    scanf("%d", &t1);
    //Sum of numbers 
    for (int i=0; i<=t1; printf("%d\n", somma+=i), i++);
    //Terniar operator to simulate an if-else in a fast and smart way
    char *c = (somma >= 15) ? "First face " : "Second face -le 15";
    printf("%s", c);
    return 0;
}
