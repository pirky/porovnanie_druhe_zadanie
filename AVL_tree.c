
#define BALANCE_FACTOR(node) (((node)->left != NULL && (node)->right != NULL) ? (((node)->right->height) - ((node)->left->height)) : (((node)->left == NULL && (node)->right != NULL) ? (node)->right->height : -(node)->left->height ))
#define MAX(left, right) (((left) > (right)) ? (left) : (right))

typedef struct node {
    int data;
    int height;
    struct node *parent;
    struct node *left;
    struct node *right;
}NODE;

NODE *createNode(int number,NODE *parent, NODE **root) {
    NODE *temp;
    if((*root) == NULL) {                                                               //ak ešte neexistuje strom vytvorím koreň
        (*root) = (NODE*) malloc(sizeof(NODE));
        (*root)->data = number;
        (*root)->height = 1;
        (*root)->parent = NULL;
        (*root)->left = NULL;
        (*root)->right = NULL;
        return (*root);
    }
    else {                                                                              //keď už existuje strom, tak vytvorím do neho nový list
        temp = (NODE *) malloc(sizeof(NODE));
        temp->data = number;
        temp->height = 1;
        temp->parent = parent;
        temp->right = NULL;
        temp->left = NULL;
        return temp;
    }
}

NODE *search_AVL(int number, NODE *root) {
    NODE *temp = root;
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

int height(NODE* temp){                                                                 //výpočet výšky uzla
    if(temp->left != NULL && temp->right != NULL){
        return 1 + MAX(temp->left->height,temp->right->height);
    }
    else if(temp->left == NULL && temp->right != NULL){
        return 1 + temp->right->height;
    }
    else if(temp->left != NULL && temp->right == NULL){
        return 1 + temp->left->height;
    }
    else{
        return 1;
    }
}

////AVL tree rotations

NODE *LL_rotation(NODE *A, NODE *B, NODE *C){                                           //left left rotation
    B->parent = A->parent;
    A->parent = B;
    A->left = B->right;
    B->right = A;
    if(A->left != NULL){
        A->left->parent = A;
    }
    if(B->parent != NULL){
        if(B->parent->left == A){
            B->parent->left = B;
        }
        else if(B->parent->right == A){
            B->parent->right = B;
        }
    }
    A->height = height(A);                                                              //update výšok, pričom poslednú updatujem výšku vrcholu,
    C->height = height(C);                                                              //ktorý je rodičom zvyšných dvoch vrcholov
    B->height = height(B);
    return B;
}

NODE *LR_rotation(NODE *A, NODE *B, NODE *C){                                           //left right rotation
    C->parent = A->parent;
    B->parent = C;
    A->parent = C;
    B->right = C->left;
    A->left = C->right;
    C->right = A;
    C->left = B;
    if(B->right != NULL){
        B->right->parent = B;
    }
    if(A->left != NULL){
        A->left->parent = A;
    }
    if(C->parent != NULL){
        if(C->parent->left == A){
            C->parent->left = C;
        }
        else if(C->parent->right == A){
            C->parent->right = C;
        }
    }
    A->height = height(A);
    B->height = height(B);
    C->height = height(C);
    return C;
}

NODE *RR_rotation(NODE *A, NODE *B, NODE *C){                                           //right right rotation
    B->parent = A->parent;
    A->parent = B;
    A->right = B->left;
    B->left = A;
    if(A->right != NULL){
        A->right->parent = A;
    }
    if(B->parent != NULL){
        if(B->parent->left == A){
            B->parent->left = B;
        }
        if(B->parent->right == A){
            B->parent->right = B;
        }
    }
    A->height = height(A);
    B->height = height(B);
    C->height = height(C);
    return B;
}

NODE *RL_rotation(NODE *A, NODE *B, NODE *C){                                           //right left rotation
    C->parent = A->parent;
    B->parent = C;
    A->parent = C;
    A->right = C->left;
    B->left = C->right;
    C->right = B;
    C->left = A;
    if(B->left != NULL){
        B->left->parent = B;
    }
    if(A->right != NULL){
        A->right->parent = A;
    }
    if(C->parent != NULL){
        if(C->parent->right == A){
            C->parent->right = C;
        }
        else if(C->parent->left == A){
            C->parent->left = C;
        }
    }
    A->height = height(A);
    B->height = height(B);
    C->height = height(C);
    return C;
}

NODE *balance(NODE *temp){                                                              //vyrovnanie stromu
    NODE *child = temp;
    temp = temp->parent;
    while(temp != NULL){                                                                //kým neprídem ku koreňu
        temp->height = height(temp);

        if(BALANCE_FACTOR(temp) == 2){                                                  //pravá vetva je preťažená
            if(BALANCE_FACTOR(temp->right) > 0){                                  //pravá strana praveho dieťaťa je preťažená
                temp = RR_rotation(temp, temp->right, temp->right->right);
            }
            else if(BALANCE_FACTOR(temp->right) < 0){                             //ľavá strana pravého dieťaťa je preťažená
                temp = RL_rotation(temp, temp->right, temp->right->left);
            }
        }
        if(BALANCE_FACTOR(temp) == -2){                                                 //lava vetva je preťažená
            if(BALANCE_FACTOR(temp->left) < 0){                                   //ľava strana ľavého dieťaťa je preťažená
                temp = LL_rotation(temp, temp->left, temp->left->left);
            }
            else if(BALANCE_FACTOR(temp->left) > 0){                              //pravá strana ľavého dieťaťa je preťažená
                temp = LR_rotation(temp, temp->left, temp->left->right);
            }
        }
        child = temp;
        temp = temp->parent;
    }
    return child;                                                                       //vrátim nový koreň
}

void insert_AVL(int number, NODE **root) {
    NODE *temp = (*root);

    if((*root) == NULL) {                                                               //ak ešte neexistuje strom, tak vytvorím koreň
        (*root) = createNode(number, temp, root);
        return;
    }
    while(1) {                                                                          //pridanie čísla do stromu
        if(number == temp->data){
            return;
        }
        if((number < temp->data) && (temp->left != NULL)) {                             //ak je číslo menšie ako číslo v uzle a existuje ľavé dieťa
            temp = temp->left;                                                          //vnorím sa do ľavého podstromu
        }
        if((number > temp->data) && (temp->right != NULL)) {                            //ak je číslo väčšie ako číslo v uzle a existuje pravé dieťa
            temp = temp->right;                                                         //vnorím sa do pravého podstromu
        }
        if((number < temp->data) && (temp->left == NULL)) {                             //ak neexistuje ľavé dieťa vytvorím tam list s danou hodnotou
            temp->left = createNode(number, temp, root);
            temp = temp->left;
            break;
        }
        if((number > temp->data) && (temp->right == NULL)) {                            //ak neexistuje pravé dieťa vytvorím tam list s danou hodnotou
            temp->right = createNode(number, temp, root);
            temp = temp->right;
            break;
        }
    }
    (*root) = balance(temp);                                                            //nakoniec spustím funkciu na vyrovnanie stromu
}

/*
 * vypísanie stromu od najpravejšieho vrcholu, teda ako prvý
 * vypíšem najpravejší vrchol a vertikálne bude najviac naľavo
 * koreň stromu
 */

void print_tree(NODE *temp, int height) {
    if(temp) {
        if(temp->right) {
            print_tree(temp->right, height + 1);
        }

        for(int i = 0; i < height; i++){
            printf("    ");
        }

        printf("%2d\n", temp->data);

        if(temp->left) {
            print_tree(temp->left, height + 1);
        }
    }
}

/*
 * vymazanie AVL stromu, ak existuje ľavý/pravý podstrom,
 * tak v ňom spustím uvoľnenie stromu,
 * po uvoľnení nastavím ľavý/pravý vrchol na NULL
 */

void free_AVL(NODE **temp){
    if((*temp)->left){
        free_AVL(&(*temp)->left);
        (*temp)->left = NULL;
    }
    if((*temp)->right){
        free_AVL(&(*temp)->right);
        (*temp)->right = NULL;
    }
    free(*temp);
    *temp = NULL;
}

////test na správne rotácie s vypisovaním po každom pridaní prvku
int test_na_rotacie(){
    NODE *root = NULL;
    int pole[7] = {4,3,1,6,7,5,2};
    for(int i = 0;i<7;i++){
        printf("\n------------------------\n");
        insert_AVL(pole[i],&root);
        print_tree(root,0);
        printf("\n------------------------\n");
    }
    free_AVL(&root);
}
