//给你n个数字。针对这些数字进行q次询问，每次询问给你一个数字a，请判断a是否在给定的n个数字中出现过。
//输入格式
//第一行是两个由空格分隔的整数n,q分别表示字符串的数量和询问的次数。接下来n行，每行是一个正整数，表示给定的数字。接下来q行，每行是一个正整数，表示一次询问。
//输出格式
//针对每次询问，输出一行一个yes或者no，表示答案。
//数据约定 1≤n,q≤10^5 1≤ai≤10^9  ps:请用hash表实现。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100000

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct HashTable {
    Node *head;
} HashTable;

int hash(int data) {
    return data % MAX;
}

void insert(HashTable *hashTable, int data) {
    int index = hash(data);
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = hashTable[index].head;
    hashTable[index].head = node;
}

int search(HashTable *hashTable, int data) {
    int index = hash(data);
    Node *node = hashTable[index].head;
    while (node) {
        if (node->data == data) {
            return 1;
        }
        node = node->next;
    }
    return 0;
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable) * MAX);
    for (int i = 0; i < MAX; i++) {
        hashTable[i].head = NULL;
    }
    for (int i = 0; i < n; i++) {
        int data;
        scanf("%d", &data);
        insert(hashTable, data);
    }
    for (int i = 0; i < q; i++) {
        int data;
        scanf("%d", &data);
        if (search(hashTable, data)) {
            printf("yes\n");
        } else {
            printf("no\n");
        }
    }
    return 0;
}