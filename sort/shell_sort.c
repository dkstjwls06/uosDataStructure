// 최악의 경우 O(N^2)
// 평균적인 경우 O(N^1.5)


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

void shellSort(int A[]){
    printf("\nBefore sort :");
    for(int i=0;i<N;i++) printf("%d ",*(A+i));
    puts("");

    puts("shell sorting...");

    int gap = N/2;

    while(gap > 0){
        for(int i=gap;i<N;i++){
            int key = A[i];
            int j = i-gap;
            
            while(j>=0 && A[j]> key){
                A[j+gap] = A[j];
                j-=gap;
            }
            A[j+gap] = key;
  
        }
        printf(" %d Step : ",gap);
        for(int i=0;i<N;i++) printf("%d ",*(A+i));
        puts("");
        gap/=2;
    }
    
    
    
}

int main(){
    int A[N];
    srand(time(NULL));
    for(int i=0;i<N;i++){
        A[i] = rand() % 100;
    }
    shellSort(A);
}