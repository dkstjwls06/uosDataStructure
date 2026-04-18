#include <stdio.h>
#include <stdlib.h>

#define N 10
typedef char element;
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

int main(){
    StackType S;
    init(&S);

    push(&S, 'A');
    push(&S, 'B');
    push(&S, 'C');
    push(&S, 'D');

    print(&S);
    getchar();
    printf("After pop : %c\n",pop(&S));
    print(&S);
    getchar();
    printf("After peek(): %c\n",peek(&S));
    print(&S);
    getchar();
}


