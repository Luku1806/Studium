/*
 ============================================================================
 Name        : NConverter.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

void convertToBinary(int num){
	char newString[16];
	int currentValue = num;
	int counter = 0;
	while(currentValue > 0){
		int rest = currentValue % 2;
		currentValue /= 2;
		if(rest == 0){
			newString[counter] = '0';
		}else{
			newString[counter] = '1';
		}
		counter++;
	}
	newString[counter] = '\0';
	printf(newString);
}

int main(void) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	convertToBinary(257);
	return EXIT_SUCCESS;
}
