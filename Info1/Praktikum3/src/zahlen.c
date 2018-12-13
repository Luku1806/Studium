/*
 * zahlen.c
 *
 *  Created on: 26.10.2018
 *      Author: Lukas Reining
 */

//#include <stdio.h>
#include "zahlen.h"
#include "strings.h"

int charTOint(char c) {
	if (c >= '0' && c <= '9') {
		return c - '0';
	} else if (c >= 'a' && c <= 'f') {
		return c - 'a' + 10;
	} else if (c >= 'A' && c <= 'F') {
		return c - 'A' + 10;
	}
	return 0;
}

char intTOchar(int i) {
	if (i >= 0 && i <= 9) {
		return i + '0';
	} else if (i >= 10 && i <= 15) {
		return i + 'A' - 10;
	}
	return 0;
}

int stringTOint(char str[]) {
	int sign = 0, offset = 0, result = 0;
	// Prüfe Vorzeichen
	if (str[0] == '-') {
		sign = -1;
		offset = 1;
	}
	if (str[offset] == '0'
			&& (str[offset + 1] == 'x' || str[offset + 1] == 'X')) {
		offset += 2;
		//Kovertiere String zu int
		for (int i = offset; str[i] != '\0'; i++) {
			if (!isHexa(str[i])) {
				return 0;
			}
			result = result * 16 + charTOint(str[i]);
		}
	} else if (str[offset] == '0'
			&& (str[offset + 1] == 'b' || str[offset + 1] == 'B')) {
		offset += 2;
		//Kovertiere String zu int
		for (int i = offset; str[i] != '\0'; i++) {
			if (!isBinary(str[i])) {
				return 0;
			}
			result = result * 2 + charTOint(str[i]);
		}
	} else if (str[offset] == '0') {
		offset++;
		//Kovertiere String zu int
		for (int i = offset; str[i] != '\0'; i++) {
			if (!isOctal(str[i])) {
				return 0;
			}
			result = result * 8 + charTOint(str[i]);
		}
	} else {
		//Kovertiere String zu int
		for (int i = offset; str[i] != '\0'; i++) {
			if (!isDezimal(str[i])) {
				return 0;
			}
			result = result * 10 + charTOint(str[i]);
		}
	}
	// Wenn Minus in String, setze Minus in int
	if (sign == -1) {
		result = -result;
	}
	return result;
}

void changeBase(int i, int base, char str[]) {
	//Wenn i negativ, mach positiv(behandlung positiv/negativ in eigenen Methoden)
	if (i < 0) {
		i = -i;
	}
	//Modulo-Algorithmus
	int currentValue = i;
	int counter = 0;
	while (currentValue > 0) {
		int rest = currentValue % base;
		currentValue /= base;
		str[counter] = intTOchar(rest);
		counter++;
	}
	//Fuelle Nullen auf
	while (counter < DIGITS) {
		str[counter] = '0';
		counter++;
	}
	str[DIGITS] = '\0';
	reverse(str);
}

void intTObinaer(int i, char str[]) {
	//i positiv -> Stellenwertsystem
	changeBase(i, 2, str);
	//i negativ -> Zweier-Komplement
	if (i >= 0)
		return;

	str[0] = '1'; //Setze Vorzeichenbit
	//Invertiere
	for (int j = 1; j < DIGITS; j++) {
		if (str[j] == '1') {
			str[j] = '0';
		} else {
			str[j] = '1';
		}
	}
	//Addiere 1
	for (int i = DIGITS - 1; i >= 0; i--) {
		if (str[i] == '0') {
			str[i] = '1';
			break;
		} else {
			str[i] = '0';
		}
	}

}

void intTOoctal(int i, char str[]) {
	//i positiv -> Stellenwertsystem
		changeBase(i, 8, str);
		if (i < 0) {
			str[0] = 'F'; //Setze Vorzeichenbit
			//Invertiere
			for (int j = 1; j < DIGITS; j++) {
				str[j] = intTOchar((7 - charTOint(str[j])));
			}
			//Addiere 1
			for (int k = DIGITS - 1; k >= 0; k--) {
				if(charTOint(str[k]) < 7){
					str[k] = intTOchar((charTOint(str[k]) + 1));
					break;
				}else{
					str[k] = 0;
				}
			}
		}
}

void intTOhexa(int i, char str[]) {
	//i positiv -> Stellenwertsystem
	changeBase(i, 16, str);
	if (i < 0) {
		str[0] = 'F'; //Setze Vorzeichenbit
		//Invertiere
		for (int j = 1; j < DIGITS; j++) {
			str[j] = intTOchar((15 - charTOint(str[j])));
		}
		//Addiere 1
		for (int k = DIGITS - 1; k >= 0; k--) {
			if(charTOint(str[k]) < 15){
				str[k] = intTOchar((charTOint(str[k]) + 1));
				break;
			}else{
				str[k] = 0;
			}
		}
	}
}

