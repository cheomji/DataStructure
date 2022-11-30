#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct person {
	int age;
	char name[20];
}element;

int mergeSort(element a[], int link[], int left, int right);
int listMerge(element a[], int link[], int start1, int start2);

void main() {
	FILE* fp = fopen("in.txt", "r");
	element tmp, arr[MAX], extra[MAX];
	int size, link[MAX];
	fscanf(fp, "%d", &size);
	for (int i = 1; i <= size; i++) {
		fscanf(fp, "%s %d", tmp.name, &tmp.age);
		arr[i] = tmp;
	}
	fclose(fp);
	for (int i = 0; i < MAX; i++)
		link[i] = 0;
	mergeSort(arr, link, 1, size);
	printf("\n");
	for (int i = 0; link[i] != 0; i = link[i]) 
		printf("%8s:%3d\n", arr[link[i]].name, arr[link[i]].age);
}

int mergeSort(element a[], int link[], int left, int right) {
	if (left >= right) return left;
	int mid = (left + right) / 2;
	printf("%8s:%3d\n", "mid", mid);
	return listMerge(a, link, mergeSort(a, link, left, mid), mergeSort(a, link, mid + 1, right));
}
int listMerge(element a[], int link[], int start1, int start2) {
	int last1, last2, lastResult = 0;
	for (last1 = start1, last2 = start2; last1 && last2;) {
		if (a[last1].age >= a[last2].age) {
			link[lastResult] = last1;
			lastResult = last1, last1 = link[last1];
		}
		else {
			link[lastResult] = last2;
			lastResult = last2, last2 = link[last2];
		}
	}
	if (last1 == 0) link[lastResult] = last2;
	else link[lastResult] = last1;
	return link[0];
}
