#include <stdio.h>

#define M 13

typedef struct
{
    int table[M];
}HashType;

void init(HashType *HT){
    for(int i=0; i<M;i++){
        HT->table[i] = 0;
    }
}

int hashFn(int key){
    return key % M;
}

int hashFn2(int key){
    return 11- (key % 11);
}

void insertItem(HashType* HT, int key){
    int hashVal = hashFn(key);
    for(int i=0; i< M; i++){
        int b = (hashVal + i) % M; // Linear probing
        //int b = (hashVal + i*i) % M; // Quadratic
        // int b = (hashVal + i + hashFn2(key)) % M;

        if(HT->table[b] == 0 ){
            HT->table[b] = key;
            break;
        }
    }
}

void findItem(HashType* HT, int key){
    int hashVal = hashFn(key);
    for(int i=0; i< M; i++){
        int b = (hashVal + i) % M; // Linear probing
        //int b = (hashVal + i*i) % M; // Quadratic
        // int b = (hashVal + i + hashFn2(key)) % M;

        if(HT->table[b] == 0){
            puts("No key to find.");
            break;
        }
        else if(HT->table[b] == key){
            printf("Found key(%d) at bucket(%d).\n",key, b);
            break;
        }
    }
}
void deleteItem(HashType* HT, int key){
    int hashVal = hashFn(key);
    for(int i=0; i< M; i++){
        int b = (hashVal + i) % M; // Linear probing
        //int b = (hashVal + i*i) % M; // Quadratic
        // int b = (hashVal + i + hashFn2(key)) % M;

        if(HT->table[b] == 0){
            puts("No key to delete.");
            break;
        }
        else if(HT->table[b] == key){
            printf("Deleted key(%d) at bucket(%d).\n",key, b);
            HT->table[b] = -1;
            break;
        }
    }
}
void print(HashType* HT){
    for(int i=0; i<M; i++)
        printf(" %2d", HT->table[i]);
    puts("");
}

void printHash(HashType* HT){
    printf("Bucket   Key\n");
    printf("============\n");

    for(int i=0; i<M; i++){
        printf("HT[%02d] : %2d\n",i, HT->table[i]);
    }
    puts("");
}

int main(){
    HashType HT;
    init(&HT);

    int data[] = {45,27,88, 9, 71,60,46,38,24};

    puts("");
    printf(" h(hey)    0  1  2  3  4  5  6  7  8  9 10 11 12\n");
    printf("=========  ================================================\n");

    for(int i=0; i<M;i++){
        printf("h(%2d):%2d",data[i], hashFn(data[i]));
        insertItem(&HT, data[i]);
        print(&HT);
    }
    puts(""); printHash(&HT);

    findItem(&HT, 46);
    deleteItem(&HT, 60);
    printHash(&HT);
    findItem(&HT, 46);
}

