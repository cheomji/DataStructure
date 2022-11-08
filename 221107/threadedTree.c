// 보너스문제. 노가다로 thread 만들었음 그냥.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef enum {False, True}Boolean;
typedef struct Tree* treePointer;
typedef struct Tree {
	short int leftThread, rightThread;
	char data;
	treePointer leftChild, rightChild;
};

treePointer queue[MAX];
int front, rear;

treePointer createNode(char data);
treePointer insucc(treePointer tree);
void tinorder(treePointer tree);

void main() {
	treePointer root, tmp;
	tmp = createNode('A');
	tmp->leftThread = False, tmp->rightThread = False;

	root = createNode('\0');
	root->leftChild = tmp, root->rightChild = root;
	root->leftThread = False, root->rightThread = False;

	tmp = createNode('B');
	tmp->leftThread = False;
	tmp->rightChild = root->leftChild;
	root->leftChild->leftChild = tmp;

	tmp = createNode('C');
	tmp->leftChild = root;
	tmp->rightChild = root->leftChild->leftChild;
	root->leftChild->leftChild->leftChild = tmp;

	tmp = createNode('D');
	tmp->rightThread = False;
	tmp->leftChild = root->leftChild;
	root->leftChild->rightChild = tmp;

	tmp = createNode('E');
	tmp->leftChild = root->leftChild->rightChild;
	tmp->rightChild = root;
	root->leftChild->rightChild->rightChild = tmp;

	tinorder(root);
}
treePointer createNode(char data) {
	treePointer temp = (treePointer)malloc(sizeof(*temp));
	temp->leftChild = NULL;
	temp->rightChild = NULL;
	temp->leftThread = True;
	temp->rightThread = True;
	temp->data = data;
	return temp;
}
treePointer insucc(treePointer node) {
	treePointer temp;
	temp = node->rightChild;
	if (!node->rightThread)
		while (!temp->leftThread)
			temp = temp->leftChild;
	return temp;
}
void tinorder(treePointer root) {
	treePointer temp = root;
	for (;;) {
		temp = insucc(temp);
		if (temp == root) break;
		printf("%3c", temp->data);
	}
}
