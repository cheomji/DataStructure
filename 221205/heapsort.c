// in.txt 파일 뇌절 ㄷㄷ
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))
#define MAX 100

typedef struct person {
	char name[20];
	int age;
}element;

void heapsort(element a[], int n);
void adjust(element a[], int root, int n);

void main(void) {
	FILE* fp = fopen("in.txt", "r");
	element tmp, arr[MAX];
	int size, i;
	fscanf(fp, "%d", &size);
	for (i = 1; i <= size; i++) {
		fscanf(fp, "%s %d", tmp.name, &tmp.age);
		arr[i] = tmp;
	}
	fclose(fp);
	printf("[Heap sort]\n");
	heapsort(arr, size);
	printf("\n");
	for (i = 1; i <= size; i++)
		printf("%8s:%4d\n", arr[i].name, arr[i].age);
}

void heapsort(element a[], int n) {
	int i, cnt = 0;
	element temp;
	for (i = n / 2; i > 0; i--) {
		printf("adjust %d: ", ++cnt);
		adjust(a, i, n);
	}
	for (i = n - 1; i > 0; i--) {		
		printf("adjust %d: ", ++cnt);
		SWAP(a[1], a[i + 1], temp);
		adjust(a, 1, i);
	}
}
void adjust(element a[], int root, int n) {
	int child = 2 * root;
	element temp = a[root];
	printf("rootkey: %d\n", temp.age);
	while (child <= n) {
		if ((child < n) && a[child].age > a[child + 1].age)
			child++;
		if (temp.age < a[child].age) break;
		else {
			a[child / 2] = a[child];
			child *= 2;
		}
	}
	a[child / 2] = temp;
}
