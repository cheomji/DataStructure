// memory allocate 해놓은 거 free시키는 게 어려웟음ㅇㅇ 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node* LINK;
typedef struct Node {
	int vertex;
	LINK next;
}node;

LINK append(LINK head, int input) {
	LINK tmp = (LINK)malloc(sizeof(node));
	tmp->vertex = input;
	tmp->next = NULL;
	if (!head)
		head = tmp;
	else {
		tmp->next = head;
		head = tmp;
	}
	return head;
}
void printList(LINK head) {
	LINK p = head;
	for (; p; p = p->next)
		printf("%3d", p->vertex);
	printf("\n");
}
int count(LINK head) {
	int cnt = 0;
	for (; head; head = head->next)
		cnt++;
	return cnt;
}
void freeList(LINK* head) {
	LINK p = *head, tmp;
	while (p) {
		tmp = p;
		p = p->next;
		free(tmp);
	} // 이 부분 서순 !!!!!!!!!! 생각을 좀 하고 코딩을 하렴
}

void main() {
	FILE* fp = fopen("in.txt", "r");
	int n, in1, in2, i;
	int** Amatrix;
	LINK* head, *invhead;
	fscanf(fp, "%d", &n);

	Amatrix = (int**)calloc(n, sizeof(int*));
	for (i = 0; i < n; i++)
		Amatrix[i] = (int*)calloc(n, sizeof(int));
	
	head = (LINK*)calloc(n, sizeof(LINK));
	invhead = (LINK*)calloc(n, sizeof(LINK));

	while (!feof(fp)) {
		fscanf(fp, "%d %d", &in1, &in2);
		Amatrix[in1][in2] = 1;
		head[in1] = append(head[in1], in2);
		invhead[in2] = append(invhead[in2], in1); 
	}
	fclose(fp);

	printf("(1) Adjacency matrix\n");
	for (i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			printf("%3d", Amatrix[i][j]);
		printf("\n");
	}

	printf("(2) Linked adjacency list\n");
	for (i = 0; i < n; i++) {
		printf("[%2d]", i);
		printList(head[i]);
	}

	printf("(3) Inverse adjacency list\n");
	for (i = 0; i < n; i++) {
		printf("[%2d]", i);
		printList(invhead[i]);
	}

	printf("(4) In degree\n");
	for (i = 0; i < n; i++)
		printf("[%2d]%2d\n", i, count(invhead[i]));

	printf("(5) Out degree\n");
	for (i = 0; i < n; i++)
		printf("[%2d]%2d\n", i, count(head[i]));

	for (i = 0; i < n; i++)
		free(Amatrix[i]);
	free(Amatrix);

	for (i = 0; i < n; i++)
		freeList(&head[i]);
	free(head);

	for (i = 0; i < n; i++)
		freeList(&invhead[i]);
	free(invhead);
}
