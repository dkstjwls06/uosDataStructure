#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

void insertionSort(int A[]){
    printf("\nBefore sort :");
    for(int i=0;i<N;i++) printf("%d ",*(A+i));
    puts("");
    
    for(int i=0;i<N;i++){
        int key = A[i];
        int j = i-1;
        
        while(j>=0 && A[j]> key){
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = key;

        printf(" %d Step : ",i+1);
        for(int i=0;i<N;i++) printf("%d ",*(A+i));
        puts("");
    }
    
}

int main(){
    int A[N];
    srand(time(NULL));
    for(int i=0;i<N;i++){
        A[i] = rand() % 100;
    }
    insertionSort(A);
}