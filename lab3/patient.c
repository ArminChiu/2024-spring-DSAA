//就诊排队系统
#include <stdio.h>
#include <stdlib.h>

#define MAXLENGTH 1000

int jiuhao=0;

//构造一个队列
typedef struct Queue{
    int *data;
    int head, tail, length;
}Queue;

//初始化队列
void InitQueue(Queue *q, int length){
    q->data = (int *)malloc(sizeof(int) * length);
    q->head = 0;
    q->tail = 0;
    q->length = length;
}

//排队挂号
void function1(Queue *q){
    printf("请输入病历号：");
    scanf("%d", &q->data[q->tail]);
    if((q->tail+1)%q->length == q->head){
        printf("排队失败，就诊人数已满。\n\n");
        return;
    }
    q->tail=(q->tail+1)%q->length;
    jiuhao ++;
    printf("排队成功。\n");
    printf("当前有%d人排队。\n\n", (q->tail-q->head)%q->length);
}

//出队就诊
void function2(Queue *q){
    if(q->head == q->tail){
        printf("当前没有人排队。\n");
        return;
    }
    printf("但前出队就诊的病历号为%d。\n出队成功。\n\n", q->data[q->head]);
    q->head=(q->head+1)%q->length;
}

//查看排队
void function3(Queue *q){
    if(q->head == q->tail){
        printf("当前没有人排队。\n\n");
        return;
    }
    printf("当前排队的病历号为：");
    for(int i=q->head; i!=q->tail; i=(i+1)%q->length){
        printf("%d ", q->data[i]);
    }
    printf("\n\n");
}

//菜单界面
void function(Queue *q){
    int choice=0;
    while(choice!=4 && jiuhao <= 1000){
        printf("==========菜单==========\n");
        printf("        1.排队\n");
        printf("        2.就诊\n");
        printf("        3.查看排队\n");
        printf("        4.下班(退出程序)\n");
        printf("选择菜单，请输入菜单编号：");
        scanf("%d", &choice);
        if(choice == 1){
            function1(q);
        }else if(choice == 2){
            function2(q);
        }else if(choice == 3){
            function3(q);
        }else if(choice != 4){
            printf("请输入正确的菜单编号！\n");
        }
    }
}

int main(){
    Queue *q = (Queue*)malloc(sizeof(Queue));
    InitQueue(q, MAXLENGTH);
    function(q);
    free(q);
    return 0;
}