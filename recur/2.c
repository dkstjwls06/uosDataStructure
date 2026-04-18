#include <stdio.h>

void print(int n){
    if (n == 0) return;
    print(n / 10);
    printf("%d\n",n);
}

int main(){
    int n;
    scanf("%d",&n);
    print(n);
}