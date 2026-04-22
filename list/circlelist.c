// 원형연결리스트.

#include <stdio.h>
#include <stdlib.h>

typedef char element;
typedef struct Node{
    element data;
    struct Node* next;
} Node;

typedef struct ListType
{
    Node* tail;
    int size;
} ListType;

void init(ListType* L){
    L->tail = NULL;
    L->size = 0;    
}

int isEmpty(ListType* L){
    return L->size == 0;
}

Node* makeNode(element e){
    Node* node = (Node *) malloc(sizeof(Node));
    node->data = e;
    node->next = NULL;
    return node;
}
// 원형 리스트는 비어있을 때 처음 삽입 / 삭제 - 평상시랑 다름.
void insertLast(ListType* L, element e){
    Node* node = makeNode(e);
    // 처음 삽입할 때 : 역할이 첫 번째 노드이자 마지막 노드가 됨.
    if(isEmpty(L)){
        L->tail = node;
        L->tail->next = node;
        
    } else {
        // 첫 번째 노드 : L->tail->next
        node->next = L->tail->next;
        L->tail->next = node;
        L->tail = node;
    }
    L->size++;
}

void insertFirst(ListType* L, element e){
    Node* node = makeNode(e);
    // 처음 삽입할 때 : 역할이 첫 번째 노드이자 마지막 노드가 됨.
    if(isEmpty(L)){
        L->tail = node;
        L->tail->next = node;
        
    } else {
        // 첫 번째 노드 : L->tail->next
        node->next = L->tail->next;
        L->tail->next = node;
    }
    L->size++;
}


void insertPosition(ListType *L, element e, int pos){
    if(pos > L->size + 1 || pos <= 0){
        puts("Invalid Position.");
        return;
    } 
    if(pos == 1) insertFirst(L, e);
    else {
        Node* node = makeNode(e);
        Node* p = L->tail->next;
        for(int i = 1; i < pos-1; i++) p = p->next;
        node->next = p->next;
        p->next = node;
        L->size++;

    }
}

element deleteFirst(ListType *L){
    if(isEmpty(L))
    { 
        puts("Empty List!");
        return '\0'; // exit(1);
    }
    Node* p = L->tail->next;
    element data = p->data;
    
    if(L->size==1){
        free(p);
        L->tail = NULL;
    } else {
        L->tail->next = p->next;
        free(p);
    }
    L->size--;
    return data;

}

element deletePosition(ListType* L, int pos){
    if(isEmpty(L))
    { 
        puts("Empty List!");
        return '\0'; // exit(1);
    }
    if(pos > L->size || pos <= 0){
        puts("Invalid Position.");
        return '\0';
    } 
    if(pos == 1){
        return deleteFirst(L);
    } else {
        Node* p = L->tail->next;
        for(int i = 1; i < pos-1; i++) p = p->next;
        element data = p->next->data;

        Node* del = p->next;
        p->next = del->next;
        if(del == L->tail) L->tail = p;
        free(del);
        L->size--;
        return data;
    }
}

element getFirst(ListType *L){
    if(isEmpty(L))
    { 
        puts("Empty List!");
        return '\0'; // exit(1);
    }  
    return L->tail->next->data;
}
// 리스트 스택은 따로 수업에서 구현 안할것임.

void print(ListType* L){
    Node* p = L->tail->next;
    do {
        printf("[%c] -> ",p->data);
        p = p->next;
    }while(p != L->tail->next);
    puts("(back to head)");
}


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