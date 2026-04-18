#include <stdio.h>
#include <math.h>

#define N 10

typedef struct polynomial{
    int degree;
    int coef[N];
} Poly;

void print(Poly p, const char *str){
    printf("%s",str);
    for(int i=p.degree;i>0;i--){
        printf("%d x^%d + ",p.coef[i], i );
    }
    printf("%d\n",p.coef[0]);
}

Poly add(Poly a, Poly b){
    Poly p;
    p.degree = (a.degree > b.degree)?a.degree:b.degree;
    for(int i=p.degree;i>=0;i--){
        p.coef[i] = ((i <=a.degree)?a.coef[i]:0)+((i<=b.degree)?b.coef[i]:0);
    }
    return p;
}

int eval(Poly p, int x){
    int result = p.coef[0];
    for(int i=1;i<=p.degree;i++){
        result += p.coef[i] * pow(x,i);
    }
}

int main(){
    Poly a, b, c;
    printf("두 다항식의 차수를 각각 입력: ");
    scanf("%d %d", &a.degree, &b.degree);
    printf("첫 번쨰 다항식의 계수들을 입력: ");
    for (int i=a.degree; i>=0;i--){
        scanf("%d",&a.coef[i]);
    }

    printf("두 번쨰 다항식의 계수들을 입력: ");
    for (int i=b.degree; i>=0;i--){
        scanf("%d",&b.coef[i]);
    }

    print(a, "A = ");
    print(b, "B = ");

    c = add(a,b);
    puts("------------------------------------------");
    print(c, "C = ");

}