#include <stdio.h>
#include <stdlib.h>

#define N 20

typedef int element;

typedef struct 
{
    element heap[N];
    int heapSize;
} HeapType;

void init(HeapType* H){
    H->heapSize = 0;
}

void upHeap(HeapType* H){
    int i = H->heapSize;
    element key = H->heap[i];

    while((i != 1) && (key > H->heap[i/2])){
        H->heap[i] = H->heap[i/2];
        i /= 2;
    }

    H->heap[i] = key;
}

void downHeap(HeapType* H){
    element key = H->heap[1];
    int parent = 1, child = 2;

    while(child <= H->heapSize){
        if((child < H->heapSize) && (H->heap[child+1] > H->heap[child])){
            child++;
        }
        if((key >= H->heap[child])) break;
        H->heap[parent] = H->heap[child];
        parent = child;
        child *= 2;
    }
    H->heap[parent]  = key;
}

int isFull(HeapType* H){
    return H->heapSize == N-1;
}
int isEmpty(HeapType* H){
    return H->heapSize <= 0;
}

void insert(HeapType* H, element key){
    if(isFull(H)){
        puts("Full");
        return;
    }
    H->heapSize++;
    H->heap[H->heapSize] = key;
    upHeap(H);
}

element delete(HeapType* H){
    if(isEmpty(H)){
        puts("Empty");
        return -1;
    }
    element key = H->heap[1];
    H->heap[1] = H->heap[H->heapSize];
    H->heapSize--;
    downHeap(H);
    return key;
}

void heapSort(HeapType* H){
    int n = H->heapSize;
    int A[n];

    for(int i = n-1; i>=0;i--){
        A[i] = delete(H);
    }
    for(int i=0;i<n;i++){
        printf("[%d] ",A[i]);
    }puts("");
}

void print(HeapType* H){
    for(int i=1; i<=H->heapSize; i++){
        printf("[%d] ", H->heap[i]);
    }
    puts("");
}



void main(){
    HeapType H;
    init(&H);

    insert(&H, 9);insert(&H, 7);insert(&H, 6);
    insert(&H, 5);insert(&H, 4);insert(&H, 3);
    insert(&H, 2);insert(&H, 2);insert(&H, 1);
    insert(&H, 3); print(&H); getchar();

    insert(&H, 8); print(&H);getchar();

    printf("Delete [%d] : ", delete(&H)); print(&H);
    heapSort(&H);
}