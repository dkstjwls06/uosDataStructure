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

void preOrder(TreeNode* root){
    if(root != NULL){
        printf("[%c] ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(TreeNode* root){
    if(root != NULL){
        inOrder(root->left);
        printf("[%c] ", root->data);
        inOrder(root->right);
    }
}

void postOrder(TreeNode* root){
    if(root != NULL){
        postOrder(root->left);
        postOrder(root->right);
        printf("[%c] ", root->data);
    }
}

int nodeCount(TreeNode* root){
    if(root == NULL)
        return 0;
    else 
        return 1 + nodeCount(root->left) + nodeCount(root->right);

}
// 단말노드의 개수만 세기 : 
int isExternal(TreeNode* root){
    return (root->left == NULL) && (root->right == NULL);
}
int leafNodeCount(TreeNode* root){
    if(root == NULL){
        return 0;
    }
    if(isExternal(root)){
        return 1;
    } else {
        return (leafNodeCount(root->left) + leafNodeCount(root->right));
    }
}

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int height(TreeNode* root){
    if(root == NULL) return 0;
    else return 1+ MAX(height(root->left), height(root->right));
}

void treeReverse(TreeNode* root){
    if(root){
        TreeNode* tmp = root->left;
        root->left = root->right;
        root->right = tmp;

        treeReverse(root->left);
        treeReverse(root->right);
    }
}


// 일반 이진트리는 꼭 아래서부터 위로 만들기.
int main(){
    TreeNode* N6 = makeNode('F',NULL,NULL);
    TreeNode* N5 = makeNode('E',N6,NULL);
    TreeNode* N4 = makeNode('D',NULL,NULL);
    TreeNode* N3 = makeNode('C',NULL,NULL);
    TreeNode* N2 = makeNode('B',N4,N5);
    TreeNode* N1 = makeNode('A',N2,N3);

    printf("Pre : "); preOrder(N1); puts("");
    printf("In : "); inOrder(N1); puts("");
    printf("Post : "); postOrder(N1); puts("\n");

    printf("Node Count : %d\n",nodeCount(N1));
    printf("height : %d\n",height(N1));
    printf("Leaf Count : %d\n",leafNodeCount(N1));

    treeReverse(N1);
    printf("Pre : "); preOrder(N1); puts("");
    printf("In : "); inOrder(N1); puts("");
    printf("Post : "); postOrder(N1); puts("\n");

    return 0;
}

// 이진트리의 반전...?