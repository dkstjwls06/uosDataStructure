#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

int sorted[N];

void merge(int A[], int left, int mid, int right){
    int i= left, j = mid+1, k= left;
    while(i <= mid && j <= right){
        if(A[i] <= A[j])
            sorted[k++] = A[i++];
        else
            sorted[k++] = A[j++];
    }

    if(i > mid)
        for(int l=j; l <= right; l++)
            sorted[k++] = A[l];
    else 
        for(int l=i; l <= mid; l++)
            sorted[k++] = A[l];
    for(int l=left; l <= right; l++)
        A[l] = sorted[l];
}

void mergeSort(int A[], int left, int right){
    if(left < right){
        int mid = (left + right)/2;
        mergeSort(A, left,mid);
        mergeSort(A, mid+1, right);
        merge(A, left, mid, right);
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

    puts("Merge sorting...");    
    
    mergeSort(A, 0, N-1);

    for(int i=0;i<N;i++) printf("%d ",*(sorted+i));

}