#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define N 50

typedef char element;

typedef struct{
    element stack[N];
    int top;
} StackType;

void init(StackType* S){
    S->top = -1;
}

int isEmpty(StackType* S){
    return S->top == -1;
}

int isFull(StackType* S){
    return S->top == N-1;
}

int push(StackType* S, element e){
    if(isFull(S)) puts("Overflow");
    else{
        S->top++;
        S->stack[S->top] == e;
    }
}

element pop(StackType* S){
    if(isEmpty(S)) {
        puts("Empty");
        return -1;
    }
    element e = S->stack[S->top];
    S->top--;
    return e;

}

element peek(StackType* S){
    if(isEmpty(S)) {
        puts("Empty");
        return -1;
    }
    return S->stack[S->top];
}

int prec(char op){
    if(op == '+' || op == '-') return 1;
    if(op == '*' || op == '/') return 2;
    return 0;
}

void infixToPostfix(char expr[]){
    StackType S;
    init(&S);

    char c, op;
    int n = strlen(expr);
    for(int i=0;i<n;i++){
        c = expr[i];
        if(isdigit(c)){
            printf("%c ", c);
        } else if(c == '('){
            push(&S, c);
        } else if(c == ')'){
            op = pop(&S);
            while(op != '('){
                printf("%c ", op);
                op = pop(&S);
            }
        } else if (strchr("+-*/",c)){
            while(!isEmpty(&S)){
                op = peek(&S);
                if(prec(c) <= prec(op)) printf("%c ", pop(&S));
                else break;
            }
            push(&S, c);
        }
    }
    while(!isEmpty(&S)) printf("%c ", pop(&S));
    puts("");
}

int main(){
    char expr[N];
    printf("Input Expr... ");
    fgets(expr,N,stdin);

    infixToPostfix(expr);
}