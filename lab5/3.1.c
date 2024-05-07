#include <stdio.h>
#include <stdlib.h>

#define MAX 100005

int n;

typedef struct  Node {
    int parent;
    int depth;
    int max1;
    int max2;
} Node;

Node tree[MAX];

typedef struct ListNode {
    int value;
    struct ListNode* next;
} ListNode;

ListNode* children[MAX]; // 邻接列表

void add_child(int parent, int child) {//孩子兄弟
    ListNode* NewNode = (ListNode*)malloc(sizeof(ListNode));
    NewNode->value = child;
    NewNode->next = children[parent];
    children[parent] = NewNode;
}

void dfs(int i) {
    ListNode* child = children[i];
    while (child != NULL) { // 遍历i的子节点
        int j = child->value;
        tree[j].depth = tree[i].depth + 1;
        dfs(j);
        if (tree[j].max1 + 1 > tree[i].max1) {
            tree[i].max2 = tree[i].max1;
            tree[i].max1 = tree[j].max1 + 1;
        } else if (tree[j].max1 + 1 > tree[i].max2) {
            tree[i].max2 = tree[j].max1 + 1;
        }
        child = child->next;
    }
}

int main() {
    tree[0].parent = -1;
    tree[0].depth = 0;
    tree[0].max1 = 0;
    tree[0].max2 = 0;
    int i;
    scanf("%d", &n);
    for (i = 1; i < n; i++) {
        scanf("%d", &tree[i].parent);
        tree[i].parent--;
        tree[i].depth = 0;
        tree[i].max1 = 0;
        tree[i].max2 = 0;
        add_child(tree[i].parent, i);
    }
    dfs(0);
    int ans = 0;
    for (i = 0; i < n; i++) {
        if (tree[i].max1 + tree[i].max2 > ans) {
            ans = tree[i].max1 + tree[i].max2;
        }
    }
    printf("%d\n", ans);
    return 0;
}