#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 200
#define idk 10

typedef struct table
{
    struct table *next;
    int value;
    char name[SIZE];
}table;

table *hash_table[SIZE];

unsigned int hash(char *name){
    int lenght = strnlen(name, SIZE);
    unsigned hash_value = 0;
    for (int i=0;i <idk;i++){
        hash_value += name[i];
        hash_value = (hash_value * name[i]) % idk;
    }
    return hash_value;
}
void init_hash(){
    for (int i=0;i<idk;i++){
        hash_table[i] = NULL;
    }
}
void use_table(){
    printf("START\n");
    for (int i=0;i<idk;i++){
        table *wow = hash_table[i];
        if (wow == NULL){
            printf("\t%i\t---\n", i);
        } else {
            printf("\t%i\t ",i);
            table *saka = wow;
           while (saka != NULL){
            printf("%s -", saka->name);
           saka = saka->next;


        }
    }

}
printf("END\n");
}

table *hash_lookup(char *name){
    int index = hash(name);
    table *tmp = hash_table[index];
    while (tmp != NULL && strncmp(tmp->name, name, SIZE) != 0){
        tmp = tmp->next;
    }
    return tmp;
}
bool hash_insert(table *person){
    if (person == NULL) return false;
    int index = hash(person->name);
    person->next = hash_table[index];
    hash_table[index] = person;
    return true;
}
table *delete(char *name){
    int index = hash(name);
    table *tmp = hash_table[index];
    table *prev = NULL;
    while (tmp != NULL && strncmp(tmp->name, name, SIZE) != 0){
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL) return NULL;
    if (prev == NULL){
        hash_table[index] = tmp->next;
    } else {
        prev->next = tmp->next;
    }
    return tmp;
}
int main(){

      init_hash();
    use_table();

    table f1 = {.name = "Try1"};
    table f2 = {.name = "Try2"};
    table f3 = {.name = "Try3"};


    hash_insert(&f1);
    hash_insert(&f2);
    hash_insert(&f3);
    use_table();

    table *aa = hash_lookup("Saka");
    if (aa) {
        printf("Found %s\n", aa->name);
    } else {
        printf("Not found\n");
    }

    delete("Try1");
    use_table();

    return 0;
}
