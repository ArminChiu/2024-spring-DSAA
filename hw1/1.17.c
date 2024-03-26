#include <stdio.h>

int main(){
    int fibonacci(int k,int m);
    int k,m,ans;//k为阶数，m为项数，ans为结果
    scanf("%d %d",&k,&m);//读取k，m的值
    ans=fibonacci(k,m);//计算k阶第m项的值
    printf("%d",ans);//打印
    return 0;
}

int fibonacci(int k,int m){
    int ans=0;//初始化每一项的值
    if(m<k-1){//前k-2项为0
        ans=0;
    }else if(m==k-1){//第k-1项为1
        ans=1;
    }else{//剩余情况通过递归计算前k项累加之和
        for(int i=1;i<=k;i++){
            ans+=fibonacci(k,m-i);//递归
        }
    }
    return ans;//输出结果
}