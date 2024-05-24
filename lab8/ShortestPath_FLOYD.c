#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
#define MAX_VERTEX_NUM 20
#define INT_MAX 10000
typedef struct Stack{
    int data[MAX_VERTEX_NUM];
    int top;
} Stack;

typedef struct Edge{
    int begin;
    int end;
    int weight;
} Edge;

typedef struct ALGraph{
    Edge edge[MAX_VERTEX_NUM];
    int vexnum, edgenum;
} ALGraph;

void CreateALGraph(ALGraph *G){ //创建有向图
    scanf("%d %d", &G->vexnum, &G->edgenum); //输入顶点数和边数
    for (int i = 0; i < G->edgenum; i++){ //输入边的起点、终点和权值（下标从0开始计数）
        scanf("%d %d %d", &G->edge[i].begin, &G->edge[i].end, &G->edge[i].weight);
    }
}

//用Floyd算法求有向图G的顶点v0到其余各顶点的最短路径D[v]
void ShortestPath_FLOYD(ALGraph G, int v0, int **D){
    //构建邻接矩阵
    int **arc = (int **)malloc(sizeof(int *) * G.vexnum);
    for (int i = 0; i < G.vexnum; i++){ //初始化邻接矩阵
        arc[i] = (int *)malloc(sizeof(int) * G.vexnum);
        for (int j = 0; j < G.vexnum; j++){
            arc[i][j] = INT_MAX;
        }
    }
    for (int i = 0; i < G.edgenum; i++){ //将边的权值存入邻接矩阵
        arc[G.edge[i].begin][G.edge[i].end] = G.edge[i].weight;
    }

    for (int i = 0; i < G.vexnum; i++){ //初始化
        for (int j = 0; j < G.vexnum; j++){
            D[i][j] = arc[i][j];
        }
    }

    for (int k = 0; k < G.vexnum; k++){
        for (int i = 0; i < G.vexnum; i++){
            for (int j = 0; j < G.vexnum; j++){
                if (D[i][k] + D[k][j] < D[i][j]){
                    D[i][j] = D[i][k] + D[k][j];
                }
            }
        }
    }
}

int main(){
    ALGraph G;
    CreateALGraph(&G);
    int **D = (int **)malloc(sizeof(int *) * G.vexnum);
    for (int i = 0; i < G.vexnum; i++){
        D[i] = (int *)malloc(sizeof(int) * G.vexnum);
    }
    ShortestPath_FLOYD(G, 0, D);
    for (int i = 0; i < G.vexnum; i++){
        for (int j = 0; j < G.vexnum; j++){
            printf("%d ", D[i][j]);
        }
        printf("\n");
    }
    return 0;
}