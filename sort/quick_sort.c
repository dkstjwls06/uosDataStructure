
// O(NlogN) - 이동횟수 적어서 무시가능
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))
int partition(int A[], int left, int right){
    int pivot = A[left];
    int low = left + 1;
    int high = right;
    int tmp;

    while(low <= high){
        while(low <= high && A[low] <= pivot)
            low++;

        while(low <= high && A[high] > pivot)
            high--;
        
        for(int i = 0; i < N;i++) printf("%d ", A[i]);
        printf("\nlow = %d, high = %d\n",low,high);

        if(low <high) SWAP(A[low],A[high],tmp);
    }
    SWAP(A[left],A[high],tmp);
    return high;
}

void quickSort(int A[], int left, int right){
    if(left < right){
        int q = partition(A,left,right);
        quickSort(A, left,q-1);
        quickSort(A, q+1, right);
    }
}


int main(){
    int A[N];
    srand(time(NULL));
    for(int i=0;i<N;i++){
        A[i] = rand() % 100;
    }
    
     printf("\nBefore sort :");
    for(int i=0;i<N;i++) printf("%d ",*(A+i));
    puts("");

    puts("Quick sorting...");    
    
    quickSort(A, 0, N-1);

    for(int i=0;i<N;i++) printf("%d ",*(A+i));

}