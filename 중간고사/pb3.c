// 텍스트파일에서 받아서 짝수면 헤드 뒤에 추가하고 홀수면 앞에 추가
// 그러고 최댓값이랑 최솟값 하나씩 찾아서 지우기 ㅇㅇ
// 리스트에 아무것도 없으면 그순간 엠티 출력
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct NODE* listPointer;
typedef struct NODE {
	int data;
	listPointer link;
}node;

listPointer createNode(int input);
listPointer append(listPointer h, listPointer cur);
listPointer insert(listPointer h, listPointer cur);
void printList(listPointer h);
int findmax(listPointer h);
int findmin(listPointer h);
void deleteNode(listPointer* h, int input);

void main() {
	FILE* fp = fopen("in3.txt", "r");
	int n;
	listPointer head = NULL, cur = NULL;
	while (!feof(fp)) {
		fscanf(fp, "%d", &n);
		cur = createNode(n);
		if (n % 2)
			head = append(head, cur);
		else
			head = insert(head, cur);
	}
	fclose(fp);
	printf("Original list:\n");
	printList(head);

	while (head) {
		printf("Delete min(%d) and max(%d)\n", findmin(head), findmax(head));
		deleteNode(&head, findmin(head));
		if (!head) {
			printf("empty list\n");
			break;
		}
		deleteNode(&head, findmax(head));
		printList(head);
	}
}

listPointer createNode(int input) {
	listPointer cur = (node*)malloc(sizeof(node));
	cur->data = input;
	cur->link = NULL;
	return cur;
}
listPointer append(listPointer h, listPointer cur) {
	listPointer p;
	if (!h) 
		h = cur;
	else {
		for (p = h; p->link; p = p->link);
		p->link = cur;
	}
	return h;
}
listPointer insert(listPointer h, listPointer cur) {
	listPointer p;
	if (!h)
		h = cur;
	else {
		cur->link = h;
		h = cur;
	}
	return h;
}
void printList(listPointer h) {
	listPointer p = h;
	if (!h) {
		printf("empty list");
	}
	else {
		for (;p;p = p->link)
			printf("%d ", p->data);
	}
	printf("\n");
}
int findmax(listPointer h) {
	int max = h->data;
	listPointer p = h;
	for (; p; p = p->link) {
		if (p->data > max)
			max = p->data;
	}
	return max;
}
int findmin(listPointer h) {
	int min = h->data;
	listPointer p = h;
	for (; p; p = p->link) {
		if (p->data < min)
			min = p->data;
	}
	return min;
}
void deleteNode(listPointer* h, int input) {
	listPointer p = *h, q = NULL;
	if ((*h)->data == input) {
		(*h) = (*h)->link;
		free(p);
	}
	else {
		q = (*h);
		p = (*h)->link;
		while (p) {
			if (p->data == input) {
				q->link = p->link;
				free(p);
				break;
			}
			q = p;
			p = p->link;
		}
	}
}
