// union find 이거 완전히 통용되게 안하고 ㅈㄴ 야매로 해서 코드 개드러움
// 연결리스트 안 썼고 그냥 배열로 함 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define True 1
#define False 0
#define MAX 100

typedef struct EDGE {
	int x, y;
	int cost;
}edge;

int parent[MAX];

int Find(int i) {
	while (parent[i] != i) 
		i = parent[i];
	return i;
}
void Union(int i, int j) {
	parent[i] = j;
}

void main() {
	FILE* fp = fopen("in.txt", "r");
	int size, Eidx = 0, Tidx = 0, i, j, matrix[MAX][MAX], Eptr = 0;
	edge E[MAX], T[MAX];
	fscanf(fp, "%d", &size);
	for (i = 0; i < size; i++) 
		for (j = 0; j < size; j++) 
			fscanf(fp, "%d", &matrix[i][j]);
	fclose(fp);
	for (i = 0; i < size; i++)
		for (j = i + 1; j < size; j++)
			if (matrix[i][j])
				E[Eidx].x = i, E[Eidx].y = j, E[Eidx++].cost = matrix[i][j];
	for (i = 0; i < Eidx; i++)
		for (j = i; j < Eidx; j++) 
			if (E[i].cost > E[j].cost) {
				edge tmp = E[i];
				E[i] = E[j];
				E[j] = tmp;
			}
	printf("(edge):weight\n");
	for (i = 0; i < size; i++)
		parent[i] = i;
	while (Tidx < size - 1 && Eptr != Eidx) {
		edge e = E[Eptr++];
		int xpar = Find(e.x);
		int ypar = Find(e.y);
		if (xpar != ypar) {
			T[Tidx++] = e;
			if (xpar == e.x && ypar == e.y) 
				Union(e.x, e.y);
			else if (xpar != e.x && ypar == e.y) 
				Union(e.y, xpar);
			else if (xpar == e.x && ypar != e.y) 
				Union(e.x, ypar);
		}
	}
	if (Tidx < size - 1)
		printf("No spanning tree\n");
	else {
		for (i = 0; i < Tidx; i++)
			printf("(%d,%2d):%3d\n", T[i].x, T[i].y, T[i].cost);
	}
}
