//选择排序
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

void SelectSort(SqList *L){
    int i, j, k;
    for(i = 1; i < L->length; i++){
        k = i;
        for(j = i + 1; j <= L->length; j++){
            if(L->r[j].key < L->r[k].key){
                k = j;
            }
        }
        if(k != i){
            L->r[0] = L->r[i];
            L->r[i] = L->r[k];
            L->r[k] = L->r[0];
        }
    }
}

int main(){
    printf("SelectSort\n");
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
        SelectSort(&L);
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
        SelectSort(&L);
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
        SelectSort(&L);
        end = clock();
        time += (end - begin)/CLOCKS_PER_SEC*1000;
    }
    printf("Time3: %fms\n", time/10);
    return 0;
}