// 인접리스트가 아니라 인접행렬을 입력으로 사용 ㅇㅇ. 원리는 똑같음
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

	while (1) {
		scanf("%d", &n);
		input[cnt++] = n;
		if (n < 0) break;
	}
	printf("[DFS]\n");
	for (i = 0; i < cnt; i++) {
		printf("Starting number:%d\n", input[i]);
		if (input[i] < 0) break;
		for (int i = 0; i < 100; i++)
			visited[i] = False;
		dfs(input[i]);
		printf("\n");
	}
	printf("\n[BFS]\n");
	for (i = 0; i < cnt; i++) {
		printf("Starting number:%d\n", input[i]);
		if (input[i] < 0) break;
		for (int i = 0; i < 100; i++)
			visited[i] = False;
		bfs(input[i]);
		printf("\n");
	}

	for (i = 0; i < size; i++)
		free(matrix[i]);
	free(matrix);
}
