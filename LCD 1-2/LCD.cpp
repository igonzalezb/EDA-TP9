#include "LCD.h"


#define CLEAR_DISPLAY				0x01	//0000 0001
#define CURSOR_DISPLAY_SHIFT_RIGHT		0x14	//0001 0100
#define CURSOR_DISPLAY_SHIFT_LEFT		0x10	//0001 0000

LCD::LCD()
{
	cadd = 1;
	lcdInitOk();
}

LCD::~LCD()
{
}

bool LCD::lcdInitOk()
{
	bool found = false;
	for (int i = 0; (i < 10) && !found; i++)
	{
		deviceHandler = deviceHandler_lcdInit(i);
		if (deviceHandler != nullptr)
			found = true;
	}
	return true;

}

FT_STATUS LCD::lcdGetError()
{
	return FT_OK;
}

bool LCD::lcdClear()
{
	lcdWriteIR(deviceHandler, CLEAR_DISPLAY);
	cadd = 1;
	return true;
}

bool LCD::lcdClearToEOL()
{

}

basicLCD& LCD::operator<<(const unsigned char c)
{

}

basicLCD& LCD::operator<<(const unsigned char * c)
{

}

bool LCD::lcdMoveCursorUp()
{

}

bool LCD::lcdMoveCursorDown()
{

}

bool LCD::lcdMoveCursorRight()
{
	lcdWriteIR(deviceHandler, CURSOR_DISPLAY_SHIFT_RIGHT);
	cadd++;
}

bool LCD::lcdMoveCursorLeft()
{
	
	lcdWriteIR(deviceHandler, CURSOR_DISPLAY_SHIFT_LEFT);
	cadd--;
}

bool LCD::lcdSetCursorPosition(const cursorPosition pos)
{
	if (pos.column < MAX_POSITION && pos.row < 2)
	{
		cadd = pos.column + pos.row * MAX_POSITION; //+ 1
		lcdUpdateCursor();
		return true;
	}
	else
		return false;




}

cursorPosition LCD::lcdGetCursorPosition()
{
	cursorPosition currentPosition = { cadd / MAX_POSITION , cadd % MAX_POSITION };
	return currentPosition;
}


void LCD::lcdUpdateCursor()
{
	lcdWriteIR(deviceHandler, LCD_SET_DDRAM | (cadd - 1));
}


