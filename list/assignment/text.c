#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef char element; // 리스트에 저장할 데이터 타입을 문자형으로 정의

// 이중 연결 리스트의 각 노드를 나타내는 구조체
typedef struct Node{
    element data; // 노드에 저장되는 문자
    struct Node* prev; // left, right : 이진 트리 구현이 됨.
    struct Node* next; // 이전, 다음 노드를 가리키는 포인터
} Node;

typedef struct DListType
{
    Node* H; // 헤드 더미 노드
    Node* T; // 테일 더미 노드
    Node* cursor; // cursor 지정. 항상 "커서 오른쪽 노드"를 가리킴
    int size;// 실제 저장된 문자 수
} DListType;

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

    DL->cursor = DL->T; // 빈 문자열 상태에서 커서는 맨 뒤이므로 T를 가리킴

    DL->size = 0;    
}

int isEmpty(DListType* DL){
    return DL->size == 0;
}
// 현재는 DL->H 는 노드를 가리킴 : 0번 노드 존재. / insertPosition, deletePosition만 있어도 다 해결됨

void insertFirst(DListType* DL, element e){
    Node* p = DL->H;
    Node* node = makeNode(e);
    node->prev = p;
    node->next = p->next;
    p->next->prev = node;
    p->next = node; 
    DL->size++;
} // O(1)

void insertLast(DListType* DL, element e){
    Node* p = DL->T;
    Node* node = makeNode(e);
    node->prev = p->prev;
    node->next = p;
    p->prev->next = node;
    p->prev = node; 
    DL->size++;
} // O(1)

void insert(DListType *DL, element e, int pos){
    if(pos <= 0 || pos > DL->size+1){
        puts("Invalid Position");
        return;
    }
    Node* p = DL->H;
    for(int i=1; i<pos; i++){
        p = p->next; // 단일 노드때는 1번과 2번이 경향이 달랐지만 이번에는 헤드테일 전부 노드이므로 똑같음
    }
    Node* node = makeNode(e);
    node->prev = p;
    node->next = p->next;
    p->next->prev = node;
    p->next = node; // 순서 바뀌면 안됨
    DL->size++;

} // O(N)

element delete(DListType *DL, int pos){
    if(isEmpty(DL)) {
        puts("Empty List.");
        return '\0';
    } 
    if(pos <= 0 || pos > DL-> size){
        puts("Invalid Position");
        return '\0';
    }
    Node* p = DL->H;
    for(int i=1; i<= pos; i++){ // 삭제할 위치 가리키는게 제일 편함
        p = p->next;
    }
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

// 커서 앞에 문자를 삽입하는 함수
void insertChar(DListType* DL, element c){
    Node* p = DL->cursor;// p는 현재 커서 오른쪽에 있는 노드
    Node* node = makeNode(c);// 삽입할 문자를 저장할 새 노드 생성
    node->prev = p->prev;// 새 노드의 이전은 원래 커서 왼쪽 노드
    node->next = p; // 새 노드의 다음은 현재 커서 오른쪽 노드
    p->prev->next = node;// 원래 왼쪽 노드의 다음을 새 노드로 연결
    p->prev = node;// 현재 오른쪽 노드의 이전을 새 노드로 연결
    DL->size++;// 문자 1개가 추가되었으므로 크기 증가
    // [HEAD] |에서 [ ] |으로 [TAIL]
    // 삽입 후에도 커서는 그대로 유지되어야 하므로 cursor는 변경하지 않음
}
// 커서를 왼쪽으로 한 칸 이동하는 함수
void moveLeft(DListType* DL){
    if(DL->cursor == DL->H->next) return; // 이미 맨 뒤면 더 이상 오른쪽 이동 불가
    DL->cursor = DL->cursor->prev; // 커서를 왼쪽 노드로 이동
}
// 커서를 오른쪽으로 한 칸 이동하는 함수
void moveRight(DListType* DL){
    if(DL->cursor == DL->T) return; // 이미 맨 뒤면 더 이상 오른쪽 이동 불가
    DL->cursor = DL->cursor->next; // 커서를 오른쪽 노드로 이동
}
// 커서 왼쪽의 문자를 삭제하는 함수(백스페이스)
void deleteChar(DListType* DL){
    Node* p = DL->cursor;// p는 현재 커서 오른쪽 노드
    // [HEAD] |으로 [ ] |에서 [TAIL]
    Node* del = p->prev;// 삭제할 노드는 커서 왼쪽 노드
    if(del == DL->H) return; // 왼쪽에 실제 문자가 없으면 아무것도 하지 않음.
    del->prev->next = p;// 삭제할 노드의 이전 노드와 현재 커서 오른쪽 노드를 연결
    p->prev = del->prev;//현재 커서 오른쪽 노드의 이전을 삭제 노드의 이전으로 변경
    DL->size--;// 문자 1개가 삭제되었으므로 크기 감소
    free(del);// 삭제한 노드의 동적 메모리 반환
}
// 현재 텍스트와 커서 위치를 출력하는 함수
void printText(DListType* DL){
    for(Node* p = DL->H->next; p != DL->T; p=p->next){ // 첫 실제 노드부터 끝 직전까지 순회
        if(DL->cursor == p){// 현재 노드가 커서가 가리키는 오른쪽 노드라면
            printf("| ");// 해당 문자 앞에 커서 표시
        }
        printf("%c ",p->data);// 현재 문자 출력
    }
    if(DL->cursor == DL->T) printf("|");// 커서가 맨 끝이면 마지막에 | 출력
    puts("");// 출력 후 줄바꿈
}

// 프로그램 종료 전 리스트의 모든 노드를 해제하는 함수
void freeAll(DListType* DL){
    Node* p = DL->H;// 헤드부터 시작하여
    while(p != NULL){// 모든 노드를 순서대로 방문할 때까지 반복
        Node* del = p;// 현재 삭제할 노드를 임시 저장
        p = p->next;// 다음 노드로 이동
        free(del); // 현재 노드의 메모리 해제
    }
}

int main(){
    DListType DL; // 이중 연결 리스트 변수 선언
    init(&DL);// 리스트 초기화
    char ch[100];// 명령어 문자열을 저장할 배열
    fgets(ch, 100, stdin);// 한 줄 입력 받기
    ch[strcspn(ch,"\n")] = '\0';// 입력 끝의 개행 문자 제거
    int i = 0;
    while(ch[i] != '\0'){ // 문자열 끝을 만날 때까지 반복
        switch (ch[i]) // 현재 문자에 따라 동작 수행
        {
            case '>':
                moveRight(&DL);// '>' 입력이면 커서를 오른쪽으로 이동
                break;
            case '<':
                moveLeft(&DL);// '<' 입력이면 커서를 왼쪽으로 이동
                break;
            case '-':
                deleteChar(&DL);// '-' 입력이면 커서 왼쪽 문자 삭제
                break;
            default: // 그 외 문자인 경우
                if(isupper(ch[i]))// 대문자 A~Z이면
                    insertChar(&DL, ch[i]);// 해당 문자를 커서 앞에 삽입
                break;
        }  
        i++;// 다음 명령 문자로 이동
    }
    printText(&DL);// 최종 편집 결과 출력

    freeAll(&DL); // 사용한 모든 동적 메모리 해제
    return 0;
}