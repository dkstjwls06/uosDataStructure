#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define N 50

typedef char element;

typedef struct{
    element stack[N];
    int top;
} StackType;

void init(StackType* S){
    S->top = -1;
}

int isEmpty(StackType* S){
    return S->top == -1;
}

int isFull(StackType* S){
    return S->top == N-1;
}

int push(StackType* S, element e){
    if(isFull(S)) puts("Overflow");
    else{
        S->top++;
        S->stack[S->top] == e;
    }
}

element pop(StackType* S){
    if(isEmpty(S)) {
        puts("Empty");
        return -1;
    }
    element e = S->stack[S->top];
    S->top--;
    return e;

}

element peek(StackType* S){
    if(isEmpty(S)) {
        puts("Empty");
        return -1;
    }
    return S->stack[S->top];
}

int prec(char op){
    if(op == '|') return 1; // ||
    if(op == '&') return 2; // &&
    if(op == '>' || op == '<') return 3; // > <
    if(op == '+' || op == '-') return 4;
    if(op == '*' || op == '/') return 5;
    if(op == '!' || op == '@' || op == '#') return 6; // 단항연산, +, -는 치환환
}

int isRightAssociative(char op){
    if(op == '!' || op == '@' || op == '#') return 1;
    return 0;
}

void printOp(char op){
    if(op == '&') print("&&");
    else if (op == '|') printf("||");
    else if (op == '@') printf("+");   // 단항 연산자 출력
    else if (op == '#') printf("-");   
    else printf("%c", op); // 그 외 일반적 연산자 출력    
}

void infixToPostfix(char expr[]){
    StackType S;
    init(&S);

    char c, op;
    int n = strlen(expr);
    int expectOperand = 1; // 다음 : 피연산자 기대 (0->연산자 기대)
    // +, - 나왔을 때 피연산자 기대중이였으면 그건 단항연산자.
    for(int i=0; i<n; i++){
        c=expr[i];
        if(isupper(c)){
            printf("%c",c);
            expectOperand = 0;
        } else if(c == '('){
            push(&S, c);
            expectOperand = 1;
        } else if(c == ')'){
            while(!isEmpty(&S) && peek(&S) != '(') printOp(pop(&S));
            if(!isEmpty(&S) && peek(&S) == '(') pop(&S);
            expectOperand = 0;
        } else {
            if(c == '&' && i+1 <n && expr[i+1] == '&'){
                op = '&';
                i++;
            } else if(c == '|' && i+1<n && expr[i+1] == '|'){
                op = '|';
                i++;
            } else {
                op = c;
            }

            if(expectOperand){
                if(op == '+') op = '@';
                else if(op == '-') op = '#';
            }

            while(!isEmpty(&S) && peek(&S) != '('){
                char topOp = peek(&S);

                if(isRightAssociative(op)){
                    if(prec(op) < prec(topOp)) printOp(pop(&S));
                    else break;
                } else{
                    if(prec(op) <= prec(topOp)){
                        printOp(pop(&S));
                    }
                    else break;
                }
            }

            push(&S, op);
            expectOperand = 1;
        }
    }
    while(!isEmpty(&S)){
        char op = pop(&S);
        if(op!='(') printOp(op);
    }
    puts("");
}

int main(){
    int round;
    scanf("%d ",&round);
    // 백준 방식으로 라운드별 입출력
    for (int i=0; i < round; i++){
        char expr[N];
        fgets(expr, N, stdin);
        if (expr[strlen(expr) - 1] == '\n') expr[strlen(expr) - 1] = '\0'; // 마지막 개행문자 제거
        infixToPostfix(expr); // 중위 -> 후위 변환
    }
}