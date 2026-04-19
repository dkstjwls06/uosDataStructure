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
    element stack[N];
    int top;
} StackType;

void init(StackType* S){
    S->top = -1;
}

int isEmpty(StackType* S){
    return S->top == -1;
}

int isFull(StackType *S){
    return S->top == N-1;
}

void push(StackType *S, element e){
    if (isFull(S)) printf("Overflow\n");
    else {
        S->top++;
        S->stack[S->top] = e;
    }
}

element pop(StackType *S){
    if(isEmpty(S)){
        puts("Empty!");
        return NULL;
    }
    element e = S->stack[S->top];
    S->top--;
    return e;
}

void iterPreOrder(element root){
    StackType S;
    init(&S);

    while(root!=NULL || !isEmpty(&S)){
        while(root!=NULL){
            printf("[%c] ",root->data);
            if(root->right != NULL){
                push(&S, root->right);
            }
            root = root->left;
        }
        if(!isEmpty(&S)){
            root = pop(&S);
        }

    }
}

void iterInOrder(element root){
    StackType S;
    init(&S);

    while(root!=NULL || !isEmpty(&S)){
        //왼쪽 끝까지 이동(L)
        while(root!=NULL){
            push(&S, root);
            root = root->left;
        }
        //데이터 읽기(V)
        root = pop(&S);
        printf("[%c] ",root->data);
        //오른쪽으로 이동 (R)
        root = root->right;
    }
}

void iterPostOrder(element root){
    StackType S;
    init(&S);

    element prev = NULL;

    while(root != NULL || !isEmpty(&S)){
        // 1. 왼쪽 끝까지 방문 (L) 
        while(root != NULL){
            push(&S, root);
            root = root->left;
        }

        // 2. Stack Top 확인
        element cur = S.stack[S.top];

        // 3. 오른쪽이 없거나 방문했으면 방문
        if(cur->right == NULL || cur->right == prev){
            printf("[%c] ",cur->data);
            pop(&S);
            prev = cur;
            root = NULL;
        }else {
            root = cur->right;
        }
    }
}

void iterTreeReverse(element root){
    if (root == NULL) return;

    StackType S;
    init(&S);

    push(&S, root);

    while(!isEmpty(&S)){
        element cur = pop(&S);

        //swap
        element temp = cur->left;
        cur->left = cur->right;
        cur->right = temp;

        if(cur->left != NULL){
            push(&S, cur->left);
        }
        if(cur->right != NULL)
            push(&S, cur->right);
    }
    
}


int main(){
    TreeNode* N6 = makeNode('F',NULL,NULL);
    TreeNode* N5 = makeNode('E',N6,NULL);
    TreeNode* N4 = makeNode('D',NULL,NULL);
    TreeNode* N3 = makeNode('C',NULL,NULL);
    TreeNode* N2 = makeNode('B',N4,N5);
    TreeNode* N1 = makeNode('A',N2,N3);

    printf("Pre : "); iterPreOrder(N1); puts("");
    printf("In : "); iterInOrder(N1); puts("");
    printf("Post : "); iterPostOrder(N1); puts("\n");    

    // printf("Node Count : %d\n",nodeCount(N1));
    // printf("height : %d\n",height(N1));
    // printf("Leaf Count : %d\n",leafNodeCount(N1));

    iterTreeReverse(N1);
    printf("In : "); iterInOrder(N1); puts("");
    // printf("Pre : "); preOrder(N1); puts("");
    // printf("In : "); inOrder(N1); puts("");
    // printf("Post : "); postOrder(N1); puts("\n");

    return 0;
}