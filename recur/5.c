#include <stdio.h>

void hanoi(int n, char from, char temp, char to){
    if(n==1){
        printf("%c %c\n",from, to);
    } else {
        hanoi(n-1, from , to ,temp);
        printf("%c %c\n",from, to);
        hanoi(n-1, temp, from, to);
    }
}

int main(){
    int n;
    scanf("%d",&n);
    hanoi(n, 'A','B','C');
}