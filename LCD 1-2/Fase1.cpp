
#include "Fase1.h"
#include <chrono>
#include <thread>

FT_HANDLE& deviceHandler_lcdInit(int iDevice) //Inicializacion del modo 4 bits.
{
	FT_HANDLE deviceHandler = 0;
	if (FT_Open(iDevice, &deviceHandler) == FT_OK)
	{
		UCHAR Mask = 0xFF;	//Selects all FTDI pins.
		UCHAR Mode = 1; 	// Set asynchronous bit-bang mode
		if (FT_SetBitMode(deviceHandler, Mask, Mode) == FT_OK)	
		{
			lcdWriteNibble(&deviceHandler, FUNCTION_SET_8, IR);					//1. Enviar el nibble alto de “function set” con el modo en 8 bits
			std::this_thread::sleep_for(std::chrono::milliseconds(50));			//2. Esperar 4 ms
			lcdWriteNibble(&deviceHandler, FUNCTION_SET_8, IR);					//3. Enviar el nibble alto de “function set” con el modo en 8 bits			
			std::this_thread::sleep_for(std::chrono::microseconds(1000));		//4. Esperar 100 µs
			lcdWriteNibble(&deviceHandler, FUNCTION_SET_8, IR);					//5. Enviar el nibble alto de “function set” con el modo en 8 bits
			lcdWriteNibble(&deviceHandler, FUNCTION_SET_4, IR);					//6. Enviar el nibble alto de “function set” con el modo en 4 bits.
			lcdWriteByte(&deviceHandler, FS_4B_2L_5x8, IR);						//7. Enviar la instrucción “function set” con el modo en 4 bits, 2 líneas y fuente de 5x8
			lcdWriteByte(&deviceHandler, DISPLAY_CONTROL, IR);					//8. Enviar la instrucción “display on / off control” con todo apagado
			lcdWriteByte(&deviceHandler, CLEAR_DISPLAY, IR);					//9. Enviar la instrucción “clear screen”
			lcdWriteByte(&deviceHandler, ENTRY_MODE_SET, IR);					//10. Enviar la instrucción “entry mode set”

			return deviceHandler;
		}	
		else
			printf("Couldn't configure LCD\n");
		FT_Close(deviceHandler);
	}
	printf("Couldn't open USB %d\n", iDevice);
	return deviceHandler;
}


void lcdWriteIR(FT_HANDLE * deviceHandler, BYTE valor)
{
	lcdWriteByte(deviceHandler, valor, IR);
}


void lcdWriteDR(FT_HANDLE * deviceHandler, BYTE valor)
{
	lcdWriteByte(deviceHandler, valor, DR);
}


void lcdWriteNibble(FT_HANDLE * deviceHandler, BYTE value, BYTE RS) //RS vale 0x00(lcdIR) o 0x02(lcdDR)
{
	char buffer[1];
	unsigned long BytesSent = 0;
	buffer[0] = ((value << 4) & 0xF0);								//buffer[0] es enable; el menos significativo
	buffer[0] |= RS;
	if (FT_Write(*deviceHandler, buffer, 1, &BytesSent) == FT_OK)	//enable en 0 || RS esta en lo que me vino || nibble en value
	{
		Sleep(1); 
		buffer[0] |= LCD_E;											//define LCD_E 0x01; //prendo el bit menos significativo

			if (FT_Write(*deviceHandler, buffer, 1, &BytesSent) == FT_OK) //enable en 1
			{
				Sleep(10); 
				buffer[0] &= (~LCD_E);
				FT_Write(*deviceHandler, buffer, 1, &BytesSent);
				Sleep(1); 
			}
	}
}


void lcdWriteByte(FT_HANDLE * deviceHandler, BYTE value, BYTE RS) //Llama a write nibble con la parte alta y con la baja del byte
{
	lcdWriteNibble(deviceHandler, ((value >> 4)&(0x0F)), RS);
	lcdWriteNibble(deviceHandler, (value & 0x0F), RS);
}
