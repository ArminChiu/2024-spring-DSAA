//求稀疏多项式的值,空间复杂度为O(n)(n为项数)
#include <stdio.h>

typedef struct{
    int coef;
    int exp;
}PolyTerm;

typedef struct{
    PolyTerm *data;
    int length;
}SqPoly;

int addup(SqPoly a, int x){
    int sum=0,base=1;
    for(int i=0;i<a.length;i++){
        for(int j=0;j<a.data->exp;j++){
            base*=x;
        }
        base*=a.data->coef;
        sum+=base;
        base=1;
        a.data++;
    }
    return sum;
}
