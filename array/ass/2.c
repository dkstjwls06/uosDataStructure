#include <stdio.h>

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(){
    int N;
    scanf("%d",&N);
    int X[N];
    for(int i=0;i<N;i++) scanf("%d ",X+i);
    int size;
    scanf("%d",&size);
    int arr[size];
    for(int i=0;i<size;i++) scanf("%d ", arr+i);
    int prev;
    for(int i=0;i<size-1; i++){
        prev = X[arr[i+1]];
        X[arr[i+1]] = X[arr[i]];
        
    }
}