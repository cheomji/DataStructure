// 큐 구현을 잘못해서 한참 헤맸다 .... ㅂㅅ
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct Tree* treePointer;
typedef struct Tree {
	char data;
	treePointer leftChild, rightChild;
};

treePointer queue[MAX];
int front, rear;

treePointer createNode(char data);
treePointer createTree(char ch);
void addq(treePointer data);
treePointer deleteq();
void inorder(treePointer ptr);
void preorder(treePointer ptr);
void postorder(treePointer ptr);
void levelorder(treePointer ptr);

void main() {
	char ch;
	treePointer root;
	printf("Input character:");
	scanf("%c", &ch);
	root = createTree(ch);
	printf("level order:");
	levelorder(root);
	printf("\ninorder:");
	inorder(root);
	printf("\npreorder:");
	preorder(root);
	printf("\npostorder:");
	postorder(root);
}

treePointer createNode(char data) {
	treePointer temp = (treePointer)malloc(sizeof(*temp));
	temp->leftChild = NULL;
	temp->rightChild = NULL;
	temp->data = data;
	return temp;
}
treePointer createTree(char ch) {
	char ptr = 'a';
	treePointer cur, root, tmp;
	root = createNode(ptr);
	addq(root);
	while (1) {
		cur = deleteq();
		if (!cur) break;
		if (ptr == ch)
			break;
		tmp = createNode(++ptr);
		addq(tmp);
		cur->leftChild = tmp;

		if (ptr == ch)
			break;
		tmp = createNode(++ptr);
		addq(tmp);
		cur->rightChild = tmp;
	}
	return root;
}
void addq(treePointer data) {
	if (rear == MAX - 1) {
		printf("full");
		return;
	}
	queue[++rear] = data;
}
treePointer deleteq() {
	if (front == rear) {
		return NULL;
	}
	return queue[++front];
}
void inorder(treePointer ptr) {
	if (ptr) {
		inorder(ptr->leftChild);
		printf("%3c", ptr->data);
		inorder(ptr->rightChild);
	}
}
void preorder(treePointer ptr) {
	if (ptr) {
		printf("%3c", ptr->data);
		preorder(ptr->leftChild);
		preorder(ptr->rightChild);
	}
}
void postorder(treePointer ptr) {
	if (ptr) {
		postorder(ptr->leftChild);
		postorder(ptr->rightChild);
		printf("%3c", ptr->data);
	}
}
void levelorder(treePointer ptr) {
	front = rear = 0;
	if (!ptr) return;
	addq(ptr);
	for (;;) {
		ptr = deleteq();
		if (ptr) {
			printf("%3c", ptr->data);
			if (ptr->leftChild)
				addq(ptr->leftChild);
			if (ptr->rightChild)
				addq(ptr->rightChild);
		}
		else break;
	}
}
