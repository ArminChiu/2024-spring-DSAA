#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
#define MAX_VERTEX_NUM 20

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

int *FindinDegree(ALGraph G){ //求入度
    int *indegree = (int *)malloc(sizeof(int) * G.vexnum); //记录各点入度
    for (int i = 0; i < G.vexnum; i++){ //初始化入度
        indegree[i] = 0;
    }

    for (int i = 0; i < G.edgenum; i++){ //遍历所有边，统计入度
        indegree[G.edge[i].end]++;
    }
    return indegree;
}

int TopologicalSort(ALGraph G, Stack *T, int *ve){ //拓扑排序，求出各点ve值
    int *indegree = FindinDegree(G); //求入度
    T->top = -1; //初始化栈
    for (int i = 0; i < G.vexnum; i++){ //初始化ve值
        ve[i] = 0;
    }
    
    for (int i = 0; i < G.vexnum; i++){ //将入度为0的点入栈
        if (indegree[i] == 0){
            T->data[++T->top] = i;
        }
    }
    int count = 0;
    while (T->top != -1){ //栈未空时
        int v = T->data[T->top--]; //出栈
        count++;
        printf("%d ", v);
        for (int j = 0; j < G.edgenum; j++){ //遍历所有边，更新ve值
            if (G.edge[j].begin == v){ 
                indegree[G.edge[j].end]--; //找到以v为起点的边，更新终点的入度
                if (ve[v] + G.edge[j].weight > ve[G.edge[j].end]){ //更新ve值
                    ve[G.edge[j].end] = ve[v] + G.edge[j].weight;
                }
                if (indegree[G.edge[j].end] == 0){ //将入度为0的点入栈
                    T->data[++T->top] = G.edge[j].end;
                }
            }
        }
    }
    printf("\n");
    if (count < G.vexnum){ //判断是否有回路
        return ERROR;
    }
    return OK;
}

int CriticalPath(ALGraph G){
    Stack T;
    int *ve = (int *)malloc(sizeof(int) * G.vexnum); //记录各点ve值
    int *vl = (int *)malloc(sizeof(int) * G.vexnum); //记录各点vl值
    if (TopologicalSort(G, &T, ve) == ERROR){ //判断是否有回路
        return ERROR;
    }
    for (int i = 0; i < G.vexnum; i++) { //初始化vl数组
        vl[i] = ve[G.vexnum - 1];
    }

    for (int i = G.vexnum - 1; i >= 0; i--){ //更新vl值
        for (int j = 0; j < G.edgenum; j++){
            if (G.edge[j].end == i){
                if (vl[G.edge[j].begin] > vl[i] - G.edge[j].weight){
                    vl[G.edge[j].begin] = vl[i] - G.edge[j].weight;
                }
            }
        }
    }
    for (int i = 0; i < G.vexnum; i++){
        for (int j = 0; j < G.edgenum; j++){
            if (G.edge[j].begin == i){
                int e = ve[i];
                int l = vl[G.edge[j].end] - G.edge[j].weight;
                if (e == l){ //关键路径上的边
                    printf("%d->%d\n", i, G.edge[j].end);
                }
            }
        }
    }
    return OK;
}

int main(){
    ALGraph G;
    CreateALGraph(&G);
    CriticalPath(G);
    return 0;
}