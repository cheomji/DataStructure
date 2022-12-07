#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef enum { Club, Dia, Heart, Spade }suits;
typedef struct trump {
	int face;
	int suit;
}element;

suits to_suit(char ch);
int radixSort(element a[], int link[], int size);
int digit(int n);
char* to_string(suits n);
char to_face(int n);

void main(void) {
	FILE* fp = fopen("in.txt", "r");
	int size, n, link[MAX], i;
	char ch;
	element arr[MAX];
	fscanf(fp, "%d", &size);
	for (i = 1; i <= size; i++) {
		fscanf(fp, "\n%c\n%d", &ch, &n);
		arr[i].face = n;
		arr[i].suit = to_suit(ch);
	}
	fclose(fp);
	i = radixSort(arr, link, size);
	for (; i; i = link[i]) {
		if (arr[i].face == 10)
			printf("(%5s, %3d)\n", to_string(arr[i].suit), 10);
		else
			printf("(%5s, %3c)\n", to_string(arr[i].suit), to_face(arr[i].face));
	}
}

int to_suit(char ch) {
	switch (ch)
	{
	case 'C': return Club;
	case 'D': return Dia;
	case 'H': return Heart;
	case 'S': return Spade;
	default: return -1;
	}
}
int radixSort(element a[], int link[], int size) {
	int front[MAX], rear[MAX];
	int i, bin, current, first = 1, last;
	for (i = 1; i < size; i++) link[i] = i + 1;
	link[size] = 0; //link에는 사이즈만큼 들어가있음 ㅇㅇ


    // 처음에는 r1 = 13, face value에 대해 정렬하는 거
	for (bin = 0; bin < 13; bin++) front[bin] = 0;
	for (current = first; current; current = link[current]) {
		bin = digit(a[current].face);
		if (front[bin] == 0) front[bin] = current;
		else link[rear[bin]] = current;
		rear[bin] = current;
	}
	for (bin = 0; !front[bin]; bin++);
	first = front[bin], last = rear[bin];
	for (bin++; bin < 13; bin++)
		if (front[bin])
			link[last] = front[bin], last = rear[bin];
	link[last] = 0;


	// 두번째는 r2 = 4, suit value에 대해 정렬.
	for (bin = 0; bin < 4; bin++) front[bin] = 0;
	for (current = first; current; current = link[current]) {
		bin = a[current].suit;
		if (front[bin] == 0) front[bin] = current;
		else link[rear[bin]] = current;
		rear[bin] = current;
	}
	for (bin = 0; !front[bin]; bin++);
	first = front[bin], last = rear[bin];
	for (bin++; bin < 4; bin++)
		if (front[bin])
			link[last] = front[bin], last = rear[bin];
	link[last] = 0;

	return first;
}
int digit(int n) {
	if (n == 1) return 12;
	return n - 2;
}
char* to_string(suits n) {
	switch (n)
	{
	case Club: return "club";
	case Dia: return "dia";
	case Heart: return "heart";
	case Spade: return "spade";
	default: return "??";
		break;
	}
}
char to_face(int n) {
	switch (n)
	{
	case 11: return 'J';
	case 12: return 'Q';
	case 13: return 'K';
	default:
		return n + '0';
		break;
	}
}
