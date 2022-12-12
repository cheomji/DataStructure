// 망햇어요.. chaining은 아님 근데
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef char element;
typedef struct n {
	element data[10];
	struct n* next;
}node;
typedef struct {
	int D;
	node** slot;
}hash;

int return_key(char data[], int D);
node* new_node(element data[]);
void insert_hash(hash* h, element data[]);
void insert_hash_from_file(hash input[], char* file);
int search_hash(hash* h, char data[]);

void main() {
	FILE* fp = fopen("in.txt", "r");
	int D;
	char temp[10];
	hash* ht;

	printf("Input size:");
	scanf("%d", &D);


	while (!feof(fp)) {
		fscanf(fp, "%s", &temp);
		insert_hash(ht, temp);
	}

	for (int i = 0;i < ht->D;i++) {
		printf("[%d]: ", i);
		node* cur = ht->slot[i];
		while (cur) {
			printf("[%6s] ", cur->data);
			cur = cur->next;
		}
		printf("\n");
	}
	char find[10];
	printf("Input string(Q for quit):");
	while (scanf("%s", &find) && strcmp(find, "Q")) {
		printf("%s\n", search_hash(ht, find) ? "Success" : "Fail");
		printf("Input string(Q for quit):");
	}
	printf("Exit\n");
}

hash* new_hash_table(int D) {
	hash* temp = (hash*)malloc(sizeof(hash));
	temp->D = D;
	temp->slot = (node**)calloc(D, sizeof(node*));
	return temp;
}

int return_key(char data[], int D) {
	int sum = 0;
	for (int i = 0;i < strlen(data);i++) {
		sum += data[i];
	}
	return sum % D;
}

node* new_node(element data[]) {
	node* temp = (node*)malloc(sizeof(node));
	strcpy(temp->data, data);
	temp->next = NULL;
	return temp;
}

void insert_hash(hash* h, element data[]) {
	int key = return_key(data, h->D);
	if (h->slot[key] == NULL) {
		h->slot[key] = new_node(data);
	}
	else {
		node* temp = new_node(data);
		temp->next = h->slot[key];
		h->slot[key] = temp;
	}
}

void insert_hash_from_file(hash input[], char* file) {
	FILE* fp = fopen(file, "r");
	char temp[10];
	while (!feof(fp)) {
		fscanf(fp, "%s", &temp);
		insert_hash(input, temp);
	}
}

int search_hash(hash* h, char data[]) {
	int key = return_key(data, h->D);
	node* cur = h->slot[key];
	while (cur) {
		if (!strcmp(cur->data, data)) return 1;
		cur = cur->next;
	}
	return 0;
}
