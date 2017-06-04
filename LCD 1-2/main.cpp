
#include <iostream>
#include "LCD.h"


int main()
{
	LCD lcd;

	const unsigned char str1[] = "Finalmente ANDA."; 
	lcd << str1;
	Sleep(5);
	lcd.lcdClear();
	const unsigned char str2[] = "By group 1 :)";
	lcd << str2;
	Sleep(5);
	lcd.lcdClear();
	lcd.lcdMoveCursorDown();
	const unsigned char str3[] = "chau ;)";
	lcd << str3;

	getchar();
	return EXIT_SUCCESS;
}
