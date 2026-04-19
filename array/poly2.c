#include <stdio.h>

#define MAX_TERMS 10

typedef struct terms{
    int expon;
    double coef;
} Terms[MAX_TERMS];

typedef struct polynomial{
    int nTerms;
    Terms terms;
} Poly;

Poly makePoly(){
    Poly p;
    printf("다항식의 항의 수 입력: ");
    scanf("%d",&p.nTerms);
    printf("고차항부터 항의 계수 지수 입력: \n");
    for(int i=0;i<p.nTerms;i++){
        printf("%d : ",i+1);
        scanf("%lf %d", &p.terms[i].coef, &p.terms[i].expon);
    }
}

void print(Poly p, const char* str){
    printf("%s",str);
    for(int i=0; i<p.nTerms; i++){
        printf("%.1lf x^%d + ", p.terms[i].coef, p.terms[i].expon);
    }
    printf("\b\b  \n");
}

int main(){
    Poly a = makePoly();
    Poly b = makePoly();
    
}