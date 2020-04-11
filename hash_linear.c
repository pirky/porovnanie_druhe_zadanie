//prevzaté z: https://www.tutorialspoint.com/data_structures_algorithms/hash_table_program_in_c.htm

#define LOAD_LINEAR(N,M) (((double)(N) / (M) >= 0.75) ? 1:0)                            //pridané macro na výpocet pomeru medzi velkostou tabuľky
#define SIZE 17                                                                         //a počtom pridaných prvkov

struct DataItem {
    int data;
    int key;
};

struct DataItem** hashArray = NULL;
struct DataItem* item;
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

void insert_Linear();

void rehash(){
    int oldSize = size;
    size *= 2;
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