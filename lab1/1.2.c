//ok
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <time.h>


typedef struct LinkedList {
    int val;
    struct LinkedList *next;
} LinkedList;

void solve(LinkedList *header, int mx) {
    LinkedList *LNode;
    LinkedList *LBehind;
    LNode=header->next;
    LBehind=header;
    while(LNode!=NULL){
        if(LNode->val>mx){
            if(LNode->next==NULL){
                LNode->val=666;//啊？神之一手！实现最终debug的居然是这条（说明代码运行逻辑有漏洞）
                LBehind->next=NULL;
                return;
            }else{
                LNode->val=(LNode->next)->val;
                LNode->next=(LNode->next)->next;
            }
        }else{
            LBehind=LNode;
            LNode=LNode->next;
        }
    }
}

int main() {
    int n, mx;   //n为链表节点数，mx待删除链表阈值
    scanf("%d%d", &n, &mx);
    LinkedList *header = NULL;
    LinkedList *tail = NULL;
    for (int i = 1; i <= n+1; i++) {
        int val; scanf("%d", &val);
        if (!header) {
            header = (LinkedList *)malloc(sizeof(LinkedList));
            tail = header;
            tail->next = NULL;
            tail->val = val;
        } else {
            LinkedList *node =  (LinkedList *)malloc(sizeof(LinkedList));
            node->val = val;
            node->next = NULL;
            tail->next = node;
            tail = node;
        }    
    }

    solve(header, mx);

    for (LinkedList *it = header; it != NULL; it = it->next) {
        printf("%d ", it->val);
    }
    puts("");
    return 0;
}