//全为1的面积最大的子矩阵
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX(a,b) ((a) > (b) ? (a) : (b))

int largestRectangleArea(int* heights, int heightsSize) {
    //返回柱状图的最大面积
    int *stack = (int *)malloc((heightsSize + 1) * sizeof(int));
    int top = -1, maxArea = 0;
    for (int i = 0; i < heightsSize; i++) {
        while (top != -1 && heights[stack[top]] >= heights[i]) {
            int height = heights[stack[top--]];
            int width = top == -1 ? i : i - stack[top] - 1;
            maxArea = MAX(maxArea, height * width);
        }
        stack[++top] = i;
    }
    while (top != -1) {
        int height = heights[stack[top--]];
        int width = top == -1 ? heightsSize : heightsSize - stack[top] - 1;
        maxArea = MAX(maxArea, height * width);
    }
    free(stack);
    return maxArea;
}

int maximalRectangle(char** matrix, int matrixSize, int* matrixColSize) {
    // 省略函数内部实现
    if (matrixSize == 0) return 0;
    int n = matrixColSize[0];
    int *heights = (int *)malloc(n * sizeof(int));
    memset(heights, 0, n * sizeof(int));
    int maxRectangle = 0;

    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == '1') {
                heights[j]++;
            } else {
                heights[j] = 0;
            }
        }
        maxRectangle = MAX(maxRectangle, largestRectangleArea(heights, n));
    }
    free(heights);
    return maxRectangle;
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n); 
    char **matrix = (char **)malloc(m * sizeof(char *));
    int *matrixColSize = (int *)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        matrix[i] = (char *)malloc((n + 1) * sizeof(char));  
        scanf("%s", matrix[i]);
        matrixColSize[i] = n;
    } 
    int maxRectangle = maximalRectangle(matrix, m, matrixColSize);
    printf("%d", maxRectangle); 
    return 0;
}