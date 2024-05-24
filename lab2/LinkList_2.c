//有序单链表的创建、插入、删除
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LARGESIZE 10000

typedef int ElemType;

typedef struct Node{
    ElemType data;
    struct Node *next;
}Node;

typedef Node *LinkList;

int size = 0;

// 创建空链表
LinkList CreateList(){
    LinkList L = (LinkList)malloc(sizeof(Node));
    L->next = NULL;
    size = 0;
    return L;
}

// 插入节点，保持链表有序
LinkList InsertList(LinkList L, ElemType e){
    Node *p = L;
    Node *prev = NULL;
    while(p && p->data < e){
        prev = p;
        p = p->next;
    }
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->data = e;
    temp->next = p;
    if(prev == NULL){
        L = temp;
    } else {
        prev->next = temp;
    }
    size++;
    return L;
}

// 删除节点，保持链表有序
LinkList DeleteList(LinkList L, ElemType e){
    Node *p = L;
    Node *prev = NULL;
    while(p && p->data < e){
        prev = p;
        p = p->next;
    }
    if(p && p->data == e){
        if(prev == NULL){
            L = p->next;
        } else {
            prev->next = p->next;
        }
        free(p);
        size--;
    }
    return L;
}

int main(){
    srand(time(NULL));
    //记录各操作用时
    clock_t start, end;
    double time;
    //创建了一个有10000个节点的链表
    start = clock();
    LinkList L = CreateList();
    for(int i = LARGESIZE; i > 0; i--){
        InsertList(L, i * 2 - 1);
    }
    end = clock();
    time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("创建链表用时：%f 秒\n", time);
    printf("链表节点数：%d\n", size);
    //在当前链表中随机位置插入10000个节点
    //生成一个包含1到10000的所有数字的数组
    int numbers[LARGESIZE];
    for(int i = 0; i < LARGESIZE; i++){
        numbers[i] = i + 1;
    }
    //打乱数组
    for(int i = LARGESIZE - 1; i > 0; i--){
        int j = rand() % (i + 1);
        int temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }
    start = clock();
    for(int i = 0; i < LARGESIZE; i++){
        InsertList(L, numbers[i] * 2);
    }
    end = clock();
    time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("插入节点用时：%f 秒\n", time);
    printf("链表节点数：%d\n", size);

    //在当前链表中随机位置删除10000个节点
    start = clock();
    for(int i = 0; i < LARGESIZE; i++){
        DeleteList(L, numbers[i] * 2 - 1);
    }
    end = clock();
    time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("删除节点用时：%f 秒\n", time);
    printf("链表节点数：%d\n", size);

    //释放链表
    Node *p = L;
    Node *q = p;
    while(p){
        q = p;
        p = p->next;
        free(q);
    }
    return 0;
}