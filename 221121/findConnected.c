// finding connected component
// 이것도 교수님 코드 .. 걍 사용하면 됨. 입력이 인접행렬이란 것만 다름.  
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef enum { False, True } Boolean;
int** matrix;
int visited[100];
int size;
int queue[100];
int front, rear;

void addq(int data) {
	if (rear >= 99) {
		printf("queue full");
		exit(EXIT_FAILURE);
	}
	queue[++rear] = data;
}
int deleteq() {
	if (front == rear) {
		printf("queue empty");
		exit(EXIT_FAILURE);
	}
	return queue[++front];
}
void dfs(int n) {
	visited[n] = True;
	printf("%4d", n);
	for (int i = 0; i < size; i++) {
		if (matrix[n][i])
			if (!visited[i])
				dfs(i);
	}
}
void bfs(int n) {
	int m;
	front = rear = -1;
	printf("%4d", n);
	visited[n] = True;
	addq(n);
	while (front != rear) {
		m = deleteq();
		for (int i = 0; i < size; i++) {
			if (matrix[m][i]) {
				if (!visited[i]) {
					printf("%4d", i);
					addq(i);
					visited[i] = True;
				}
			}
		}
	}
}

void main() {
	FILE* fp = fopen("in.txt", "r");
	int i, n, input[100], cnt = 0;

	fscanf(fp, "%d", &size);
	matrix = (int**)calloc(size, sizeof(int*));
	for (i = 0; i < size; i++)
		matrix[i] = (int*)calloc(size, sizeof(int));
	for (i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			fscanf(fp, "%d", &matrix[i][j]);
	fclose(fp);

	printf("by DFS\n");
	for (i = 0; i < size; i++)
		if (!visited[i]) {
			printf("Compponent #%d", ++cnt);
			dfs(i);
			printf("\n");
		}
	for (int i = 0; i < 100; i++)
		visited[i] = False;
	printf("\nby BFS\n");
	for (i = 0; i < size; i++)
		if (!visited[i]) {
			printf("Compponent #%d", ++cnt);
			bfs(i);
			printf("\n");
		}

	for (i = 0; i < size; i++)
		free(matrix[i]);
	free(matrix);
}
