//一个图需要再加几条边才能使其变成连通图
#include <stdio.h>
#include <stdlib.h>

#define MAX 1000
int graph[MAX][MAX]; //邻接矩阵
int visited[MAX]; //访问标记数组


int CreateGraph(int n){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            scanf("%d", &graph[i][j]);
        }
    }
}

void DFS(int v, int n, int *p){
    visited[v] = 1;
    for(int i = 0; i < n; i++){
        if(graph[v][i] == 1 && visited[i] == 0){
            (*p)--;
            DFS(i, n, p);
        }
    }
}

int main(){
    int n; //顶点数
    int sum;
    int *p = &sum;
    scanf("%d", &n);
    sum = n; //连通块数量
    CreateGraph(n);
    for(int i = 0; i < n; i++){
        visited[i] = 0;
    }
    for(int i = 0; i < n; i++){
        if(visited[i] == 0){
            DFS(i, n, p);
        }
    }
    printf("%d\n", sum - 1);
}