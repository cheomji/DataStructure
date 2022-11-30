// input file 은 데이터 개수랑 그 밑에 데이텈(이름, 나이)들 있는 파일임
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct person {
	char name[10];
	int age;
}element;

void insert(element e, element d[], int i) {
	d[0] = e;
	while (e.age > d[i].age) {
		d[i + 1] = d[i];
		i--;
	}
	d[i + 1] = e;
}
void insertionSort(element d[], int n) {
	int j;
	for (j = 2;j <= n;j++) {
		element tmp = d[j];
		insert(tmp, d, j - 1);
	}
}

void main() {
	FILE* fp = fopen("in.txt", "r");
	int size, age;
	char name[10];
	element* arr;
	fscanf(fp, "%d", &size);
	arr = (element*)calloc(size + 1, sizeof(*arr));
	for (int i = 1; i <= size; i++){
		fscanf(fp, "%s %d", name, &age);
		strcpy(arr[i].name, name);
		arr[i].age = age;
	}
	fclose(fp);
	printf("[Insert sort]\n");
	insertionSort(arr, size);
	for (int i = 1; i <= size; i++)
		printf("%10s:%4d\n", arr[i].name, arr[i].age);
	free(arr);
}
