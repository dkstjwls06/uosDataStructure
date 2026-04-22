#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 10

typedef struct terms{
    double coef; // 계수
    int expon; // 지수
} Terms[MAX_TERMS];

typedef struct polynomial{
    int nTerms;
    Terms terms;
} Poly;

// 차수 비교
char compare(int a, int b){
    if(a > b) return '>';
    else if(a == b) return '=';
    else return '<';
}

Poly makePoly(){
    Poly p;
    printf("다항식의 항의 수 입력: ");
    scanf("%d",&p.nTerms);

    printf("고차항부터 항의 계수 지수 입력: \n");
    for(int i=0;i<p.nTerms;i++){
        printf("%d : ",i+1);
        scanf("%lf %d", &p.terms[i].coef, &p.terms[i].expon);
    }

    return p;
}

void print(Poly p, const char* str){
    printf("%s",str);
    for(int i=0; i<p.nTerms; i++){
        printf("%.1lf x^%d + ", p.terms[i].coef, p.terms[i].expon);
    }
    printf("\b\b  \n");
}

Poly add(Poly a, Poly b){
    Poly c;
    c.nTerms = 0;

    int Apos = 0, Bpos = 0;
    double tempcoef;

    while(Apos < a.nTerms && Bpos < b.nTerms){
        switch (compare(a.terms[Apos].expon, b.terms[Bpos].expon))
        {
            case '>':
                c.terms[c.nTerms++] = a.terms[Apos++];
                break;
            case '=':
                tempcoef = a.terms[Apos].coef + b.terms[Bpos].coef;
                if(tempcoef != 0){
                    c.terms[c.nTerms].coef = tempcoef;
                    c.terms[c.nTerms].expon = a.terms[Apos].expon;
                    c.nTerms++;
                }
                Apos++, Bpos++;
                break;
            case '<':
                c.terms[c.nTerms++] = b.terms[Bpos++];
                break; 
            default:
                break;
        }
    }
    // A의 나머지 항 복사
    while(Apos < a.nTerms){
        c.terms[c.nTerms++] = a.terms[Apos++];
        if(c.nTerms > MAX_TERMS){
            fprintf(stderr, "항의 개수가 너무 많음\n");
            exit(1);
        }
    }

    // B의 나머지 항 복사
    while(Bpos < b.nTerms){
        c.terms[c.nTerms++] = b.terms[Bpos++];
        if(c.nTerms > MAX_TERMS){
            fprintf(stderr, "항의 개수가 너무 많음\n");
            exit(1);
        }
    }

    return c;
}

int main(){
    Poly a = makePoly();
    Poly b = makePoly();
    Poly c = add(a, b);

    print(a, "A = ");
    print(b, "B = ");
    printf("----------------------------------------\n");
    print(c, "C = ");

}