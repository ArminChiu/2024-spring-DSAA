//最近公共祖先
#include <stdio.h>
#include <stdlib.h>

#define MAX 100005

typedef struct node {
    int parent;
    long long worth;
    long long cost;
    long long value;
} Node;

Node tree[MAX];

void maxworth(int n) {
    for(int i = n - 1; i > 0; i--) {
        if(tree[i].worth > 0) {
            tree[tree[i].parent].worth += tree[i].worth;
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    
    for(int i = 0; i < n; i++){
        scanf("%lld", &tree[i].cost);
    }
    for(int i = 0; i < n; i++){
        scanf("%lld", &tree[i].value);
        tree[i].worth = tree[i].value - tree[i].cost;
    }
    tree[0].parent = -1;
    for(int i = 1; i < n; i++) {
        scanf("%d", &tree[i].parent);
        tree[i].parent--;
    }
    maxworth(n);
    printf("%lld\n", tree[0].worth);
    return 0;
}