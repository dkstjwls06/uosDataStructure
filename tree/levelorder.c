#include <stdio.h>
#include <stdlib.h>

typedef char Telement;

typedef struct TreeNode{
    Telement data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* makeNode(Telement data, TreeNode* left, TreeNode* right){
    TreeNode* node = (TreeNode*) malloc(sizeof(TreeNode));
    node->data = data;
    node->left = left;
    node->right = right;
    return node;
}

#define N 10
typedef TreeNode* element;
typedef struct 
{
    element queue[N];
    int front, rear;
} QueueType;

void init(QueueType* Q){
    Q->front = Q->rear = 0;
}

int isEmpty(QueueType* Q){
    return Q->front == Q->rear;
}

int isFull(QueueType *Q){
    return Q->front  == (Q->rear + 1) % N;
}

void enqueue(QueueType *Q, element e){
    if (isFull(Q)) printf("Overflow\n");
    else {
        Q->rear = (Q->rear + 1) % N;
        Q->queue[Q->rear] = e;
    }
}

element dequeue(QueueType *Q){
    if (isEmpty(Q)) {
        printf("Empty\n");
        return NULL;
    }
    else {
        Q->front = (Q->front + 1) % N;
        element e = Q->queue[Q->front];
        return e;
    }
}   

void levelOrder(element root){
    if(root == NULL) return;

    QueueType Q;
    init(&Q);

    enqueue(&Q, root);
    while(!isEmpty(&Q)){
        element cur = dequeue(&Q);
        printf("[%c] ",cur->data);

        if(cur->left!= NULL) enqueue(&Q, cur->left);
        if(cur->right!= NULL) enqueue(&Q, cur->right);
        
    }
}

int main(){
    TreeNode* N6 = makeNode('F',NULL,NULL);
    TreeNode* N5 = makeNode('E',N6,NULL);
    TreeNode* N4 = makeNode('D',NULL,NULL);
    TreeNode* N3 = makeNode('C',NULL,NULL);
    TreeNode* N2 = makeNode('B',N4,N5);
    TreeNode* N1 = makeNode('A',N2,N3);

    printf("Level : "); levelOrder(N1); puts("");

    return 0;
}