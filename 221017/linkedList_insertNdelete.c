/*
in3은 오리지널 연결리스트
in4 랑 in5는 삽입 혹은 삭제할 수들 적어논거
짝수면 삽입, 홀수면 삭제
*/
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
listPointer insertNode(listPointer, int);
listPointer deletetNode(listPointer, int);

void main(void) {
	FILE* f1 = fopen("in3.txt", "r"), * f2 = fopen("in4.txt", "r"), * f3 = fopen("in5.txt", "r");
	listPointer L1 = NULL, L2 = NULL, L3 = NULL, L1_copy = NULL, cur;
	int input;
	printf("[original]\n");
	L1 = createList(f1, L1);
	printList(L1);
	fclose(f1);

	listPointer p = L1;
	while (p) {
		input = p->data;
		cur = createNode(input);
		L1_copy = appendNode(L1_copy, cur);
		p = p->link;
	}

	while (fscanf(f2, "%d", &input) != EOF) {
		if (input % 2) {
			//odd
			printf("Delete %d==>", input);
			L1 = deletetNode(L1, input);
		}
		else {
			//even
			printf("Insert %d==>", input);
			L1 = insertNode(L1, input);
		}
		printList(L1);
	}
	fclose(f2);

	//printList(L1_copy);
	printf("\n");
	while (fscanf(f3, "%d", &input) != EOF) {
		if (input % 2) {
			//odd
			printf("Delete %d==>", input);
			L1_copy = deletetNode(L1_copy, input);
		}
		else {
			//even
			printf("Insert %d==>", input);
			L1_copy = insertNode(L1_copy, input);
		}
		printList(L1_copy);
	}
	fclose(f3);
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
	while (p) {
		printf("%3d", p->data);
		p = p->link;
	}
	printf("\n");
}
listPointer insertNode(listPointer head, int input) {
	listPointer p = head, q = NULL;
	listPointer cur = createNode(input);
	if (p->data > input) {
		cur->link = p;
		head = cur;
	}
	else {
		while (p) {
			if (p->data > input) {
				cur->link = p;
				q->link = cur;
				break;
			}
			q = p;
			p = p->link;
		}
		if (!p)
			q->link = cur;
	}
	return head;
}
listPointer deletetNode(listPointer head, int input) {
	listPointer prev = NULL, cur = head;
	if (head->data == input) {
		head = head->link;
		free(cur);
	}
	else {
		prev = head;
		cur = head->link;
		while (cur) {
			if (cur->data == input) {
				prev->link = cur->link;
				free(cur);
				break;
			}
			prev = cur;
			cur = cur->link;
		}
		if (!cur)
			printf("%d æ¯¿Ω.", input);
	}
	return head;
}
