//回文序列判断
#include <stdio.h>
#include <stdlib.h>
//定义栈
#define MAX_STACK_SIZE 100

typedef int ElemType;
typedef struct{
    ElemType *base;
    int top;
}SqStack;

//初始化
void init(SqStack *s){
    s->base=(ElemType *)malloc(MAX_STACK_SIZE*sizeof(ElemType));
    s->top=0;
}
//入栈
void push(SqStack *s,ElemType e){
    (s->base)[s->top]=e;
    s->top++;
}
//出栈
void pop(SqStack *s,ElemType *c){
    s->top--;
    *c=(s->base)[s->top];
}
//空栈
int isEmpty(SqStack *s){
    if(s->top==0){
        return 1;
    }else{
        return 0;
    }
}
//获取字符串
void getmyline(char a[]){
    int length=0;
    while(1){
        a[length]=getchar();
        if(a[length]=='\n')
            break;
        length++;
    }
    a[length]='\0';
}

int main(){
    void init(SqStack *s);
    void push(SqStack *s,ElemType e);
    void pop(SqStack *s,ElemType *c);
    int isEmpty(SqStack *s);
    void getmyline(char *a);
    char a[MAX_STACK_SIZE];
    SqStack *s=(SqStack *)malloc(sizeof(SqStack));
    ElemType e;
    ElemType *c=(ElemType *)malloc(sizeof(ElemType));
    init(s);
    getmyline(a);
    int i;
    //读到&前先进行进栈操作
    for(i=0;a[i]!='&';i++){
        //在&前就读到@,不合要求
        if(a[i]=='@'){
            printf("no");
            return 0;
        }
        push(s,a[i]);
    }
    //回文:当栈未空时将剩余输入与退栈结果比较.
    for(i=i+1;isEmpty(s)==0;i++){
        pop(s,c);
        //不满足回文
        if(a[i]!=*c){
            printf("no");
            return 0;
        }
    }
    //栈空时的下一个元素应为@
    if(a[i]=='@'){
        printf("yes");
        return 0;
    }else{
        printf("no");
        return 0;
    }
    return 0;
}
