// 단순연결리스트

#include <stdio.h>
#include <stdlib.h>

typedef char element;
typedef struct Node{
    element data;
    struct Node* next;
} Node;

typedef struct ListType
{
    Node* head;
    int size;
} ListType;

void init(ListType* L){
    L->head = NULL;
    L->size = 0;
}

int isEmpty(ListType* L){
    return L->size == 0;
}

Node* makeNode(element e){
    Node* node = (Node *)malloc(sizeof(Node));
    node->data = e;
    node->next = NULL;
    return node;
}


// 첫 번째 자리에 Node 끼워넣기.
void insertFirst(ListType* L, element e){
    Node* node = makeNode(e);
    node->next = L->head;
    L->head = node;
    L->size++;
}

// 임의 자리에 Node 끼워넣기.
// pos : 1-based. / 맨 마지막 노드로 추가하는것까지 고려하여 size+1로 잡음.
void insertPosition(ListType* L, element e, int pos){
    if(pos > L->size+1 || pos <= 0){ 
        puts("Invalid Position.");
        return;
    }
    if(pos == 1) insertFirst(L, e);
    else {
        Node* node = makeNode(e);
        Node* p = L->head; // 첫번째 노드
        for(int i = 2; i<pos; i++) p = p->next; // 위치 바로 전까지 이동
        node->next = p->next; // 마지막이면 NULL, 아니면 그 다음 노드
        p->next = node;
        L->size++;
    }
}

element deleteFirst(ListType *L){
    if(isEmpty(L)){
        puts("Empty!");
        return '\0';
    }
    Node *p = L->head;
    element data = p->data;
    L->head = p->next;
    L->size--;
    free(p);
    return data;
}

element deletePosition(ListType* L, int pos){
    if(isEmpty(L)){
        puts("Empty List!");
        return '\0';
    }
    if(pos <= 0 || pos > L->size){
        puts("Invalid Position.");
        return '\0';
    }
    if(pos == 1) deleteFirst(L);
    else {
        Node* p = L->head;
        for(int i=2; i<pos; i++) p = p->next;
        element data = p->next->data;

        Node* del = p->next;
        p->next = del->next;
        free(del);
        L->size--;
        return data;
    }
}

element getFirst(ListType* L){
    if(isEmpty(L)){
        puts("Empty!");
        return '\0';
    }
    return L->head->data;
}

element getPosition(ListType* L, int pos){
    if(isEmpty(L)){
        puts("Empty List!");
        return '\0';
    }
    if(pos <= 0 || pos > L->size){
        puts("Invalid Position.");
        return '\0';
    }
    if(pos == 1) getFirst(L);
    else {
        Node* p = L->head;
        for(int i=2; i<pos; i++) p = p->next;
        return p->next->data;
    }
}

void print(ListType* L){
    Node* p = L->head;
    printf("[%c]",p->data);
    p = p->next;
    while(p != NULL){
        printf(" -> [%c]",p->data);
        p=p->next;
    }
    puts("");
} // 제로록 방식.

int main(){
    ListType L;
    init(&L);
    insertFirst(&L, 'A');
    insertFirst(&L, 'C');
    insertFirst(&L, 'B');
    print(&L);

    insertPosition(&L, 'D', 2);
    insertPosition(&L, 'E', 5);
    print(&L);

    printf("Del [%c] : ",deleteFirst(&L));
    print(&L);

    printf("Del [%c] : ",deletePosition(&L, 3));
    print(&L);
}