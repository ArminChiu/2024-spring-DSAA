//跳表的创建、插入、删除
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//16层可容纳约30,000个数,考虑到随机数rand()的范围(2^15)
#define MAXLEVEL 16
#define LARGESIZE 10000

typedef int ElemType;

typedef struct Node{
    ElemType data;//数据域
    struct Node *next[];//指针数组(柔性数组)
} Node, *PNode;

typedef struct{
    int level;
    int size;
    PNode head;
} SkipList;

//初始化跳表
SkipList *InitSkipList(){
    SkipList *list = (SkipList*)malloc(sizeof(SkipList));
    list->head = (PNode)malloc(sizeof(Node) + MAXLEVEL * sizeof(PNode));
    for(int i = 0; i < MAXLEVEL; i++){
        //各层此时均未存储数据,指针均为NULL
        list->head->next[i] = NULL;
    }
    list->size = 0;
    list->level = 1;
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

//生成新节点
PNode CreateNode(int level, ElemType data){
    //分配内存，包括节点本身和指向下一节点的指针数组
    PNode node = (PNode)malloc(sizeof(Node) + level * sizeof(PNode));
    node->data = data;
    //初始化所有下一节点指针为 NULL
    for(int i = 0; i < level; i++){
        node->next[i] = NULL;
    }
    return node;
}

//插入新节点
void InsertNode(SkipList *list, ElemType data){
    //update数组用于保存每层需要更新的节点
    PNode update[MAXLEVEL];
    PNode p = list->head;
    //从最高层开始遍历，记录每层需要插入新节点(前一个节点)的位置
    for(int i = list->level - 1; i >= 0; i--){
        while(p->next[i] && p->next[i]->data < data){
            //访问本层下一节点
            p = p->next[i];
        }
        //若本层已访问至末尾或下一节点的值大于待插入值,该层插入位置为p
        update[i] = p;
    }
    //生成新节点的层数
    int level = RandomLevel();
    //若大于当前跳表的层数，更新跳表的层数
    if(level > list->level){
        for(int i = list->level; i < level; i++){
            update[i] = list->head;
        }
        list->level = level;
    }
    //创建新节点
    PNode node = CreateNode(level, data);
    //类似链表的插入操作
    for(int i = 0; i < level; i++){
        node->next[i] = update[i]->next[i];
        update[i]->next[i] = node;
    }
    list->size++;
}

//删除节点
void DeleteNode(SkipList *list, ElemType data){
    //update数组用于保存每层需要更新的节点
    PNode update[MAXLEVEL];
    PNode p = list->head;
    //从最高层开始遍历，记录每层需要删除节点(前一个节点)的位置
    for(int i = list->level - 1; i >= 0; i--){
        while(p->next[i] && p->next[i]->data < data){
            p = p->next[i];
        }
        update[i] = p;
    }
    //确定需删除节点存在，进行删除
    if(p->next[0] && p->next[0]->data == data){
        PNode node = p->next[0];
        //在每层中删除该节点
        for(int i = 0; i < list->level; i++){
            if(update[i]->next[i] == node){
                update[i]->next[i] = node->next[i];
            }
        }
        //释放内存
        free(node);
    }
    list->size--;
}

//打印跳表
void PrintSkipList(SkipList *list){
    PNode p = list->head;
    while(p->next[0]){
        printf("%5d ", p->next[0]->data);
        p = p->next[0];
    }
    printf("\n");
}

//打印每一层的节点，并且相同数据对齐，实现跳表可视化
void PrintSkipList2(SkipList *list){
    for(int i = list->level - 1; i >= 0; i--){
        PNode p = list->head->next[i];
        while(p){
            printf("%d ", p->data);
            p = p->next[i];
        }
        printf("\n");
    }
}

int main(){
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
        DeleteNode(list, numbers[i] * 2 - 1);
    }
    end = clock();
    time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("删除节点用时：%f 秒\n", time);
    printf("跳表层数：%d\n", list->level);
    printf("跳表节点数：%d\n", list->size);

/*  小范围测试(40个数) 用于打印
    for(int i = 0; i < 41; i++){
        InsertNode(list, (i*7)%53);
    }
    PrintSkipList2(list);
    printf("\n");
*/    
    return 0;
}