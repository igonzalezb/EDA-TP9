
#include "Fase3.h"


void printDisplay(Titulares data, LCD lcd)
{

	for (auto rit = data.getList().begin(); rit != data.getList().end(); rit++)
	{
		showDate(lcd, rit->getDate());
		showTitle(lcd, data.getChTitle() + ": " + rit->getTitle());
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
		title16 = title.substr(i, 16);

		//printf("%s\n", title16.c_str());
		lcd.lcdClearToEOL();
		lcd << title16.c_str();
		Sleep(5);

	}
}



