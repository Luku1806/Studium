/*
 * main.c
 *
 *  Created on: 14.12.2018
 *      Author: Lukas Reining
 */

#include "include/display.h"
#include "cToolMod.h"

void printNumbers() {
	unsigned char num = 0;
	do {
		display_set_cursor(0, 0);
		display_printf("%d", num++);
		delay5ms(1);
	} while (num);
}

int main(void) {
	display_init();
	printNumbers();
	while (1) {
	}
}
