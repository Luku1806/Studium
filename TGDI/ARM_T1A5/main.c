/*
 * main.c
 *
 *  Created on: 14.12.2018
 *      Author: Lukas Reining
 */

#include "include/AT91SAM7S64.h"
#include "include/display.h"

#define		BUTTON1	AT91C_PIO_PA1
#define		BUTTON2	AT91C_PIO_PA0
#define		BUTTON3	AT91C_PIO_PA31

int btn1 = 0, btn2 = 0, btn3 = 0;

//unsigned char get_Button() {
//	btn1 = (AT91C_BASE_PIOA->PIO_PDSR & BUTTON1) >> 1; //Inverted value for Button1
//	btn2 = (AT91C_BASE_PIOA->PIO_PDSR & BUTTON2); //Inverted value for Button2
//	btn3 = (AT91C_BASE_PIOA->PIO_PDSR & BUTTON3) >> 31; //Inverted value for Button3
//	return (~(btn1 | (btn2 << 1) | (btn3 << 2))) & 0b111;
//}

unsigned char get_Button() {
	btn1 = (~((AT91C_BASE_PIOA->PIO_PDSR & BUTTON1) >> 1)) & 1; //Value for Button1
	btn2 = (~(AT91C_BASE_PIOA->PIO_PDSR & BUTTON2)) & 1; //Value for Button2
	btn3 = (~(AT91C_BASE_PIOA->PIO_PDSR & BUTTON3) >> 31) & 1; //Value for Button3
	return (btn1 | (btn2 << 1) | (btn3 << 2));
}

int main(void) {
	AT91C_BASE_PMC->PMC_PCER = (1 << AT91C_ID_PIOA); //Enable Clock
	display_init();
	while (1) {
		display_set_cursor(0, 0);
		display_printf("%d", get_Button());
		display_set_cursor(0, 1);
		display_printf("B1:%d B2:%d B2:%d", btn1, btn2, btn3);
	}
	while (1)
		;
}
