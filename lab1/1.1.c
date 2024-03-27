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


int solve(LinkedList *header) {
    LinkedList *fast;
    LinkedList *low;
    fast=header;
    low=header;
    while(fast->next!=NULL){
        fast=fast->next;
        if(fast->next==NULL){
            //奇数结点在此返回
            return low->val;
        }else{
            low=low->next;
            fast=fast->next;
        }
    }
    //偶数结点在此返回
    return low->val;
}




int main() {
    int n;
    scanf("%d", &n);
    LinkedList *header = NULL;
    LinkedList *tail = NULL;
    for (int i = 1; i <= n; i++) {
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

    int ans = solve(header);
    printf("%d\n", ans);
    return 0;
}