/* Verwende zur Darstellung maximal
 *  DIGITS lange Zeichenketten */
#define DIGITS 16

/* Verwandle ein ASCII char in die entsprechende Ganzzahl
 * und gebe diese als Ergebnis zurueck.
 * @param c Charakter
 * @return der integer
 * */
int charTOint(char c);

/* Verwandle eine Ganzzahl in das entsprechende
 * ASCII Zeichen und gebe diese als Ergebnis zurueck. */
char intTOchar(int i);

/* Bilde aus der Zeichenkette str eine Ganzzahl zur Basis 10
 * und gebe diese als Ergebnis zurueck. */
int stringTOint(char str[]);

/* Schreibt Binaerdarstellung der Ganzzahl i nach str. */
void intTObinaer(int i, char str[]);

/* Schreibt Binaerdarstellung der Ganzzahl i nach str. */
void intTOoctal(int i, char str[]);

/* Schreibt Binaerdarstellung der Ganzzahl i nach str. */
void intTOhexa(int i, char str[]);

