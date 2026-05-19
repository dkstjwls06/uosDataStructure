// 교재에 없음. 이렇게 표현할 수도 있다 참고. 파이썬 형태..?

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define N 8 // 정점의 개수
#define D 3 // 정점별 최대 차수

typedef struct Vertex
{
    char vName;
    int adj[D];
    int adjCount;
} Vertex; 


Vertex G[N] = {
    {'A', {1,2}, 2},
    {'B', {0,3}, 2},  
    {'C', {0,3,4}, 3},
    {'D', {1,2,5}, 3},
    {'E', {2,6,7}, 3},
    {'F', {3}, 1},
    {'G', {4,7}, 2},
    {'H', {4,6}, 2},
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


// 반복문으로 (핵심)
void iDFS(bool visited[], int s){
    StackType S;
    init(&S);

    push(&S, s);
    visited[s] = true;
    printf("[%c] ",G[s].vName);

    while(!isEmpty(&S)){
        s = peek(&S); // 일단 버리진 않고 / 실제는 이걸 뺄 때에는 더 이상 갈 곳이 없어야 함. (순환호출 매커니즘과 동일)
        bool flag = false;

        for(int i = 0; i < G[s].adjCount; i++){
            int t = G[s].adj[i];
            if(!visited[t]) {
                push(&S, t);
                visited[t] = true;
                printf("[%c] ",G[t].vName);

                flag = true;
                break;
            }
        }
        if(!flag){ // 인접 정점에서 갈 데가 없는 경우 (분기문에 걸리지 않음)
            pop(&S);
        }
    }
}

// 순환 호출로...
void rDFS(bool visited[], int s){
    visited[s] = true;
    printf("[%c] ",G[s].vName);

    for(int i = 0; i < G[s].adjCount; i++){
        int t = G[s].adj[i];
        if(!visited[t]) rDFS(visited, t);
    }
}


int main(){
    bool visited[N] = {false};

    rDFS(visited, 2); puts("");
    memset(visited, 0, sizeof(visited));
    iDFS(visited, 2); puts("");
}