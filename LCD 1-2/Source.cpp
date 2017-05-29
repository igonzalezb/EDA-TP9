#include <iostream>
#include "Fase1.h"
//#include "Fase2.h"
#include "LCD.h"

int main()
{
	LCD* myclass = new LCD;

	myclass->lcdClear();

	const unsigned char str[] = "kkkkkk";
	*myclass << &str[0];
	*myclass << 'h';



	return EXIT_SUCCESS;
}
