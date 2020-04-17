#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define LOAD_LINEAR(N,M) (((double)(N) / (M) >= 0.75) ? 1:0)                            //pridané macro na výpocet pomeru medzi velkostou tabuľky
#define SIZE 13                                                                         //a počtom pridaných prvkov

struct DataItem {
    int data;
    int key;
};

struct DataItem** hashArray = NULL;
int size = SIZE;
int elements = 0;

int hashCode(int key) {
    return key % size;
}

void init(){
    for(int i = 0; i < size; i++){
        hashArray[i] = NULL;
    }
}

struct DataItem *search_Linear(int key) {
    //get the hash
    int hashIndex = hashCode(key);

    //move in array until an empty
    while(hashArray[hashIndex] != NULL) {

        if(hashArray[hashIndex]->key == key)
            return hashArray[hashIndex];

        //go to next cell
        ++hashIndex;

        //wrap around the table
        hashIndex %= size;
    }

    return NULL;
}

void insert_Linear(int key, int data);

int notprimeNumber_linear(int number){                                                  //zistenie prvočísla
    for(int i = 2; i < sqrt(number); i++){
        if(number % i == 0){
            return 1;
        }
    }
    return 0;
}

int newSize_linear(int number){                                                         //zistenie novej veľkosti tabuľky (najbližšie 2-krát väčšie prvočíslo)
    number = number * 2 + 1;
    while(notprimeNumber_linear(number)){
        number += 2;
    }
    return number;
}

void rehash(){
    int oldSize = size;
    size = newSize_linear(oldSize);
    struct DataItem** newArray = (struct DataItem**)malloc(size* sizeof(struct DataItem*));
    struct DataItem** oldArray = hashArray;
    hashArray = newArray;
    init();
    elements = 0;
    for(int i = 0; i<oldSize;i++){
        if(oldArray[i]!=NULL)
            insert_Linear(oldArray[i]->key,oldArray[i]->data);
    }
}

void insert_Linear(int key, int data) {
    struct DataItem *item = (struct DataItem*) malloc(sizeof(struct DataItem));
    item->data = data;
    item->key = key;

    //get the hash
    int hashIndex = hashCode(key);

    //move in array until an empty or deleted cell
    while(hashArray[hashIndex] != NULL) {
        if(hashArray[hashIndex]->key == key){
            return;
        }
        //go to next cell
        ++hashIndex;

        //wrap around the table
        hashIndex %= size;
    }

    hashArray[hashIndex] = item;
    elements++;
    if(LOAD_LINEAR(elements, size)){
        rehash();
    }
}

void display() {
    int i = 0;

    for(i = 0; i<size; i++) {

        if(hashArray[i] != NULL)
            printf(" (%d,%d)",hashArray[i]->key,hashArray[i]->data);
        else
            printf(" ~~ ");
    }

    printf("\n");
}

void freeLinear(){
    for(int i = 0; i < size; i++){
        free(hashArray[i]);
        hashArray[i] = NULL;
    }
    free(hashArray);
    size = SIZE;
    elements = 0;
    hashArray = NULL;
}