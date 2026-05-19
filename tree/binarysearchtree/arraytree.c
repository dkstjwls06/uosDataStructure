#include <stdio.h>
#include <stdlib.h>

#define N 100

int BST[N];

void insertNode(int root, int key){
    while(1){
        if(root>=N){
            puts("Overflow.");
            return;
        }
        if(BST[root] == 0){
            BST[root]=key;
            return;
        }
        if(key < BST[root]){
            root = root * 2;
        } else if(key > BST[root]){
            root = root *2 + 1;
        }
    }
}

void preOrder(int root){
    if(BST[root] != 0){
        printf("[%2d] ",BST[root]);
        preOrder(root * 2);
        preOrder(root * 2 + 1);
    }
}

int main(){
    int keys[] = {35,18,7,26,12,3,68,22,30,99};
    for(int i=0;i<10;i++){
        insertNode(1, keys[i]);
        preOrder(1);
        printf("\n");
    }
    printf("\n");
}