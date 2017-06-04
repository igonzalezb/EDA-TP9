#pragma once

#include "Fase2.h"


class LCD : public basicLCD
{
public:
	LCD();

	~LCD();
	
	bool lcdInitOk();

	FT_STATUS lcdGetError();

	bool lcdClear();

	bool lcdClearToEOL();

	basicLCD& operator<<(const unsigned char c);

	basicLCD& operator<<(const unsigned char * c);

	bool lcdMoveCursorUp();

	bool lcdMoveCursorDown();

	bool lcdMoveCursorRight();

	bool lcdMoveCursorLeft();

	bool lcdSetCursorPosition(const cursorPosition pos);

	cursorPosition lcdGetCursorPosition();

	void lcdUpdateCursor();

private:
	FT_HANDLE deviceHandler;
};