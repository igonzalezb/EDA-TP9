
#include "Fase3.h"


void printDisplay(Titulares data, LCD lcd)
{

	for (auto rit = data.getList().begin(); rit != data.getList().end(); rit++)
	{
		showDate(lcd, rit->getDate());
		showTitle(lcd, rit->getTitle());
		Sleep(5);
		
	}
}


void showDate(LCD lcd, string date)
{
	lcd.lcdClear();
	lcd << date.c_str();

}



void showTitle(LCD lcd, string title)
{
	/*lcd.lcdMoveCursorDown();
	lcd.lcdClearToEOL();*/

	for (int i = 0; i < title.length(); i++)
	{
		string title16;
		title.copy()
	}
}



