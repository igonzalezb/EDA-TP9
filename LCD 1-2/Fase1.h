#pragma once
#include <cstdint>
#include <windows.h>
#include <iostream>

#define FTD2XX_EXPORTS
extern "C"
{
	#include "ftd2xx.h"
}


typedef uint8_t BYTE;

#define IR	0x00 //tendrian que ser un byte. LOS PONEMOS ACA Y ASI??????
#define DR	0x02

#define PORT_P0		0	//ENUM????
#define PORT_P1		1
#define PORT_P2		2
#define PORT_P3		3
#define PORT_P4		4
#define PORT_P5		5
#define PORT_P6		6
#define PORT_P7		7


#define LCD_RS		(1 << PORT_P1)		//LCD RS, LCD_RS = 0000 0010 
#define LCD_E		(1 << PORT_P0)		//



#define LED_ROJO	(1 << PORT_P0)    
#define LED_VERDE	(1 << PORT_P7) 
#define MASK_LEDS	(LED_ROJO | LED_VERDE)		//MASK_LEDS = 1000 0001   
#define NOT_MASK_LEDS	~(MASK_LEDS)			//NOT_MASK_LEDS = 0111 1110


// Hardware not inverted (active high) 
#define LCD_RS_ON	(LCD_RS) 
#define LCD_RS_OFF	(LCD_RS ^ LCD_RS)

// Hardware inverted (active low) 
#define LCD_TEST_ON	(LCD_TEST ^ LCD_TEST)  
#define LCD_TEST_OFF	(LCD_TEST)

#define LCD_SET_DDRAM	0x80		//1000 0000

#define MAX_POSITION	16
#define MAX_ROW			2

#define ROW_1	0
#define ROW_2	4
#define CLEAR_DISPLAY					0x01	//0000 0001

#define SET_ADDRESS(a,b)			(0x80 + (a) + (b) * 0x40)


//Inicializa el FTDI y el LCD 
FT_HANDLE& deviceHandler_lcdInit(int iDevice);

//Escribe un byte al IR 
void lcdWriteIR(FT_HANDLE * deviceHandler, BYTE valor);

//Escribe un byte al DR 
void lcdWriteDR(FT_HANDLE * deviceHandler, BYTE valor);

//La primera función escribe directamente un nibble al display.Por ejemplo :
//lcdWriteNibble(deviceHandler, LCD_RS | LCD_D6);

void lcdWriteNibble(FT_HANDLE * deviceHandler, BYTE value, BYTE RS); //NUESTRA
//void lcdWriteNibble(FT_HANDLE * deviceHandler, BYTE value); //AG

//Escribe el byte recibido al display.Si utilizamos el modo 4 bits
//deberemos realizar dos llamadas a lcdWrietNibble(); por lo que la primera función será
//invocada dos veces por la segunda.
void lcdWriteByte(FT_HANDLE * deviceHandler, BYTE value, BYTE RS);