// 파일에서 숫자 두개씩 읽어서 두 개가 서로소인지 아닌지 판별하는 문제
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef enum{False, True}Boolean;

Boolean prime(int x, int y) {
	if (x == 1 || y == 1) 
		return True;
	else if (x != 1 && y != 1) {
		if (x == y)
			return False;
		else if (x < y)
			return prime(x, y - x);
		else
			return prime(x - y, y);
	}
}

void main() {
	FILE* fp = fopen("in1.txt", "r");
	int a, b;
	while (!feof(fp)) {
		fscanf(fp, "%d %d", &a, &b);
		printf("%d, %d:º≠∑Œº“ ", a, b); //이게 서로소입니다 아닙니다 .. 뭐 이런 거였더인듯
		if (prime(a, b) == False)
			printf("æ∆¥‘");
		printf("\n");
	}
	fclose(fp);
}
