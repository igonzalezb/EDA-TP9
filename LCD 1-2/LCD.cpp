#include "LCD.h"



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
	for (int i = 1; (i < 10) && !found; i++)
	{
		deviceHandler = deviceHandler_lcdInit(i);
		if (deviceHandler != 0)
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
	lcdWriteIR(&deviceHandler, CLEAR_DISPLAY);
	cadd = 1;
	return true;
}

bool LCD::lcdClearToEOL()
{
	int _cadd = cadd;

	for (int i = (cadd % MAX_POSITION); i<= MAX_POSITION; i++)  //cheaquear que este bien 
	{

		escritura(' ');
	}

	cadd = _cadd;
	lcdUpdateCursor();

	return true;

}

basicLCD& LCD::operator<<(const unsigned char c)
{
	
	escritura(c);

	return *this;
}



basicLCD& LCD::operator<<(const unsigned char * c)
{
	for (int i = 0; c[i]!='\0'; i++)
	{
		escritura(c[i]);
	}

	return *this;
}

bool LCD::lcdMoveCursorUp()
{
	cursorPosition Pos = lcdGetCursorPosition();

	if (Pos.row == ROW_2)
	{
		Pos.row = ROW_1;
		lcdSetCursorPosition(Pos);
		lcdUpdateCursor();
		return true;
	}
	else
	{
		return false;
	}
}

bool LCD::lcdMoveCursorDown()
{
	cursorPosition Pos = lcdGetCursorPosition();

	if (Pos.row == ROW_1)
	{
		Pos.row = ROW_2;
		lcdSetCursorPosition(Pos);
		lcdUpdateCursor();
		return true;
	}
	else
	{
		return false;
	}
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
		cadd = pos.column + pos.row * MAX_POSITION + 1; // +1 porque lcdUpdateCursor() 
														// posiciona uno antes
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
	lcdWriteIR(&deviceHandler, LCD_SET_DDRAM | (cadd - 1));

}


void LCD::escritura(const unsigned char c)
{
	lcdWriteDR(&deviceHandler, c);
	cadd++;
	lcdUpdateCursor();

	cursorPosition Pos = lcdGetCursorPosition();

	switch (Pos.row)
	{
	case ROW_1:
	{
		if (Pos.column == MAX_POSITION)
		{
			Pos.row = ROW_2;
			Pos.column = 0;

		}
		else
		{
			Pos.column++;
		}

		lcdSetCursorPosition(Pos); //cambia el valor de cadd
		lcdUpdateCursor();
	}
	break;

	case ROW_2:
	{
		if (Pos.column == MAX_POSITION)
		{
			Sleep(1000);

			lcdClear();

			Pos.row = ROW_1;
			Pos.column = 0;
		}
		else
		{
			Pos.column++;
		}
		lcdSetCursorPosition(Pos);
		lcdUpdateCursor();
	}
	break;

	}
}
