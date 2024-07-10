//直接插入排序
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

void InsertSort(SqList *L){
    int i, j;
    for(i = 2; i <= L->length; i++){
        if(L->r[i].key < L->r[i-1].key){
            L->r[0] = L->r[i]; //设置哨兵
            for(j = i - 1; L->r[j].key > L->r[0].key; j--){
                L->r[j+1] = L->r[j]; //记录后移
            }
            L->r[j+1] = L->r[0]; //插入到正确位置
        }
    }
}

int main(){
    SqList L;
    int i;
    scanf("%d", &L.length);
    for(i = 1; i <= L.length; i++){
        scanf("%d", &L.r[i].key);
    }
    InsertSort(&L);
    for(i = 1; i <= L.length; i++){
        printf("%d ", L.r[i].key);
    }
    printf("\n");
    return 0;
}