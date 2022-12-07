#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))
#define MAX 100

typedef struct person {
	char name[20];
	int age;
}element;

void recursiveMerge(element a[], int left, int right);
void listMerge(element a[], int left, int mid, int right);

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
	printf("[after merge sort]\n");
	recursiveMerge(arr, 1, size);
	printf("\n");
	for (i = 1; i <= size; i++)
		printf("%8s:%4d\n", arr[i].name, arr[i].age);
}

void recursiveMerge(element a[], int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;
		recursiveMerge(a, left, mid);
		recursiveMerge(a, mid + 1, right);
		listMerge(a, left, mid, right);
	}
}
void listMerge(element a[], int left, int mid, int right) {
	int idx1 = left, idx2 = mid + 1, cnt = left;
	element temp[MAX];

	while (idx1 <= mid && idx2 <= right) {
		if (a[idx1].age <= a[idx2].age)
			temp[cnt++] = a[idx1++];
		else
			temp[cnt++] = a[idx2++];
	}
	while (idx1 <= mid)
		temp[cnt++] = a[idx1++];
	while (idx2 <= right)
		temp[cnt++] = a[idx2++];

	for (int i = left; i <= right; i++)
		a[i] = temp[i];
}
