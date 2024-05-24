//不是很有效的括号匹配
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_SIZE 1001

typedef struct {
    char* data;
    int top;
    int size;
} Stack;

Stack* initStack(int size);
void push(Stack* s, char c);
char pop(Stack* s);
bool isValidWithOneModification(char* s);

Stack* initStack(int size) {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->data = (char*)malloc(sizeof(char) * size);
    s->top = -1;
    s->size = size;
    return s;
}

void push(Stack* s, char c) {
    if (s->top == s->size - 1) {
        return;
    }
    s->data[++s->top] = c;
}

char pop(Stack* s) {
    if (s->top == -1) {
        return '\0';
    }
    return s->data[s->top--];
}

bool isValidWithOneModification(char* s) {
    Stack* stack = initStack(MAX_SIZE);
    int len = strlen(s);
    int error = 0;
    for (int i = 0; i < len; i++) {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
            push(stack, s[i]);
        } else {
            if (s[i] == ')') {
                if (stack->top == -1) {
                    return false;
                }else if(stack->data[stack->top] != '('){
                    error++;
                }
                if(error > 1)
                    return false;
                pop(stack);
            } else if (s[i] == ']') {
                if (stack->top == -1) {
                    return false;
                }else if(stack->data[stack->top] != '['){
                    error++;
                }
                if(error > 1)
                    return false;
                pop(stack);
            } else if (s[i] == '}') {
                if (stack->top == -1) {
                    return false;
                }else if(stack->data[stack->top] != '{'){
                    error++;
                }
                if(error > 1)
                    return false;
                pop(stack);
            }
        }
    }
    if(stack->top == -1 && error <= 1){
        return true;
    }else{
        return false;
    }
}

int main() {
    char s[1001];
    scanf("%1000s", s);
    if (isValidWithOneModification(s)) {
        printf("%d\n", 1);
    } else {
        printf("%d\n", 0);
    }
    return 0;
}