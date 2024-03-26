#include <stdio.h>

typedef struct{
    int coef;
    int exp;
}PolyTerm;

typedef struct{
    PolyTerm *data;
    int length;
}SqPoly;

SqPoly b;

int sub(SqPoly a1,SqPoly a2){
    int n1,n2=0;
    b.length=0;
    while(n1<a1.length&&n2<a2.length){
        if((a1.data+n1)->exp==(a2.data+n2)->exp){
            if((a1.data+n1)->coef!=(a2.data+n2)->coef){
                b.length++;
                (b.data+b.length-1)->exp=(a1.data+n1)->exp;
                (b.data+b.length-1)->coef=(a1.data+n1)->coef-(a2.data+n2)->coef;
            }
            n1++;
            n2++;
        }
        if((a1.data+n1)->exp>(a2.data+n2)->exp){
            b.length++;
            (b.data+b.length-1)->exp=(a2.data+n2)->exp;
            (b.data+b.length-1)->coef=-(a2.data+n2)->coef;
            n2++;
        }
        if((a1.data+n1)->exp<(a2.data+n2)->exp){
            b.length++;
            (b.data+b.length-1)->exp=(a1.data+n1)->exp;
            (b.data+b.length-1)->coef=(a1.data+n1)->coef;
            n1++;
        }
    }
    while(n1!=a1.length||n2!=a2.length){
        if(n1!=a1.length){
            b.length++;
            (b.data+b.length-1)->exp=(a1.data+n1)->exp;
            (b.data+b.length-1)->coef=(a1.data+n1)->coef;
            n1++;
        }
        if(n2!=a2.length){
            b.length++;
            (b.data+b.length-1)->exp=(a2.data+n2)->exp;
            (b.data+b.length-1)->coef=-(a2.data+n2)->coef;
            n2++;
        }
    }
    return b.length;
}
