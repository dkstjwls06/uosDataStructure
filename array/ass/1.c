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
    for(int i=0; i<N; i++){
        scanf("%d",X+i);
    }
    int m;
    scanf("%d",&m);
    int from[m], to[m];
    for(int i=0; i<m; i++){
        scanf("%d %d", from+i, to+i);
    }
    for (int i=0; i<m; i++){
         // from[i] : 시작 인덱스, to[i] : 끝 인덱스
        for(int j=from[i]; j <= (from[i]+to[i])/2; j++){
            swap(X+j, X+(to[i]-j));
        } 
    }
    for(int i=0; i<N; i++){
        printf("%d ",X[i]);
    }
    puts("");
}