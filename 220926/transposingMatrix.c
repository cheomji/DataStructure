/*예제텍스트파일
a1.txt
0 0 0 5 7 0 0
0 0 0 0 0 10 0
0 0 0 3 0 0 0
0 0 0 0 0 0 0
0 0 0 0 0 6 0
0 7 0 0 0 0 6
b1.txt
0 0 0 0 0 1 0 0 2
0 3 0 0 0 0 0 0 0
0 0 0 0 0 0 0 4 5
0 0 6 0 0 0 0 7 0
0 8 0 0 0 0 0 0 0
0 9 10 0 0 0 0 0 0
0 0 11 0 0 0 0 0 0
0 0 0 0 0 0 0 12 0
*/
//포인터 상수에는 아무것도 못 집어넣는다... 함수에 실인자로 넣어봤자 상수 값은 안바뀜!!
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define max 101

typedef struct Term {
	int row, col, val;
}term;

int createMatrix(FILE* f, term** d);
void printMatrix(term d[]);
void transpose(term** d);

void main() {
	FILE* f1 = fopen("a1.txt", "r"), * f2 = fopen("b1.txt", "r");
	term* a = (term*)malloc(max * sizeof(term)), * b = (term*)malloc(max * sizeof(term));
	a[0].row = 6, a[0].col = 7;
	a[0].val = createMatrix(f1, &a); fclose(f1);
	printf("Before Transposing Maxrix A\n");
	printMatrix(a);
	printf("\nAfter Transposing Maxrix A\n");
	transpose(&a);
	printMatrix(a);

	b[0].row = 8, b[0].col = 9;
	b[0].val = createMatrix(f2, &b); fclose(f2);
	printf("\nBefore Transposing Maxrix B\n");
	printMatrix(b);
	printf("\nAfter Transposing Maxrix B\n");
	transpose(&b);
	printMatrix(b);

	free(a), free(b);
}

int createMatrix(FILE* f, term** d) {
	int cnt = 1, row = 0, col = 0, n;
	if (!f) {
		printf("error");
		return -1;
	}
	while (fscanf(f, "%d", &n) != EOF) {
		if (n) {
			(*d)[cnt].row = row;
			(*d)[cnt].col = col;
			(*d)[cnt++].val = n;
		}
		col++;
		if (col == (*d)[0].col)
			row++, col = 0;
	}
	return cnt - 1;
}

void printMatrix(term d[]) {
	for (int i = 0; i <= d[0].val; i++)
		printf("[%3d%3d%3d]\n", d[i].row, d[i].col, d[i].val);
}

void transpose(term** d) {
	term a[max];
	for (int i = 0; i <= (*d)[0].val; i++) 
		a[i].row = (*d)[i].row, a[i].col = (*d)[i].col, a[i].val = (*d)[i].val;
	//d에 있는 값 a로 복사 후 d에 바로 전치시킨 값 때려박기
	int rowTerm[max], startPos[max];
	int i, j, numCol = a[0].col, numTerm = a[0].val;
	(*d)[0].row = numCol, (*d)[0].col = a[0].row;
	if (numTerm > 0) {
		for (i = 0; i < numCol; i++)
			rowTerm[i] = 0;
		for (i = 1; i <= numTerm; i++)
			rowTerm[a[i].col]++;
		startPos[0] = 1;
		for (i = 1; i <= numCol; i++)
			startPos[i] = startPos[i - 1] + rowTerm[i - 1];
		for (i = 1; i <= numTerm; i++) {
			j = startPos[a[i].col]++;
			(*d)[j].row = a[i].col, (*d)[j].col = a[i].row, (*d)[j].val = a[i].val;
		}
	}
}
