//二叉树的创建、非递归先序、中序、后序遍历
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct Node{
    ElemType data;
    struct Node *lchild, *rchild;
}Node;

//依次按顺序输入字母或0(0表示此处无节点)，构建二叉树
Node *CreateTree(){
    Node *T = (Node*)malloc(sizeof(Node));
    //利用队列存储已存入节点，队列中节点均需判断是否有左右孩子
    Node *queue[100];
    //队头和队尾指针
    int front = 0, rear = 0;
    int ch;
    printf("根节点:");
    scanf("%d", &ch);
    T->data = ch;
    T->lchild = T->rchild = NULL;
    queue[rear++] = T;
    while(front != rear){
        Node *p = queue[front++];
        printf("%d的左孩子:", p->data);
        scanf("%d", &ch);
        //输入0表示无左孩子
        if(ch != -1){
            Node *temp = (Node*)malloc(sizeof(Node));
            temp->data = ch;
            temp->lchild = temp->rchild = NULL;
            p->lchild = temp;
            queue[rear++] = temp;
        }
        printf("%d的右孩子:", p->data);
        scanf("%d", &ch);
        //输入0表示无右孩子
        if(ch != -1){
            Node *temp = (Node*)malloc(sizeof(Node));
            temp->data = ch;
            temp->lchild = temp->rchild = NULL;
            p->rchild = temp;
            queue[rear++] = temp;
        }
    }
    return T;
}

//非递归中序遍历
void MidOrder(Node *T, int x){
    Node *stack[100];
    int top = -1;
    Node *p = T;
    while(p || top != -1){
        //循环压入右子树
        while(p){
            stack[++top] = p;
            p = p->rchild;
        }
        //退栈，输出右节点，转向左子树
        if(top != -1){
            p = stack[top--];
            if(p->data < x){
                break;
            }
            printf("%d ", p->data);
            p = p->lchild;
        }
    }
    printf("\n");
}

int main(){
    printf("请输入x:");
    int x;
    scanf("%d", &x);
    Node *T = CreateTree();
    printf("反序中序遍历结果:");
    MidOrder(T, x);
    return 0;
}