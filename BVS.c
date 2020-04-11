#include <stdio.h>
#include <stdlib.h>

typedef struct node_BVS {
    int data;
    struct node_BVS *left;
    struct node_BVS *right;
}NODE_BVS;

NODE_BVS *createNode_BVS(int number, NODE_BVS **root) {
    NODE_BVS *temp;
    if((*root) == NULL) {                                                      //ak ešte neexistuje strom vytvorím koreň
        (*root) = (NODE_BVS*) malloc(sizeof(NODE_BVS));
        (*root)->data = number;
        (*root)->left = NULL;
        (*root)->right = NULL;
        return (*root);
    }
    else {                                                                 //keď už existuje strom, tak vytvorím do neho nový list
        temp = (NODE_BVS *) malloc(sizeof(NODE_BVS));
        temp->data = number;
        temp->right = NULL;
        temp->left = NULL;
        return temp;
    }
}

NODE_BVS *search_BVS(int number, NODE_BVS *root) {
    NODE_BVS *temp = root;
    while(temp != NULL) {
        if(number == temp->data){
            return temp;
        }
        if(number < temp->data) {
            temp = temp->left;
        }
        else{
            temp = temp->right;
        }
    }
    return NULL;
}

void insert_BVS(int number, NODE_BVS **root) {
    NODE_BVS *temp = (*root);

    if((*root) == NULL) {                                                         //ak ešte neexistuje strom
        (*root) = createNode_BVS(number, root);
        return;
    }
    while(1) {                                                                    //pridanie čísla do stromu
        if(number == temp->data){
            return;
        }
        if((number < temp->data) && (temp->left != NULL)) {                       //ak je číslo menšie ako číslo v uzle a existuje ľavé dieťa
            temp = temp->left;                                                    //vnorím sa do ľavého podstromu
        }
        if((number > temp->data) && (temp->right != NULL)) {                      //ak je číslo väčšie ako číslo v uzle a existuje pravé dieťa
            temp = temp->right;                                                   //vnorím sa do pravého podstromu
        }
        if((number < temp->data) && (temp->left == NULL)) {                       //ak neexistuje ľavé dieťa vytvorím tam list s danou hodnotou
            temp->left = createNode_BVS(number, root);
            temp = temp->left;
            break;
        }
        if((number > temp->data) && (temp->right == NULL)) {                      //ak neexistuje pravé dieťa vytvorím tam list s danou hodnotou
            temp->right = createNode_BVS(number, root);
            temp = temp->right;
            break;
        }
    }
}

void print_tree_BVS(NODE_BVS *temp, int height) {                                       //vypísanie stromu
    if(temp) {
        if(temp->right) {
            print_tree_BVS(temp->right, height + 1);
        }

        for(int i = 0; i < height; i++){
            printf("    ");
        }

        printf("%2d\n", temp->data);

        if(temp->left) {
            print_tree_BVS(temp->left, height + 1);
        }
    }
}