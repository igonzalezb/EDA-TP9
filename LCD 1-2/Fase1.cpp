#include "Fase1.h"

FT_HANDLE * deviceHandler_lcdInit(int iDevice)
{
	return nullptr;
}

void lcdWriteIR(FT_HANDLE * deviceHandler, BYTE valor)
{
}

void lcdWriteDR(FT_HANDLE * deviceHandler, BYTE valor)
{
}

void lcdWriteNibble(FT_HANDLE * deviceHandler, BYTE value, BYTE RS) //RS vale 0x00(lcdIR) o 0x02(lcdDR) 
{
	char buffer[1];
	unsigned int BytesSent = 0;
	buffer[0] = ((value << 4) & 0xF0); //buffer[0] es enable osea el menos significativo
	buffer[0] |= RS;
	if (FT_write(deviceHandler, buffer, 1, &BytesSent) == FT_OK) //enable en 0 || RS esta en lo que me vino || nibble en value
	{
		Sleep(1); //1ms
		buffer[0] |= LCD_E //define LCD_E 0x01; //prendo el bit menos significativo
			if (FT_write(deviceHandler, buffer, 1, &bytesSent) == FT_OK) //enable en 1
			{
				Sleep(10) //10ms
					buffer[0] &= (~LCD_E);
				FT_write(deviceHandler, buffer, 1, &BytesSent);
				Sleep(1); //1ms
			}
	}

}

void lcdWriteByte(FT_HANDLE * deviceHandler, BYTE value, BYTE RS)
{
	lcdWriteNibble(deviceHandler, ((value >> 4)&(0x0F)), RS);
	lcdWriteNibble(deviceHandler, (value & 0x0F), RS);
}
