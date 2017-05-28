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

	for (int i = cadd; i <= MAX_POSITION; i++)  //cheaquear que este bien 
	{
		lcdWriteDR(deviceHandler, ' ');
	}
	return true;


	
	//int oldcadd = cadd;		//se debe mantener la direccion original del cursor
	//do
	//{
	//	lcdWriteDR(deviceHandler,' ');
	//} while (cadd % (MAX_POSITION + 1));

	//cadd = oldcadd;

	//lcdUpdateCursor();
	//return true;
}

basicLCD& LCD::operator<<(const unsigned char c)
{
	lcdWriteDR(deviceHandler, c);
	//falta chequear algo
	return *this;
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
	int columna = ((cadd - 1) % MAX_POSITION);
	if (columna < (MAX_POSITION - 1))
	{
		cadd++;
		lcdUpdateCursor();
		return true;
	}
	else
	{
		return false;
	}
}

bool LCD::lcdMoveCursorLeft()
{
	int columna = ((cadd - 1) % MAX_POSITION);
	if (columna !=0) 
	{
		cadd--;
		lcdUpdateCursor();
		return true;
	}

	else
	{
		return false;
	}
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
	cursorPosition currentPosition = { cadd / MAX_POSITION , cadd % MAX_POSITION }; //fila , columna
	return currentPosition;
}


void LCD::lcdUpdateCursor()
{
	lcdWriteIR(deviceHandler, LCD_SET_DDRAM | (cadd - 1));
}


