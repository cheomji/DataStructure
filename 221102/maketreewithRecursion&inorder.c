#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* treePointer;
typedef struct node {
	int data;
	treePointer leftChild, rightChild;
};

treePointer makeTree(int data) {
	treePointer h = NULL;

	if (data < 1000) {
		h = (treePointer)malloc(sizeof(*h));
		h->data = data;
		h->leftChild = makeTree(data * data);
		h->rightChild = makeTree(data * 5);
	}
	
	return h;
}

void inorder(treePointer p) {
	if (p) {
		inorder(p->leftChild);
		printf("%d ", p->data);
		inorder(p->rightChild);
	}
}

void main() {
	treePointer root;
	int n;
	printf("Input number: ");
	scanf("%d", &n);
	root = makeTree(n);
	inorder(root);
}
