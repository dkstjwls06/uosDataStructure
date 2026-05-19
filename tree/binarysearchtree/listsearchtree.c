#include <stdio.h>
#include <stdlib.h>

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

TreeNode* insertNode(TreeNode* root, int key){
    if(root == NULL){
        return makeNode(key);
    }
    if(key < root->data){
        root ->left = insertNode(root->left, key);
    } else if(key > root->data){
        root->right = insertNode(root->right, key);
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

TreeNode* minValueNode(TreeNode* root){
    TreeNode* cur = root;
    while(cur->left != NULL) cur = cur->left;
    return cur;
}

TreeNode* maxValueNode(TreeNode* root){
    TreeNode* cur = root;
    while(cur->right != NULL) cur = cur->right;
    return cur;
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
    return root;
}

int main(){
    TreeNode* root = NULL;
    Telement keys[] = {35,18,7,26,12,3,68,22,30,99};
    for(int i=0;i<10;i++){
        root = insertNode(root, keys[i]);
        preOrder(root);
        printf("\n");
    }
    printf("\n");

    root = deleteNode(root, 30); preOrder(root);
    printf("\n"); getchar();
    root = deleteNode(root, 26); preOrder(root);
    printf("\n"); getchar();
    root = deleteNode(root, 18); preOrder(root);
    printf("\n"); getchar();
    
}