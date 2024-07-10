#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUM_OF_KEY 5
#define RADIX 10
#define MAX 30000

float begin, end;

typedef struct SLCell{
    int keys[MAX_NUM_OF_KEY];
    int data;
    int next;
} SLCell;

typedef struct SLList{
    SLCell r[MAX];
    int keynum;
    int recnum;
} SLList;

void Distribute(SLList *L, int i, int *f, int *e){
    for (int j = 0; j < RADIX; ++j)
        f[j] = e[j] = 0;
    for (int p = L->r[0].next; p != 0; p = L->r[p].next){
        int j = L->r[p].keys[i];
        if (f[j] == 0)
            f[j] = p;
        else
            L->r[e[j]].next = p;
        e[j] = p;
    }
}

void Collect(SLList *L, int *f, int *e){
    int j = 0;
    while (j < RADIX && f[j] == 0)
        ++j;
    L->r[0].next = f[j];
    int t = e[j];
    while (j < RADIX){
        for (j = j + 1; j < RADIX && f[j] == 0; ++j);
        if (j < RADIX && f[j] != 0){
            L->r[t].next = f[j];
            t = e[j];
        }
    }
    L->r[t].next = 0;
}

void RadixSort(SLList *L){
    int f[RADIX], e[RADIX];
    L->r[0].next = 1;
    for (int i = 1; i < L->recnum; ++i){
        L->r[i].next = i + 1;
    }
    L->r[L->recnum].next = 0;

    for (int i = L->keynum - 1; i >= 0; --i){
        Distribute(L, i, f, e);
        Collect(L, f, e);
    }
}

void PrintList(SLList *L){
    for (int i = L->r[0].next; i != 0; i = L->r[i].next){
        for (int j = 0; j < L->keynum; ++j)
            printf("%d ", L->r[i].keys[j]);
        printf("\n");
    }
}

int main(){
    printf("RadixSort\n");
    SLList L;
    float time = 0.0;
    L.keynum = MAX_NUM_OF_KEY;
    L.recnum = 20000;
    int key;
    //正序
    for(int j = 0; j < 10; j++){
        for (int i = 1; i <= L.recnum; ++i){   
                L.r->data = i;
                key = L.r->data;
                for (int j = 0; j < L.keynum; ++j){
                    L.r[i].keys[L.keynum - j - 1] = key % RADIX;
                    key = key / RADIX;
                }
        }
        begin = clock();
        RadixSort(&L);
        end = clock();
        time += (end - begin)/CLOCKS_PER_SEC*1000;
    }
    printf("Time1: %fms\n", time/10);
    time = 0.0;
    //逆序
    for(int j = 0; j < 10; j++){
        for (int i = 1; i <= L.recnum; ++i){
                L.r->data = L.recnum - i;
                key = L.r->data;
                for (int j = 0; j < L.keynum; ++j){
                    L.r[i].keys[L.keynum - j - 1] = key % RADIX;
                    key = key / RADIX;
                }
        }
        begin = clock();
        RadixSort(&L);
        end = clock();
        time += (end - begin)/CLOCKS_PER_SEC*1000;
    }
    printf("Time2: %fms\n", time/10);
    time = 0.0;
    //随机
    for(int j = 0; j < 10; j++){
        for (int i = 1; i <= L.recnum; ++i){
                L.r->data = rand();
                key = L.r->data;
                for (int j = 0; j < L.keynum; ++j){
                    L.r[i].keys[L.keynum - j - 1] = key % RADIX;
                    key = key / RADIX;
                }
        }
        begin = clock();
        RadixSort(&L);
        end = clock();
        time += (end - begin)/CLOCKS_PER_SEC*1000;
    }
    printf("Time3: %fms\n", time/10);
    return 0;
}