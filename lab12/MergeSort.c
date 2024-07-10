//2-路归并排序
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
    RedType r[MAX];
    int length;
} SqList;

void Merge(RedType SR[], RedType TR[], int l, int m, int n){
    //将有序的SR[l...m]和SR[m+1...n]归并为有序的TR[l...n]
    int i, j, k;
    for(i = l, j = m + 1, k = l; i <= m && j <= n; k++){
        if(SR[i].key <= SR[j].key){
            TR[k] = SR[i++];
        }else{
            TR[k] = SR[j++];
        }
    }
    while(i <= m){
        TR[k++] = SR[i++];
    }
    while(j <= n){
        TR[k++] = SR[j++];
    }
}

void MSort(RedType SR[], RedType TR1[], int s, int t){
    //将SR[s...t]归并排序为TR1[s...t]
    int m;
    RedType TR2[MAX];
    if(s == t){
        TR1[s] = SR[s];
    }else{
        m = (s + t) / 2;
        MSort(SR, TR2, s, m);
        MSort(SR, TR2, m + 1, t);
        Merge(TR2, TR1, s, m, t);
    }
}

void MergeSort(SqList *L){
    //对顺序表L作归并排序
    MSort(L->r, L->r, 0, L->length - 1);
}

void print(SqList *L){
    for(int i = 0; i < L->length; i ++){
        printf("%d\n", L->r[i].key);
    }
}

int main(){
    printf("MergeSort\n");
    SqList L;
    int i;
    float time = 0.0;
    L.length = 20000;
    //正序
    for(int j = 0; j < 10; j++){
        for(i = 0; i < L.length; i++){
            L.r[i].key = i;
        }
        begin = clock();
        MergeSort(&L);
        end = clock();
        time += (end - begin)/CLOCKS_PER_SEC*1000;
    }
    printf("Time1: %fms\n", time/10);
    time = 0.0;
    //逆序
    for(int j = 0; j < 10; j++){
        for(i = 0; i < L.length; i++){
            L.r[i].key = L.length - 1 - i;
        }
        begin = clock();
        MergeSort(&L);
        end = clock();
        time += (end - begin)/CLOCKS_PER_SEC*1000;
    }
    printf("Time2: %fms\n", time/10);
    time = 0.0;
    //随机
    for(int j = 0; j < 10; j++){
        for(i = 0; i < L.length; i++){
            L.r[i].key = rand() % L.length;
        }
        begin = clock();
        MergeSort(&L);
        end = clock();
        time += (end - begin)/CLOCKS_PER_SEC*1000;
    }
    printf("Time3: %fms\n", time/10);
    return 0;
}