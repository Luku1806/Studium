//********************************************************************
// ARM_T0A1  									Version 23.11.2017 CS
//********************************************************************
#include	"include/AT91SAM7S64.h"			// Definition von ARM7 typischen Registern etc.
#include 	"include/stdlib.h"
#include	"include/serial.h"
#include 	"include/string.h"
#include 	"include/stdio.h"

#define BUFFSIZE					60

// Betriebsfrequenzen des Timers
#define TIMER_FRQ_12000000HZ		0
#define TIMER_FRQ_3000000HZ			1
#define TIMER_FRQ_750000HZ			2
#define TIMER_FRQ_187500HZ			3
#define TIMER_FRQ_23437_5HZ			4

#define USED_FREQUENCY				12000000000			// Timerfrequency in mHz

#if USED_FREQUENCY == 12000000000
#define USED_TIMER	TIMER_FRQ_12000000HZ
#else
#if  USED_FREQUENCY==3000000000
#define USED_TIMER	TIMER_FRQ_3000000HZ
#else
#if   USED_FREQUENCY==750000000
#define USED_TIMER	TIMER_FRQ_750000HZ
#else
#if   USED_FREQUENCY==187500000
#define USED_TIMER	TIMER_FRQ_187500HZ
#else
#if   USED_FREQUENCY==23437500
#define USED_TIMER	TIMER_FRQ_23437_5HZ
#endif
#endif
#endif
#endif
#endif

#define ZEILEN		2
#define SPALTEN		2

// *****************************************************************
// ******* Change here for different data types ********************
// *****************************************************************
#define	DATATYPE	1		// 1: int; 2:float; 3:double
#if DATATYPE == 1
#define	TYPE	int
#define PRN		"%d"
#else
#if DATATYPE == 2
#define	TYPE	float
#define PRN		"%f"
#else
#if DATATYPE == 3
#define	TYPE	double
#define PRN		"%lf"
#endif
#endif
#endif

int main() {
	TYPE matrix_a[ZEILEN][SPALTEN];
	TYPE matrix_b[ZEILEN][SPALTEN];
	TYPE matrix_c[ZEILEN][SPALTEN];
	usart0_init();
	char buffer[BUFFSIZE];

	//Fuelle Matrizen A,B
	for (int i = 0; i < ZEILEN; i++) {
		for (int j = 0; j < SPALTEN; j++) {
			matrix_a[i][j] = rand() % 4096;
			matrix_b[i][j] = rand() % 4096;
		}
	}
	//Nulle Matrize C
	for (int i = 0; i < ZEILEN; i++) {
		for (int j = 0; j < SPALTEN; j++) {
			matrix_c[i][j] = 0;
		}
	}

	// Ausgabe der Matrix A
	usart0_puts("\n\n Matrix a:\n");
	for (int i = 0; i < ZEILEN; i++) {
		for (int j = 0; j < SPALTEN; j++) {
			snprintf(buffer, BUFFSIZE, PRN"\t", matrix_a[i][j]);
			usart0_puts(buffer);
		}
		usart0_puts("\n");
	}

	// Ausgabe der Matrix B
	usart0_puts("\n\n Matrix b:\n");
	for (int i = 0; i < ZEILEN; i++) {
		for (int j = 0; j < SPALTEN; j++) {
			snprintf(buffer, BUFFSIZE, PRN"\t", matrix_b[i][j]);
			usart0_puts(buffer);
		}
		usart0_puts("\n");
	}

	//Timer initialisierung
	AT91C_BASE_PMC->PMC_PCER = (1 << AT91C_ID_TC0); // Taktweiterleitung an Timer
	// Timer-Betriebsfrequenz und Modus
	AT91C_BASE_TC0->TC_CMR = AT91C_TC_WAVE | AT91C_TC_CPCDIS | USED_TIMER;
	AT91C_BASE_TC0->TC_RC = 0xFFFF; // Maximaler Timerwert
	AT91C_BASE_TC0->TC_CCR = AT91C_TC_CLKEN; // Taktfreigabe
	AT91C_BASE_TC0->TC_CCR = AT91C_TC_SWTRG; // Zurücksetzen des Zählers

	// Matrizenmultiplikation
	for (int row = 0; row < ZEILEN; row++) {
		for (int col = 0; col < SPALTEN; col++) {
			for (int inner = 0; inner < ZEILEN; inner++) {
				//Multipliziere Reihe A und Spalte B um das Produkt zu bekommen
				matrix_c[row][col] += matrix_a[row][inner]
						* matrix_b[inner][col];
			}
		}
	}

	// Timer auslesen und Zeit berechnen
	unsigned int timer_val = AT91C_BASE_TC0->TC_CV;
	double calc_time = timer_val / (USED_FREQUENCY * 10e-6);

	// Ausgabe der Matrix C
	usart0_puts("\n\n Result:\n");
	for (int i = 0; i < ZEILEN; i++) {
		for (int j = 0; j < SPALTEN; j++) {
			snprintf(buffer, BUFFSIZE, PRN"\t\t", matrix_c[i][j]);
			usart0_puts(buffer);
		}
		usart0_puts("\n");
	}

	if (timer_val == 0xffff) {
		usart0_puts(
				"\n\n################### Timerueberlauf ###################\n");
		usart0_puts(
				"########## Bitte Timerfrequenz anpassen !!! ##########\n\n");
		usart0_puts(buffer);
	} else {
		snprintf(buffer, BUFFSIZE, "Berechnung dauerte: %f\n", calc_time);
		usart0_puts(buffer);
	}

	while (1) {
	}							// Endlosschleife
}

