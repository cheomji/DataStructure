#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node* listPointer;
typedef struct Node {
	int coef, exp;
	listPointer link;
}node;

void createPoly(FILE*, listPointer*);
listPointer createNode(int, int);
listPointer append(listPointer, listPointer);
void printPoly(listPointer);
listPointer polyAdd(listPointer, listPointer);
void attach(int, int, listPointer*);
void erase(listPointer*);

void main(void) {
	FILE* f1 = fopen("padd1.txt", "r"), * f2 = fopen("padd2.txt", "r");
	listPointer head1 = NULL, head2 = NULL, head3 = NULL;

	createPoly(f1, &head1);
	printf("%10s", "poly A:");
	printPoly(head1);

	createPoly(f2, &head2);
	printf("%10s", "poly B:");
	printPoly(head2);

	fclose(f1), fclose(f2);

	head3 = polyAdd(head1, head2);
	printf("%10s", "poly (A+B):");
	printPoly(head3);

	erase(&head1);
	erase(&head2);
	erase(&head3);

	printf("\nafter erasing...\n");

	printPoly(head1);
	printPoly(head2);
	printPoly(head3);
}

void createPoly(FILE* fp, listPointer* h) {
	int coef, exp;
	listPointer cur;
	while (!feof(fp)) {
		fscanf(fp, "%d %d", &coef, &exp);
		cur = createNode(coef, exp);
		*h = append(*h, cur);
	}
}
listPointer createNode(int coef, int exp) {
	listPointer cur = (node*)malloc(sizeof(node));
	cur->coef = coef;
	cur->exp = exp;
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
void printPoly(listPointer h) {
	listPointer p;
	if (!h)
		printf("empty list!");
	else 
		for (p = h; p; p = p->link)
			printf("<%3d, %3d> ", p->coef, p->exp);
	printf("\n");
}
listPointer polyAdd(listPointer a, listPointer b) {
	listPointer head = NULL, cur;
	int sum;
	cur = createNode(0, 0);
	head = cur;
	while (a && b) {
		//더 큰걸 헤드에 추가하고 커서를 옮겨 줘야 함
		if (a->exp == b->exp) {
			sum = a->coef + b->coef;
			if (sum) attach(sum, a->exp, &cur);
			a = a->link, b = b->link;
		}
		else if (a->exp > b->exp) {
			attach(a->coef, a->exp, &cur);
			a = a->link;
		}
		else {
			attach(b->coef, b->exp, &cur);
			b = b->link;
		}
	}
	for (; a; a = a->link) attach(a->coef, a->exp, &cur);
	for (; b; b = b->link) attach(b->coef, b->exp, &cur);
	//cur->link = NULL;
	listPointer temp = head;
	head = head->link;
	free(temp);
	return head;
}
void attach(int coef, int exp, listPointer* cur) {
	listPointer temp;
	temp = createNode(coef, exp);
	(*cur)->link = temp;
	*cur = temp;
}
void erase(listPointer* h) {
	listPointer temp;
	while (*h) {
		temp = *h;
		*h = (*h)->link;
		free(temp);
	}
}
