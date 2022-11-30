#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SWAP(x, y, tmp) ((tmp)=(x), (x)=(y), (y)=(tmp))

typedef struct person {
	char name[10];
	int age;
}element;

void quicksort(element d[], int left, int right) {
	int pivot, i, j;
	element temp;
	if (left < right) {
		i = left, j = right + 1;
		pivot = d[left].age;
		do {
			do i++; while (d[i].age > pivot);
			do j--; while (d[j].age < pivot);
			if (i < j) SWAP(d[i], d[j], temp);
		} while (i < j);
		SWAP(d[left], d[j], temp);
		quicksort(d, left, j - 1);
		quicksort(d, j + 1, right);
	}
}

void main() {
	FILE* fp = fopen("in.txt", "r");
	int size, age;
	char name[10];
	element* arr;
	fscanf(fp, "%d", &size);
	arr = (element*)calloc(size + 1, sizeof(*arr));
	for (int i = 1; i <= size; i++) {
		fscanf(fp, "%s %d", name, &age);
		strcpy(arr[i].name, name);
		arr[i].age = age;
	}
	fclose(fp);
	printf("[Quick sort]\n");
	quicksort(arr, 1, size);
	for (int i = 1; i <= size; i++)
		printf("%10s:%4d\n", arr[i].name, arr[i].age);
	free(arr);
}
