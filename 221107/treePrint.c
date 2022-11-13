// 큐 구현을 잘못해서 한참 헤맸다 .... ㅂㅅ

/*
이거는 트리 구현하는 부분 실습때 너무 얼렁뚱땅 한 것 같아서 숫자 ver. 으로 다ㅅㅣ 해본 거
그뭐냐 큐는 n을 뭐 얼마를 넣든 꽉 차면 차지 절대 비지는 않으니까 큐가 비었을 때를 탈출조건으로 넣지  ㅇㅇ
#include <stdio.h>
#include <stdlib.h>
#define MAX 100
typedef struct Node* treePointer;
typedef struct Node{
    int data;
    treePointer leftChild, rightChild;
}node;
treePointer queue[MAX];
int front, rear;

treePointer createTree(int n);
void addq(treePointer element);
treePointer deleteq(void);
void createNode(treePointer *cur, int n);
void inorder(treePointer tree);

int main(int argc, const char * argv[]) {
    int n;
    treePointer root;
    scanf("%d", &n);
    root = createTree(n);
    inorder(root);
    return 0;
}
treePointer createTree(int n){
    treePointer root, tmp, cur;
    int i = 1;
    createNode(&root, i);
    addq(root);
    while (1) {
        tmp = deleteq();
        if (n < ++i) break;
        createNode(&cur, i);
        addq(cur);
        tmp->leftChild = cur;
        if (n < ++i) break;
        createNode(&cur, i);
        addq(cur);
        tmp->rightChild = cur;
    }
    return root;
}
void addq(treePointer element){
    if (rear == MAX-1){
        printf("Queue full");
        exit(EXIT_FAILURE);
    }
    queue[++rear] = element;
}
treePointer deleteq(){
    if (front == rear){
        printf("Queue empty");
        return NULL;
    }
    return queue[++front];
}
void createNode(treePointer *cur, int n){
    *cur = (treePointer)malloc(sizeof(node));
    (*cur)->data = n;
    (*cur)->leftChild = NULL;
    (*cur)->rightChild = NULL;
}
void inorder(treePointer tree){
    if (tree){
        inorder(tree->leftChild);
        printf("%d ", tree->data);
        inorder(tree->rightChild);
    }
}
*/
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
	return queue[++front]; // 이거 front++ 로 했었는데 생각해보니까 그렇게 하면 안되네 
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
