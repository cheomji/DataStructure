// 텍스트파일은 그냥 이진탐색트리에 넣을 숫자들 주루룩 있는 거 ㅇㅇ
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct NODE* treePointer;
typedef struct NODE {
	int data;
	treePointer leftChild, rightChild;
}node;

int search(treePointer root, int searchnum);
void insert(treePointer* root, int input);
treePointer modifiedSearch(treePointer tree, int searchnum);
void postorder(treePointer tree);

void main() {
	FILE* fp = fopen("in1.txt", "r");
	treePointer root = NULL;
	int n;
	while (fscanf(fp, "%d", &n) != EOF) 
		insert(&root, n);
	fclose(fp);

	printf("Postorder traversal:\n");
	postorder(root);
	printf("\n");

	while (1) {
		printf("Input number: ");
		scanf("%d", &n);
		if (n < 0) {
			printf("Quit.");
			break;
		}
		printf("%4d: %c\n", n, search(root, n) ? 'O' : 'X');
	}
}

int search(treePointer root, int searchnum) {
	if (!root) return 0;
	if (searchnum == root->data) return 1;
	if (searchnum < root->data) return search(root->leftChild, searchnum);
	return search(root->rightChild, searchnum);
}
void insert(treePointer* root, int input) {
	treePointer ptr, tmp = modifiedSearch(*root, input);
	if (tmp || !(*root)) {
		ptr = (treePointer)malloc(sizeof(*ptr));
		ptr->data = input;
		ptr->leftChild = ptr->rightChild = NULL;

		if (*root) {
			if (input < tmp->data) tmp->leftChild = ptr;
			else tmp->rightChild = ptr;
		}
		else 
			*root = ptr;
	}
}
treePointer modifiedSearch(treePointer tree, int searchnum) {
	treePointer p = tree;
	while (tree) {
		if (searchnum == tree->data) return NULL;
		if (searchnum < tree->data) {
			p = tree;
			tree = tree->leftChild;
		}
		else {
			p = tree;
			tree = tree->rightChild;
		}
	}
	return p;
}
void postorder(treePointer tree) {
	if (tree) {
		postorder(tree->leftChild);
		postorder(tree->rightChild);
		printf("%4d", tree->data);
	}
}
