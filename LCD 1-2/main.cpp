
#include <iostream>
#include "LCD.h"


int main()
{
	LCD lcd;

	const unsigned char str1[] = "EN EDA NO ANDA NADA."; 
	lcd << str1;
	Sleep(4);
	lcd.lcdClear();
	const unsigned char str2[] = "LAS COSAS TURBIAS, SI.";
	lcd << str2;
	Sleep(4);
	lcd.lcdClear();
	lcd.lcdMoveCursorDown();
	const unsigned char str3[] = "chau";
	lcd << str3;

	getchar();
	return EXIT_SUCCESS;
}
