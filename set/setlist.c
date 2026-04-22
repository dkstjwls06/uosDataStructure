#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct Node{
    element data;
    struct Node* next;
} Node;

typedef struct SetType{
    Node* head;
    int size;
} SetType;

// 초기화
void init(SetType* S){
    S->head = NULL;
    S->size = 0;
}

// 공집합 검사
int isEmpty(SetType* S){
    return S->size == 0;
}

// 노드 생성
Node* makeNode(element e){
    Node* node = (Node*)malloc(sizeof(Node));
    if(node == NULL){
        fprintf(stderr, "메모리 할당 실패\n");
        exit(1);
    }
    node->data = e;
    node->next = NULL;
    return node;
}

// 원소 존재 여부 검사
int contains(SetType* S, element e){
    Node* p = S->head;
    while(p != NULL){
        if(p->data == e) return 1;
        p = p->next;
    }
    return 0;
}

// 집합에 삽입
void insertSet(SetType* S, element e){
    // 중복 허용 안 함
    if(contains(S, e)) return;

    Node* node = makeNode(e);
    node->next = S->head;   // 맨 앞 삽입
    S->head = node;
    S->size++;
}

// 집합에서 삭제
int deleteSet(SetType* S, element e){
    if(isEmpty(S)) return 0;

    Node* p = S->head;
    Node* prev = NULL;

    while(p != NULL){
        if(p->data == e){
            if(prev == NULL){           // 첫 노드 삭제
                S->head = p->next;
            } else {                    // 중간/마지막 노드 삭제
                prev->next = p->next;
            }
            free(p);
            S->size--;
            return 1;   // 삭제 성공
        }
        prev = p;
        p = p->next;
    }

    return 0;   // 원소 없음
}

// 출력
void printSet(SetType* S){
    printf("{ ");
    for(Node* p = S->head; p != NULL; p = p->next){
        printf("%d ", p->data);
    }
    printf("}\n");
}

// 전체 해제
void clear(SetType* S){
    Node* p = S->head;
    while(p != NULL){
        Node* del = p;
        p = p->next;
        free(del);
    }
    S->head = NULL;
    S->size = 0;
}

// 합집합 C = A ∪ B
SetType setUnion(SetType* A, SetType* B){
    SetType C;
    init(&C);

    for(Node* p = A->head; p != NULL; p = p->next){
        insertSet(&C, p->data);
    }
    for(Node* p = B->head; p != NULL; p = p->next){
        insertSet(&C, p->data);
    }

    return C;
}

// 교집합 C = A ∩ B
SetType setIntersect(SetType* A, SetType* B){
    SetType C;
    init(&C);

    for(Node* p = A->head; p != NULL; p = p->next){
        if(contains(B, p->data)){
            insertSet(&C, p->data);
        }
    }

    return C;
}

// 차집합 C = A - B
SetType setDifference(SetType* A, SetType* B){
    SetType C;
    init(&C);

    for(Node* p = A->head; p != NULL; p = p->next){
        if(!contains(B, p->data)){
            insertSet(&C, p->data);
        }
    }

    return C;
}

int main(void){
    SetType A, B, C, D, E;
    init(&A);
    init(&B);

    insertSet(&A, 1);
    insertSet(&A, 3);
    insertSet(&A, 5);
    insertSet(&A, 3);   // 중복 삽입 -> 무시

    insertSet(&B, 3);
    insertSet(&B, 4);
    insertSet(&B, 5);

    printf("A = ");
    printSet(&A);

    printf("B = ");
    printSet(&B);

    deleteSet(&A, 1);
    printf("A after delete 1 = ");
    printSet(&A);

    C = setUnion(&A, &B);
    D = setIntersect(&A, &B);
    E = setDifference(&A, &B);

    printf("A U B = ");
    printSet(&C);

    printf("A ∩ B = ");
    printSet(&D);

    printf("A - B = ");
    printSet(&E);

    clear(&A);
    clear(&B);
    clear(&C);
    clear(&D);
    clear(&E);

    return 0;
}