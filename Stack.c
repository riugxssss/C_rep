//Project esample made by riugxs
//How to create a stack with push, pop and peek functions.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct 
{
    int* list;
    int size;
    int container;
}Prj;

Prj *main1(int c1);
void dest(Prj *m2);
bool full(Prj *m2);
bool empty(Prj *m2);
bool push(Prj *m2, int value);
bool pop(Prj *m2, int *value);
bool peek(Prj *m2, int *value);
bool dam(Prj *m2, int *value, int a);

int main(void){

    int c2 = 0;
    int ps = 0;
    int aPop = 0;
    int counter = 0;
    int choice;
    int size = 0;
    printf("\033[1;32m[\033[1;37m!\033[0m\033[1;32m] \033[0mSTACK PROJECT from 𝖗𝖎𝖚𝖌𝖝𝖘\n\n");
    printf("Enter a size for \033[1;32myour container: \033[0m");
    scanf("%d", &c2);
    Prj *var = main1(c2);
    if (var == NULL){
        printf("A \033[1;31mproblem\033[0m occured.. ");
        free(var);
        return 1;
    }
    while (choice != 5){
    printf("\n1\033[1;32m)\033[0mPUSH ITEM\n2\033[1;32m)\033[0mPOP ITEM\n3\033[1;32m)\033[0mPEEK ITEM\n4\033[1;32m)\033[0mADD MEMORY\n5\033[1;32m)\033[0mEXIT\n\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        if (full(var)){
            printf("\nThe list is \033[1;32mfull.\033[0m\n");
            break;
        }
        printf("Enter the number to \033[1;32mpush: \033[0m");
        scanf("%d", &ps);
        push(var, ps);
        printf("Number \033[1;32mpushed: \033[0m%d\n", ps);

        break;
    case 2:
    if (empty(var)){
        printf("\nThe list is \033[1;32mempty..\033[0m\n");
        break;
    }
        pop(var, &aPop);
        printf("The \033[1;32mremoved item: %d\033[0m\n", aPop);
        break;
    case 3:
        peek(var, &c2);
        if (empty(var)){ 
            printf("\nThe list is \033[1;32mempty..\033[0m\n");
        }
        for(int i=var->size - 1; i>=0;i--){
            printf("Item[%d] = %d\n", counter++ ,var->list[i]);
        }
        break;
    case 4:
        printf("Enter a \033[1;32mnumber\033[0m for adding memory: ");
        scanf("%d", &size);
        if (var->container >= 30){
            printf("\033[1;31m[\033[1;37m!\033[1;31m]\033[0m \033[1;37mMax limit reached[30]\n\033[0m");
            break;
        }
        dam(var, var->list, size);
        printf("\n+%d memory \033[1;32mcontainer\033[0m\n", size);
        break;
    case 5:
        printf("Thank \033[1;32myou\033[0m for using.");
        return 0;
        break;
    default:
        printf("\033[1;31mInvalid input.\033[0m\n");
        break;
    }
    }
    dest(var);


    
    return 0;
}

Prj *main1(int c1){
    if (c1 <= 0) return NULL;
    Prj *m3 = malloc(sizeof(Prj));
    if (m3 == NULL) return NULL;

    m3 ->list = malloc(c1 * sizeof(int));
    if (m3->list == NULL) {
        free(m3);
        return NULL;
    }
    m3->container = c1;
    m3->size = 0;
    return m3;
}
void dest(Prj *m2){
    free(m2->list);
    free(m2);
}
bool full(Prj *m2){
    return m2->container == m2->size;
}
bool empty(Prj *m2){
    return m2->size == 0;
}
bool push(Prj *m2, int value)
{
    if (full(m2)) return false;

    m2->list[m2->size] = value;
    m2->size++;
    return true;
}
bool pop(Prj *m2, int *value){
    if (empty(m2)) return false;
    *value= m2->list[m2->size - 1];
    m2->size--;

    return true;
}
bool peek(Prj *m2, int *value){
    if (empty(m2)) return false;
    *value = m2->list[m2->size - 1];
    return true;
}
bool dam(Prj *m2, int *value, int a){
    value = realloc(value, sizeof(int)*a);
    m2->container+=a;
    return true;
}

//.
