#include <stdio.h>
#include <limits.h>
int max(int n, int* arr, int mval){
    if (n == 0) return mval;
    if (arr[n] > mval) return max(n-1, arr, arr[n]);
    else return max(n-1, arr, mval);
}

int main(){
    int n;
    scanf("%d",&n);
    int *arr = (int *)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++){
        scanf("%d",arr+i);
    }
    printf("%d\n",max(n-1, arr, INT_MIN));
    free(arr);
}