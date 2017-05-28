#include "LCD.h"
#include "Fase1.h"





#define CLEAR_DISPLAY				0x01	//0000 0001
#define CURSOR_DISPLAY_SHIFT_RIGHT		0x14	//0001 0100
#define CURSOR_DISPLAY_SHIFT_LEFT		0x10	//0001 0000

bool LCD::lcdInitOk()
{


}

FT_STATUS LCD::lcdGetError()
{

}

bool LCD::lcdClear()
{
	lcdWriteByte(CLEAR_DISPLAY, IR);
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

	lcdWriteByte(CURSOR_DISPLAY_SHIFT_RIGHT, IR);
}

bool LCD::lcdMoveCursorLeft()
{
	lcdWriteByte(CURSOR_DISPLAY_SHIFT_LEFT, IR);
}

bool LCD::lcdSetCursorPosition(const cursorPosition pos)
{
	for (int i = pos; i < lastPosition; i++)
	{
		lcdWriteByte(' ', DR);
	}
}

cursorPosition LCD::lcdGetCursorPosition()
{

}



