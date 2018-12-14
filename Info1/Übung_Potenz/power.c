/*
 * power.c
 *
 *  Created on: 14.12.2018
 *      Author: Lukas Reining
 */
#include <stdio.h>

int power(int n, int x) {
	if (x == 1)
		return n;
	return n * power(n, x - 1);
}

int main(void) {
	int p = power(5,3);
	printf("Power: %d", p);
	return 0;
}
