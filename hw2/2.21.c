//顺序表的就地逆置
#include <stdio.h>

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef struct{
    int *elem;
    int length;
    int listsize;
}SqList;

int reverse(SqList *a){
    int left=0;
    int right=a->listsize-1;
    int temp;
    for(int i=0;i<(a->listsize)/2;i++){
        temp=a->elem[left+i];
        a->elem[left+i]=a->elem[right-i];
    }
}
