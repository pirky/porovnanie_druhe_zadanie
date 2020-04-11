#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <profileapi.h>
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

int *createArrayNRandom(int n){
    int *array = malloc(n * sizeof(int)), number;
    srand(0);
    for(int i = 0; i < n; i++){
        number = (rand() * rand()) % n;
        array[i] = number;
    }
    return array;
}

////test pridanie všetkých prvkov poĽa
int test_insert_HASH_CHAINING(int n, int *array){
    TABLE *table = NULL;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double temp = 0;
    int SAMPLE = 10;
    for(int j = 0; j < SAMPLE; j++){
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        createTable(&table);
        for(int i = 0; i < n; i++){
            insert_HASH(array[i], &table);
        }
        QueryPerformanceCounter(&end);
        freeTable(&table);
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    printf("%g\n",temp/SAMPLE);
    return 0;
}

int test_insert_AVL(int n, int *array){
    NODE *root = NULL;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double temp = 0;
    int SAMPLE = 1;
    for(int j = 0; j < SAMPLE; j++){
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < n; i++){
            insert_AVL(array[i], &root);
        }
        QueryPerformanceCounter(&end);
//        free_AVL(&root);
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    printf("%g\n",temp/SAMPLE);
    return 0;
}

int test_insert_BVS(int n, int *array){
    NODE_BVS *root = NULL;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double temp = 0;
    int SAMPLE = 1;
    for(int j = 0; j < SAMPLE; j++){
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < n; i++){
            insert_BVS(array[i], &root);
        }
        QueryPerformanceCounter(&end);
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    printf("%g\n",temp/SAMPLE);
    return 0;
}

int test_insert_HASH_LINEAR(int n, int *array){
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double temp = 0;
    int SAMPLE = 10;
    for(int j = 0; j < SAMPLE; j++){
        hashArray = (struct DataItem**) malloc(SIZE *sizeof(struct DataItem*));
        init();
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < n; i++){
            insert_Linear(array[i],1);
        }
        QueryPerformanceCounter(&end);
        freeLinear();
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    printf("%g\n",temp/SAMPLE);
    return 0;
}

int test_insert_RB(int n, int *array){
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double temp = 0;
    int SAMPLE = 10;
    for(int j = 0; j < SAMPLE; j++){
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < n; i++){
            insert_RB(array[i]);
        }
        QueryPerformanceCounter(&end);
        free_RB(&root_RB);
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    printf("%g\n",temp/SAMPLE);
    return 0;
}

void test_insert(int n, int * array){
//    test_insert_HASH_CHAINING(n, array);
    test_insert_AVL(n, array);
//    test_insert_BVS(n, array);
//    test_insert_HASH_LINEAR(n, array);
//    test_insert_RB(n,array);
}

////test vyhľadanie všetkých prvkov poľa
int test_search_AVL(int n, int *array){
    NODE *root = NULL;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double temp = 0;
    int SAMPLE = 10;
    for(int j = 0; j < SAMPLE; j++){
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < 10000000; i++){
            insert_AVL(i, &root);
            search_AVL(i, root);
        }
        QueryPerformanceCounter(&end);
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    printf("%g\n",temp/SAMPLE);

    for(int j = 0; j < SAMPLE; j++){
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < 10000000; i++){
            search_AVL(i, root);
        }
        QueryPerformanceCounter(&end);
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    printf("AVL search: %20g",temp/SAMPLE);
    free_AVL(&root);
    return 0;
}

////test pridanie a následne vyhľadanie prvku
int test_insert_search_HASH_CHAINING(int n, int *array){
    TABLE *table = NULL;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double temp = 0;
    int SAMPLE = 10;
    for(int j = 0; j < SAMPLE; j++){
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        createTable(&table);
        for(int i = 0; i < n; i++){
            insert_HASH(array[i], &table);
            search_HASH(array[i], table);
        }
        QueryPerformanceCounter(&end);
        freeTable(&table);
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    printf("%g\n",temp/SAMPLE);
    return 0;
}

int test_insert_search_AVL(int n, int *array){
    NODE *root = NULL;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double temp = 0;
    int SAMPLE = 10;
    for(int j = 0; j < SAMPLE; j++){
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < n; i++){
            insert_AVL(array[i], &root);
            search_AVL(array[i], root);
        }
        QueryPerformanceCounter(&end);
        free_AVL(&root);
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    printf("%g\n",temp/SAMPLE);
    return 0;
}

int test_insert_search_BVS(int n, int *array){
    NODE_BVS *root = NULL;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double temp = 0;
    int SAMPLE = 1;
    for(int j = 0; j < SAMPLE; j++){
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < n; i++){
            insert_BVS(array[i], &root);
            search_BVS(array[i], root);
        }
        QueryPerformanceCounter(&end);
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    printf("%g\n",temp/SAMPLE);
    return 0;
}

int test_insert_search_HASH_LINEAR(int n, int *array){
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double temp = 0;
    int SAMPLE = 10;
    for(int j = 0; j < SAMPLE; j++){
        hashArray = (struct DataItem**) malloc(SIZE *sizeof(struct DataItem*));
        init();
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < n; i++){
            insert_Linear(array[i],1);
            search_Linear(array[i]);
        }
        QueryPerformanceCounter(&end);
        freeLinear();
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    printf("%g\n",temp/SAMPLE);
    return 0;
}

int test_insert_search_RB(int n, int *array){
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double temp = 0;
    int SAMPLE = 10;
    for(int j = 0; j < SAMPLE; j++){
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < n; i++){
            insert_RB(array[i]);
            search_RB(array[i],root_RB);
        }
        QueryPerformanceCounter(&end);
        free_RB(&root_RB);
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    printf("%g\n",temp/SAMPLE);
    return 0;
}

void test_insert_search(int n, int * array){
    test_insert_search_HASH_CHAINING(n, array);
    test_insert_search_AVL(n, array);
    test_insert_search_BVS(n, array);
    test_insert_search_HASH_LINEAR(n, array);
    test_insert_search_RB(n,array);
}

void main() {
    int *array = NULL, n = 1000000;
    array = createArrayNRandom(n);
    test_insert(n,array);
//    test_insert_search(n, array);


}
