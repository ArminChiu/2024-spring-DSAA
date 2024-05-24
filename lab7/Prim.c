#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#define MAXCOST 9999

int graph[MAX][MAX];

void prim(int graph[][MAX], int n){
    int lowcost[MAX];
    int mst[MAX];
    int min, minid, sum = 0;
    for (int i = 2; i <= n; i++){
        lowcost[i] = graph[1][i];
        mst[i] = 1;
    }
    mst[1] = 0;
    for (int i = 2; i <= n; i++){
        min = MAXCOST;
        minid = 0;
        for (int j = 2; j <= n; j++){
            if (lowcost[j] < min && lowcost[j] != 0) {
                min = lowcost[j];
                minid = j;
            }
        }
        printf("(%d,%d) %d\n", mst[minid], minid, min);
        sum += min;
        lowcost[minid] = 0;
        for (int j = 2; j <= n; j++){
            if (graph[minid][j] < lowcost[j]){
                lowcost[j] = graph[minid][j];
                mst[j] = minid;
            }
        }
    }
    printf("sum=%d\n", sum);
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m); //n顶点数，m边数
    for (int i = 1; i <= n; i++){ //初始化图
        for (int j = 1; j <= n; j++){
            graph[i][j] = MAXCOST;
        }
    }
    for (int i = 1; i <= m; i++){ //输入各边的信息
        int u, v, cost;
        scanf("%d %d %d", &u, &v, &cost);
        graph[u][v] = cost;
        graph[v][u] = cost;
    }
    prim(graph, n);
    return 0;
}