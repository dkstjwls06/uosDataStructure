#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

void bubbleSort(int A[]){
    printf("\nBefore sort :");
    for(int i=0;i<N;i++) printf("%d ",*(A+i));
    puts("");
    
    for(int i=N-1;i>0;i--){
        int flag = 0;

        for(int j=0;j<i;j++){
            if(A[j] > A[j+1]){
                int tmp = A[j];
                A[j] = A[j+1];
                A[j+1] = tmp;
                flag = 1;
            }
        }

        printf(" %d Step : ",N-i);
        for(int i=0;i<N;i++) printf("%d ",*(A+i));

        if(flag == 0) break;
    }
    
}

int main(){
    int A[N];
    srand(time(NULL));
    for(int i=0;i<N;i++){
        A[i] = rand() % 100;
    }
    bubbleSort(A);
}
