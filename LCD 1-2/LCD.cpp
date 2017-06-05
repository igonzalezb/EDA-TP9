#include "LCD.h"

LCD::LCD()
{
	cadd = 1;
	lcdInitOk();
	lcdClear();

}

LCD::~LCD()
{
	FT_Close(deviceHandler);
}

bool LCD::lcdInitOk()
{
	bool found = false;
	for (int i = 1; (i < 10) && !found; i++)
	{
		deviceHandler = deviceHandler_lcdInit(i);
		if (deviceHandler != 0)
			found = true;
	}

	const unsigned char str[] = "   ";
	*this << str;
	return found;
}

FT_STATUS LCD::lcdGetError()
{
	return FT_OK;
}

bool LCD::lcdClear()
{
	bool status = true;
	lcdWriteIR(&deviceHandler, CLEAR_DISPLAY);
	cursorPosition pos;				
	pos.column = 0;				
	pos.row = 0;
	return (status &= lcdSetCursorPosition(pos));
}

bool LCD::lcdClearToEOL()
{
	int _cadd = cadd;
	for (int i = (cadd % MAX_POSITION); i<= MAX_POSITION; i++)
	{
		*this << ' ';
	}
	cadd = _cadd;
	lcdUpdateCursor();
	return true;
}

basicLCD& LCD::operator<<(const unsigned char c)
{
	lcdWriteDR(&deviceHandler,c);
	lcdMoveCursorRight();
	Sleep(1);
	return *this;
}

basicLCD& LCD::operator<<(const unsigned char * c)
{
	for (int i = 0; c[i]!='\0'; i++)
	{
		*this<<(c[i]);
	}
	return *this;
}

bool LCD::lcdMoveCursorUp()
{
	bool status = true;
	cursorPosition pos;
	pos = lcdGetCursorPosition();
	if (pos.row != 0)
	{
		pos.row--; 	
		status &= lcdSetCursorPosition(pos);
	}
	else
	{
		std::cout << "Couldn't move cursor" << std::endl;
		status = false;
	}
	return status;
}

bool LCD::lcdMoveCursorDown()
{
	bool status = true;
	cursorPosition pos;
	pos = lcdGetCursorPosition();
	if (pos.row < 1)
	{
		pos.row++; 
		status &= lcdSetCursorPosition(pos);
	}
	else
	{
		std::cout << "Cannot move cursor Down" << std::endl;
		status = false;
	}
	return status;
}

bool LCD::lcdMoveCursorRight()
{
	bool status = true;
	cursorPosition pos; 
	pos = lcdGetCursorPosition(); 
	
	if (pos.column < (MAX_POSITION - 1))
	{
		pos.column++;
	}
	else if(pos.column == (MAX_POSITION - 1))
	{
		if (pos.row < MAX_ROW - 1)
		{
			pos.column = 0;
			pos.row++;
		}
		else if (pos.row == (MAX_ROW - 1))
		{
			pos.column = 0;
			pos.row = 0;
		}
	}
	else
	{
		status = false; 
	}
	return (status &= lcdSetCursorPosition(pos));
}

bool LCD::lcdMoveCursorLeft()
{
	bool status = true;
	cursorPosition pos; 
	pos = lcdGetCursorPosition(); 

	if (pos.column > 0) 
		pos.column--; 
	else if (pos.column == 0)
	{
		if (pos.row != 0)
		{
			pos.column = MAX_POSITION - 1;
			pos.row--;
		}
		else if (pos.row == 0)
		{
			pos.column = MAX_POSITION - 1;
			pos.row = MAX_ROW - 1;
		}
	}
	else
	{
		status = false; 
	}
	return (status &= lcdSetCursorPosition(pos));
}

bool LCD::lcdSetCursorPosition(const cursorPosition pos)
{
	bool status = true;

	if ((pos.row>=0) && (pos.row<MAX_ROW) && (pos.column>=0) && (pos.column<MAX_POSITION))
	{
		cadd = ((MAX_POSITION*pos.row) + pos.column) + 1;
		lcdUpdateCursor();
	}
	else
	{
		status = false;
	}

	return status;
}

cursorPosition LCD::lcdGetCursorPosition()
{
	cursorPosition pos;
	unsigned int row;
	if ((cadd - 1) < MAX_POSITION)
		row = 0;
	else
		row = 1;
	pos.column = ((cadd - 1) - (row*MAX_POSITION));
	pos.row = row;
	return pos;
}

void LCD::lcdUpdateCursor()
{
	unsigned int row, column;
	if ((cadd - 1) < MAX_POSITION)
		row = 0;
	else
		row = 1;
	column = ((cadd - 1) - (row*MAX_POSITION));
	lcdWriteIR(&deviceHandler, SET_ADDRESS(column, row));
}