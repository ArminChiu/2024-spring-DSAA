//求字符串各字符出现次数
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING_SIZE 1000

typedef struct{
    char *ch;
    int length;
    int strsize;
}HString;

typedef struct{
    char *ch;
    int *sum;
    int length;
}data;

//初始化字符串
void init(HString *s){
    s->ch=(char *)malloc(MAX_STRING_SIZE*sizeof(char));
    s->ch[0]='\0';
    s->length=0;
    s->strsize=MAX_STRING_SIZE;
}

//获取字符串
void getmyline(HString *s){
    while(1){
        s->ch[s->length]=getchar();
        if(s->ch[s->length]=='\n')
            break;
        s->length++;
    }
    s->ch[s->length]='\0';
}

//初始化数据
void initdata(data *t){
    t->ch=(char *)malloc(128*sizeof(char));
    t->ch[0]='\0';
    t->sum=(int *)malloc(128*sizeof(int));
    t->sum[0]=0;
    t->length=0;
}

//存储统计数据
void statis(HString *s,data *t){
    int i=0;
    int j=0;
    //未读到终止符
    while(s->ch[i]!='\0'){
        //在已存字符序列中查找被读取字符
        while(j<t->length){
            //找到,+1并跳出
            if(t->ch[j]==s->ch[i]){
                t->sum[j]++;
                j=0;
                break;
            }
            j++;
        }
        //未找到
        if(j==t->length){
            t->ch[j]=s->ch[i];
            t->sum[j]=1;         
            t->ch[j+1]='\0';
            t->sum[j+1]=0;
            t->length++;
            j=0;
        }
        i++;
    }
}

int main(){
    void init(HString *s);
    void getmyline(HString *s);
    void initdata(data *t);
    void statis(HString *s,data *t);

    HString *s=(HString *)malloc(sizeof(HString));
    data *t=(data *)malloc(sizeof(data));
    init(s);
    initdata(t);
    printf("请输入字符串\n");
    getmyline(s);
    statis(s,t);
    printf("该字符串含%d个不同字符(不含终止符)\n",t->length);
    for(int i=0;i<t->length;i++){
        printf("第%2d个字符%c    %d个\n",i+1,t->ch[i],t->sum[i]);
    }
    return 0;
}
