/*--------以下为读取DHT段数据并进行Huffman树建立的函数--------*/
#include "jpg_decode.h"

//生成哈夫曼树节点
void CreateTree(int code, int value, int length, huffman *root) {
    //根据二进制哈夫曼码code建立哈夫曼树
    //value为码字对应的值，length为码字长度
    //建立一个栈存code的每一位
    int stack[16];
    int top = 0;
    int storecode = code; //存储原code值
    for (int i = 0; i < length; i++) {
        stack[top++] = code % 2;
        code /= 2;
    }
    //根据栈建立哈夫曼树
    huffman *p = root;
    for (int i = top - 1; i >= 0; i--) {
        if (stack[i] == 0) {
            if (p->left == NULL) {
                p->left = (huffman*)malloc(sizeof(huffman));
                p = p->left;
            }
            else {
                p = p->left;
            }
        }
        else {
            if (p->right == NULL) {
                p->right = (huffman*)malloc(sizeof(huffman));
                p = p->right;
            }
            else {
                p = p->right;
            }
        }
        if(i == 0) {
            p->value = value;
            p->length = length;
            p->code = storecode;
        }
        else {
            p->value = -1;
            p->length = -1;
            p->code = -1;
        }
    }
}

//打印第n个哈夫曼树(num:0~3)(只打印叶子节点)
void PrintTree(huffman *tree, int n) {
    huffman *p= tree + n;
    if (p->left != NULL) {
        PrintTree(p->left, 0);
    }
    if (p->right != NULL) {
        PrintTree(p->right, 0);
    }
    if(p->left == NULL && p->right == NULL){
        //打印叶子节点值
        printf("%4d  |  ", p->value);
        //打印码值，形式为二进制01串，码长为length
        for (int i = p->length - 1; i >= 0; i--) {
            printf("%d", (p->code >> i) % 2);
        }
        printf("\n");
    }
}

//建立DHT表
void CreateDHT(jpg *JPG) {
    int i = 2; //DHT表指针
    int j = 0; //哈夫曼表数量(0~3)
    int k = 0; //码字指针
    dht *p;
    p = JPG->DHT;
    p->tree = (huffman*)malloc(4 * sizeof(huffman));
    for(int l = 0; l < 4; l++) { //初始化
        for(int m = 0; m < 18; m++) {
            p->num[l][m] = 0;
        }
        p->num[l][16] = -1;
    }
    while (i < JPG->DHT->size) { //遍历DHT段
        int m = 0;//哈夫曼编码
        //表号 1字节
        p->num[j][16] = JPG->DHT->data[i++];
        //码字数量 16字节
        for (k = 0; k < 16; k++) {
            p->num[j][k] = JPG->DHT->data[i++];
            p->num[j][17] += p->num[j][k];
        }
        //码字 p->num[j][17]字节
        //建立哈夫曼树
        //根节点
        (p->tree+j)->left = NULL;
        (p->tree+j)->right = NULL;
        int code = 0;
        int value, length;
        k = 0;
        //插入叶子节点
        for (int sum = 0; sum < p->num[j][17]; sum++) {
            if(p->num[j][k] != 0){
                code++;
            }
            while (p->num[j][k] == 0) {
                if(k != 0)
                    code = (code + 1) * 2;
                k++;
            }
            value = JPG->DHT->data[i++];
            length = k + 1;
            p->num[j][k]--;
            CreateTree(code, value, length, p->tree+j);
        }
        j++; //下一个哈夫曼表
    }
}