#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING_SIZE 1000

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
            next[j]=k;
        }else k=next[k];
    }
}

//删去一段字符
void delete(HString *s,int delen,int pos){
    int i=pos-1+delen;
    while(i<=s->length){
        s->ch[i-delen]=s->ch[i];
        i++;
    }
    s->length-=delen;
}

//模式串匹配
void StrDex(HString *s,HString *t,int pos){
    void GetNext(HString *t,int next[]);
    void delete(HString *s,int delen,int pos);
    int next[MAX_STRING_SIZE];
    GetNext(t,next);
    int i,j;
    i=pos-1;
    j=0;
    while(i<s->length&&j<t->length){
        if(j==-1||s->ch[i]==t->ch[j]){
            i++;
            j++;
        }else{
            j=next[j];
        }
    }
    if(j>=t->length){
        delete(s,t->length,i-t->length+1);
        StrDex(s,t,i-t->length+1);
    }
}

int main(){
    void init(HString *s);
    void getmyline(HString *s);
    void StrDex(HString *s,HString *t,int pos);

    HString *s=(HString *)malloc(sizeof(HString));
    HString *t=(HString *)malloc(sizeof(HString));
    init(s);
    init(t);
    printf("请输入母串s\n");
    getmyline(s);
    printf("请输入子串t\n");
    getmyline(t);
    int i=1;
    StrDex(s,t,i);
    printf("处理结果如下\n%s\n",s->ch);
    return 0;
}
