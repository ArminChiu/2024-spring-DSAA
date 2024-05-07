//最近公共祖先
#include <stdio.h>
#include <stdlib.h>

#define MAX 100005

typedef struct node {
    int parent;
    int depth;
} Node;

int main() {
    int n,q,i,parent;
    Node tree[MAX];
    tree[0].parent = -1;
    tree[0].depth = 0;
    scanf("%d %d", &n, &q);
    for (i = 1; i < n; i++) {
        scanf("%d", &parent);
        parent--;
        tree[i].parent = parent;
        tree[i].depth = tree[parent].depth + 1;
    }
    for (i = 0; i < q; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        x--;
        y--;
        while (x != y) {
            if (tree[x].depth > tree[y].depth) {
                x = tree[x].parent;
            } else {
                y = tree[y].parent;
            }
        }
        printf("%d\n", x + 1);
    }
    return 0;
}