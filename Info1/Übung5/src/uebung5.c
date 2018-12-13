/*
 * uebung5.c
 *
 *  Created on: 11.12.2018
 *      Author: Lukas Reining
 */
#include <stdio.h>

//Aufgabe 1
double sequence(double x, unsigned char a) {
	if (x == 0) {
		return 1;
	}
	return sequence(x - 1, a) / a;
}

double masch(double x) {
	return 1.0 + x;
}

int testMasch(int a) {
	int xn = 0;
	double result = 0;
	while (result != 1) {
		result = masch(sequence(xn++, a));
	}
	return xn;
}

//Aufgabe 2
int faculty(int x) {
	if (x == 0 || x == 1) {
		return 1;
	}
	return x * faculty(x - 1);
}

int binomco(int n, int k) {
	if (k < 0 || k > n) {
		return 0;
	}
	if (k == 0 || k == n) {
		return 1;
	}
	return faculty(n) / ((faculty(k) * faculty(n - k)));
}

//Aufgabe 3
/**
 * Immer 1
 */
int function1(int n) {
	if (n == 1) {
		return 1;
	}
	if (n % 2 == 0) {
		return function1(n / 2);
	} else {
		return function1(3 * n + 1);
	}
}

/**
 * Quadratzahlen
 */
int function2(int n) {
	if (n == 1) {
		return 1;
	}
	return function2(n - 1) + 2 * n - 1;
}

int function3(int n) {
	if (n == 1 || n == 2) {
		return 1;
	}
	return function3(n - function3(n - 1)) + function3(n - function3(n - 2));
}

/**
 * Immer 91
 */
int function4(int n) {
	if (n > 100) {
		return n - 10;
	}
	return function4(function4(n + 11));
}

int main(void) {
	printf("faculty(%d) = %d\n", 5, faculty(5));
	printf("sequence(%d) = %.17f\n", 25, sequence(56, 2));
	printf("masch(sequence(%d)) = %.32f\n", 54, masch(sequence(54, 2)));
	printf("testMasch(%d) = %d\n", 2, testMasch(2));
	printf("binomco(%d,%d) = %d\n", 6, 2, binomco(6, 2));
	printf("\n");
	for (int i = 1; i < 8; i++) {
		printf("function1(%d) = %d\n", i, function1(i));
	}
	printf("\n");
	for (int i = 1; i < 8; i++) {
		printf("function2(%d) = %d\n", i, function2(i));
	}
	printf("\n");
	for (int i = 1; i < 16; i++) {
		printf("function3(%d) = %d\n", i, function3(i));
	}
	printf("\n");
	for (int i = 1; i < 8; i++) {
		printf("function4(%d) = %d\n", i, function4(i));
	}
}
