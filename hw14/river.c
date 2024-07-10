//附加思考题：已知一条河长度为L，河的起点（Start）和终点（End）分别有两块石头，S到E的距离就是L。
//河中有n块石头，给出每块石头到S的距离。现在要你移除其中的m块，使得两块相邻石头间距的最小值最大。
//（输入：河的长度L；石头数量n；移除石头数量每块石头到S的距离di，共n个数）请设计合理的贪心算法解决此问题。
#include<stdio.h>

int main(){
    int L, n, m;
    int mid;
    scanf("%d %d %d", &L, &n, &m);
    int max = L;
    int min = L;
    int stone[n+2];
    stone[0] = 0;
    stone[n+1] = L;

    //存入每块石头的位置，冒泡比较得到最小距离
    for(int i=1; i<=n; i++){
        scanf("%d", &stone[i]);
        if(stone[i] - stone[i-1] < min){
            min = stone[i] - stone[i-1];
        }
    }
    if(stone[n+1] - stone[n] < min){
        min = stone[n+1] - stone[n];
    }

    //二分查找最大的最小值，退出条件为min > max
    while(min <= max){
        mid = (max + min) / 2;
        int count = 0;
        int length = 0;
        //遍历所有石头
        for(int i=1; i<=n+1; i++){
            //若本石头与前面的石头的总距离小于mid，则可以继续移去石头
            if(length + stone[i] - stone[i-1] <= mid){
                count ++;
                length += stone[i] - stone[i-1];
            //否则本石头不可被移去，重新计算length
            }else{
                length = 0;
            }
        }
        //调整min和max的值后继续二分查找
        if(count <= m){
            min = mid + 1;
        }else{
            max = mid - 1;
        }
    }

    //输出最终结果
    printf("%d\n", min);
    return 0;
}