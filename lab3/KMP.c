//KMP算法
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING_SIZE 1000

int sum=0;
int compare[1000];

typedef struct{
    char *ch;
    int length;
    int strsize;
}HString;

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

//求next[j]
void GetNext(HString *t,int next[]){
    int j,k;
    j=0;
    k=-1;
    next[0]=-1;
    while(j<t->length){
        if(k==-1||t->ch[j]==t->ch[k]){
            j++;k++;
            if(t->ch[j]==t->ch[k]){
                next[j]=next[k];
            }else{
                next[j]=k;
            }
        }else k=next[k];
    }
}

//模式串匹配
void StrDex(HString *s,HString *t,int i){
    int next[MAX_STRING_SIZE];
    GetNext(t,next);
    int j=0;
    while(i<s->length&&j<t->length){
        if(j==-1||s->ch[i]==t->ch[j]){
            i++;
            j++;
        }else{
            j=next[j];
        }
    }
    if(i==s->length&&j<t->length){
        printf("在母串中找到%d处与模式串匹配\n",sum);
        for(int k=0;k<sum;k++){
            printf("第%d处匹配位置为%d\n",k+1,compare[k]);
        }
        return;
    }
    if(j==t->length){
        compare[sum]=i-j+1;
        sum++;
    }
    StrDex(s,t,i);
}

int main(){
    HString *s=(HString *)malloc(sizeof(HString));
    HString *t=(HString *)malloc(sizeof(HString));
    init(s);
    init(t);
    printf("请输入母串s\n");
    getmyline(s);
    printf("请输入子串t\n");
    getmyline(t);
    int i=0;
    StrDex(s,t,i);
    return 0;
}