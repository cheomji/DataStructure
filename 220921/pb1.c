//startA같은 지표를 컨트롤하는게 헷갈리고 어려웠던 것 같음.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct POLY {
	int coef;
	int exp;
}poly;

poly terms[100];
int avail = 0;

void attach(int coefficient, int exponent);
void minus(int startA, int finishA, int startB, int finishB, int* startD, int* finishD);
void printPoly(int start, int finish);

void main() {
	FILE* f1 = fopen("a.txt", "r"), * f2 = fopen("b.txt", "r");
	int sa = 0, fa = 0, sb, fb, sd, fd, i;

	while (!feof(f1)) {
		fscanf(f1, "%d %d", &terms[fa].coef, &terms[fa].exp);
		attach(terms[fa].coef, terms[fa].exp);
		fa++;
	}fclose(f1);
	fa--;
	printf("A(x):");
	printPoly(sa, fa);
	printf("\n");
	sb = fb = avail;

	while (!feof(f2)) {
		fscanf(f2, "%d %d", &terms[fb].coef, &terms[fb].exp);
		attach(terms[fb].coef, terms[fb].exp);
		fb++;
	}fclose(f2);
	fb--;
	printf("B(x):");
	printPoly(sb, fb);
	printf("\n\n");

	minus(sa, fa, sb, fb, &sd, &fd);
	printf("C(x):");
	for (i = 0; i <= fa; i++)
		if (terms[sa + i].coef != terms[sb + i].coef && terms[sa + i].exp != terms[sb + i].exp)
			break;
	if (i == fa + 1)
		printf("0");
	else
		printPoly(sd, fd);
}

void attach(int coefficient, int exponent) {
	terms[avail].coef = coefficient;
	terms[avail++].exp = exponent;
}

void minus(int startA, int finishA, int startB, int finishB, int* startD, int* finishD) {
	int coef;
	*startD = avail;
	while (startA <= finishA && startB <= finishB) {
		if (terms[startA].exp == terms[startB].exp) {
			coef = terms[startA].coef - terms[startB].coef;
			if (coef)
				attach(coef, terms[startA].exp);
			startA++, startB++;
		}
		else if (terms[startA].exp > terms[startB].exp) {
			attach(-terms[startB].coef, terms[startB].exp);
			startB++;
		}
		else {
			attach(terms[startA].coef, terms[startA].exp);
			startA++;
		}
	}
	for (; startA <= finishA; startA++)
		attach(terms[startA].coef, terms[startA].exp);
	for (; startB <= finishB; startB++)
		attach(terms[startB].coef, terms[startB].exp);
	*finishD = avail - 1;
}

void printPoly(int start, int finish) {
	for (int i = start; i <= finish; i++) {
		printf("%dx^%d ", terms[i].coef, terms[i].exp);
		if (i != finish)
			printf("+ ");
	}
}
