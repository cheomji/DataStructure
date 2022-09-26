/*예제파일
a2.txt
0 0 0 0 1 2 3 0 0
0 1 0 0 0 0 0 1 10
2 0 0 3 0 0 4 0 0
5 0 0 0 6 0 0 0 0
0 7 0 0 0 0 8 0 0
b2.txt
1 0 0 0 2 0 0 0 0
-2 0 0 -3 0 0 -4 0 0
0 0 0 5 0 0 0 5 0
-7 -8 0 0 0 0 0 0 10
1 0 0 0 11 0 0 0 20
*/
//와일문 안에서 조건 처리하는거 너무 지저분한데 어떻게해야 더 나을지 생각이안남... 이게최선임 ㅋㅋ 특히 a랑 b 행이 다를때 처리하는거...
//cnt 초기값을 0으로 해놓고 계속 왜안되지 이러고있었음ㅋㅋ
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define max 101

typedef struct Term {
	int row, col, val;
}term;

int createMatrix(FILE* f, term** d);
void printMatrix(term d[]);

void main() {
	FILE* f1 = fopen("a2.txt", "r"), * f2 = fopen("b2.txt", "r");
	term* a = (term*)malloc(max * sizeof(term)), * b = (term*)malloc(max * sizeof(term)), c[max];
	int i = 1, j = 1, cnt = 1;
	a[0].row = 5, a[0].col = 9;
	a[0].val = createMatrix(f1, &a); fclose(f1);
	b[0].row = 5, b[0].col = 9;
	b[0].val = createMatrix(f2, &b); fclose(f2);

	if (a[0].val == -1 || b[0].val == -1) {
		printf("cannot open the file");
		exit(0);
	}

	c[0].row = 5, c[0].col = 9;
	while (i <= a[0].val && j <= b[0].val) {
		//printf("%d번 %d %d\n", cnt, i, j);
		if (a[i].row == b[j].row) {
			if (a[i].col == b[j].col) {
				c[cnt].row = a[i].row, c[cnt].col = a[i].col;
				c[cnt].val = a[i++].val - b[j++].val;
			}
			else if (a[i].col > b[j].col) {
				c[cnt].row = b[j].row, c[cnt].col = b[j].col;
				c[cnt].val = -b[j++].val;
			}
			else {
				c[cnt].row = a[i].row, c[cnt].col = a[i].col;
				c[cnt].val = a[i++].val;
			}
			cnt++;
		}
		else if (a[i].row > b[j].row) {
			while (1) {
				if (b[j].row != b[j + 1].row) {
					c[cnt].row = b[j].row, c[cnt].col = b[j].col;
					c[cnt++].val = -b[j++].val;
					break;
				}
				c[cnt].row = b[j].row, c[cnt].col = b[j].col;
				c[cnt++].val = -b[j++].val;
			}
		}
		
		else {
			while (1) {
				if (a[i].row != a[i + 1].row) {
					c[cnt].row = a[i].row, c[cnt].col = a[i].col;
					c[cnt++].val = a[i++].val;
					break;
				}
				c[cnt].row = a[i].row, c[cnt].col = a[i].col;
				c[cnt++].val = a[i++].val;
			}
		}
	}
	
	for (; i <= a[0].val; i++) {
		c[cnt].row = a[i].row, c[cnt].col = a[i].col;
		c[cnt++].val = a[i].val;
	}
	for (; j <= b[0].val; j++) {
		c[cnt].row = b[j].row, c[cnt].col = b[j].col;
		c[cnt++].val = -b[j].val;
	}
	c[0].val = cnt - 1;
	//printf("%d ???", cnt);
	printMatrix(c);

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
