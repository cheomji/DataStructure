//미완성.. 보너스문제(괄호 수 안맞을 때 안맞다고 출력하는 거)까지 완성하면
//메인함수에서 포문이 아니라 와일문 돌려서 파일이 뭐든지간에 알아서 한줄한줄 끊어 받아주게 만들면 됨

//개행문자때매 고생 좀 했음;

/*
infix.txt
(9%8%7)+(6-5/4)/(3*2-5)%5
(((1+2/3)*4-5)+((6-7*8)/3)%2)-9
1+2-3*4/2-6%7-8*9
((1+2)-3)*4-5
((1+2)-3)*4)-5
1+(((2*3)-4+5
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define MAX 100

typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand } precedence;

static int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };
int stack[MAX];
char expr[MAX]; //char형을 전역변수로 선언하면 모든 곳에 \0(null)이 들어감
int top;

void push(int input);
int pop(void);
int eval(void);
precedence get_token(char* sym, int* i);
void postfix(void);
void print_token(precedence token);
char PtoC(precedence token);

int main() {
    FILE* fp = fopen("infix.txt", "r");
    if (!fp) {
        printf("cannot open file");
        return 0;
    }
    for (int i = 0; i < 4; i++) {
        fgets(expr, MAX, fp);
        printf("Infix: %s", expr);
        postfix();
        printf("Result: %d\n\n", eval());
    }
    fclose(fp);
    return 0;
}

void push(int input) {
    if (top >= MAX - 1) {
        printf("stack full");
        return;
    }
    stack[++top] = input;
}

int pop(void) {
    if (top == -1) {
        printf("stack empty");
        return -1;
    }
    return stack[top--];
}

int eval(void) {
    precedence token;
    char sym;
    int op1, op2, i = 0;
    top = -1;
    for (token = get_token(&sym, &i); token != eos; token = get_token(&sym, &i)){
        if (token == operand)
            push(sym - '0');
        else {
            op2 = pop();
            op1 = pop();
            switch (token)
            {
            case plus: push(op1 + op2); break;
            case minus: push(op1 - op2); break;
            case times: push(op1 * op2); break;
            case divide: push(op1 / op2); break;
            case mod: push(op1 % op2); break;
            default:
                break;
            }
        }
    }
    return pop();
}

precedence get_token(char* sym, int* i) {
    *sym = expr[(*i)++];
    switch (*sym) {
    case '(': return lparen;
    case ')': return rparen;
    case '+': return plus;
    case '-': return minus;
    case '/': return divide;
    case '*': return times;
    case '%': return mod;
    case '\n': return eos; //이거 ppt에는 \0으로 돼있길래 그렇게 적었는데 제대로 안돌아갔음. expr에  받고 나면 맨끝에는 개행문자 있으니까 조건을 \n로 해줘야함.
    default: return operand;
    }
}

void postfix(void) {
    char sym, tmp[MAX];
    precedence token;
    int i = 0, idx = 0;
    top = 0;
    stack[top] = eos;
    for (token = get_token(&sym, &i); token != eos; token = get_token(&sym, &i)) {
        //printf("%d ", token);
        if (token == operand) {
            //printf("%c", sym);
            tmp[idx++] = sym;
        }
        else if (token == rparen) {
            while (stack[top] != lparen) {
                //print_token(pop());
                tmp[idx++] = PtoC(pop());
            }
            pop();
        }
        else {
            while (isp[stack[top]] >= icp[token]) {
                //print_token(pop());
                tmp[idx++] = PtoC(pop());
            }
            push(token);
        }
    }
    while ((token = pop()) != eos) {
        //print_token(token);
        tmp[idx++] = PtoC(token);
    }
    printf("Postfix: ");
    for (i = 0; i < idx; i++) 
        printf("%c", tmp[i]);
    printf("\n");
    tmp[idx] = '\n';
    strcpy(expr, tmp);
}

void print_token(precedence token) {
    switch (token)
    {
    case plus: printf("+"); break;
    case minus: printf("-"); break;
    case divide: printf("/"); break;
    case times: printf("*"); break;
    case mod: printf("%%"); break;
    case eos: printf("eos"); break;
    default: printf("fuck off");
    }
}

char PtoC(precedence token) {
    switch (token)
    {
    //case lparen: return '(';
    case plus: return '+';
    case minus: return '-';
    case divide: return '/';
    case times: return '*';
    case mod: return '%';
    case eos: return ' ';
    default: printf("fuck off");
    }
}
