//하 개그지같은거 이거 mark 초기화를 해줘야됐네;; 동작순서 일일이 생각해보다가 깨달음
//메인함수 기준으로 함수가 돌아가는 순서를 잘 알아야함
//확실히 전역변수가 많으니까 헷갈림... 웬만하면 지역변수 쓰고 함수호출할때는 주소를 넘겨주자
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
	short int row, col, dir;
}element;
typedef struct {
	short int vert, horiz;
}offsets;
typedef enum { False, True }Boolean;
typedef enum { North, East, South, West }Direction;

element stack[MAX];
offsets move[4];
int maze[MAX][MAX], mark[MAX][MAX];
int ROW, COL, s_row, s_col, f_row, f_col;
int top;

void createMaze(FILE* fp);
void printMaze();
void push(element input);
element pop();
void path();

void printStack() {
	for (int i = 0; i <= top; i++)
		printf("> %d %d\n", stack[i].row, stack[i].col);
}

void main() {
	FILE* f1 = fopen("maze1.txt", "r"), * f2 = fopen("maze2.txt", "r"), * f3 = fopen("maze3.txt", "r"), * f4 = fopen("maze4.txt", "r");
	move[North].vert = -1, move[East].horiz = 1, move[South].vert = 1, move[West].horiz = -1;
	
	createMaze(f1);
	fclose(f1);
	printMaze();
	path();
	printf("\n");

	createMaze(f2);
	fclose(f2);
	printMaze();
	path();
	printStack();
	printf("\n");

	createMaze(f3);
	fclose(f3);
	printMaze();
	path();
	printStack();
	printf("\n");

	createMaze(f4);
	fclose(f4);
	printMaze();
	path();
}

void createMaze(FILE* fp) {
	int i, j;
	fscanf(fp, "%d %d", &ROW, &COL);
	for (i = 0; i < ROW + 2; i++) {
		maze[i][0] = 1;
		maze[i][COL + 1] = 1;
	}
	for (i = 0; i < COL + 2; i++) {
		maze[0][i] = 1;
		maze[ROW + 1][i] = 1;
	}
	for (i = 1; i <= ROW; i++) 
		for (j = 1; j <= COL; j++) 
			fscanf(fp, "%d", &maze[i][j]);
	fscanf(fp, "%d %d %d %d", &s_row, &s_col, &f_row, &f_col);
	s_row++, s_col++, f_row++, f_col++;
}
void printMaze() {
	int i, j;
	printf("MAZE\n");
	for (i = 1; i <= ROW; i++){
		for (j = 1; j <= COL; j++)
			printf("%3d", maze[i][j]);
		printf("\n");
	}
}
void push(element input) {
	if (top >= MAX - 1) {
		printf("stack full");
		return;
	}
	stack[++top] = input;
}
element pop() {
	return stack[top--];
}
void path() {
	int i, j, row, col, nextRow, nextCol, dir;
	Boolean found = False;
	element position;
	for (i = 1; i <= ROW; i++)
		for (j = 1; j <= COL; j++)
			mark[i][j] = 0;
	mark[s_row][s_col] = 1, top = 0;
	stack[top].row = s_row, stack[top].col = s_col, stack[top].dir = North;
	
	while (top > -1 && !found) {
		position = pop();
		row = position.row, col = position.col, dir = position.dir;
		//printf("%d ", top);
		while (dir < 4 && !found) {
			nextRow = row + move[dir].vert, nextCol = col + move[dir].horiz;
			if (nextRow == f_row && nextCol == f_col)
				found = True;
			else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol]) {
				mark[nextRow][nextCol] = 1;
				position.row = row, position.col = col, position.dir = ++dir;
				push(position);
				row = nextRow, col = nextCol, dir = North;
			}
			else ++dir;
		}
	}

	if (found) {
		for (i = 0; i <= top; i++)
			maze[stack[i].row][stack[i].col] = 10;
		printf("The path is:\n");
		for (i = 1; i <= ROW; i++) {
			for (j = 1; j <= COL; j++) {
				if (i == s_row && j == s_col)
					printf("  S");
				else if (maze[i][j] == 10)
					printf("  X");
				else if (i == row && j == col)
					printf("  X");
				else if (i == f_row && j == f_col)
					printf("  F");
				else
					printf("%3d", maze[i][j]);
			}
			printf("\n");
		}
	}
	else {
		printf("No path!\n");
		for (i = 1; i <= ROW; i++) {
			for (j = 1; j <= COL; j++) {
				if (i == s_row && j == s_col)
					printf("  S");
				else if (i == f_row && j == f_col)
					printf("  F");
				else
					printf("%3d", maze[i][j]);
			}
			printf("\n");
		}
	}
	//printStack();
	int idx = top;
	for (i = 0; i <= idx; i++)
		pop();
}
