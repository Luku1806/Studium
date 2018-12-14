/*
 * farbtest.c
 *
 *  Created on: 06.12.2018
 *      Author: Lukas Reining
 */

#include <stdio.h>

#define R_MASK 0x00FF0000
#define G_MASK 0x0000FF00
#define B_MASK 0x000000FF

unsigned char getRed(int color) {
	return ((color & R_MASK) >> 16);
}

unsigned char getGreen(int color) {
	return ((color & G_MASK) >> 8);
}

unsigned char getBlue(int color) {
	return (color & B_MASK);
}

int setRed(int color, unsigned char r) {
	return ((color & ~R_MASK) | (r << 16));
}
int setGreen(int color, unsigned char g) {
	return ((color & ~G_MASK) | (g << 8));
}
int setBlue(int color, unsigned char b) {
	return ((color & ~B_MASK) | b);
}

int mixColor(unsigned char r, unsigned char g, unsigned char b) {
	int zahl = 0;
	zahl = setRed(zahl, r);
	zahl = setGreen(zahl, g);
	zahl = setBlue(zahl, b);
	return zahl;
}


int main(void) {
	int color = mixColor(100, 200, 50);
	//color = setRed(color, 255);
	//color = setGreen(color, 8);
	//color = setBlue(color, 0);
	int red = getRed(color);
	int green = getGreen(color);
	int blue = getBlue(color);
	printf("Encoded RGB:\nDezimal:%d\nHexa:%x\n", color, color);
	printf("\nDecoded (R|G|B) dez.:\(%d|%d|%d)\n", red, green, blue);
	printf("Decoded (R|G|B) hex.:\(%x|%x|%x)\n", red, green, blue);
	return 0;
}

