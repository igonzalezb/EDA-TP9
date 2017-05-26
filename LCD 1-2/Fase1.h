#pragma once
#define FTD2XX_EXPORTS
#include "ftd2xx.h"


#define PORT_P0		0	//ENUM????
#define PORT_P1		1
#define PORT_P2		2
#define PORT_P3		3
#define PORT_P4		4
#define PORT_P5		5
#define PORT_P6		6
#define PORT_P7		7




#define LCD_RS		(1 << PORT_P1)		//LCD RS, LCD_RS = 0000 0010 
#define LCD_E		(1 << PORT_P0)		//????



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





//Inicializa el FTDI y el LCD 
FT_HANDLE * deviceHandler_lcdInit(int iDevice);

//Escribe un byte al IR 
void lcdWriteIR(FT_HANDLE * deviceHandler, BYTE valor);

//Escribe un byte al DR 
void lcdWriteDR(FT_HANDLE * deviceHandler, BYTE valor);