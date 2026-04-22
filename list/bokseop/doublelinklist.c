// 이중연결리스트.

#include <stdio.h>
#include <stdlib.h>

typedef char element;
typedef struct Node{
    element data;
    struct Node* prev; // left, right : 이진 트리 구현이 됨.
    struct Node* next;
} Node;

typedef struct DListType{
    Node* H;
    Node* T;
    int size;
}DListType;

Node* makeNode(element e){
    Node* node = (Node *) malloc(sizeof(Node));
    node->data = e;
    node->prev = node->next = NULL;
    return node;
}

void init(DListType* DL){
    DL->H = makeNode(0);
    DL->T = makeNode(0);
    DL->H->next = DL->T;
    DL->T->prev = DL->H;

    DL->size = 0;
}

int isEmpty(DListType* DL){ 
    return DL->size == 0;
}
// 현재는 DL->H 는 노드를 가리킴 : 0번 노드 존재. / insertPosition, deletePosition만 있어도 다 해결됨

void insertFirst(DListType* DL, element e){
    Node* p = DL->H; // 더미 노드
    Node* node = makeNode(e);
    node->prev = p;
    node->next = p->next;
    p->next->prev = node;
    p->next = node;
    DL->size++;
} // O(1);

void insertLast(DListType* DL, element e){
    Node* p = DL->T;
    Node* node = makeNode(e);
    node->prev = p->prev;
    node->next = p;
    p->prev->next = node;
    p->prev = node;
    DL->size++;
} // O(1);

void insert(DListType* DL, element e, int pos){
    if(pos <= 0 || pos > DL->size+1){
        puts("Invalid Position");
        return;
    }
    Node* p = DL->H;
    for(int i=1; i<pos; i++) p = p->next;

    Node* node = makeNode(e);
    node->prev = p;
    node->next = p->next;
    p->next->prev = node;
    p->next = node; // 순서 바뀌면 안됨 - 주의! (H에서 접근이랑 T에서 접근이랑 순서 반대.)
    DL->size++;
} // O(N);

element delete(DListType* DL, int pos){
    if(isEmpty(DL)){
        puts("Empty List!");
        return '\0';
    }
    if(pos <= 0 || pos > DL-> size){
        puts("Invalid Position");
        return '\0';
    }
    Node* p = DL->H;
    for(int i=1; i<=pos; i++) p = p->next; // 삭제할 위치 가리키게 하기.
    element data = p->data;
    p->prev->next = p->next;
    p->next->prev = p->prev;
    DL->size--;
    free(p);
    return data;
}

void print(DListType* DL){
    for(Node* p = DL->H->next; p != DL->T; p=p->next){
        printf("[%c] ", p->data);
        if(p->next != DL->T) printf("<-> ");
    }
    puts("");
}


int main(){
    DListType DL;
    init(&DL);

    insert(&DL, 'A', 1); print(&DL);
    insert(&DL, 'B', 1); print(&DL);
    insert(&DL, 'C', 3); print(&DL);
    insert(&DL, 'D', 2); print(&DL);
    insert(&DL, 'E', 5); print(&DL); getchar();

    printf("Del [%c] : ",delete(&DL, 1));
    print(&DL);
    printf("Del [%c] : ",delete(&DL, 1));
    print(&DL);

    return 0;
}
