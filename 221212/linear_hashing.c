#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define False 0
#define True 1

typedef struct B {
	int visit;
	char slot[20];
}element;

element* ht;
int bsize;

unsigned int string_to_int(char* key);
int search(element*ht, char input[]);
void insertHash(element* ht, char input[]);

void main(void) {
	FILE* fp = fopen("in.txt", "r");
	int i;
	char tmp[20];

	printf("Input bucket size:");
	scanf("%d", &bsize);
	ht = (element*)calloc(bsize, sizeof(element));

	while (!feof(fp)) {
		fscanf(fp, "%s", tmp);
		insertHash(ht, tmp);
	}

	for (i = 0; i < bsize; i++)
		printf("[%d]: %s\n", i, ht[i].slot);

	while (1) {
		printf("Input string(Q for quit):");
		scanf("%s", tmp);
		if (!strcmp("Q", tmp)) break;
		if (search(ht, tmp) == 0) printf("Fail\n");
		else printf("Success\n");
	}
	printf("Exit");
	fclose(fp);
}

unsigned int string_to_int(char* key) {
	int number = 0;
	while (*key)
		number += *key++;
	return number;
}

int search(element* ht, char input[]) {
	int k = string_to_int(input) % bsize;
	int s = k;
	if (!strcmp(input, ht[k++].slot)) return k - 1;
	else {
		while ((k % bsize) != s)
			if (!strcmp(input, ht[k++ % bsize].slot))
				return k;
		return 0;
	}
}

void insertHash(element* ht, char input[]) {
	int k = string_to_int(input) % bsize;
	if (ht[k].visit == 0) {
		strcpy(ht[k].slot, input);
		ht[k].visit = True;
	}
	else {
		while (ht[k % bsize].visit) k++;
		strcpy(ht[k % bsize].slot, input);
		ht[k].visit = True;
	}
}
