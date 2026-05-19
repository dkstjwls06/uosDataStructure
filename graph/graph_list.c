#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
// 최대 차수 제한을 타파하기 위해 child Sibiling 방식을 사용.
typedef struct AdjVertex{
    char aName;
    struct AdjVertex* next;
} AdjVertex;

typedef struct Vertex{
    char vName;
    bool isVisit;
    AdjVertex* aHead;
    struct Vertex* next;
} Vertex; // 단순 연결 리스트.

typedef struct GraphType
{
    Vertex* vHead;
} GraphType;

void initGraph(GraphType* G){
    G->vHead = NULL;
}

Vertex* findVertex(GraphType* G, char vName){
    Vertex* p = G->vHead;
    while(p->vName != vName){
        p = p->next;
    }
    return p;
}

void makeVertex(GraphType* G, char vName){
    Vertex* v = (Vertex*) malloc(sizeof(Vertex));
    v->vName = vName;
    v->isVisit = false;
    v->aHead = NULL;
    v->next = NULL;

    Vertex* p = G->vHead;
    if(p == NULL){
        G->vHead = v;
    } else{
        while(p->next != NULL){
            p = p->next;
        }
        p->next = v;
    }
}

void makeAdjacentVertex(Vertex* v, char aName){
    AdjVertex* a = (AdjVertex*) malloc(sizeof(AdjVertex));
    a->aName = aName;
    a->next = NULL;

    AdjVertex* p = v->aHead;
    if(p == NULL) v->aHead = a;
    else{
        while(p->next != NULL) p = p->next;
        p->next = a;
    }
}

void insertEdge(GraphType* G, char v1, char v2){
    Vertex* v = findVertex(G, v1);
    makeAdjacentVertex(v, v2);

    v = findVertex(G, v2);
    makeAdjacentVertex(v, v1); // 무방향이므로 양쪽 다 만들어줌.
}

void print(GraphType* G){
    for(Vertex* p = G->vHead; p!=NULL;p=p->next){
        printf("[%c] : ", p->vName);
        for(AdjVertex* q = p->aHead; q != NULL; q= q->next) printf("[%c] ",q->aName);
        puts("");
    }

}


int main(){
    GraphType G;
    initGraph(&G);

    makeVertex(&G, 'A'); makeVertex(&G, 'B');
    makeVertex(&G, 'C'); makeVertex(&G, 'D');
    makeVertex(&G, 'E'); makeVertex(&G, 'F');
    makeVertex(&G, 'G'); makeVertex(&G, 'H');
    
    insertEdge(&G, 'A', 'B'); insertEdge(&G, 'A', 'C');
    insertEdge(&G, 'B', 'D'); 
    insertEdge(&G, 'C', 'D'); insertEdge(&G, 'C', 'E');
    insertEdge(&G, 'D', 'F');
    insertEdge(&G, 'E', 'G'); insertEdge(&G, 'E', 'H');
    insertEdge(&G, 'G', 'H');
    print(&G);

}