//!!!!!!!!!!!!!!!!!!!!!초기화 주의 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
int len(listPointer);
listPointer polyMult(listPointer, listPointer);

void main(void) {
	FILE* f1 = fopen("in1.txt", "r"), * f2 = fopen("in2.txt", "r");
	listPointer head1 = NULL, head2 = NULL, head3 = NULL;

	createPoly(f1, &head1);
	printf("[poly 1]\n");
	printPoly(head1);

	createPoly(f2, &head2);
	printf("[poly 2]\n");
	printPoly(head2);

	fclose(f1), fclose(f2);

	printf("[poly1 * poly 2]\n");
	head3 = polyMult(head1, head2);
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
			printf("(%2d,%2d) ", p->coef, p->exp);
	printf("\n");
}
listPointer polyAdd(listPointer a, listPointer b) {
	listPointer head = NULL, cur;
	int sum;
	cur = createNode(0, 0);
	head = cur;
	if (!a)
		return b;
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
int len(listPointer h) {
	listPointer p = h;
	int cnt = 0;
	for (; p; p = p->link)
		cnt++;
	return cnt;
}
listPointer polyMult(listPointer a, listPointer b) {
	listPointer* auxpoly, p = a, q = b, polysum = NULL;
	int size = len(a), i = 0, coef;
	auxpoly = (listPointer*)calloc(size, sizeof(listPointer));//아 말록으로 해서 초기화가 안됐었음. 초기화해서 넣어야함
	for (p = a; p; p = p->link) {
		for (q = b; q; q = q->link) {
			listPointer temp = createNode(p->coef * q->coef, p->exp + q->exp);
			auxpoly[i] = append(auxpoly[i], temp);
		}
		i++;
	}
	for (int j = 0; j < size; j++) {
		polysum = polyAdd(polysum, auxpoly[j]);
	}
	return polysum;
}
