//基于DFS判别邻接表存储的有向图中是否存在有顶点i到顶点j的路径
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

#define MAX 100 //最大顶点数

typedef struct node { //邻接表
    int vertex;
    struct node *next;
} Node;

Node *graph[MAX]; //邻接表

void add_edge(int i, int j) { //添加边(i, j)
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->vertex = j;
    newNode->next = graph[i];
    graph[i] = newNode;
}

int visited[MAX]; //标记数组

void free_graph() { //释放邻接表
    for(int i = 0; i < MAX; i++) {
        Node *p = graph[i];
        while(p != NULL) {
            Node *q = p;
            p = p->next;
            free(q);
        }
    }
}

int dfs(int i, int j) { //判断是否存在从顶点i到顶点j的路径
    if(i == j) {
        return 1;
    }
    visited[i] = 1;
    Node *p = graph[i];
    while(p != NULL) {
        if(visited[p->vertex] == 0) {
            if(dfs(p->vertex, j) == 1) {
                return 1;
            }
        }
        p = p->next;
    }
    return 0;
}

int main() {
    int n, m;
    printf("Please input the number of vertices and edges:\n");
    scanf("%d %d", &n, &m);
    printf("Please input the edges:\n");
    for(int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        add_edge(a, b);
    }
    printf("Please input the pairs of vertices:(input -1 -1 to exit)\n");
    while(1) {
        int i, j;
        scanf("%d %d", &i, &j);
        if(i == -1 && j == -1) {
            break;
        }
        if(dfs(i, j) == 1) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
        for(int i = 0; i < n; i++) {
            visited[i] = 0;
        }
    }
    free_graph();
    return 0;
}