// 기말고사 필수출제...
#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))

typedef int Telement;
typedef struct TreeNode{
    Telement data;
    struct TreeNode* left;
    struct TreeNode* right;
}TreeNode;

TreeNode* makeNode(Telement key){
    TreeNode* node = (TreeNode *)malloc(sizeof(TreeNode));

    node->data = key;
    node->left = node->right = NULL;

    return node;
}

int getHeight(TreeNode* root){
    if(!root)
        return 0;
    else 
        return 1 + MAX(getHeight(root->left), getHeight(root->right));
}

int getBalance(TreeNode* root){
    if(root == NULL)
        return 0;
    
    return getHeight(root->left) - getHeight(root->right);
}

TreeNode* minValueNode(TreeNode* root){
    TreeNode* cur = root;
    while(cur->left != NULL) cur = cur->left;
    return cur;
}

TreeNode* rotateLeft(TreeNode* p){
    TreeNode* c = p->right;

    p->right = c->left;
    c->left = p;

    return c;
}

TreeNode* rotateRight(TreeNode* p){
    TreeNode* c = p->left;

    p->left = c->right;
    c->right  = p;

    return c;
}

TreeNode* insertNode(TreeNode* root, int key){
    if(root == NULL){
        return makeNode(key);
    }
    if(key < root->data){
        root ->left = insertNode(root->left, key);
    } else if(key > root->data){
        root->right = insertNode(root->right, key);
    }
    int balance = getBalance(root);
    
    if(balance > 1 && key < root->left->data) // LL
    {
        puts("--- LL Type --"); 
        return rotateRight(root);
    }

    if(balance < -1 && key > root->right->data) // RR
    {
        puts("--- RR Type --");
        return rotateLeft(root);
    }
    if(balance > 1 && key > root->left->data) // LL
    {
        puts("--- LR Type --"); 
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if(balance < -1 && key < root->right->data) // RR
    {
        puts("--- RL Type --");
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }


    return root;
}

TreeNode* deleteNode(TreeNode* root, Telement key){
    if(root== NULL)
        return NULL;
    if(key < root->data){
        root ->left = deleteNode(root->left, key);
    } else if(key > root->data){
        root->right = deleteNode(root->right, key);
    }
    else{
        if(root->left == NULL){
            TreeNode* temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right == NULL){
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }else{
            TreeNode* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
        
        
    }

    int balance = getBalance(root);

    if(balance > 1 && getBalance(root->left) >= 0) // LL
    {
        puts("--- LL Type --"); 
        return rotateRight(root);
    }

    if(balance < -1 && getBalance(root->right) <= 0) // RR
    {
        puts("--- RR Type --");
        return rotateLeft(root);
    }
    if(balance > 1 && getBalance(root->left)<0) // LR
    {
        puts("--- LR Type --"); 
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if(balance < -1 && getBalance(root->right)>0) // RL
    {
        puts("--- RL Type --");
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

void preOrder(TreeNode* root){
    if(root != NULL){
        printf("[%2d] ",root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void displayInserted(TreeNode* root, Telement key){
    printf("[Insert %d] : ",key);
    preOrder(root);
    puts("");
}

void displayDeleted(TreeNode* root, Telement key){
    printf("[Delete %d] : ",key);
    preOrder(root);
    puts("");
}

int main(){
    TreeNode* root = NULL;
    // Telement data[] = {7,8,9,2,1,5,3,6,4};
    Telement data[] = {1,2,3,4};
    for(int i=0;i<4;i++){
        root = insertNode(root, data[i]);
        displayInserted(root, data[i]);
    }

    root = deleteNode(root, 1); displayDeleted(root, 1);
    // root = deleteNode(root, 3); displayDeleted(root, 3);
    
}
// 삭제 연산도 구현할 것. 과제.
// (삽입 연산의 balance 탐색 부터 거의 그대로 이용하여)