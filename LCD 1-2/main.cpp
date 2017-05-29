#include <iostream>
#include "LCD.h"

//using namespace LCD;

int main()
{
	//LCD* myclass = new LCD();

	//myclass->lcdClear();

	//const unsigned char str[] = "HOLA";
	//*myclass << str;
	//*myclass << 'h';


	//LCD lcd;
	//lcd << 'a' << 'a' << 'a';
	//lcd << "Hola" << " " << "Mundo";

	FT_HANDLE  deviceHandler;
	deviceHandler_lcdInit(0);
	lcdWriteDR(&deviceHandler,'A');

	std::cout << "chau";
	getchar();
	//delete myclass;
	return EXIT_SUCCESS;
}
