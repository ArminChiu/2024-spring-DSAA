//平衡二叉树判定
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <time.h>


typedef struct Tree {
    int val; // 数字
    struct Tree *left, *right; //左右孩子指针
} Tree;

int isBalance(Tree *root) {
    int left, right;
    if(root==NULL) return 0;
    if(root->left != NULL){
        left=isBalance(root->left);
    }else{
        left=0;
    }
    if(root->right != NULL){
        right=isBalance(root->right);
    }else{
        right=0;
    }
    if(left==-1||right==-1||abs(left-right)>1) return -1;
    if(abs(left-right)>1) return -1;
    return left>right?left+1:right+1;
}

Tree *insert(Tree *node, int val) {
    if (node == NULL) {
        Tree *newNode = (Tree *)malloc(sizeof(Tree));
        newNode->val = val;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (val < node->val) {
        node->left = insert(node->left, val);
    } else {
        node->right = insert(node->right, val);
    }
    return node;
}

int main() {
    int n; 
    scanf("%d", &n);
    Tree *root = NULL;
    for (int i = 0; i < n; i++) {
        int val; scanf("%d", &val);
        root = insert(root, val);
    }
    puts(isBalance(root) != -1 ? "yes" : "no");    
    return 0;
}