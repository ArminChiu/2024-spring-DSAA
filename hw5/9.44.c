#include <stdio.h>
#include <stdlib.h>

//哈希表数据结构
typedef char* ElemType;
typedef struct{
    int key;
    ElemType value;
}elem;

typedef struct{
    elem* elemArray;
    int size;
}HashTable;

//初始化哈希表
HashTable* InitHash(int size){
    HashTable* H = (HashTable*)malloc(sizeof(HashTable));
    H->elemArray = (elem*)malloc(size * sizeof(elem));
    H->size = size;
    for(int i = 0;i < size;i++){
        H->elemArray[i].key = -1;
    }
    return H;
}

//插入哈希表
void InsertHash(HashTable* H,int key,ElemType value){
    int index = (key-'a') % H->size;
    int distance = 1;
    while(H->elemArray[index].key != -1){
        index = (index + distance) % H->size;
    }
    H->elemArray[index].key = key -'a';
    H->elemArray[index].value = value;
}

//查找哈希表
elem* SearchHash(HashTable* H,int key){
    int index = (key-'a') % H->size;
    int distance = 1;
    while(H->elemArray[index].key != key && H->elemArray[index].key != 0){
        index = (index + distance) % H->size;
    }
    if(H->elemArray[index].key == key){
        return &H->elemArray[index];
    }
    return NULL;
}

//删除哈希表
void DeleteHash(HashTable* H,int key){
    elem* e = SearchHash(H,key);
    if(e != NULL){
        e->key = 0;
    }
}

//打印哈希表
void PrintHash(HashTable* H){
    for(int i = 0;i < H->size;i++){
        if(H->elemArray[i].key != -1){
            printf("key:%d value:%s\n",H->elemArray[i].key,H->elemArray[i].value);
        }
    }
}

//按关键字第一个字母顺序打印哈希表
void PrintHash2(HashTable* H){
    for(int i = 0;i < 26;i++){
        int index = i % H->size;
        int distance = 1;
        for(int j = 0;j<H->size;j++){
            if(H->elemArray[index].key == i){
                printf("key:%d value:%s\n",H->elemArray[index].key+'a',H->elemArray[index].value);
            }
            index = (index + distance) % H->size;
        }
    }
}


int main(){
    HashTable* H = InitHash(10);
    InsertHash(H,'a',"abandon");
    InsertHash(H,'i',"identity");
    InsertHash(H,'j',"jewel");
    InsertHash(H,'s',"subway");
    InsertHash(H,'z',"zoo");
    InsertHash(H,'k',"kyoto");
    InsertHash(H,'n',"none");
    InsertHash(H,'f',"fun");
    InsertHash(H,'y',"young");
    InsertHash(H,'c',"carnival");
    PrintHash2(H);
    return 0;
}