#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define N 20 // 간선 정렬 -> 배열로 만들기


typedef struct Edge
{
    char v1, v2;
    int weight;
    struct Edge* next;
} Edge;


// 최대 차수 제한을 타파하기 위해 child Sibiling 방식을 사용.
typedef struct AdjVertex{
    char aName;
    Edge* e;
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
    Edge* eHead;
    int vCount, eCount;
} GraphType;

void initGraph(GraphType* G){
    G->vHead = NULL;
    G->eHead = NULL;
    G->eCount = G->vCount = 0;

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

    G->vCount++;

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

void makeAdjacentVertex(Vertex* v, char aName, Edge* e){
    AdjVertex* a = (AdjVertex*) malloc(sizeof(AdjVertex));
    a->aName = aName;
    a->e = e;
    a->next = NULL;

    AdjVertex* p = v->aHead;
    if(p == NULL) v->aHead = a;
    else{
        while(p->next != NULL) p = p->next;
        p->next = a;
    }
}

void insertEdge(GraphType* G, char v1, char v2, int weight){
    Edge* e = (Edge *)malloc(sizeof(Edge));
    e->v1 = v1;
    e->v2 = v2;
    e->weight = weight;
    e->next = NULL;

    G->eCount++;

    Edge* p = G->eHead;
    if(p == NULL) 
        G->eHead = e;
    else{
        while(p->next != NULL){
            p = p->next;
        }
        p->next = e;
    }

    Vertex* v = findVertex(G, v1);
    makeAdjacentVertex(v, v2, e);

    v = findVertex(G, v2);
    makeAdjacentVertex(v, v1, e); // 무방향이므로 양쪽 다 만들어줌.
}

void selectionSort(GraphType* G, Edge* edges[]){
    Edge* p = G->eHead;

    for(int i=0; i<G->eCount; i++){
        edges[i] = p;
        p = p->next;
    }

    for(int i = 0; i< G->eCount - 1; i++){
        int min = i;
        for(int j = i+1; j<G->eCount; j++){
            if(edges[j]->weight < edges[min]->weight){
                min = j;
            }
        }
        p = edges[min];
        edges[min] = edges[i];
        edges[i] = p;
    }

    for(int i=0; i<G->eCount; i++){
        printf("[%c%c%d] ",edges[i]->v1,edges[i]->v2,edges[i]->weight);
    }
    puts("\n");
}



void print(GraphType* G){
    for(Vertex* p = G->vHead; p!=NULL;p=p->next){
        printf("[%c] : ", p->vName);
        for(AdjVertex* q = p->aHead; q != NULL; q= q->next) printf("([%c], [%d]) ",q->aName, q->e->weight);
        puts("");
    }

}


int main(){
    GraphType G;
    initGraph(&G);

    makeVertex(&G, 'A'); makeVertex(&G, 'B');
    makeVertex(&G, 'C'); makeVertex(&G, 'D');
    makeVertex(&G, 'E'); makeVertex(&G, 'F');
    makeVertex(&G, 'G');
    
    insertEdge(&G, 'A', 'B', 29); insertEdge(&G, 'A', 'C', 10);
    insertEdge(&G, 'B', 'C', 16); insertEdge(&G, 'B', 'G', 15);
    insertEdge(&G, 'C', 'D', 12);
    insertEdge(&G, 'D', 'E', 22); insertEdge(&G, 'D', 'G', 18);
    insertEdge(&G, 'E', 'F', 27); insertEdge(&G, 'E', 'G', 25);

    print(&G); puts("");
    
    Edge* edges[N];
    selectionSort(&G, edges);


}