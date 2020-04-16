#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define LOAD_FACTOR(elements,size) (((double)(elements) / (size) >= 1.5) ? 1:0)     //macro na výpočet pomeru medzi počtom pridaných prvkov a veľkosťou tabuľky
#define HASH_FUNCTION(key,size) ((key)%(size))                                      //hešovacia funkcia
#define MIN_SIZE 13                                                                 //mnou zvolená minimálna veľkosť hešovacej tabuľky

typedef struct hash{
    int number;
    struct hash *next;
}HASH;

typedef struct TABLE{
    int size;
    int elements;
    HASH **table;
}TABLE;

void createTable(TABLE **table){
    (*table) = (TABLE*)malloc(sizeof(TABLE));
    (*table)->elements = 0;
    (*table)->size = MIN_SIZE;
    (*table)->table = NULL;
}

HASH* search_HASH(int number, TABLE *table){                                        //search funkcia pre hešovaciu tabuľku
    HASH *temp = table->table[HASH_FUNCTION(number,table->size)];
    if(temp != NULL){
        while(temp != NULL){
            if(temp->number == number){
                return temp;
            }
            temp = temp->next;
        }
    }
    return NULL;
}

void resize();

/*
 * *pridám číslo do tabuľky na dané miesto
*/

TABLE** add_HASH(int number, TABLE **table){
    (*table)->table[HASH_FUNCTION(number,(*table)->size)] = (HASH*)malloc(sizeof(HASH));
    (*table)->table[HASH_FUNCTION(number,(*table)->size)]->number = number;
    (*table)->table[HASH_FUNCTION(number,(*table)->size)]->next = NULL;
    return table;
}

int insert_HASH(int number, TABLE **table){
    HASH *temp = NULL;
    if((*table)->table == NULL){                                                    //prázdna tabuľka
        (*table)->table = (HASH**) malloc ((*table)->size * sizeof(HASH*));
        for(int i = 0; i < (*table)->size; i++){
            (*table)->table[i] = NULL;
        }
        table = add_HASH(number, table);
    }
    else{                                                                           //už niečo je v tabuľke
        if(search_HASH(number, *table)){
            return 0;
        }
        if((*table)->table[HASH_FUNCTION(number,(*table)->size)]){             //ak už je nejaké číslo v danom "košíku"
            temp = (*table)->table[HASH_FUNCTION(number,(*table)->size)];
            while(temp->next != NULL){
                temp = temp->next;
            }
            temp->next = (HASH*)malloc(sizeof(HASH));
            temp->next->number = number;
            temp->next->next = NULL;
        }
        else{                                                                       //ak je "košík" prázdny
            table = add_HASH(number, table);
        }
    }
    (*table)->elements++;
    if(LOAD_FACTOR((*table)->elements,(*table)->size)){
        resize(table);
    }
    return 1;
}

int notprimeNumber(int number){                                                     //zistenie prvočísla
    for(int i = 2; i < sqrt(number); i++){
        if(number % i == 0){
            return 1;
        }
    }
    return 0;
}

int newSize(int size){                                                              //zistenie novej veľkosti tabuľky (najbližšie 2-krát väčšie prvočíslo)
    size = size * 2 + 1;
    while(notprimeNumber(size)){
        size += 2;
    }
    return size;
}

void resize(TABLE **table){                                                         //funkcia na zmenu veľkosti tabuľky
    HASH *temp = NULL;
    TABLE *newTable = (TABLE*)malloc(sizeof(TABLE));
    newTable->elements = 0;
    newTable->size = newSize((*table)->size);
    newTable->table = NULL;
    for(int i = 0; i < (*table)->size; i++) {                                       //zapísanie čísel do novej väčšej tabuľky
        if ((*table)->table[i] != NULL) {
            temp = (*table)->table[i];
            while (temp != NULL) {
                insert_HASH(temp->number,&newTable);
                temp = temp->next;
            }
        }
    }
    *table = newTable;                                                              //zmena starej tabuľky na novú
}

void printTable(TABLE *table){                                                      //výpis tabuľky
    HASH *temp;
    int size = table->size;
    for(int i = 0; i < size; i++){
        if(table->table[i] == NULL){
            printf("NULL\n");
        }
        else{
            printf("%d-ty bucket: ",i);
            temp = table->table[i];
            while(temp != NULL){
                printf("-> %d ",temp->number);
                temp = temp->next;
            }
            printf("\n");
        }
    }
}

void freeTable(TABLE **table) {                                                     //uvoľnenie tabuľky
    HASH *temp, *next;
    for (int i = 0; i < (*table)->size; i++) {
        temp = (*table)->table[i];
        while (temp != NULL) {
            next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(*table);
    *table = NULL;
}

void test_resize(){
    TABLE *table = NULL;
    createTable(&table);
    table->size = 3;
    for(int i = 0; i < 5; i++){
        insert_HASH(i,&table);
        if(i == 3){
            printf("\n--------------------\n");
            printTable(table);
            printf("\n--------------------\n");
        }
    }
    printTable(table);
    printf("\n--------------------\n");
    freeTable(&table);
}