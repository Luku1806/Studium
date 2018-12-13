/*
 * uebung1.c
 *
 *  Created on: 31.10.2018
 *      Author: Lukas Reining
 */

#include <stdio.h>

/* sum of the odd numbers 1 to 2n-1. */
int sumOdd(int n) {
	int sum = 0;
	for (int i = 1; i <= (2 * n) - 1; i += 2) {
		sum += i;
	}
	return sum;
}

/*sum of the even numbers 2 to 2n. */
int sumEven(int n) {
	int sum = 0;
	for (int i = 2; i <= (2 * n); i += 2) {
		sum += i;
	}
	return sum;
}

int main(void) {
	printf("%d", sumEven(5));
}
