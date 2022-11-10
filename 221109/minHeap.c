// 텍스트파일은 이름이랑 등급 쭈루룩 적힌 파일임 Kim 5 뭐 이렇게 ㅇㅇ
// 배열로 이진트리 구현한거라 좀 헷갈림.. 배열로 하면 그냥 ㅇ배열 순서 그대로 출력해주는게 레벨오더임
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // 파이썬처럼 문자열을 바로 대입하면 안 됨. 문자열은 스트링카피 써서 대입해줘야함...
#define MAX 200
#define HEAP_FULL(n) (n == MAX-1)
#define HEAP_EMPTY(n) (!n)

typedef struct node {
	char name[10];
	int key;
}element;
element heap[MAX];
int n = 0;

void push(element item, int* n);
element pop(int* n);

void main() {
	FILE* fp = fopen("in1.txt", "r");
	char name[10];
	int score, idx;
	element tmp;
	while (!feof(fp)) {
		fscanf(fp, "%s%d", name, &score);
		strcpy(tmp.name, name);
		tmp.key = score;
		push(tmp, &n); // n은 주소를 넣기 때문에 푸쉬랑 팝 함수 내에서 값이 저절로 바뀜. 메인 함수 내에서 건드리면 안됨ㅇㅇ
	}
	fclose(fp);
	printf("Before deleting:\n");
	for (int i = 1; i <= n; i++)
		printf("[%s,%d]", heap[i].name, heap[i].key);
	printf("\n\nInput number:");
	scanf("%d", &idx);
	for (int i = 0; i < idx; i++) {
		tmp = pop(&n); // 이렇게 임시로 담아두고 해야하는데 첨에 그냥 pop().name pop().key 이렇게 써서 두번 꺼냄..;;
		printf("item(served): (%s, %d)\n", tmp.name, tmp.key);
	}
	printf("After deleting:\n");
	for (int i = 1; i <= n; i++)
		printf("[%s, %d]", heap[i].name, heap[i].key);
}

void push(element item, int* n) {
	int i;
	if (HEAP_FULL(*n)) {
		printf("Heap Full\n");
		exit(EXIT_FAILURE);
	}
	i = ++(*n);
	while ((i != 1) && (item.key < heap[i / 2].key)) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = item;
}
element pop(int* n) {
	int parent, child;
	element item, temp;
	if (HEAP_EMPTY(*n)) {
		printf("Heap Empty\n");
		exit(EXIT_FAILURE);
	}
	item = heap[1];
	temp = heap[(*n)--];
	parent = 1;
	child = 2;
	while (child <= *n) { // 자식 노드가 하나만 있을 경우도 계산해주기 위해 
		if ((child < *n) && (heap[child].key > heap[child + 1].key)) // 더 작은 노드로 커서를 옮겨줌. 첫번째 조건에 등호가 빠진 이유는 ++했을 때 빈 노드를 가리키면 안되기 때문.
			child++;
		if (temp.key <= heap[child].key) break; // 젤 마지막 노드가 현재 child 커서 노드보다 작으면 빠져나와서 부모노드에 젤 마지막 노드 값 넣어줌 (minheap이니까 더 작은걸 부모노드에 넣어야 함)
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	return item;
}
