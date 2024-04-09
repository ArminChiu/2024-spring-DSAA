//判断单链表是否成环
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *next;
}Node;

typedef struct{
    Node *head;
    int size;
}List;

List* createList(){
    List *list = (List*)malloc(sizeof(List));
    list->head = (Node*)malloc(sizeof(Node));
    list->head->next = NULL;
    list->size = 0;
    return list;
}

void insert(List *list, int data){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = list->head->next;
    list->head->next = newNode;
    list->size++;
}

void createCycle(List *list){//将首尾连成环
    Node *p = list->head;
    while(p->next != NULL){
        p = p->next;
    }
    p->next = list->head;
}

int isCycle(List *list){
    Node *slow = list->head;
    Node *fast = list->head;
    //走到NULL说明一定不成环
    while(fast != NULL && fast->next != NULL){
        slow = slow->next;
        fast = fast->next;
        fast = fast->next;
        //在成环的情况下，有限步内一定会相遇
        if(slow == fast){
            return 1;
        }
    }
    //不成环
    return 0;
}

int main(){
    List *list = createList();
    insert(list, 1);
    insert(list, 2);
    insert(list, 3);
    insert(list, 4);
    insert(list, 5);
    printf("%d\n", isCycle(list));
    createCycle(list);
    printf("%d\n", isCycle(list));
    return 0;
}