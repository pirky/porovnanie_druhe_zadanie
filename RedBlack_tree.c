// Implementing Red-Black Tree in C
//prevzaté z: https://www.programiz.com/dsa/red-black-tree
//search prevzatý z: https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/
#include <stdio.h>
#include <stdlib.h>

enum nodeColor{
    RED,
    BLACK
};

struct rbNode{
    int data, color;
    struct rbNode *link[2];
};

struct rbNode *root_RB = NULL;

struct rbNode *createNode_RB(int data){
    struct rbNode *newnode;
    newnode = (struct rbNode *)malloc(sizeof(struct rbNode));
    newnode->data = data;
    newnode->color = RED;
    newnode->link[0] = newnode->link[1] = NULL;
    return newnode;
}

struct rbNode* search_RB(int key, struct rbNode* root){                                     //pridaná funkcia na prehľadávanie stromu z geeksforgeeks.org
    // Base Cases: root is null or key is present at root
    if (root == NULL || root->data == key)
        return root;

    // Key is greater than root's key
    if (root->data < key)
        return search_RB(key,root->link[1]);

    // Key is smaller than root's key
    return search_RB( key,root->link[0]);
}

void insert_RB(int data){
    struct rbNode *stack[98], *ptr, *newnode, *xPtr, *yPtr;
    int dir[98], ht = 0, index;
    ptr = root_RB;
    if (!root_RB){
        root_RB = createNode_RB(data);
        return;
    }
    stack[ht] = root_RB;
    dir[ht++] = 0;
    while (ptr != NULL){
        if (ptr->data == data){
            return;
        }
        index = (data - ptr->data) > 0 ? 1 : 0;
        stack[ht] = ptr;
        ptr = ptr->link[index];
        dir[ht++] = index;
    }
    stack[ht - 1]->link[index] = newnode = createNode_RB(data);
    while ((ht >= 3) && (stack[ht - 1]->color == RED)){
        if (dir[ht - 2] == 0){
            yPtr = stack[ht - 2]->link[1];
            if (yPtr != NULL && yPtr->color == RED){
                stack[ht - 2]->color = RED;
                stack[ht - 1]->color = yPtr->color = BLACK;
                ht = ht - 2;
            }
            else{
                if (dir[ht - 1] == 0){
                    yPtr = stack[ht - 1];
                }
                else{
                    xPtr = stack[ht - 1];
                    yPtr = xPtr->link[1];
                    xPtr->link[1] = yPtr->link[0];
                    yPtr->link[0] = xPtr;
                    stack[ht - 2]->link[0] = yPtr;
                }
                xPtr = stack[ht - 2];
                xPtr->color = RED;
                yPtr->color = BLACK;
                xPtr->link[0] = yPtr->link[1];
                yPtr->link[1] = xPtr;
                if (xPtr == root_RB){
                    root_RB = yPtr;
                }
                else{
                    stack[ht - 3]->link[dir[ht - 3]] = yPtr;
                }
                break;
            }
        }
        else{
            yPtr = stack[ht - 2]->link[0];
            if ((yPtr != NULL) && (yPtr->color == RED)){
                stack[ht - 2]->color = RED;
                stack[ht - 1]->color = yPtr->color = BLACK;
                ht = ht - 2;
            }
            else{
                if (dir[ht - 1] == 1){
                    yPtr = stack[ht - 1];
                }
                else{
                    xPtr = stack[ht - 1];
                    yPtr = xPtr->link[0];
                    xPtr->link[0] = yPtr->link[1];
                    yPtr->link[1] = xPtr;
                    stack[ht - 2]->link[1] = yPtr;
                }
                xPtr = stack[ht - 2];
                yPtr->color = BLACK;
                xPtr->color = RED;
                xPtr->link[1] = yPtr->link[0];
                yPtr->link[0] = xPtr;
                if (xPtr == root_RB){
                    root_RB = yPtr;
                }
                else{
                    stack[ht - 3]->link[dir[ht - 3]] = yPtr;
                }
                break;
            }
        }
    }
    root_RB->color = BLACK;
}

void print_RB(struct rbNode *temp, int height) {                                       //pridaná funkcia na vypísanie stromu aj s farbou vrchola
    if(temp) {
        if(temp->link[1]) {
            print_RB(temp->link[1], height + 1);
        }

        for(int i = 0; i < height; i++){
            printf("    ");
        }
        if(temp->color == RED){
            printf("%5dr\n", temp->data);
        }
        else{
            printf("%5db\n", temp->data);
        }

        if(temp->link[0]) {
            print_RB(temp->link[0], height + 1);
        }
    }
}

struct rbNode* free_RB(struct rbNode **temp){                                           //pridaná funkcia na uvoľnenie stromu
    if((*temp)->link[0]){
        free_RB(&(*temp)->link[0]);
        (*temp)->link[0] = NULL;
    }
    if((*temp)->link[1]){
        free_RB(&(*temp)->link[1]);
        (*temp)->link[1] = NULL;
    }
    free(*temp);
    *temp = NULL;
}