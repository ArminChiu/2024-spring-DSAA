#include <stdio.h>
//消除递归
int function(int n){
    int result=1;
    while(n!=0){
        result*=n;
        n/=2;
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
