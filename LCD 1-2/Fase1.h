#pragma once
#include <cstdint>
#include <windows.h>

#define FTD2XX_EXPORTS
extern "C"
{
	#include "ftd2xx.h"
}



typedef uint8_t BYTE;

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

//La primera función escribe directamente un nibble al display.Por ejemplo :
//lcdWriteNibble(deviceHandler, LCD_RS | LCD_D6);
void lcdWriteNibble(FT_HANDLE * deviceHandler, BYTE value, BYTE RS);

//Escribe el byte recibido al display.Si utilizamos el modo 4 bits
//deberemos realizar dos llamadas a lcdWrietNibble(); por lo que la primera función será
//invocada dos veces por la segunda.
void lcdWriteByte(FT_HANDLE * deviceHandler, BYTE value, BYTE RS);


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
//Para referencias del fabricante, ver la hoja de datos(Figura 24).