// delete하는 부분 망함 ㅋㅋ 걍 내긴했길래 올림
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct NODE* treePointer;
typedef struct NODE {
	int data;
	treePointer leftChild, rightChild;
}node;

void insert(treePointer* root, int input);
void Delete(treePointer* root, int input);
treePointer modifiedSearch(treePointer tree, int searchnum);
void inorder(treePointer tree);
treePointer leftMax(treePointer cur);

void main() {
	FILE* fp = fopen("in2.txt", "r");
	treePointer root = NULL;
	int n;
	while (fscanf(fp, "%d", &n) != EOF) 
		insert(&root, n);
	
	fclose(fp);
	printf("Binary search tree(Inorder):\n");
	inorder(root);
	printf("\n");
	while (1) {
		printf("Delete number: ");
		scanf("%d", &n);
		if (n < 0) {
			printf("Quit.");
			break;
		}
		Delete(&root, n);
		inorder(root);
		printf("\n");
	}
}
void Delete(treePointer* root, int input) {
	treePointer cur = *root, parent = *root, tmp, tmp2;
	while (cur) {
		if (input == cur->data) break;
		if (input < cur->data) {
			parent = cur;
			cur = cur->leftChild;
		}
		else {
			parent = cur;
			cur = cur->rightChild;
		}
	}

	if (!cur->leftChild) {
		tmp = cur->rightChild;
		if (cur->data < parent->data) 
			parent->leftChild = tmp;
		else
			parent->rightChild = tmp;
		free(cur);
	}
	else if (!cur->rightChild) {
		tmp = cur->leftChild;
		if (cur->data < parent->data)
			parent->leftChild = tmp;
		else
			parent->rightChild = tmp;
		free(cur);
	}
	else {
		tmp = leftMax(cur->leftChild);
		cur->data = tmp->data;
		/*while (tmp) {
			tmp2 = leftMax(tmp);
			if (tmp2 == NULL) {
				tmp = NULL;
			}
			tmp->data = tmp2->data;
			free(tmp2);
			if (tmp->leftChild)
				tmp = tmp->rightChild;
			else if (tmp->rightChild)
				tmp = tmp->leftChild;
		}*/
		tmp = NULL;
	}
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
void inorder(treePointer tree) {
	if (tree) {
		inorder(tree->leftChild);
		printf("%4d", tree->data);
		inorder(tree->rightChild);
	}
}
treePointer leftMax(treePointer cur) {
	treePointer q = NULL;
	for (; cur; q = cur, cur = cur->rightChild);
	return q;
}
