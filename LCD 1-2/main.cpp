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


	LCD lcd;
	lcd << 'a';
	//lcd << "Hola" << " " << "Mundo";

	//FT_HANDLE  deviceHandler;
	//FT_HANDLE* jaja=deviceHandler_lcdInit(0);
	//lcdWriteDR(jaja,'A');


	//delete myclass;

	std::cout<<"a";
	getchar();
	return EXIT_SUCCESS;
}
