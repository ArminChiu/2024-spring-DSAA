//构建二叉搜索树
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <time.h>

typedef struct Tree {
    int val; // 数值
    struct Tree *left, *right; // 左右孩子指针
} Tree;

Tree* buildTree(int *preorder, int n) {
    if (n == 0) {
        return NULL;
    }
    //数列第一个元素为根节点
    Tree *root = (Tree *)malloc(sizeof(Tree));
    root->val = preorder[0];
    root->left = root->right = NULL;
    //根节点即叶子节点
    if (n == 1) {
        return root;
    }
    //有孩子节点
    int i = 0;
    //在值大于根节点值前，节点的都在左子树
    while (i < n - 1 && preorder[i+1] < preorder[0]) {
        i++;
    }
    root->left = buildTree(preorder + 1, i);
    root->right = buildTree(preorder + i + 1, n - i - 1);
    return root;
}

typedef struct Queue {
    struct Tree *node;
    struct Queue *next;
} Queue;
Queue *head, *tail;
void initQueue() {
    head = tail = NULL;
}
int empty() {
    return head == NULL;
}
Tree* peek() {
    return head->node;
}
void pop() {
    if (empty()) {
        return;
    }
    Queue *nxt = head->next;
    free(head);
    head = nxt;
}
void push(Tree *node) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->next = NULL;
    q->node = node;
    if (head == NULL) {
        head = tail = q;
    } else {
        tail->next = q;
        tail = q;
    }
    
}

int main() {
    initQueue();
    int n; scanf("%d", &n);
    int *preorder = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &preorder[i]);
    }

    Tree *root = buildTree(preorder, n);
    
    push(root);
    while(!empty()) {
        Tree *node = peek();
        pop();
        if (node == NULL) {
            printf("null ");
            continue;
        }
        printf("%d ", node->val);
        if (!node->left && !node->right) {
            continue;
        }
        push(node->left);
        push(node->right);
    }

    puts("");
    return 0;
}