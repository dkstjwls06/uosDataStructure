#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define N 8
char vName[N] = {'A','B','C','D','E','F','G','H'};

int Graph[N][N] ={
    {0,1,1,0,0,0,0,0},
    {1,0,0,1,0,0,0,0},
    {1,0,0,1,1,0,0,0},
    {0,1,1,0,0,1,0,0},
    {0,0,1,0,0,0,1,1},
    {0,0,0,1,0,0,0,0},
    {0,0,0,0,1,0,0,1},
    {0,0,0,0,1,0,1,0}
};

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

void rDFS(bool visited[], int s){
    visited[s] = true;
    printf("[%c] ",vName[s]);
    for(int t = 0; t < N; t++){
        if(Graph[s][t] == 1 && visited[t] == false)
        rDFS(visited, t);
    }
}

void iDFS(bool visited[], int s){
    StackType S;
    init(&S);
    
    push(&S, s);
    visited[s] = true;
    printf("[%c] ", vName[s]);
    
    while(!isEmpty(&S)){
        s = peek(&S);
        bool flag = false;
        
        for(int i=0; i < N; i++){
            if(Graph[s][i]){
                if(!visited[i]) {
                    push(&S, i);
                    visited[i] = true;
                    printf("[%c] ", vName[i]);
                    
                    flag = true;
                    break;
                }
            }
            
        }
        if(!flag) pop(&S);
        
    }
    
}


int main(){
    bool visited[N] = {false};

    rDFS(visited, 2); puts("");
    for(int i=0; i<N; i++) visited[i] = false;
    iDFS(visited, 2); puts("");
}