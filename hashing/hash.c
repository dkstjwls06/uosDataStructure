#include <stdio.h>

#define M 11

int hashFn2(int key){
    return 11- (key % 11);
}

void insertItem(HashType* HT, int key){
    int hashVal = hashFn(key);
    for(int i=0; i< M; i++){
        int b = (hashVal + i) % M; // Linear
        // int b = (hashVal + i*i) % M; // Quadratic
        // int b = (hashVal + i + hashFn2(key)) % M;

        if(HT->table[b] == 0){
            printf("No Key to Find.\n");
        }
    }
}