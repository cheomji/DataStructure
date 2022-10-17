#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node* listPointer;
typedef struct Node {
	int data;
	listPointer link;
}node;

listPointer createList(FILE*, listPointer);
listPointer createNode(int);
listPointer appendNode(listPointer, listPointer);
void printList(listPointer);
listPointer AND(listPointer, listPointer);

void main(void) {
	FILE* f1 = fopen("in1.txt", "r"), * f2 = fopen("in2.txt", "r");
	listPointer L1 = NULL, L2 = NULL, L3 = NULL;

	printf("[in1.txt]\n");
	L1 = createList(f1, L1);
	printList(L1);
	fclose(f1);
	
	printf("[in2.txt]\n");
	L2 = createList(f2, L2);
	printList(L2);
	fclose(f2);

	printf("[in1 AND in2]\n");
	L3 = AND(L1, L2);
	printList(L3);
}

listPointer createList(FILE* fp, listPointer head) {
	int input;
	listPointer cur;
	while (fscanf(fp, "%d", &input) != EOF) {
		cur = createNode(input);
		head = appendNode(head, cur);
	}
	return head;
}
listPointer createNode(int input) {
	listPointer curr = (node*)malloc(sizeof(node));
	curr->data = input;
	curr->link = NULL;
	return curr;
}
listPointer appendNode(listPointer head, listPointer curr) {
	listPointer p;
	if (!head)
		head = curr;
	else {
		p = head;
		while (p->link)
			p = p->link;
		p->link = curr;
	}
	return head;
}
void printList(listPointer head) {
	listPointer p = head;
	if (!p) {
		printf("∞¯≈Îµ» ø¯º“∞° æ¯¿Ω.\n");
		return;
	}
	while (p) {
		printf("%3d", p->data);
		p = p->link;
	}
	printf("\n");
}
listPointer AND(listPointer head1, listPointer head2) {
	listPointer p1 = head1, p2 = head2, head3 = NULL;
	if (!p1 || !p2) return head3;
	while (p1 && p2) {
		if (p1->data == p2->data) {
			listPointer cur = createNode(p1->data);
			head3 = appendNode(head3, cur);
			p1 = p1->link;
			p2 = p2->link;
		}
		else if (p1->data > p2->data) 
			p2 = p2->link;
		else 
			p1 = p1->link;
	}
	return head3;
}
