#include <stdio.h>
#include <string.h>
/*
int rSub(char str[], char c, int idx){
    int cnt = (str[idx] == c) ? 1 : 0;
    if (idx == 0) return cnt;
    else return cnt + rSub(str,c,idx-1);
}
*/


int check(char ch, char* str){
    if (str[0] == '\0') return 0;
    if (str[0] == ch) return 1 + check(ch, str+1);
    else return check(ch,str+1);
}

int main(){
    char str[101], ch;
    fgets(str, sizeof(str), stdin);
    str[strlen(str)-1] = '\0';
    scanf(" %c",&ch); // getchar or " %c", fflush(stdin)???
    printf("%d\n",check(ch, str));
}