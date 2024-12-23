#include <stdio.h>
#include <string.h>

int main(){

    char *mam = "anna";
    int middle = strlen(mam) / 2;
    int len = strlen(mam);
    for (int i=0; i<middle; i++){
        if (mam[i] != mam[len -i -1]){
        printf("Non a palindromo");
        } else {
            printf("Palindromo");
            break;
        }
        
    }




    return 0;
}
