/*
 * main.c
 *
 *  Created on: 14.12.2018
 *      Author: Lukas Reining
 */

#include "include/display.h"

//**************************************************************
// delay5ms(uiK) verzögert um ca. uiK * 5ms
//**************************************************************
void delay5ms(unsigned int uiK) {
	volatile unsigned int uiI;

	while (uiK--)				// folgende for-Schleife wird uiK-mal aufgerufen
		for (uiI = 0; uiI < 8192; uiI++)
			;		//  for-Schleife wird 8192-mal durchlaufen. Dies
					//  verursacht eine Zeitverzögerung von ca. 5ms.
}

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
