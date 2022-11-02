// 스택 이용해서 괄호 밖의 알파벳을 모두 출력하는 문제
// 텍스트파일은 한 줄에 하나씩 있음 예제 a(b)(c(d)ef)g(h)i ==> agi
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

//typedef enum{lparen, rparen, eos, alphabet}precedence;
typedef char element;

int top = -1;
element stack[MAX];
char exp[MAX];

void push(element item);
element pop();
void recreate();
void printstack();

void main() {
	FILE* fp = fopen("in2.txt", "r");

	while (!feof(fp)) {
		fscanf(fp, "%s", exp);
		printf("πÆ¿⁄ø≠: %s\n", exp);
		recreate();
		printf("Ω««‡∞·∞˙:");
		printstack();
		printf("\n\n");
		top = -1;
	}
	fclose(fp);
}

void push(element item) {
	if (top >= MAX - 1)
		printf("stack full");
	else
		stack[++top] = item;
}
element pop() {
	if (top == -1) {
		printf("stack empty");
		return -1;
	}
	else
		return stack[top--];
}
void recreate() {
	for (int i = 0; i < strlen(exp); i++) {
		if (exp[i] == ')') {
			while (stack[top] != '(')
				pop();
			pop();
		}
		else
			push(exp[i]);
	}
}
void printstack() {
	for (int i = 0; i <= top; i++) {
		printf("%c", stack[i]);
	}
}
