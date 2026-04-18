#include <stdio.h>

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
        int temp[to[i]-from[i]];
        for(int j=from[i]; j<=to[i];j++){
            temp[j-from[i]] = X[j];
        }
        for(int j=from[i]; j<=to[i];j++){
        }
    }
}