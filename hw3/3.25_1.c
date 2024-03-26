#include <stdio.h>
//递归算法
int function(int n){
    int result;
    if(n==0){
        result=n+1;
    }else{
        result=n*function(n/2);
    }
    return result;
}

int main(){
    int function(int n);
    int n;
    scanf("%d",&n);
    printf("%d\n",function(n));
    return 0;
}
