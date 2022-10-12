#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//요렇게 타입데프 쓰는거 손에 익혀두기
//그냥 함수 깔끔해서 이걸 기본으로 알고 쓰라고 올려봄
typedef struct Node* link;
typedef struct Node {
	int data;
	link next;
}node;

void printList(link);
link insert(link, link);
link createNode(int);

void main(void) {
	FILE* fp = fopen("in4.txt", "r");
	link head = NULL, cur;
	int input;
	while (fscanf(fp, "%d", &input) != EOF) {
		cur = createNode(input);
		head = insert(head, cur);
	}
	printList(head);
}
void printList(link h) {
	link p = h;
	while (p) {
		printf("%4d", p->data);
		p = p->next;
	}
}
link insert(link h, link cur) {
	link p = h;
	cur->next = h;
	h = cur;
}
link createNode(int input) {
	link curr = (node*)malloc(sizeof(node));
	curr->data = input;
	curr->next = NULL;
	return curr;
}
