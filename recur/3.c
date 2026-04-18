#include <stdio.h>

void print(int n){
    if (n == 0) return;
    printf("%d\n",n%10);
    print(n / 10);
    
}

int main(){
    int n;
    scanf("%d",&n);
    print(n);
}