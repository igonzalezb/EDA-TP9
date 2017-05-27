#include "Fase1.h"

void lcdWriteNibble(FT_HANDLE * deviceHandler, BYTE value);
void lcdWriteByte(FT_HANDLE * deviceHandler, BYTE value, BYTE rs);


class LCD : public basicLCD
{
public:
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

private:

};