/*
 * cToolMod.c
 *
 *  Created on: 09.01.2019
 *      Author: Lukas Reining
 */


//**************************************************************
// delay1ms(uiK) verzögert um ca. uiK * 1ms
//**************************************************************
void delay1ms(unsigned int uiK) {
	volatile unsigned int uiI;

	while (uiK--)				// folgende for-Schleife wird uiK-mal aufgerufen
		for (uiI = 0; uiI < 1638; uiI++)
			;		//  for-Schleife wird 1638-mal durchlaufen. Dies
					//  verursacht eine Zeitverzögerung von ca. 5ms.
}

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
