//快速排序
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX 20000

float begin, end;

typedef int  KeyType;

typedef struct {
    KeyType key;
} RedType;

typedef struct {
    RedType r[MAX+1]; //r[0]闲置或用作哨兵单元
    int length;
} SqList;

int Partition(SqList *L, int low, int high){
    L->r[0] = L->r[low]; //设置哨兵
    int pivotkey = L->r[low].key;
    while(low < high){
        while(low < high && L->r[high].key >= pivotkey){
            high--;
        }
        L->r[low] = L->r[high]; //交换比枢轴小的记录到左端
        while(low < high && L->r[low].key <= pivotkey){
            low++;
        }
        L->r[high] = L->r[low]; //交换比枢轴大的记录到右端
    }
    L->r[low] = L->r[0]; //枢轴记录到位
    return low; //返回枢轴位置
}
void QSort(SqList *L, int low, int high){
    if(low < high){
        int pivotloc = Partition(L, low, high);
        QSort(L, low, pivotloc - 1); //对左区间递归排序
        QSort(L, pivotloc + 1, high); //对右区间递归排序
    }
}

void QuickSort(SqList *L){
    QSort(L, 1, L->length);
}

int main(){
    printf("QuickSort\n");
    SqList L;
    int i;
    float time = 0.0;
    L.length = 20000;
    //正序
    for(int j = 0; j < 10; j++){
        for(i = 1; i <= L.length; i++){
            L.r[i].key = i;
        }
        begin = clock();
        QuickSort(&L);
        end = clock();
        time += (end - begin)/CLOCKS_PER_SEC*1000;
    }
    printf("Time1: %fms\n", time/10);
    time = 0.0;
    //逆序
    for(int j = 0; j < 10; j++){
        for(i = 1; i <= L.length; i++){
            L.r[i].key = L.length + 1 - i;
        }
        begin = clock();
        QuickSort(&L);
        end = clock();
        time += (end - begin)/CLOCKS_PER_SEC*1000;
    }
    printf("Time2: %fms\n", time/10);
    time = 0.0;
    //随机
    for(int j = 0; j < 10; j++){
        for(i = 1; i <= L.length; i++){
            L.r[i].key = rand() % L.length;
        }
        begin = clock();
        QuickSort(&L);
        end = clock();
        time += (end - begin)/CLOCKS_PER_SEC*1000;
    }
    printf("Time3: %fms\n", time/10);
    return 0;
}