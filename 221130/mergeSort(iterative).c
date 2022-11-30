#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct person {
	int age;
	char name[20];
}element;

void merge(element initList[], element mergedList[], int i, int m, int n);
void mergePass(element initList[], element mergedList[], int n, int s);
void mergeSort(element d[], int n);
void printList(element d[], int size);

void main() {
	FILE* fp = fopen("in.txt", "r");
	element tmp, arr[MAX], extra[MAX];
	int size, s = 1;
	fscanf(fp, "%d", &size);
	for (int i = 1; i <= size; i++) {
		fscanf(fp, "%s %d", tmp.name, &tmp.age);
		arr[i] = tmp;
	}
	fclose(fp);

	printf("[Iterative merge sort]\n");
	mergeSort(arr, size);
	printList(arr, size);
}
void merge(element initList[], element mergedList[], int i, int m, int n) {
	int j = m + 1, k = i;
	while (i <= m && j <= n) {
		if (initList[i].age >= initList[j].age)
			mergedList[k++] = initList[i++];
		else
			mergedList[k++] = initList[j++];
	}
	if (i > m)
		for (int x = j; x <= n; x++)
			mergedList[x] = initList[x];
	else
		for (int x = i; x <= m; x++)
			mergedList[k + x - i] = initList[x];
}
void mergePass(element initList[], element mergedList[], int n, int s) {
	int i, j;
	for (i = 1; i <= n - 2 * s + 1; i += 2 * s)
		merge(initList, mergedList, i, i + s - 1, i + 2 * s - 1);
	if (i + s - 1 < n)
		merge(initList, mergedList, i, i + s - 1, n);
	else
		for (j = i; j <= n; j++)
			mergedList[j] = initList[j];
}
void mergeSort(element d[], int n) {
	int s = 1;
	element extra[MAX];
	while (s < n) {
		mergePass(d, extra, n, s);
		printList(d, s);
		printf("--------------------\n");
		s *= 2;
		mergePass(extra, d, n, s);
		printList(d, s);
		printf("--------------------\n");
		s *= 2;
	}
}
void printList(element d[], int size) {
	for (int i = 1; i <= size; i++)
		printf("%10s:%4d\n", d[i].name, d[i].age);
}
