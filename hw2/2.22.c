#include <stdio.h>

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef struct LNode{
    int data;
    struct LNode *next;
}LNode,*LinkList;
LinkList b;

int reverse(LinkList a){
    LinkList temp;
    b->data=a->data;
    b->next=NULL;
    while(a->next!=NULL){
        a=a->next;
        temp->data=a->data;
        temp->next=b->next;
        b->next=temp;
    }
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           