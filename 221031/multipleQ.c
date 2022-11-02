// 연결리스트로 큐 구현하기
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_Q 10

typedef int element;
typedef struct queue* queuePointer;
typedef struct queue {
	element data;
	queuePointer link;
}Queue;
typedef enum {X, Y, Z, W} Rides;
queuePointer front[MAX_Q], rear[MAX_Q];

void addq(int i, int item);
element deleteq(int i);
void printq(int i);
Rides toRide(char ch);

void main() {
	FILE* fp = fopen("in.txt", "r");
	int n;
	char ch;
	while (!feof(fp)) {
		fscanf(fp, "%c ", &ch);
		if (ch == 'D') {
			fscanf(fp, "%c ", &ch);
			printf("(Delete %c) ==> ", ch);
			deleteq(toRide(ch));
		}
		else {
			fscanf(fp, "%d ", &n);
			printf("(Insert %c %d) ==> %c:", ch, n, ch);
			addq(toRide(ch), n);
		}
		printq(toRide(ch));
	}
	fclose(fp);
}

void addq(int i, int item) {
	queuePointer tmp = (queuePointer)malloc(sizeof(Queue));
	tmp->data = item;
	tmp->link = NULL;
	if (front[i])
		rear[i]->link = tmp;
	else
		front[i] = tmp;
	rear[i] = tmp;
}
element deleteq(int i) {
	if (!front[i]) {
		printf("Waiting. ");
		return -1;
	}
	queuePointer tmp1 = front[i], tmp2;
	element item1 = tmp1->data, item2;

	if (front[i] == rear[i]) {
		printf("Person %d served. ", item1);
		front[i] = NULL;
		free(tmp1);
		return item1;
	}
	else {
		tmp2 = tmp1->link;
		item2 = tmp1->link->data;
		printf("Person %d, %d served. ", item1, item2);
		front[i] = tmp2->link;
		free(tmp1), free(tmp2);
		return item2;
	}
}
void printq(int i) {
	queuePointer p;
	if (!front[i]) {
		printf("Empty");
	}
	else {
		p = front[i];
		for (; p; p = p->link)
			printf("[%2d]", p->data);
	}
	printf("\n");
}
Rides toRide(char ch) {
	switch (ch)
	{
	case 'X': return X; break;
	case 'Y': return Y; break;
	case 'Z': return Z; break;
	case 'W': return W; break;
	default: return 100; break;
	}
}
