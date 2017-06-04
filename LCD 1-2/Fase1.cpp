
#include "Fase1.h"
#include <chrono>
#include <thread>

//Para inicializar en el modo de 4 bits debemos seguir esta secuencia :
//1. Enviar el nibble alto de “function set” con el modo en 8 bits 
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
			std::this_thread::sleep_for(std::chrono::milliseconds(50)); 

			lcdWriteNibble(&deviceHandler, 0x03, IR);					
			std::this_thread::sleep_for(std::chrono::microseconds(1000));

			lcdWriteNibble(&deviceHandler, 0x03, IR);
			lcdWriteNibble(&deviceHandler, 0x02, IR);
			lcdWriteByte(&deviceHandler, 0x38, IR); //28
			lcdWriteByte(&deviceHandler, 0x08, IR); 
			lcdWriteByte(&deviceHandler, 0x01, IR); 
			lcdWriteByte(&deviceHandler, 0x06, IR); 

			
	/*		Sleep(50);
			lcdWriteNibble(&deviceHandler, 0x30);
			Sleep(5);
			lcdWriteNibble(&deviceHandler, 0x30);
			Sleep(1);
			lcdWriteNibble(&deviceHandler, 0x30);
			Sleep(1);
			lcdWriteNibble(&deviceHandler, 0x20);
			Sleep(1);
			lcdWriteIR(&deviceHandler, 0x28);
			Sleep(1);
			lcdWriteIR(&deviceHandler, 0x08);
			Sleep(1);
			lcdWriteIR(&deviceHandler, 0x01);
			Sleep(10);
			lcdWriteIR(&deviceHandler, 0x06);
			Sleep(1);*/

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


void lcdWriteNibble(FT_HANDLE * deviceHandler, BYTE value, BYTE RS) //RS vale 0x00(lcdIR) o 0x02(lcdDR) //NUESTRAAAA
{
	char buffer[1];
	unsigned long BytesSent = 0;
	buffer[0] = ((value << 4) & 0xF0); //buffer[0] es enable osea el menos significativo
	buffer[0] |= RS;
	if (FT_Write(*deviceHandler, buffer, 1, &BytesSent) == FT_OK) //enable en 0 || RS esta en lo que me vino || nibble en value
	{
		Sleep(1); //1ms
		buffer[0] |= LCD_E; //define LCD_E 0x01; //prendo el bit menos significativo

			if (FT_Write(*deviceHandler, buffer, 1, &BytesSent) == FT_OK) //enable en 1
			{
				Sleep(10); 
				buffer[0] &= (~LCD_E);
				FT_Write(*deviceHandler, buffer, 1, &BytesSent);//se esta poniendo negro el cuadradito de la esquina arriba a la derecha
				Sleep(1); 
			}
	}
}

//bool lcdWriteNibble(unsigned char value) //RAMA
//{
//	//Envia un nibble al puerto.
//	bool prog_status = false;//true si estuvo todo 10 puntitos
//	DWORD sizeSent = 0;
//	unsigned char info = LCD_RS;
//
//	if ((status_display = FT_Write(deviceHandler, &info, 1, &sizeSent)) == FT_OK)
//	{
//		info = value;
//		if ((status_display = FT_Write(display_handle, &info, 1, &sizeSent)) == FT_OK)
//		{
//			Sleep(1);
//			info = value | LCD_E;
//			if ((status_display = FT_Write(display_handle, &info, 1, &sizeSent)) == FT_OK)
//			{
//				mySleep(1);
//				info = value;
//				if ((status_display = FT_Write(display_handle, &info, 1, &sizeSent)) == FT_OK)
//				{
//					mySleep(1);
//					prog_status = true;
//				}
//			}
//		}
//	}
//	return prog_status;
//}

//void lcdWriteNibble(FT_HANDLE * deviceHandler, BYTE value) //AGUSTIN
//{
//	value &= 0xF2;
//	BYTE info = value&LCD_RS;
//	DWORD sizeSent = 0;
//	FT_STATUS status = FT_OK;
//	status += FT_Write(*deviceHandler, &info, 1, &sizeSent);
//	info = value;
//	status += FT_Write(*deviceHandler, &info, 1, &sizeSent);
//	Sleep(1);
//	info = value | LCD_E;
//	status += FT_Write(*deviceHandler, &info, 1, &sizeSent);
//	Sleep(1);
//	info = value;
//	status += FT_Write(*deviceHandler, &info, 1, &sizeSent);
//	Sleep(1);
//}

//NUESTRA
void lcdWriteByte(FT_HANDLE * deviceHandler, BYTE value, BYTE RS) //esta bien esto? tiene que llamar a write nibble con parte baja y despues alta
{
	lcdWriteNibble(deviceHandler, ((value >> 4)&(0x0F)), RS);
	lcdWriteNibble(deviceHandler, (value & 0x0F), RS);
}

//AGUSTIN
//#define MSN(x) ((x)&0xF0)
//#define LSN(x) (((x)<<4)&0xF0)
//void lcdWriteByte(FT_HANDLE * deviceHandler, BYTE value, BYTE rs)
//{
//
//	lcdWriteNibble(deviceHandler, ((value&(0xF0)) | rs));
//	lcdWriteNibble(deviceHandler, ((value << 4) & 0xF0) | rs);
//}
