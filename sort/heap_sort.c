#include <stdio.h>

#define N 11 // 0은 사용하지 않음
#define SWAP(t,x,y)((t)=(x),(x)=(y),(y)=(t))


void heapify(int A[], int i, int n){
    int largest , tmp;
    if((2*i < n)&&(A[2*i]> A[i]))
        largest = 2*i;
    else largest = i;

    if((2*i+1 < n) && (A[2*i+1]>A[largest]))
        largest = 2*i + 1;

    if(largest != i){
        SWAP(tmp, A[i], A[largest]);

        heapify(A, largest, n);
    }
}


void buildHeap(int A[], int n){ // N
    for(int i=n/2;i>0;i--)
        heapify(A,i,n); // log N
    
}

void printHeap(int A[], int n){
    for(int i=1;i <n;i++){
        printf("[%d] ",A[i]);
    }
    puts("");
}

void heapSort(int A[], int n){
    buildHeap(A,N); // Buildheap 시 NlogN이라고 생각해야함
    printHeap(A,N);
    printf("\n============================\n");
    for(int i = n-1; i >1; i--){
        int tmp;
        SWAP(tmp, A[i], A[1]);

        heapify(A,1,i);
        printHeap(A,N);
    }
}

int main(){
    int A[N] = {0,4,1,3,2,16,9,10,14,8,7};

    // buildHeap(A,N); // O(N) = NlogN 
    // printHeap(A,N);
    heapSort(A,N);
}