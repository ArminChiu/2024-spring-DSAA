//最大值栈
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    int max;
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
    list->head->data = -1;
    list->head->max = -1;
    list->size = 0;
    return list;
}

void insert(List *list, int data){
    Node *newNode = (Node*)malloc(sizeof(Node));
    list->size++;
    newNode->data = data;
    newNode->next = list->head->next;
    list->head->next = newNode;
    if(newNode->next == NULL || newNode->data > newNode->next->max){
        newNode->max = data;
    }else{
        newNode->max = newNode->next->max;
    }
}

int max(List *list){
    if(list->size == 0){
        return -1;
    }else{
        return list->head->next->max;
    }   
}

int main(){
    List *list = createList();
    int n;
    int data;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", &data);
        insert(list, data);
    }
    printf("%d\n", max(list));
    return 0;
}