#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 50

typedef int element;
typedef struct 
{
    element stack[N];
    int top;
} StackType;

void init(StackType* S){
    S->top = -1;
}

int isEmpty(StackType* S){
    return S->top == -1;
}

int isFull(StackType *S){
    return S->top == N-1;
}

void push(StackType *S, element e){
    if (isFull(S)) printf("Overflow\n");
    else {
        S->top++;
        S->stack[S->top] = e;
    }
}

void print(StackType *S){
    for(int i=S->top;i>=0;i--){
        printf(" |  %c  |\n",S->stack[i]);
        printf("  ______ \n");
    }
}

element pop(StackType *S){
    if(isEmpty(S)){
        puts("Empty!");
        return -1;
    }
    element e = S->stack[S->top];
    S->top--;
    return e;
}

element peek(StackType *S){
    if(isEmpty(S)){
        puts("Empty!");
        return -1;
    }
    return S->stack[S->top];
}

int check(char expr[]){
    StackType S;
    init(&S);

    char c, t;
    int n = strlen(expr);
    for (int i=0; i<n; i++){
        c = expr[i];
        if (strchr("({[", c)){
            push(&S, c);
        } else if(strchr(")}]", c)){
            if(isEmpty(&S)) return 2;
            else {
                t = pop(&S);
                if ((t == '[' && c != ']') 
                || (t == '{' && c != '}') 
                || (t == '(' && c != ')')) return 3;
            }
        }
    }
    if(!isEmpty(&S)) return 1;
    else return 0;
}

int evaluate(char expr[]){
    StackType S;
    init(&S);

    int op1, op2, num;
    char c;
    int n = strlen(expr);
    for ( int i=0; i<n; i++){
        c = expr[i];
        if (isdigit(c)) {
            num = c - '0';
            push(&S, num);
        } else if(strchr("+-*/", c)){
            op2 = pop(&S), op1 = pop(&S);
            switch(c){
                case '+':push(&S, op1+op2); break;
                case '-':push(&S, op1-op2); break;
                case '*':push(&S, op1*op2); break;
                case '/':push(&S, op1/op2); break;
            }
        }
    }
    return pop(&S);
}

int main(){
    char expr[N];
    printf("Input Expr... ");
    fgets(expr,N,stdin);

    printf("result = %d\n", evaluate(expr));
}


