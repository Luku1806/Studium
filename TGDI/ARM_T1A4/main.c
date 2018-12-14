/*
 * main.c
 *
 *  Created on: 14.12.2018
 *      Author: Lukas Reining
 */

#include "include/display.h"

void printNumbers() {
	unsigned char num = 0;
	do {
		display_set_cursor(0, 0);
		display_printf("%d", num++);
		delay1us(500000);
	} while (num);
}

int main(void) {
	display_init();
	printNumbers();
	while (1) {
	}
}
