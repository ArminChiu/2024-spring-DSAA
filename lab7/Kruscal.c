#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct Edge{
    int begin;
    int end;
    int weight;
} Edge;

typedef struct Graph{
    int vertexNum;
    int edgeNum;
    Edge edges[MAX];
} Graph;

void CreateGraph(Graph *G){
    scanf("%d %d", &G->vertexNum, &G->edgeNum);
    for (int i = 0; i < G->edgeNum; i++){
        scanf("%d %d %d", &G->edges[i].begin, &G->edges[i].end, &G->edges[i].weight);
    }
}

int Find(int *parent, int f){ //回溯双亲
    while (parent[f] > 0){
        f = parent[f];
    }
    return f;
}

void Kruskal(Graph *G){
    int parent[MAX];
    for (int i = 0; i < MAX; i++){ //parent数组初始化
        parent[i] = 0;
    }
    int sum = 0;
    for (int i = 0; i < G->edgeNum; i++){
        int n = Find(parent, G->edges[i].begin);
        int m = Find(parent, G->edges[i].end);
        if (n != m){
            parent[m] = n;
            printf("(%d,%d) %d\n", G->edges[i].begin, G->edges[i].end, G->edges[i].weight);
            sum += G->edges[i].weight;
        }
    } //输出最小生成树的边
    printf("sum=%d\n", sum);
}

int main(){
    Graph G;
    CreateGraph(&G);
    Kruskal(&G);
    return 0;
}
