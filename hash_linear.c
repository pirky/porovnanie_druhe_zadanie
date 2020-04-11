#include <stdio.h>
#include <stdlib.h>

#define LOAD_LINEAR(N,M) (((double)(N) / (M) >= 0.75) ? 1:0)                            //pridané macro na výpocet pomeru medzi velkostou tabuľky
#define SIZE 17                                                                         //a počtom pridaných prvkov

struct DataItem {
    int data;
    int key;
};

struct DataItem** hashArray = NULL;                                                     //zmenené statické pole na dynamické
struct DataItem* item;
int size = SIZE;                                                                        //pridaná globálna premenná na veĽkosť poľa
int elements = 0;                                                                       //pridaná globálna premenná na počet pridaných prvkov

int hashCode(int key) {
    return key % size;
}

void init(){                                                                            //pridaná funkcia na inicializáciu poľa
    for(int i = 0; i < size; i++){
        hashArray[i] = NULL;
    }
}

struct DataItem *search(int key) {
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

void insert_Linear();

void rehash(){                                                                          //pridaná funkcia rehash
    int oldSize = size;
    size *= 2;
    struct DataItem** newArray = (struct DataItem**)malloc(size* sizeof(struct DataItem*));
    struct DataItem** oldArray = hashArray;
    hashArray = newArray;
    init();
    elements = 0;
    for(int i = 0; i<oldSize;i++)
    {
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

////test s casom
//int main(){
//    clock_t start_t, end_t;
//    hashArray = (struct DataItem**) malloc(SIZE *sizeof(struct DataItem*));
//    init();
//    start_t = clock();
//    for(int i = 0; i < 10000000; i++){
//        insert_Linear(i,1);
//    }
//    end_t = clock();
//    printf("HASHOVANIE LINEAR pridanie:  %20g\n", (double)(-start_t + end_t)/ CLOCKS_PER_SEC);
//    return 0;
//}