//冒泡排序
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

void BubbleSort(SqList *L){
    int i, j;
    //进行n-1轮冒泡
    for(i = 1; i < L->length; i++){
        //一轮冒泡
        for(j = L->length; j > i; j--){
            if(L->r[j].key < L->r[j-1].key){
                L->r[0] = L->r[j]; //设置哨兵
                L->r[j] = L->r[j-1];
                L->r[j-1] = L->r[0];
            }
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
    BubbleSort(&L);
    for(i = 1; i <= L.length; i++){
        printf("%d ", L.r[i].key);
    }
    printf("\n");
    return 0;
}