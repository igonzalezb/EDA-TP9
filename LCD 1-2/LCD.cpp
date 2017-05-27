#include "LCD.h"

bool LCD::lcdInitOk()
{
	//LA QUE NOS DIO AGUSTIN
	//lcdWriteNibble(0x03, IR);
	//wait(4 milisegundos);
	//lcdWriteNibble(0x03, IR);
	//wait(100 microsegundos); //1ms 
	//lcdWriteNibble(0x03, IR);
	//lcdWriteNibble(0x02, IR); // todas las escrituras consisten en 2 nibbles
	//						  //ACA ESTOY EN 4 BITS
	//lcdWriteByte(0x38, IR); // va llamar a lcdWritenNibble con la parte alta y despues con la parte baja 
	//							//lcdWriteNibble(0x03,IR)
	//							//lcdWriteNibble(0x08,IR)
	//lcdWriteBytes(0x0F, IR); //prende el display
	//lcdWriteByte(0x01, IR);
	//lcdWriteByte(0x06, IR);

	//LA QUE NOS DIO PEDRO
	//initOK = 1;
	//Sleep(50);
	//initOK &= lcdWriteNibble(0x30);
	//Sleep(5);
	//initOK &= lcdWriteNibble(0x30);
	//Sleep(1);
	//initOK &= lcdWriteNibble(0x30);
	//Sleep(1);
	//initOK &= lcdWriteNibble(0x20);
	//Sleep(1);
	//initOK &= lcdWriteIR(FUNTION_SET);
	//Sleep(1);
	//initOK &= lcdWriteIR(DISPLAY_CONTROL);
	//Sleep(1);
	//initOK &= lcdWriteIR(CLEAR_SCREEN);
	//Sleep(10);
	//initOK &= lcdWriteIR(ENTRY_MODE_SET);
	//Sleep(1);
	//pos.column = 0;
	//pos.row = 0;

}

FT_STATUS LCD::lcdGetError()
{

}

bool LCD::lcdClear()
{

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

}

bool LCD::lcdMoveCursorLeft()
{

}

bool LCD::lcdSetCursorPosition(const cursorPosition pos)
{

}

cursorPosition LCD::lcdGetCursorPosition()
{

}



void lcdWriteNibble(FT_HANDLE * deviceHandler, BYTE value, BYTE RS) //RS vale 0x00(lcdIR) o 0x02(lcdDR) 
{
	char buffer[1];
	unsigned int BytesSend = 0;
	buffer[0] = ((value < 4) & 0xF0); //buffer[0] es enable osea el menos significativo
	buffer[0] |= RS;
	if (FT_write(h, buffer, 1, &BytesSend) == FT_OK) //enable en 0 || RS esta en lo que me vino || nibble en value
	{
		Sleep(1); //1ms
		buffer[0] |= LCD_E //define LCD_E 0x01; //prendo el bit menos significativo
			if (FT_write(h, buffer, 1, &bytesSent) == FT_ok) //enable en 1
			{
				Sleep(10) //10ms
				buffer[0] &= (~LCD_E);
				FT_write(h, buffer, 1, &bytesSent);
				Sleep(1); //1ms
			}
	}

}

void lcdWriteByte(FT_HANDLE * deviceHandler, BYTE value, BYTE RS)
{
	lcdWriteNibble(deviceHandler,((value>>4)&(0x0F)), RS);
	lcdWriteNibble(deviceHandler,(value&0x0F), RS);
}