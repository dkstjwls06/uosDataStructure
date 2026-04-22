#include <stdio.h>
#include <stdlib.h>

#define N 6
#define QSIZE (N * N + 1)

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
} Coor;

typedef Coor element;
typedef struct
{
    element queue[QSIZE];
    int front, rear;
} QueueType;

void init(QueueType* Q){
    Q->front = Q->rear = 0;
}

int isEmpty(QueueType* Q){
    return Q->front == Q->rear;
}

int isFull(QueueType *Q){
    return Q->front == (Q->rear + 1) % QSIZE;
}

void enqueue(QueueType *Q, element e){
    if (isFull(Q)) printf("Overflow\n");
    else {
        Q->rear = (Q->rear + 1) % QSIZE;
        Q->queue[Q->rear] = e;
    }
}

element dequeue(QueueType *Q){
    if (isEmpty(Q)) {
        puts("Empty!");
        return (element){-1, -1};
    }
    else {
        Q->front = (Q->front + 1) % QSIZE;
        return Q->queue[Q->front];
    }
}

void print(QueueType *Q){
    printf("[ ");
    if(!isEmpty(Q)){
        int i = Q->front;
        while(i != Q->rear){
            i = (i + 1) % QSIZE;
            printf("(%d, %d) ", Q->queue[i].r, Q->queue[i].c);
        }
    }
    puts("]");
}

void insertPos(QueueType* Q, int r, int c){
    if(r < 0 || c < 0 || r >= N || c >= N) return;

    if(map[r][c] != '0' && map[r][c] != 'x') return;

    element pos = {r, c};
    enqueue(Q, pos);

    if(map[r][c] == '0') map[r][c] = '.';   // enqueue 시 방문 표시해서 중복 삽입 방지
}

void printMaze(element e){
    for(int r = 0; r < N; r++){
        for(int c = 0; c < N; c++){
            if(e.r == r && e.c == c) printf(" @ ");
            else printf(" %c ", map[r][c]);
        }
        puts("");
    }
    puts("");
}

int main(){
    QueueType Q;
    init(&Q);
    int found = 0;

    insertPos(&Q, 1, 0);

    while(!isEmpty(&Q)){
        element e = dequeue(&Q);
        int r = e.r, c = e.c;

        printMaze(e);
        if(map[r][c] == 'x'){
            puts("Success.");
            found = 1;
            break;
        }

        insertPos(&Q, r + 1, c);
        insertPos(&Q, r - 1, c);
        insertPos(&Q, r, c + 1);
        insertPos(&Q, r, c - 1);
    }

    if(!found) puts("Fail.");
    return 0;
}
