#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#define WHITE "\033[1;37m"
#define RESET "\033[0m"
#define RED "\033[1;31m"

typedef struct 
{
    int count, 
    count2, 
    count3;
    int wcount, 
    w2count, 
    w3count;
}info;

//Funzione per gestire i clienti vari
void handle(info *data){
    int dolce_scelta = 0;
    char dolce_var[20];

    printf("Benvenuto cliente N:%d\n\n", data->count++);
    while (dolce_scelta != 99){
        printf( WHITE "DOLCE SCELTA:" RESET "\n1\033[1;37m)\033[0mBABÀ\n2\033[1;37m)\033[0mTORTA\nClicca 99 per terminare l'operazione\n> ");
        if (fgets(dolce_var, sizeof(dolce_var), stdin) != NULL){
            if (!sscanf(dolce_var, "%d", &dolce_scelta) == 1){
                fprintf(stderr, "Solo i numeri interi son accettati\n");
                continue;
            }
        }
        if (dolce_scelta == 99){
            break;
        }

        if (dolce_scelta == 1){
            printf("Hai scelto l'opzione <babà>\n\n");
            data->count2++;
        } else if (dolce_scelta == 2){
            printf("Hai scelto l'opzione <torta>\n\n");
            data->count3++;
        } else {
            fprintf(stderr, RED"[!]"WHITE"Scelta non valida\n"RESET);
        }
        
    }
    putchar('\n');


}
//Funzione per la gestione dei pesi
int weight_handle(info *data){
    int peso;
    char num[20];
    int cash_var;
    bool var_a = true;

    while (peso != 0 && var_a){
    printf(WHITE"PESO INFO:"RESET"\n1\033[1;37m)\033[0m700 GR\n2\033[1;37m)\033[0m1500 GR\n3\033[1;37m)\033[0m2000 GR\n> ");
    if (fgets(num, sizeof(num), stdin) != NULL){
        if (!sscanf(num, "%d", &peso) == 1){
            fprintf(stderr, RED"[!]"WHITE"2Solo numeri sono accettati\n"RESET);
            continue;
        }
    }
    //700 = 14 euro, 1500 = 30, 2000 = 40 w sconto 10% = 36 euro
    switch (peso)
    {
    case 1:
        printf("Peso selezionato per i dolci: %dgr\n", 700);
        cash_var = (14 * data->count2) + (14 * data->count3);
        printf("Costo totale dei dolci: %d euro\n", cash_var);
        data->wcount++;
        var_a = false;
        break;
    case 2:
        printf("Peso selezionato per i dolci: %dgr\n", 1500);
        cash_var = (30 * data->count2) + (30 * data->count3);
        printf("Costo totale dei dolci: %d euro\n", cash_var);
        data->w2count++;
        var_a = false;
        break;
    case 3:
        printf("Peso selezionato per i dolci: %dgr\n", 2000);
        cash_var = (36 * data->count2) + (36 * data->count3);
        printf("Costo totale dei dolci: %d euro\n", cash_var);
        data->w3count++;
        var_a = false;
        break;
    default:
        printf(RED"\n[!]"WHITE"Opzione non valida\n\n"RESET);
        break;
    }
    }
    return 0;
    
}

//Funzione main con gestione del menu interattivo
int main(){

    info *data = malloc(sizeof(info));
    if (data == NULL){
        fprintf(stderr, "Error allocating the memory\n");
        return 1;
    }
   int usage_options = 0;
   char num_control[20];
    data->count = 1;
   while (usage_options != 3){
    printf(WHITE "MENU:" RESET"\n1\033[1;37m)\033[0mADD CLIENT\n2\033[1;37m)\033[0mSTATISTICHE\n3\033[1;37m)\033[0mEXIT\n> ");
    if (fgets(num_control, sizeof(num_control), stdin) != NULL){
        if (!sscanf(num_control, "%d", &usage_options) == 1){
            fprintf(stderr, RED"\n[!]"WHITE"Solo numeri interi sono accettati!\n\n"RESET);
            continue;
        }
    }
    switch (usage_options)
    {
    case 1:
    handle(data);
    weight_handle(data);
        break;
        //Mostra le statistiche
    case 2:
        printf(WHITE"INFO GIORNATA\n"RESET);
        printf("-Babà comprati: %d\n-Torte comprate: %d\n", data->count2, data->count3);
        printf("-Peso dei dolci scelto:\n 700gr : %d\n 1500gr : %d\n 2000gr : %d\n", data->wcount, data->w2count, data->w3count);
        printf("-Clienti totali: %d\n", data->count - 1);
        printf(WHITE"\n[!] Enter to return "RESET);
        getchar();
        printf("\n\n");
        break;
    case 3:
        printf(WHITE"Giornata finita, a domani!\n" RESET);
        exit(EXIT_SUCCESS);
        break;
    default:
        printf(RED"\n[!]"WHITE"Opzione non valida\n\n"RESET);
        break;
    }
   }
   free(data);
    return 0;
}
