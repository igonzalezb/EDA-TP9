
#include "Fase1.h"
#include <chrono>
#include <thread>

//Para inicializar en el modo de 4 bits debemos seguir esta secuencia :
//1. Enviar el nibble alto de �function set� con el modo en 8 bits 
//2. Esperar 4 ms
//3. Enviar el nibble alto de �function set� con el modo en 8 bits
//4. Esperar 100 �s
//5. Enviar el nibble alto de �function set� con el modo en 8 bits
//6. Enviar el nibble alto de �function set� con el modo en 4 bits.
//(a partir de ahora enviamos las instrucciones separadas en dos nibbles)
//7. Enviar la instrucci�n �function set� con el modo en 4 bits, 2 l�neas y fuente de 5x8
//8. Enviar la instrucci�n �display on / off control� con todo apagado
//9. Enviar la instrucci�n �clear screen�
//10. Enviar la instrucci�n �entry mode set�
//Para referencias del fabricante, ver la hoja de datos(Figura 24)



FT_HANDLE& deviceHandler_lcdInit(int iDevice)	//REVISAR 
{
	FT_HANDLE deviceHandler = 0;
	if (FT_Open(iDevice, &deviceHandler) == FT_OK)
	{
		UCHAR Mask = 0xFF;	//Selects all FTDI pins.
		UCHAR Mode = 1; 	// Set asynchronous bit-bang mode
		if (FT_SetBitMode(deviceHandler, Mask, Mode) == FT_OK)	
		{
			lcdWriteNibble(&deviceHandler, 0x03, IR); 
			//Sleep(4);
			std::this_thread::sleep_for(std::chrono::milliseconds(4));

			lcdWriteNibble(&deviceHandler, 0x03, IR);
			//Sleep(0.1);						
			std::this_thread::sleep_for(std::chrono::microseconds(100));

			lcdWriteNibble(&deviceHandler, 0x03, IR);
			lcdWriteNibble(&deviceHandler, 0x02, IR);
			lcdWriteByte(&deviceHandler, 0x38, IR); //28
			lcdWriteByte(&deviceHandler, 0x08, IR); 
			lcdWriteByte(&deviceHandler, 0x01, IR); 
			lcdWriteByte(&deviceHandler, 0x06, IR); 


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
	buffer[0] = ((value << 4) & 0xF0); //buffer[0] es enable osea el menos significativo
	buffer[0] |= RS;
	if (FT_Write(deviceHandler, buffer, 1, &BytesSent) == FT_OK) //enable en 0 || RS esta en lo que me vino || nibble en value
	{
		Sleep(1); //1ms
		buffer[0] |= LCD_E; //define LCD_E 0x01; //prendo el bit menos significativo

			if (FT_Write(deviceHandler, buffer, 1, &BytesSent) == FT_OK) //enable en 1
			{
				Sleep(10); 
				buffer[0] &= (~LCD_E);
				FT_Write(deviceHandler, buffer, 1, &BytesSent);
				Sleep(1); 
			}
	}

}

void lcdWriteByte(FT_HANDLE * deviceHandler, BYTE value, BYTE RS) //esta bien esto? tiene que llamar a write nibble con parte baja y despues alta
{
	lcdWriteNibble(deviceHandler, ((value >> 4)&(0x0F)), RS);
	lcdWriteNibble(deviceHandler, (value & 0x0F), RS);
}
