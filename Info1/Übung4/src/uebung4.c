/*
 * uebung4.c
 *
 *  Created on: 07.12.2018
 *      Author: Lukas Reining
 */
#include <stdio.h>

#define dabs(x) (x)<0 ? -(x) : (x)

void insertionSort(int n, double* x) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - 1; j++) {
			double temp = x[j];
			if (temp > x[j + 1]) {
				x[j] = x[j + 1];
				x[j + 1] = temp;
			}
		}
	}
}

void sortTest() {
	int i, n = 10;
	//double x[] = { 3, 2, 4, 1, 5, 7, 6 };
	double x[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
	printf("unsorted: ");
	for (i = 0; i < n; i++) {
		printf("%5.2f ", x[i]);
	}
	insertionSort(n, x);
	printf("\n  sorted: ");
	for (i = 0; i < n; i++) {
		printf("%5.2f ", x[i]);
	}
}

//Annäherung an die Quadratwurzel
int naeherungsVerfahen(int a, double x_0, double eps, unsigned int nmax) {
	double delta, x_k_1, x_k = x_0;
	unsigned int k = 0;
	do {
		x_k_1 = x_k;
		/** find the next better approximation g(x_k_1). */
		x_k = (x_k_1 + (a / x_k_1)) / 2;
		/** calculate relative and/or absolute difference . */
		delta = dabs(x_k);
	} while (delta > eps && ++k < nmax);
	if (k >= nmax) {
		printf("no convergence!");
	}
	return x_k;
}

void testNaeherung(){
	int root = naeherungsVerfahen(25, 25, 0, 10);
	printf("Wurzel 25: %d",root);
}

int main(void) {
	sortTest();
	testNaeherung();
	return 0;
}
