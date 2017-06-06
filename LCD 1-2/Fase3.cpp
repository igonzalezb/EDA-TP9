
#include "Fase3.h"


void printDisplay(Titulares data, LCD& lcd)
{

	for (auto rit = data.getList().begin(); rit != data.getList().end(); rit++)
	{
		showDate(lcd, rit->getDate());
		showTitle(lcd, data.getChTitle() + ": " + rit->getTitle());
	}
	Sleep(100);
	lcd.lcdClear();
}


void showDate(LCD& lcd, string date)
{
	lcd.lcdClear();
	lcd << date.c_str();
}

void showTitle(LCD& lcd, string title)
{
	for (int i = 0; i < title.length(); i++)
	{
		string title16;
		title16 = title.substr(i, 16);
		if (title16.length() < 16) 
		{
			for (unsigned int j = title16.length(); (j < 16); j++) { title16 += ' '; }
		}
		lcd.lcdMoveCursorDown();
		lcd << title16.c_str();
		
	}
}



