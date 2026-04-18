#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
typedef char element;
typedef struct DequeType
{
    element deque[N];
    int front, rear;
} DequeType;

void init(DequeType* D){
    D->front = D->rear = 0;
}

int isEmpty(DequeType* D){
    return D->front == D->rear;
}

int isFull(DequeType *D){
    return D->front  == (D->rear + 1) % N;
}

void addFront(DequeType *D, element e){
    if(isFUll(D)) puts("Overflow");
    else {
        D->deque[D->front] = e;
        D->front = (D->front - 1 + N) % N;
    }
}

void addRear(DequeType *D, element e){ // == enqueue
    if (isFull(D)) printf("Overflow\n");
    else {
        D->rear = (D->rear + 1) % N;
        D->deque[D->rear] = e;
    }
}

element deleteFront(DequeType *D){ // == deque
    if (isEmpty(D)) {
        puts("Empty");
        return 0;
    }
    else {
        D->front = (D->front + 1) % N;
        element e = D->deque[D->front];
        return e;
    }
}

element deleteRear(DequeType *D){
    if (isEmpty(D)) {
        puts("Empty");
        return 0;
    }
    else {
        element e = D->deque[D->rear];
        D->rear = (D->rear - 1 + N) % N;
        return e;
    }
}

element getFront(DequeType *D){ // == deque
    if (isEmpty(D)) {
        puts("Empty");
        return 0;
    }
    else {
        element e = D->deque[(D->front + 1) % N];
        return e;
    }
}

element getRear(DequeType *D){
    if (isEmpty(D)) {
        puts("Empty");
        return 0;
    }
    else {
        element e = D->deque[D->rear];
        return e;
    }
}

void print(DequeType *D){
    printf("Front : %d - Rear : %d\n", D->front, D->rear);
    if(isEmpty(D)){
        puts("Empty");
        return;
    }
    int i = D->front;
    while(i != D->rear){
        i = (i + 1) % N;
        printf("[%c] ", D->deque[i]);
    }
    puts("");
}

int main(){

    DequeType D;
    init(&D);
    srand(time(NULL));

    // for(int i=0; i<6;i++){
    //     enqueue(&D, rand()%26 + 65);
    //     print(&D); getchar();
    // }
    // for(int i=0; i<3; i++){
    //     printf("[%c] ",dequeue(&D));
    // }
    // printf("\n");
    // print(&Q);getchar();
    // for(int i=0; i<6;i++){
    //     enqueue(&Q, rand()%26 + 65);
    //     print(&Q); getchar();
    // }
}


