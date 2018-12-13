#include <stdio.h>
#include "zahlen.h"

int main(int argc, char* argv[]) {
	char puffer[DIGITS + 1]; //Puffer für Zahl als Zeichenkette mit terminierender 0
	char *str = "-4711";
	int x;
	/* 1) Optionales Kommandozeilenargument verwenden. */
	if (argc > 1) {
		str = argv[1];
		/* 2) Zahl aus einer Zeichenkette berechnen. */
		x = stringTOint(str);
		printf("Zeichenkette \"%s\" als int: %d\n", str, x);
		/* 3) Zahl als Binaerzeichenkette darstellen */
		intTObinaer(x, puffer);
		printf("Zahl int: %d als Binaerzahl: %s\n", x, puffer);
		/* 3) Zahl als Oktalkette darstellen */
		intTOoctal(x, puffer);
		printf("Zahl int: %d als Oktalzahl: %s\n", x, puffer);
		/* 3) Zahl als Hexadezimalkette darstellen */
		intTOhexa(x, puffer);
		printf("Zahl int: %d als Hexadezimalzahl: %s\n", x, puffer);
	} else {
		//aufgabe4
		printf(" Dezimal |     Binaer     |      Oktal     |  Hexadezimal  \n");
		printf("---------|----------------|----------------|---------------\n");
		for (int i = -65; i < 66; i++) {
			printf("%9i|", i);
			intTObinaer(i, puffer);
			printf("%16s|", puffer);
			intTOoctal(i, puffer);
			printf("%16s|", puffer);
			intTOhexa(i, puffer);
			printf("%16s\n", puffer);
		}
	}

	return 0;
}
