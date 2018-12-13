/*
 * strings.h
 *
 *  Created on: 14.11.2018
 *      Author: Lukas Reining
 */

#ifndef STRINGS_H_
#define STRINGS_H_

/* Gibt die Länge einer String ohne NULL-Character zurueck
 * @param str[] Die String deren Laenge bestimmt wird
 * @return Die Laenge der String ohne NULL
 * */
int stringLength(char str[]);

/* Gibt eine String umgedreht zurück
 * @param str[] Die umzudrehende String
 * */
void reverse(char str[]);

/* Schreibt die Substring von str[start] bis einschließlich str[end] in sub[]
 * @param str[] Die String aus der die Substring geholt wird
 * @param sub[] Die Substring, in die die ermittelte Substring geschrieben wird
 * @param start Der erste Index von str[] der zu sub[] gehoert
 * @param end Der letzte Index von str[] der zu sub[] gehoert
 * */
void substring(char str[], char sub[], int start, int end);

/*
 * Kopiert die String str nach new
 * @param str[] Die zu kopierende String
 * @param new[] Die Kopie der String str
 */
void stringCopy(char str[], char new[]);

/**
 * Vergleicht zwei Strings ung gibt 1 zurueck fuer str1==str2, 0 fuer str1!=str2
 * @return 1 wenn str2 == str1, sonst 0
 */
int equals(char str1[], char str2[]);

/**
 * Prueft ob str2 in str2 enthalten ist und gibt 1 zurueck fuer str1 enthaelt str2, 0 fuer str1 enthalet nicht str2
 * @return 1 wenn str2 Teilstring von str1, sonst 0
 */
int contains(char str1[], char str2[]);

/**
 * Wandelt eine String in Uppercase um.
 * @param str Die umzuwandelnde String
 * @param result Die String in die die umgewandelte String geschrieben wird
 */
void toUpper(char str[], char result[]);

/* Gibt zurück ob ein char ein ASCII-Zeichen aus dem Dezimalalphabet ist.*/
char isDezimal(char c);

/* Gibt zurück ob ein char ein ASCII-Zeichen aus dem Binaeralphabet ist.*/
char isBinary(char c);

/* Gibt zurück ob ein char ein ASCII-Zeichen aus dem Oktalalphabet ist*/
char isOctal(char c);

/*Gibt zurück ob ein char ein ASCII-Zeichen aus dem Hexadezimalalphabet ist*/
char isHexa(char c);

/**
 * Gibt zurück ob eine String nur aus Zeichen des Dezimalalphabetes besteht.
 */
char isDezimalStr(char str[]);

/*
 * Gibt zurück ob eine String den Paefix 0b oder 0B besitzt und nur aus Zeichen des Binaeralphabetes besteht.
 */
char isBinaryStr(char str[]);

/*
 * Gibt zurück ob eine String den Paefix 0 besitzt und nur aus Zeichen des Oktalalphabetes besteht.
 */
char isOctalStr(char str[]);

/*
 * Gibt zurück ob eine String den Paefix 0x oder 0X besitzt und nur aus Zeichen des Hexadezimalalphabetes besteht.
 */
char isHexaStr(char str[]);

#endif /* STRINGS_H_ */
