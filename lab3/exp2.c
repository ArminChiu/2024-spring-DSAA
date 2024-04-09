#include <stdio.h>
#include <stdlib.h>

void function(){
    int choice=0;
    while(choice!=4){
        printf("==========菜单==========\n");
        printf("        1.排队\n");
        printf("        2.就诊\n");
        printf("        3.查看排队\n");
        printf("        4.下班(退出程序)\n");
        printf("选择菜单，请输入菜单编号：");
        scanf("%d", &choice);
        if(choice == 1){
            function1();
        }else if(choice == 2){
            function2();
        }else if(choice == 3){
            function3();
        }else if(choice != 4){
            printf("请输入正确的菜单编号！\n");
        }
    }
    return;
}

void function1(){
    printf("这是菜单1\n");
    return;
}



int main(){
    function();
    return 0;
}