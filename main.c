#include <stdio.h>
#include <stdlib.h>
#include "AVL_tree.c"
#include "BVS.c"
#include "hash.c"
#include "hash_linear.c"
#include "RedBlack_tree.c"

////vytvorenie polí, z ktorých budem pridávať dané hodnoty v testoch

int *createArray0toN(int n){
    int *array = malloc(n * sizeof(int));
    for(int i = 0; i < n; i++){
        array[i] = i;
    }
    return array;
}

int *createArrayNto0(int n){
    int *array = malloc(n * sizeof(int));
    for(int i = n; i > 0; i--){
        array[i] = i;
    }
    return array;
}

int *createArrayNAlternate(int n){
    int *array = malloc(n * sizeof(int));
    for(int i = 0, j = 0; j < n; i++ , j++){
        array[j] = i;
        array[++j] = n-i-1;
    }
    return array;
}

int *createNRandom(int n){
    int *array = malloc(n * sizeof(int)), number;
    srand(0);
    for(int i = 0; i < n; i++){
        number = (rand() * rand()) % n;
        array[i] = number;
    }
    return array;
}

void main() {
    int *array = NULL, n = 1000;
    array = createArrayNAlternate(n);
}
