#include <stdio.h>
#include <stdlib.h>
//定义循环链表
typedef int ElemType;
typedef struct queue{
    ElemType *base;
    int front;
    int rear;
}CircularQueue;
//给队列分配空间,并初始化为斐波那契前k项:0,0,...,0,1
void init(CircularQueue *cq,int k){
    cq->base=(ElemType *)malloc(k*sizeof(ElemType));
    for(int i=0;i<k-1;i++)
        (cq->base)[i]=0;
    (cq->base)[k-1]=1;
    cq->front=0;
    cq->rear=0;
}
//计算当前队列元素之和,删除队头后,将和插入队尾并打印
void calc(CircularQueue *cq,int k){
    int result=0;
    for(int i=0;i<k;i++){
        result+=(cq->base)[i];
    }
    cq->front=((cq->front)+1)%k;
    cq->base[cq->rear]=result;
    cq->rear=((cq->rear)+1)%k;
    printf("%d\n",result);
}
//输入k和n,给出k阶斐波那契数列前n+1项的值
int main(){
    void init(CircularQueue *cq,int k);
    void calc(CircularQueue *cq,int k);
    CircularQueue *cq;
    int k,n;
    scanf("%d %d",&k,&n);
    init(cq,k);
    for(int i=0;i<k;i++)
        printf("第%d项 %d\n",i,cq->base[i]);
    for(int i=k;i<=n;i++){
        printf("第%d项 ",i);
        calc(cq,k);
    }
    return 0;
}
