//교수님 코드는 visit 말고 out 씀. 이건 논리 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 24

typedef struct node* nodePointer;
typedef struct node {
	int data;
	nodePointer link;
};
typedef enum { False, True }Boolean;

nodePointer seq[MAX];
Boolean visited[MAX];
nodePointer top;

void printList(int i) {
	nodePointer p;
	for (p = seq[i]; p; p = p->link)
		printf("  <%d>", p->data);
	printf("\n");
}

void main() {
	FILE* fp = fopen("e3.txt", "r");
	int n, x, y;
	nodePointer p, tmp;

	fscanf(fp, "%d", &n);
	while (!feof(fp)) {
		fscanf(fp, "%d %d", &x, &y);
		p = (nodePointer)malloc(sizeof(*p));
		p->data = y, p->link = seq[x], seq[x] = p;
		p = (nodePointer)malloc(sizeof(*p));
		p->data = x, p->link = seq[y], seq[y] = p;
	}
	fclose(fp);
	for (int i = 0; i <= n; i++) {
		printf("[%d]", i);
		printList(i);
	}

	for (int i = 0; i <= n; i++) {
		if (!visited[i]) {
			printf("\nNew class:%4d", i);
			visited[i] = True;
			p = seq[i], top = NULL;

			for(;;) {
				
				while (p) {
					x = p->data;
					if (!visited[x]) {
						printf("%4d", x);
						visited[x] = True;
						tmp = p->link, p->link = top, top = p, p = tmp;
					}
					else p = p->link;
				}
				if (!top) break;
				p = seq[top->data], top = top->link;
			}
		}
	}
	printf("\n");
}
