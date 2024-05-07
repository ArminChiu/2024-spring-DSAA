//二叉树的创建、非递归先序、中序、后序遍历
#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;

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
    char ch;
    printf("根节点:");
    scanf(" %c", &ch);
    T->data = ch;
    T->lchild = T->rchild = NULL;
    queue[rear++] = T;
    while(front != rear){
        Node *p = queue[front++];
        printf("%c的左孩子:", p->data);
        scanf(" %c", &ch);
        //输入0表示无左孩子
        if(ch != '0'){
            Node *temp = (Node*)malloc(sizeof(Node));
            temp->data = ch;
            temp->lchild = temp->rchild = NULL;
            p->lchild = temp;
            queue[rear++] = temp;
        }
        printf("%c的右孩子:", p->data);
        scanf(" %c", &ch);
        //输入0表示无右孩子
        if(ch != '0'){
            Node *temp = (Node*)malloc(sizeof(Node));
            temp->data = ch;
            temp->lchild = temp->rchild = NULL;
            p->rchild = temp;
            queue[rear++] = temp;
        }
    }
    return T;
}

//非递归先序遍历
void PreOrder(Node *T){
    Node *stack[100];
    int top = -1;
    Node *p = T;
    while(p || top != -1){
        //循环压入左子树,同时输出根节点
        while(p){
            printf("%c ", p->data);
            stack[++top] = p;
            p = p->lchild;
        }
        //退栈，转向兄弟节点(右子树)
        if(top != -1){
            p = stack[top--];
            p = p->rchild;
        }
    }
    //遍历至最右节点时,栈空且p==NULL
    printf("\n");
}

//非递归中序遍历
void MidOrder(Node *T){
    Node *stack[100];
    int top = -1;
    Node *p = T;
    while(p || top != -1){
        //循环压入左子树
        while(p){
            stack[++top] = p;
            p = p->lchild;
        }
        //退栈，输出左节点，转向右子树
        if(top != -1){
            p = stack[top--];
            printf("%c ", p->data);
            p = p->rchild;
        }
    }
    printf("\n");
}

//非递归后序遍历
void PostOrder(Node *T){
    Node *stack[100];
    int top = -1;
    Node *p = T;
    Node *last = NULL;//用来记录上一个节点
    while(p || top != -1){
        //循环压入左子树
        while(p){
            stack[++top] = p;
            p = p->lchild;
        }
        //退栈，转向右子树
        if(top != -1){
            p = stack[top];
            //若右子树为空或已访问过,则输出根节点
            if(!p->rchild || p->rchild == last){
                printf("%c ", p->data);
                //访问过的节点赋值给last
                last = p;
                top--;
                p = NULL;
            }else{//否则转向右子树
                p = p->rchild;
            }
        }
    }
    printf("\n");
}

int main(){
    Node *T = CreateTree();
    printf("先序遍历结果:");
    PreOrder(T);
    printf("中序遍历结果:");
    MidOrder(T);
    printf("后序遍历结果:");
    PostOrder(T);
    return 0;
}