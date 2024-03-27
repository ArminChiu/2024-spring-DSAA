#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_SIZE 1000
#define LISTINCREMENT 100

typedef int Elemtype;
//单向链表
typedef struct LNode{
    Elemtype data;
    LinkList *next;
}LinkList;

LinkList * newlist(int n){
    //头结点，前后结点
    LinkList *LHead=(LinkList *)malloc(sizeof(LinkList));
    LinkList *LFront;
    LinkList *LBehind;
    LFront=LHead;
    int data;
    for(int i=1;i<=n-1;i++){
        scanf("%d ",&data);
        //给下一结点分配空间
        LBehind=(LinkList *)malloc(sizeof(LinkList));
        LBehind->data=data;
        LFront->next=LBehind;
        LFront=LBehind;
    }
    scanf("%d",&data);
    //给下一结点分配空间
    LBehind=(LinkList *)malloc(sizeof(LinkList));
    LBehind->data=data;
    LFront->next=LBehind;
    LBehind->next=NULL;
    return LHead;
}

//输出中间结点的值
Elemtype searchmid(LinkList *head){
    LinkList *fast;
    LinkList *low;
    fast=head;
    low=head;
    while(fast->next!=NULL){
        low=low->next;
        fast=fast->next;
        if(fast->next==NULL){
            //奇数结点在此返回
            return low->data;
        }else{
            fast=fast->next;
        }
    }
    //偶数结点在此返回
    return low->data;
}

int main(){
    LinkList *LHead;
    Elemtype mid;
    getchar();
    getchar();
    int n;
    scanf("%d",&n);
    LHead=newlist(n);
    mid=searchmid(LHead);
    printf("val = 6\n真实程序输出是：\n%d\n",mid);
    return 0;
}