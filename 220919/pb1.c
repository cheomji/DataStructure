//배열로 받아서 정렬하는 문제
//저 하나하나 비교하고 순서대로 출력하는거 조건을 어케 처리해야될지가 개헷갈려서 엄청 헤맸음.. 처음에 스캔하는 와일문 안에서 다 처리하려고 하다가실패함 
//밤 새고 와서 그런가ㅋㅋ 머리가안돌아갓음 .. 와일문 저렇게 처리할거 같으면 먼저 도달한 배열 말고 남은 배열의 원소를 다 추가해줘야함.
//저렇게 안하고 i==cnt1 && j==cnt2 이렇게 할거면 와일문 나와서 포문돌려서 일일이 추가해주면될듯?
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void main() {
	FILE* f1 = fopen("in1.txt", "r"), * f2 = fopen("in2.txt", "r");
	int arr1[50], arr2[50], cnt1 = 0, cnt2 = 0, i = 0, j = 0;
	while (!feof(f1)) 
		fscanf(f1, "%d", &arr1[cnt1++]);
	while (!feof(f2)) 
		fscanf(f2, "%d", &arr2[cnt2++]);
	fclose(f1), fclose(f2);

	while (!(i == cnt1 && j == cnt2)) {
		if (i == cnt1)
			printf("%d ", arr2[j++]);
		else if (j == cnt2)
			printf("%d ", arr1[i++]);
		else if (arr1[i] < arr2[j]) 
			printf("%d ", arr1[i++]);
		else if (arr1[i] == arr2[j]) {
			printf("%d ", arr1[i++]);
			j++;
		}
		else 
			printf("%d ", arr2[j++]);
	}
}
