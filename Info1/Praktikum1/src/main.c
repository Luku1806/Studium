/*
 * Praktikum1.c
 *
 *  Created on: 11.10.2018
 *      Author: Lukas Reining
 */

#include <stdio.h>

void aufgabe2A() {
	int a, b, c;
	a = 5;
	b = 4;
	c = a + b;
	printf("%i + %i = %i\n", a, b, c);
}

void aufgabe2B() {
	float a, b, c;
	a = 3.141;
	b = 2.718;
	c = a + b;
	printf("%f + %f = %f\n", a, b, c);
}

/*
 * Methode zu Aufgabe 3.
 * Gibt für die Zahlen 1-10 die Quadratzahl,
 * Summe aller Zahlen und die Summe der Quadratzahlen formatiert auf der Konsole aus.
 */
void aufgabe3() {
	int sum = 0;
	int squareSum = 0;
	printf("  n | n*n  | s(n) |  q(n)\n");
	printf("----|------|------|-------\n");
	for (int i = 1; i < 11; i++) {
		int square = i * i;
		sum += i;
		squareSum += square;
		printf(" %2i | %3i  |   %2i |  %3i\n", i, square, sum, squareSum);
	}
}

int main(int argc, char* argv[]) {
	for (int i = 0; i < argc; i++) {
		printf("%s\n", argv[i]);

	}
	printf("Hello World\n");
	aufgabe2A();
	aufgabe2B();
	aufgabe3();
}

