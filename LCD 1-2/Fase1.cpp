
#include "Fase1.h"
#include "ftd2xx.h"

//Para inicializar en el modo de 4 bits debemos seguir esta secuencia :
//1. Enviar el nibble alto de “function set” con el modo en 8 bits (function set: 00
//2. Esperar 4 ms
//3. Enviar el nibble alto de “function set” con el modo en 8 bits
//4. Esperar 100 µs
//5. Enviar el nibble alto de “function set” con el modo en 8 bits
//6. Enviar el nibble alto de “function set” con el modo en 4 bits.
//(a partir de ahora enviamos las instrucciones separadas en dos nibbles)
//7. Enviar la instrucción “function set” con el modo en 4 bits, 2 líneas y fuente de 5x8
//8. Enviar la instrucción “display on / off control” con todo apagado
//9. Enviar la instrucción “clear screen”
//10. Enviar la instrucción “entry mode set”
//Para referencias del fabricante, ver la hoja de datos(Figura 24)
FT_HANDLE * deviceHandler_lcdInit(int iDevice)	//REVISAR 
{
	FT_HANDLE deviceHandler;
	if (FT_Open(iDevice, &deviceHandler) == FT_OK)
	{
		UCHAR Mask = 0xFF;	//Selects all FTDI pins.
		UCHAR Mode = 1; 	// Set asynchronous bit-bang mode
		if (FT_SetBitMode(deviceHandler, Mask, Mode) == FT_OK)	// Sets LCD as asynch bit mode. Otherwise it doesn't work.
		{
			//lcdWriteNibble(FT_HANDLE * deviceHandler, BYTE value, BYTE RS);

			lcdWriteNibble(&deviceHandler, 0x03, IR); //definir que lpo estoy haciendo en el IR
								  //wait(4ms);
			lcdWriteNibble(&deviceHandler, 0x03, IR);
			//wait (1ms);
			lcdWriteNibble(&deviceHandler, 0x03, IR);
			lcdWriteNibble(&deviceHandler, 0x02, IR);

			//A partir de aca se envian instrucciones de a bytes (que llama dos veces a nibble)

			//Enviar la instrucción “function set” con el modo en 4 bits, 2 líneas y fuente de 5x8:	0010 1000
			//lcdWriteNibble(FT_HANDLE * deviceHandler, 0x02, IR); //parte alta	
			//lcdWriteNibble(FT_HANDLE * deviceHandler, 0x08, IR); // parte baja
			lcdWriteByte(&deviceHandler, 0x40, IR); // parte baja

								//Enviar la instrucción “display on / off control” con todo apagado 0000 1000
								//lcdWriteNibble(FT_HANDLE * deviceHandler, 0x00, IR); //parte alta
								//lcdWriteNibble(FT_HANDLE * deviceHandler, 0x08, IR); // parte baja
			lcdWriteByte(&deviceHandler, 0x08, IR); // parte baja

								//Enviar la instrucción “clear screen” (clear display): 0000 0001
								//lcdWriteNibble(FT_HANDLE * deviceHandler, 0x00, IR); //parte alta
								//lcdWriteNibble(FT_HANDLE * deviceHandler, 0x01, IR); // parte baja
			lcdWriteByte(&deviceHandler, 0x01, IR); // parte baja

								//Enviar la instrucción “entry mode set”: (cursor se desplaza hacia la derecha:increment y no acompaña shift:0) 0000 0110
								//lcdWriteNibble(FT_HANDLE * deviceHandler, 0x00, IR); //parte alta
								//lcdWriteNibble(FT_HANDLE * deviceHandler, 0x06, IR); // parte baja
			lcdWriteByte(&deviceHandler, 0x06, IR); // parte baja


			return &deviceHandler;
		}
		
		else
			printf("Couldn't configure LCD\n");

		FT_Close(deviceHandler);
	}

	printf("Couldn't open USB %d\n", iDevice);
	return nullptr;
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
				Sleep(10); //10ms
				buffer[0] &= (~LCD_E);
				FT_Write(deviceHandler, buffer, 1, &BytesSent);
				Sleep(1); //1ms
			}
	}

}

void lcdWriteByte(FT_HANDLE * deviceHandler, BYTE value, BYTE RS) //esta bien esto? tiene que llamar a write nibble con parte baja y despues alta
{
	lcdWriteNibble(deviceHandler, ((value >> 4)&(0x0F)), RS);
	lcdWriteNibble(deviceHandler, (value & 0x0F), RS);
}
