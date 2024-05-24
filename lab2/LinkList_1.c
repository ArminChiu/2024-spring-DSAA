//无序单链表的创建、插入、删除
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

//创建链表
LinkList CreateList(int n){
    LinkList L = (LinkList)malloc(sizeof(Node));
    L->next = NULL;
    Node *p = L;
    //在链表尾部插入节点
    for(int i = 0; i < n; i++){
        Node *temp = (Node*)malloc(sizeof(Node));
        /*这里不妨使用int型data进行测试,将i写入data.
        scanf("%d", &temp->data);*/
        temp->data = 2*i+1;
        temp->next = NULL;
        p->next = temp;
        p = temp;
    }
    size = n;
    return L;
}

//插入节点
//这里的i指:节点将被插入头结点后的第i个位置(所以i从1开始)
LinkList InsertList(LinkList L, int i, ElemType e){
    Node *p = L;
    int j = 0;
    while(p && j < i - 1){
        p = p->next;
        j++;
    }
    if(!p || j > i - 1){
        return NULL;
    }
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->data = e;
    temp->next = p->next;
    p->next = temp;
    size++;
    return L;
}

//删除节点
LinkList DeleteList(LinkList L, ElemType e){
    Node *p = L;
    ElemType j = 0;
    while(p && j < e - 1){
        p = p->next;
        j++;
    }
    if(!p || j > e - 1){
        return NULL;
    }
    Node *q = p->next;
    p->next = q->next;
    free(q);
    size--;
    return L;
}

int main(){
    srand(time(NULL));
    //记录各操作用时
    clock_t start, end;
    double time;

    //创建了一个有10000个节点的链表
    start = clock();
    LinkList L = CreateList(LARGESIZE);
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
        InsertList(L, numbers[i] + i, numbers[i] * 2);
    }
    end = clock();
    time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("插入节点用时：%f 秒\n", time);
    printf("链表节点数：%d\n", size);

    //在当前链表中随机位置删除10000个节点
    start = clock();
    for(int i = 0; i < LARGESIZE; i++){
        DeleteList(L, numbers[i]);
    }
    end = clock();
    time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("删除节点用时：%f 秒\n", time);
    printf("链表节点数：%d\n", size);

    //释放链表空间
    Node *p = L;
    Node *q = p;
    while(p){
        q = p;
        p = p->next;
        free(q);
    }
    return 0;
}