#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 100

typedef char element;
typedef struct 
{
    element stack[N];
    int top;
} StackType;

void init(StackType* S){
    S->top = -1;
}

int isEmpty(StackType* S){
    return S->top == -1;
}

int isFull(StackType *S){
    return S->top == N-1;
}

void push(StackType *S, element e){
    if (isFull(S)) printf("Overflow\n");
    else {
        S->top++;
        S->stack[S->top] = e;
    }
}

void print(StackType *S){
    for(int i=S->top;i>=0;i--){
        printf(" |  %c  |\n",S->stack[i]);
        printf("  ______ \n");
    }
}

element pop(StackType *S){
    if(isEmpty(S)){
        puts("Empty!");
        return -1;
    }
    element e = S->stack[S->top];
    S->top--;
    return e;
}

element peek(StackType *S){
    if(isEmpty(S)){
        puts("Empty!");
        return -1;
    }
    return S->stack[S->top];
}

// 연산자 우선순위 확인
int prec(char op){
    if (op == '+' || op == '-') return 1; // */ > +-
    if (op == '*' || op == '/') return 2;
    return 0;
}

void infixToPostfix(char expr[]){
    StackType S;
    StackType P; // 후위표기식 저장용 스택 추가
    init(&S);
    init(&P); // 두 스택 초기화

    char c, op; // 현재 문자 / 연산자
    int n = strlen(expr);
    int digit = 1;        // 여러 자리 수 처리용
    int num = 0;          // 현재 숫자 저장
    int started = 0;      // 숫자 읽기 시작 여부
    for(int i=0; i<n; i++){ // 각 문자에 대하여
        c = expr[i];
        if(isdigit(c)){ // 문자가 숫자인 경우
            if(started == 0){ // 숫자를 처음 읽기 시작한 경우
                num = c - '0'; // 첫 자릿값 저장
                digit = 10; // 다음 자릿수
                started = 1; // 읽기 시작 전환
            }
            else{ // 숫자 읽는 중인 경우
                num = num * 10 + (c - '0'); // 자리수로 누적
                digit *= 10; // 자리수 증가
            }
        } else { // 숫자가 아닌경우 
            if(started == 1){ // 직전에 숫자를 읽고 있었으면
                char temp[20]; // 숫자를 문자열로 바꿔 저장할 배열
                sprintf(temp, "%d", num); // 정수를 문자열로 변환
                for(int k=0; temp[k] != '\0'; k++){ 
                    push(&P, temp[k]); // 숫자의 각 자리 문자 -> 후위표기식 스택에 저장
                }
                push(&P, ' '); // 다음 토큰 구분을 위해 공백 push
                num = 0;
                digit = 1; 
                started = 0; // 숫자 읽기 상태 초기화
            }
        }
        
        if(c == ' ') continue;
        
        else if(c == '('){
            push(&S, c); // 이전과 동일 : 여는 괄호 stack push
        } else if(c == ')'){
            while(!isEmpty(&S) && peek(&S) != '('){
                op = pop(&S); // 여는 괄호 만날 때까지 연산자 뽑아서 출력용 스택 저장
                push(&P, op);
                push(&P, ' ');
            }
            if(!isEmpty(&S) && peek(&S) == '(') pop(&S); // 여는 괄호 제거 
        } else if(strchr("+-*/", c)){ // 연산자인 경우  
            while(!isEmpty(&S)){ // stack이 비거나 여는 괄호 만나기 전까지 스택에 남아있는 연산자 전부 push
                op = peek(&S);
                if(op == '(') break;
                if(prec(c) <= prec(op)){ // 우선순위 높을 때까지 연산자 우선순위 순서대로 출력 스택 push
                    push(&P, pop(&S)); 
                    push(&P, ' ');
                } else break; 
            }
            push(&S, c); //현재 연산자 스택에 저장
        }
    }
    // 식이 숫자로 끝나는 경우 마지막 숫자 처리
    if(started == 1){
        char temp[20];
        sprintf(temp, "%d", num);

        for(int k=0; temp[k] != '\0'; k++){
            push(&P, temp[k]);
        }
        push(&P, ' ');
    }
    // 연산자 스택에 남아 있는 연산자 모두 후위표기식 이동
    while(!isEmpty(&S)){
        push(&P, pop(&S));
        push(&P, ' ');
    }
    // 저장된 후위표기식 출력
    for(int i=0; i<=P.top; i++){
        printf("%c", P.stack[i]);
    }
    puts("");

    
    int calc[N]; // 임시로 정수용 스택 하나 계산용으로 만들어놓기
    int top = -1; // 계산 스택 top
    int value = 0; // 현재 읽고 있는 숫자
    int reading = 0; // 숫자를 읽는 중인지 표시
    // 저장된 후위표기식을 앞에서부터 읽으면서 계산
    for(int i=0; i<=P.top; i++){
        c = P.stack[i];// 현재 후위표기식 문자

        if(isdigit(c)){ // 숫자이면
            value = value * 10 + (c - '0'); // 자리수 누적
            reading = 1; // 숫자 읽기 상태 표시
        }
        else if(c == ' '){ //공백이면
            if(reading == 1){ // 직전에 숫자 읽고 있었다면 읽기가 끝난 것
                calc[++top] = value; // 계산 스택에 숫자 push
                value = 0; // 새 숫자를 받기 위한 초기화
                reading = 0;
            }
        }
        else if(strchr("+-*/", c)){ // 연산자이면
            int b = calc[top--]; // 두번째 숫자 pop
            int a = calc[top--]; // 첫번째 숫자 pop
            int r = 0; // 연산 결과

            switch(c){ // 연산자에 따른 계산
                case '+': r = a + b; break;
                case '-': r = a - b; break;
                case '*': r = a * b; break;
                case '/': r = a / b; break;
            }

            calc[++top] = r; // 결과를 다시 stack에 push
        }
    }

    printf("%d\n", calc[top]); // 최종 계산 결과 출력
}

int main(){
    char expr[N];
    printf("Input Expr... ");
    fgets(expr,N,stdin); // 기존 수업시간과 동일

    infixToPostfix(expr);

}


