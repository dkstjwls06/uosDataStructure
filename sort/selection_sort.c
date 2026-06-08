#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

void selectionSort(int A[]){
    printf("\nBefore sort :");
    for(int i=0;i<N;i++) printf("%d ",*(A+i));
    puts("");
    
    for(int i=0;i<N-1;i++){
        
        int minIdx = i;
        for(int j=i+1;j<N;j++){
            if(A[j] < A[minIdx]) minIdx = j;
        }
        if(minIdx != i){
            int tmp = A[i];
            A[i] = A[minIdx];
            A[minIdx] = tmp;
            
        }
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
    selectionSort(A);
}