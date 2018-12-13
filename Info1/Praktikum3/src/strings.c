/*
 * strings.c
 *
 *  Created on: 14.11.2018
 *      Author: Lukas Reining
 */

int stringLength(char str[]) {
	int length = 0;
	for (length = 0; str[length] != '\0'; length++) {
	}
	return length;
}

void reverse(char str[]) {
	int length = stringLength(str);
	int countUp = 0;
	int countDown = length - 1;
	char temp;
	while (countUp < countDown) {
		temp = str[countUp];
		str[countUp] = str[countDown];
		str[countDown] = temp;
		countUp++;
		countDown--;
	}
}

void substring(char str[], char sub[], int start, int end) {
	int counter = 0;
	for (int i = start; i <= end; i++) {
		sub[counter] = str[i];
		counter++;
	}
	sub[counter] = '\0';
}

void stringCopy(char str[], char new[]) {
	int length = stringLength(str);
	for (int i = 0; i <= length; i++) {
		new[i] = str[i];
	}
}

int equals(char str1[], char str2[]) {
	int length1 = stringLength(str1);
	int length2 = stringLength(str2);
	if (length1 != length2) {
		return 0;
	}
	for (int i = 0; i < length1; i++) {
		if (str1[i] != str2[i]) {
			return 0;
		}
	}
	return 1;
}

int contains(char str1[], char str2[]) {
	int length1 = stringLength(str1);
	int length2 = stringLength(str2);
	for (int i = 0; i < length1; i++) {
		if (str1[i] == str2[0]) {
			int j = 0;
			for (j = 0; j < length2 - 1; j++) {
				if (str1[i + j] != str2[j]) {
					break;
				}
			}
			if (str1[i + j] == str2[j]) {
				return 1;
			}
		}
	}
	return 0;
}

void toUpper(char str[], char result[]) {
	int length = stringLength(str);
	for (int i = 0; i <= length; i++) {
		if (str[i] > 96 && str[i] < 123) {
			result[i] = str[i] - 32;
		} else {
			result[i] = str[i];
		}
	}
}

char isDezimal(char c) {
	return ('0' <= c && c <= '9');
}

char isBinary(char c) {
	return (c == '0' || c == '1');
}

char isOctal(char c) {
	return ('0' <= c && c <= '7');
}

char isHexa(char c) {
	return (isDezimal(c) || ('a' <= c && c <= 'f') || ('A' <= c && c <= 'F'));
}

char isDezimalStr(char str[]) {
	int length = stringLength(str);
	int i = 0;
	if (str[i] == '-') {
		i++;
	}
	if (str[i] == '0' || length <= i) {
		return 0;
	}
	for (i++; i < length; i++) {
		if (!isDezimal(str[i])) {
			return 0;
		}
	}
	return 1;
}

char isBinaryStr(char str[]) {
	int length = stringLength(str);
	int i = 0;
	if (str[i] == '-') {
		i++;
	}
	if (!(str[i++] == '0' && (str[i] == 'b' || str[i] == 'B')) || length <= i) {
		return 0;
	}
	for (i++; i < length; i++) {
		if (!isBinary(str[i])) {
			return 0;
		}
	}
	return 1;
}

char isOctalStr(char str[]) {
	int length = stringLength(str);
	int i = 0;
	if (str[i] == '-') {
		i++;
	}
	if (!(str[i] == '0') || length <= i) {
		return 0;
	}
	for (i++; i < length; i++) {
		if (!isOctal(str[i])) {
			return 0;
		}
	}
	return 1;
}

char isHexaStr(char str[]) {
	int length = stringLength(str);
	int i = 0;
	if (str[i] == '-') {
		i++;
	}
	if (!(str[i++] == '0' && (str[i] == 'x' || str[i] == 'X')) || length <= i) {
		return 0;
	}
	for (i++; i < length; i++) {
		if (!isHexa(str[i])) {
			return 0;
		}
	}
	return 1;
}

