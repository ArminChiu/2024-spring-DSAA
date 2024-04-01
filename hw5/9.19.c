#include <stdio.h>
#include <stdlib.h>

//哈希表数据结构
typedef int ElemType;
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
        H->elemArray[i].key = 0;
    }
    return H;
}

//插入哈希表
void InsertHash(HashTable* H,int key,ElemType value){
    int index = (3*key) % H->size;
    int distance = (7*key) % 10 + 1;
    while(H->elemArray[index].key != 0){
        index = (index + distance) % H->size;
    }
    H->elemArray[index].key = key;
    H->elemArray[index].value = value;
}

//查找哈希表
elem* SearchHash(HashTable* H,int key){
    int index = (3*key) % H->size;
    int distance = (7*key) % 10 + 1;
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
        if(H->elemArray[i].key != 0){
            printf("key:%d value:%d\n",H->elemArray[i].key,H->elemArray[i].value);
        }
    }
}

//平均查找长度
double ASL(HashTable* H){
    int sum = 0;
    for(int i = 0;i < H->size;i++){
        if(H->elemArray[i].key != 0){
            int index = (3*H->elemArray[i].key) % H->size;
            int distance = (7*H->elemArray[i].key) % 10 + 1;
            while(H->elemArray[index].key != H->elemArray[i].key){
                index = (index + distance) % H->size;
            }
            sum += distance;
        }
    }
    return (double)sum / H->size;
}


int main(){
    HashTable* H = InitHash(11);
    int array[]={22,41,53,46,30,13,01,67};
    for(int i = 0;i < 8;i++){
        InsertHash(H,array[i],array[i]);
    }
    PrintHash(H);
    printf("ASL:%lf\n",ASL(H));
}