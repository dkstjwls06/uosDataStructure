#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
typedef char element;
typedef struct 
{
    element queue[N];
    int front, rear;
} QueueType;

void init(QueueType* Q){
    Q->front = Q->rear = -1;
}

int isEmpty(QueueType* Q){
    return Q->front == Q->rear;
}

int isFull(QueueType *Q){
    return Q->rear == N-1;
}

void enqueue(QueueType *Q, element e){
    if (isFull(Q)) printf("Overflow\n");
    else {
        Q->rear++;
        Q->queue[Q->rear] = e;
    }
}

element dequeue(QueueType *Q){
    if (isEmpty(Q)) {
        printf("Empty\n");
        return 0;
    }
    else {
        element e = Q->queue[++(Q->front)];
        return e;
    }
}

void print(QueueType *Q){
    printf("Front : %d - Rear : %d\n", Q->front, Q->rear);
    if(!isEmpty(Q)){

        for(int i= Q->front+1; i<=Q->rear; i++){
            printf("[%c] ", Q->queue[i]);
        }
    }
}

// element peek(QueueType *S){
//     if(isEmpty(S)){
//         puts("Empty!");
//         return -1;
//     }
//     return S->stack[S->top];
// }

int main(){
    QueueType Q;
    init(&Q);
    srand(time(NULL));

    for(int i=0; i<6;i++){
        enqueue(&Q, rand()%26 + 65);
        print(&Q); getchar();
    }
    printf("\n\n");
    for(int i=0; i<3; i++){
        printf("[%c] ",dequeue(&Q));
    }
    printf("\n\n");
    print(&Q);getchar();

}


