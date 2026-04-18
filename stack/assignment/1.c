#include <stdio.h>

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
    if (op == '|') return 1;                  // ||
    if (op == '&') return 2;                  // &&
    if (op == '>' || op == '<') return 3;     // > <
    if (op == '+' || op == '-') return 4;     // 이항 +- 연산자
    if (op == '*' || op == '/') return 5;     // * /
    if (op == '!' || op == '@' || op == '#') return 6; // 단항 연산자 + - !
    return 0;
}
// 단항연산자인지 확인하여 우/좌결합 결정
int isRightAssociative(char op){ 
    if (op == '!' || op == '@' || op == '#') return 1;
    return 0;
}
//후위 표기식 연산자 출력: 실제 기호로 바꿔야 해서 따로 함수로 뺐음
void printOp(char op){
    if (op == '&') printf("&&"); // 두 글자 연산자 출력
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
    int expectOperand = 1; // 두 글자 연산자 처리를 위해 트리거 설정
    for(int i=0;i < n;i ++){ // 각 문자에 대하여
        c = expr[i];
        if(isupper(c)){ // 대문자면 피연산자
            printf("%c",c); // 피연산자는 그대로 출력
            expectOperand = 0; // 피연산자를 기대하는가? 1 -> 단항 가능, 0 -> 이항 가능
        } else if (c == '('){
            push(&S, c); // 여는 괄호 스택에 push
            expectOperand = 1; //괄호 다음에는 피연산자 와야 함
        } else if(c == ')'){
            while(!isEmpty(&S) && peek(&S) != '('){ // 여는 괄호 만날 때까지 
                printOp(pop(&S)); // 스택 연산자 뽑아서 출력
            }
            if(!isEmpty(&S) && peek(&S) == '(') pop(&S); // 여는 괄호 제거 후
            expectOperand = 0; // 괄호식 끝이므로 연산자 기대
        } else { // 연산자인경우

            // 두 글자 연산자 처리
            if (c == '&' && i + 1 < n && expr[i + 1] == '&'){
                op = '&';
                i++;
            } // and 연산자 -> index 2번 세기
            else if (c == '|' && i + 1 < n && expr[i + 1] == '|'){
                op = '|';
                i++;
            } // or 연산자 -> index 2번 세기
            else{
                op = c;
            } // 그 외엔 기본 연산자 처리

            // 단항 +, - 구분을 위해 스택 내부에서만 @, #로 치환)
            if (expectOperand){
                if (op == '+') op = '@';
                else if (op == '-') op = '#';
            }

            // 스택 top 연산자와 우선순위 비교
            while(!isEmpty(&S) && peek(&S) != '('){
                char topOp = peek(&S); // 현재 스택 top 연산자 확인

                if (isRightAssociative(op)){ // 현재 연산자가 단항연산자면 (우결합)
                    if (prec(op) < prec(topOp)) // top이 더 높은 우선순위일 때만 pop
                        printOp(pop(&S));
                    else
                        break;
                }
                else{ // 이항연산자 - 좌결합이면    
                    if (prec(op) <= prec(topOp)) // top이 높거나 같으면 pop
                        printOp(pop(&S));
                    else
                        break;
                }
            }

            push(&S, op); // 현재 연산자 스택에 push
            expectOperand = 1; // 연산자 뒤엔 다시 피연산자 기대
        }
    }

    // 식을 모두 읽은 뒤 여는 괄호 만나기 전까지 스택에 남아있는 연산자 전부 출력
    while(!isEmpty(&S)){
        char op = pop(&S);
        if (op != '(') printOp(op); // 하나 꺼내서 여는 괄호 아니면 출력
    }
    puts(""); // 다음 라운드 입력을 위해 개행
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