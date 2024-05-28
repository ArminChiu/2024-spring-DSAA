//给你n个字符串。针对这些字符串进行q次询问，每次询问给你一个字符串s，请判断s是否在给定的n个字符串中出现过。
//输入格式 第一行是两个由空格分隔的整数n,q分别表示字符串的数量和询问的次数。接下来n行，每行是一个仅由小写字母组成的字符串，表示给定的字符串。接下来q行，每行是一个仅由小写字母组成的字符串，表示一次询问。
//输出格式 针对每次询问，输出一行一个yes或者no，表示答案。
//数据约定 1≤n,q≤10^5 ∑𝑖=0𝑛−1𝑙𝑒𝑛(𝑠𝑖)≤10^6 ps:请用trie树方式实现

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 26

typedef struct Node {
    int flag;
    struct Node *next[MAX];
} Node;

Node *getNewNode() {
    Node *p = (Node *)malloc(sizeof(Node));
    p->flag = 0;
    for (int i = 0; i < MAX; i++) {
        p->next[i] = NULL;
    }
    return p;
}

void insert(Node *root, char *str) {
    Node *p = root;
    for (int i = 0; str[i]; i++) {
        int ind = str[i] - 'a';
        if (p->next[ind] == NULL) {
            p->next[ind] = getNewNode();
        }
        p = p->next[ind];
    }
    p->flag = 1;
}

int search(Node *root, char *str) {
    Node *p = root;
    for (int i = 0; str[i]; i++) {
        int ind = str[i] - 'a';
        if (p->next[ind] == NULL) {
            return 0;
        }
        p = p->next[ind];
    }
    return p->flag;
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    Node *root = getNewNode();
    for (int i = 0; i < n; i++) {
        char str[1000000];
        scanf("%s", str);
        insert(root, str);
    }
    for (int i = 0; i < q; i++) {
        char str[1000000];
        scanf("%s", str);
        printf("%s\n", search(root, str) ? "yes" : "no");
    }
    return 0;
}