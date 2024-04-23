//指针数组跳表的创建、插入、删除
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//16层可容纳约30,000个数,考虑到随机数rand()的范围(2^15)
#define MAXLEVEL 16
#define LARGESIZE 10000

typedef int ElemType;

typedef struct Node {
    ElemType data;
    struct Node *next;
    struct Node *down;
} Node;

typedef struct SkipList {
    Node *head;
    int size;
    int level;
} SkipList;

//创建节点
Node* CreateNode(ElemType data) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    node->down = NULL;
    return node;
}

//初始化跳表
SkipList* InitSkipList() {
    SkipList *list = (SkipList*)malloc(sizeof(SkipList));
    list->head = CreateNode(-1);  // 创建一个头节点，数据设为最小值
    list->size = 0;
    list->level = 1;  // 初始时只有一层
    return list;
}

//随机层数生成函数
int RandomLevel(){
    int level = 1;
    while(rand() % 2)
        level++;
    if(level > MAXLEVEL)
        level = MAXLEVEL;
    return level;
}

//插入新节点
Node* InsertNode(SkipList *list, int data) {
    int newLevel = RandomLevel();
    if (newLevel > MAXLEVEL) {
        printf("Error: The new level %d exceeds the maximum level %d.\n", newLevel, MAXLEVEL);
        return NULL;
    }
    Node *newNode = CreateNode(data);
    if (newNode == NULL) {
        printf("Error: Failed to create a new node.\n");
        return NULL;
    }
    Node *cur = list->head;
    Node *prev = NULL;
    int level = list->level;
    while (level >= 1) {
        while (cur->next != NULL && cur->next->data < data) {
            cur = cur->next;
        }
        if (level <= newLevel) {
            newNode->next = cur->next;
            cur->next = newNode;
            if (prev != NULL) {
                prev->down = newNode;
            }
            prev = newNode;
        }
        cur = cur->down;
        level--;
    }
    list->size++;
    if (newLevel > list->level) {
        list->level = newLevel;
    }
    return list->head;
}

// 删除节点
Node* DeleteNode(SkipList *list, ElemType data) {
    Node *cur = list->head;
    Node *prev = NULL;
    Node *newNode = NULL;
    int level = list->level;
    while (level >= 1) {
        while (cur->next != NULL && cur->next->data < data) {
            cur = cur->next;
        }
        if (cur->next != NULL && cur->next->data == data) {
            Node *temp = cur->next;
            cur->next = cur->next->next;
            if (newNode != NULL) {
                newNode->down = cur->next;
            }
            free(temp);
            list->size--;
            if (prev != NULL) {
                prev->down = cur;
            }
        }
        prev = cur;
        newNode = cur->next;
        cur = cur->down;
        level--;
    }
    // 如果删除节点后，节点数量小于当前层数的一半，减少一层
    if (list->size < (1 << (list->level - 1))) {
        list->level--;
    }
    return list->head;
}

int main() {
    srand(time(NULL));
    //记录各操作用时
    clock_t start, end;
    double time;
    start = clock();
    SkipList *list = InitSkipList();
/*  大范围测试(10,000个数) */
    //先逆序插入从1~20000的所有奇数,实现10000个节点跳表的初始化
    for(int i = LARGESIZE-1; i >= 0; i--){
        InsertNode(list, 2*i+1);
    }
    end = clock();
    time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("创建跳表用时：%f 秒\n", time);
    printf("跳表层数：%d\n", list->level);
    printf("跳表节点数：%d\n", list->size);
    //随机插入10000个1~20000的偶数
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
    //插入跳表
    start = clock();
    for(int i = 0; i < LARGESIZE; i++){
        InsertNode(list, numbers[i]*2);
    }
    end = clock();
    time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("插入节点用时：%f 秒\n", time);
    printf("跳表层数：%d\n", list->level);
    printf("跳表节点数：%d\n", list->size);
    //打乱数组
    for(int i = LARGESIZE - 1; i > 0; i--){
        int j = rand() % (i + 1);
        int temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }
    //移出跳表
    start = clock();
    for(int i = 0; i < LARGESIZE; i++){
        DeleteNode(list, numbers[i]*2);
    }
    end = clock();
    time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("删除节点用时：%f 秒\n", time);
    printf("跳表层数：%d\n", list->level);
    printf("跳表节点数：%d\n", list->size);

/*  小范围测试(40个数)用于打印
    for(int i = 0; i < 41; i++){
        InsertNode(list, (i*7)%53);
    }
*/
    return 0;
}