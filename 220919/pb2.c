#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>\
//이렇게하는거맞나.
void main() {
	int*** arr;
	int i, j, k;

	printf("A[I][J][K]...\n");
	printf("Input I:");
	scanf("%d", &i);
	printf("Input J:");
	scanf("%d", &j);
	printf("Input K:");
	scanf("%d", &k);

	arr = (int***)malloc(sizeof(int) * i);
	for (int x = 0; x < i; x++) {
		arr[x] = (int**)malloc(sizeof(int) * j);
		for (int y = 0; y < j; y++) {
			arr[x][y] = (int*)malloc(sizeof(int) * k);
			for (int z = 0; z < k; z++) {
				arr[x][y][z] = x + y + z;
				printf("A[%d][%d][%d]=%d	", x, y, z, arr[x][y][z]);
			}
			printf("\n");
		}
		printf("\n");
	}

	for (int x = 0; x < i; x++)
		for (int y = 0; y < j; y++)
			free(arr[x][y]);
	for (int x = 0; x < i; x++)
		free(arr[x]);
	free(arr);

}
