#include <stdio.h>
#include <stdlib.h>

#define N 6

char map[N][N] = {
    {'1','1','1','1','1','1'},
    {'0','0','0','0','0','1'},
    {'1','0','1','0','1','1'},
    {'1','1','1','0','0','x'},
    {'1','1','1','0','1','1'},
    {'1','1','1','1','1','1'}
};

typedef struct
{
    int r, c;
}Coor;


typedef Coor element;
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
    // for(int i=S->top;i>=0;i--){
    //     printf(" |  %c  |\n",S->stack[i]);
    //     printf("  ______ \n");
    // }
    printf("[ ");
    for(int i = S->top; i>=0;i--){
        printf("(%d, %d) ", S->stack[i].r, S->stack[i].c);
    }
    puts("]");
}

element pop(StackType *S){
    if(isEmpty(S)){
        puts("Empty!");
        return (element){-1, -1};
    }
    element e = S->stack[S->top];
    S->top--;
    return e;
}

element peek(StackType *S){
    if(isEmpty(S)){
        puts("Empty!");
        return (element){-1, -1};
    }
    return S->stack[S->top];
}

void insertPos(StackType* S, int r, int c){
    if(r < 0 || c < 0 || r >= N || c >= N) return;

    if(map[r][c] != '0' && map[r][c] != 'x') return;

    element pos = {r, c};
    push(S, pos);
}

void printMaze(element e){
    for(int r = 0;r < N; r++){
        for(int c=0; c<N; c++){
            if(e.r == r && e.c == c) printf(" @ ");
            else printf(" %c ", map[r][c]);
        }
        puts("");
    }
    puts("");
}

int main(){
    StackType S;
    init(&S);
    int order = 1;

    insertPos(&S, 1, 0);
    while(!isEmpty(&S)){
        element e = pop(&S);
        int r = e.r, c = e.c;

        // printf("%2d. (%d, %d) : ",order++, r, c);
        printMaze(e);
        if(map[r][c] == 'x') {
            puts("Success.");
            break;
        } else {
            map[r][c] = '.';
            insertPos(&S, r+1, c);
            insertPos(&S, r-1, c);
            insertPos(&S, r, c+1);
            insertPos(&S, r, c-1);
        }
        // print(&S);

    }
    return 0;
}