/*
 * rechner.c
 *
 *  Created on: 14.11.2018
 *      Author: Lukas Reining
 */
#include <stdio.h>
#include "zahlen.h"
#include "strings.h"

int add(int x, int y) {
	int result = x + y;
	if (((x > 0) && (y > 0) && (x + y < 0))) {
		printf("Overflow\n");
		return 0;
	} else {
		return result;
	}
}

int sub(int x, int y) {
	int result = x - y;
	if (((x > 0) && (y < 0) && (x - y < 0))) {
		printf("Overflow\n");
		return 0;
	} else {
		return result;
	}
}

int multiply(int x, int y) {
	int result = x * y;
	if (((x > 0) && (y > 0) && (x * y < 0))) {
		printf("Overflow\n");
		return 0;
	} else {
		return result;
	}
}

int divide(int x, int y) {
	if (y == 0) {
		printf("Durch 0 teilen ist ungueltig");
		return 0;
	}
	int result = x + y;
	if (x - y == result) {
		return result;
	} else {
		printf("Overflow\n");
		return 0;
	}
}

int mod(int x, int y) {
	return x % y;
}

int and(int x, int y) {
	return x & y;
}

int or(int x, int y) {
	return x | y;
}

int xor(int x, int y) {
	return x ^ y;
}

int solve(int x, char op, int y) {
	int result = 0;
	switch (op) {
	case '+':
		result = add(x, y);
		break;
	case '-':
		result = sub(x, y);
		break;
	case '*':
		result = multiply(x, y);
		break;
	case '/':
		result = divide(x, y);
		break;
	case '%':
		result = mod(x, y);
		break;
	case '&':
		result = and(x, y);
		break;
	case '|':
		result = or(x, y);
		break;
	case '^':
		result = xor(x, y);
		break;
	default:
		return 0;
	}
	return result;
}

int main(int argc, char* argv[]) {
	char flag = 'd', op, argX[stringLength(argv[1])],
			argY[stringLength(argv[2])];
	char sx[DIGITS + 1], sy[DIGITS + 1], sz[DIGITS + 1];
	int x, y, z;
	/* 1) Kommandozeile auswerten */
	if (argc < 4 || argc > 5) {
		printf("Aufruf: %s <x> <op> <y> \n", argv[0]);
		return 1;
	} else {
		if (argc == 5) {
			flag = argv[1][1];
			op = argv[3][0];
			//Fehlerbehandlung Flag
			if (flag != 'b' && flag != 'o' && flag != 'h') {
				printf("Ungueltige Ausgabeoption: '-%c'", flag);
				return 1;
			}
			//Fehlerbehandlung operator
			if (op != '+' && op != '-' && op != '*' && op != '/' && op != '%'
					&& op != '&' && op != '|' && op != '^') {
				printf("Ungueltige Operation: '%c'", op);
				return 1;
			}
			//Argumente nach argX/Y kopieren
			stringCopy(argv[2], argX);
			stringCopy(argv[4], argY);
		} else {
			op = argv[2][1];
			//Argumente nach argX/Y kopieren
			stringCopy(argv[1], argX);
			stringCopy(argv[3], argY);
		}
		//Fehlerbehandlung Zahlen
		if (!(isDezimalStr(argX) || isBinaryStr(argX) || isOctalStr(argX)
				|| isHexaStr(argX))) {
			printf("Ungueltiges Zahlensystem fuer Zahl 1: '%s'", argX);
			return 1;
		} else if (!isDezimalStr(argY) && !isBinaryStr(argY)
				&& !isOctalStr(argY) && !isHexaStr(argY)) {
			printf("Ungueltiges Zahlensystem fuer Zahl 2: '%s'", argY);
			return 1;
		}
		//Konvertierung String --> int
		x = stringTOint(argX);
		y = stringTOint(argY);
	}
	/* 2) Aufgabe loesen */
	printf("solve: %s %c %s \n", argX, op, argY);
	z = solve(x, op, y);
	/* 3) Ergebnisdarstellungen abhängig vom Flag ermitteln */
	if (flag == 'b') {
		intTObinaer(x, sx);
		intTObinaer(y, sy);
		intTObinaer(z, sz);
	} else if (flag == 'o') {
		intTOoctal(x, sx);
		intTOoctal(y, sy);
		intTOoctal(z, sz);
	} else if (flag == 'h') {
		intTOhexa(x, sx);
		intTOhexa(y, sy);
		intTOhexa(z, sz);
	}
	/* 4) Ausgabe des Ergebnis */
	if (flag == 'b' || flag == 'o' || flag == 'h') {
		printf("\n  %s %d\n%c %s %d\n= %s %d\n", sx, x, op, sy, y, sz, z);
	} else {
		printf("\n%d %c %d = %d\n", x, op, y, z);
	}

	return 0;
}
