//折半插入排序
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

void BinaryInsertSort(SqList *L){
    int i, j, low, high, mid;
    for(i = 2; i <= L->length; i++){
        if(L->r[i].key < L->r[i-1].key){
            L->r[0] = L->r[i]; //设置哨兵
            low = 1;
            high = i - 1;
            while(low <= high){
                mid = (low + high) / 2;
                if(L->r[mid].key > L->r[0].key){
                    high = mid - 1;
                }else{
                    low = mid + 1;
                }
            }
            for(j = i - 1; j >= high + 1; j--){
                L->r[j+1] = L->r[j]; //记录后移
            }
            L->r[high+1] = L->r[0]; //插入到正确位置
        }
    }
}

int main(){
    printf("BinaryInsertSort\n");
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
        BinaryInsertSort(&L);
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
        BinaryInsertSort(&L);
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
        BinaryInsertSort(&L);
        end = clock();
        time += (end - begin)/CLOCKS_PER_SEC*1000;
    }
    printf("Time3: %fms\n", time/10);
    return 0;
}