
#include "Fase3.h"


void printDisplay()
{

}


void showDate(Titulares data, LCD lcd)
{
	
	for (auto rit = data.getList().begin(); rit != data.getList().end(); rit++)
	{
		lcd << rit->getDate().c_str();
		Sleep(5);
		lcd.lcdClear();
	}

}



//void showTitle(Titulares data, LCD lcd)
//{
//
//}



