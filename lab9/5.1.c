//给你一个有向图图𝐺，请求出两两节点之间的最短路径。
//输入格式：第一行一个正整数𝑛表示图的节点数量。接下来是一个𝑛∗𝑛大小的矩阵，表示𝐺的邻接矩阵。其中第i行第j列的值𝑎𝑖,𝑗表示从节点i到节点j存在一条长度为𝑎𝑖,𝑗的边。当𝑎𝑖,𝑗=−1时表示不存在边。矩阵正对角线上的元素保证为0。
//输出格式：输出一个𝑛∗𝑛大小的矩阵，表示两两节点之间的最短路径。如果两节点之间不存在路径，则输出-1。

#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int graph[MAX][MAX]; //邻接矩阵

void floyd(int graph[][MAX], int n){ //Floyd算法
    for (int k = 1; k <= n; k++){
        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= n; j++){
                if (graph[i][k] != -1 && graph[k][j] != -1){
                    if (graph[i][j] == -1 || graph[i][j] > graph[i][k] + graph[k][j]){
                        graph[i][j] = graph[i][k] + graph[k][j];
                    }
                }
            }
        }
    }
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            scanf("%d", &graph[i][j]);
        }
    }
    floyd(graph, n);
    return 0;
}