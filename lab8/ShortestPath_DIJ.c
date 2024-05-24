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

//用Dijkstra算法求有向图G的顶点v0到其余各顶点的最短路径P[v]及带权长度D[v]
void ShortestPath_DIJ(ALGraph G, int v0, int *P, int *D){
    int *final = (int *)malloc(sizeof(int) * G.vexnum); //记录是否已经找到最短路径
    
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
        final[i] = 0;
        D[i] = arc[v0][i];
        P[i] = -1;
    }
    D[v0] = 0; //v0到v0的距离为0
    final[v0] = 1; //v0到v0的最短路径已经找到

    for (int i = 1; i < G.vexnum; i++){
        int min = INT_MAX;
        int k = v0;
        for (int j = 0; j < G.vexnum; j++){
            if (!final[j] && D[j] < min){ //找到当前距离v0最近的顶点
                min = D[j];
                k = j;
            }
        }
        final[k] = 1;
        for (int j = 0; j < G.vexnum; j++){
            if (!final[j] && min + arc[k][j] < D[j]){ //更新最短路径
                D[j] = min + arc[k][j];
                P[j] = k;
            }
        }
    }
}

int main(){
    ALGraph G;
    CreateALGraph(&G);
    int *P = (int *)malloc(sizeof(int) * G.vexnum); //记录最短路径
    int *D = (int *)malloc(sizeof(int) * G.vexnum); //记录最短距离
    for(int i = 0; i < G.vexnum; i++){
        ShortestPath_DIJ(G, i, P, D);
        for (int j = 0; j < G.vexnum; j++){
            printf("%d ", D[j]);
        }
        printf("\n");
    }
    return 0;
}