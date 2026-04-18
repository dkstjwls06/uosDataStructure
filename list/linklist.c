// 단순연결리스트.

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
    Node* node = (Node *) malloc(sizeof(Node));
    node->data = e;
    node->next = NULL;
    return node;
}

void insertFirst(ListType* L, element e){
    Node* node = makeNode(e);
    node->next = L->head;
    L->head = node;
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
        Node* p = L->head;
        for(int i = 2; i < pos; i++) p = p->next;
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
    Node* p = L->head;
    element data = p->data;
    L->head = p->next;
    L->size--;
    free(p);   
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
        Node* p = L->head;
        for(int i = 2; i < pos; i++) p = p->next;
        element data = p->next->data;

        Node* del = p->next;
        p->next = del->next;
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
    return L->head->data;
}
// 리스트 스택은 따로 수업에서 구현 안할것임.

void print(ListType* L){
    Node* p = L->head;
    while(p != NULL){
        printf("[%c] -> ",p->data);
        p = p->next;
    }
    puts("NULL");
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