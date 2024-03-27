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


void solve(LinkedList *header, int remove) {
    LinkedList *fast=header;
    LinkedList *low=header;
    LinkedList *evenlow=low;
    //fast指针先走remove步
    for(int i=1;i<=remove;i++)
        fast=fast->next;
    while(fast!=NULL){
        fast=fast->next;
        evenlow=low;
        low=low->next;
    }
    //退出循环说明low已走至倒数第remove个节点
    low->val=low->next->val;
    evenlow->val=low->next->val;
    low->next=low->next->next;
}


int main() {
    int n, mx;
    scanf("%d%d", &n, &mx);  //n为链表节点数，mx即为待删除第mx个节点
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