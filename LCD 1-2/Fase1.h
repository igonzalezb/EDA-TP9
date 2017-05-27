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



////Inicializa el FTDI y el LCD 
//FT_HANDLE * deviceHandler_lcdInit(int iDevice);
//
////Escribe un byte al IR 
//void lcdWriteIR(FT_HANDLE * deviceHandler, BYTE valor);
//
////Escribe un byte al DR 
//void lcdWriteDR(FT_HANDLE * deviceHandler, BYTE valor);





struct cursorPosition
{
	int row;
	int column;
};



class basicLCD
{
public:
	/*=====================================================
	* Name: basicLCD
	* Entra: -
	* Resulta: Constructor de la clase. Inicializa el LCD y deja
	* todo listo comenzar a utilizarlo.
	*
	* cadd =1 (cursor address) (ver NOTA 1)
	*=====================================================*/
	basicLCD();


	/*=====================================================
	* Name: ~basicLCD
	* Entra: -
	* Resulta: Destructor de la clase. Libera cualquier recurso
	* que se hubiera tomado de forma de evitar
	* "resources leak".
	*=====================================================*/
	~basicLCD();


	/*=====================================================
	* Name: lcdInitOk
	* Entra: -
	* Resulta: No genera ning�n cambio en el display.
	* Devuelve en su nombre �true� si el display se inicializ�
	* correctamente (el constructor no tuvo errores) o �false
	* en caso contrario.
	*=====================================================*/
	virtual bool lcdInitOk() = 0;


	/*=====================================================
	* Name: lcdGetError
	* Entra: -
	* Resulta: No genera ning�n cambio en el display.
	* Devuelve en su nombre FT_OK si no existe ning�n error.
	* Caso contrario devuelve en su nombre el error que se
	* haya producido trabajando con la librer�a ftd2xx
	*=====================================================*/
	virtual FT_STATUS lcdGetError() = 0;


	/*=====================================================
	* Name: lcdClear
	* Entra: -
	* Resulta: Borra el display y el cursor va a HOME
	* cadd =1
	* Devuelve en su nombre �true� si fue satisfactoria �false�
	* en caso contrario.
	*=====================================================*/
	virtual bool lcdClear() = 0;


	/*=====================================================
	* Name: lcdClearToEOL
	* Entra: -
	* Resulta: Borra el display desde la posici�n actual
	* del cursor hasta el final de la l�nea.
	* cadd = No se altera
	* Devuelve en su nombre �true� si fue satisfactoria �false�
	* en caso contrario.
	*=====================================================*/
	virtual bool lcdClearToEOL() = 0;


	/*=====================================================
	* Name: operator<<()
	* Entra: Un car�cter
	* Resulta: Pone el car�cter en la posici�n actual
	* del cursor del display y avanza el cursor a la pr�xima
	* posici�n respetando el gap (si el car�cter no es imprimible
	* lo ignora)
	* Modifica: (cadd)
	* Devuelve en su nombre una referencia a un basicLCD que permite
	* encascar la funci�n:
	* basicLCD lcd;
	* lcd << �a� << �b� << �c�;
	*=====================================================*/
	virtual basicLCD& operator<<(const unsigned char c) = 0; 


	/*=====================================================
	* Name: operator<<()
	* Entra: Una cadena de caracteres NULL terminated
	* Resulta: imprime la cadena de caracteres en la posici�n actual
	* del cursor y avanza el cursor al final de la cadena respetando
	* el gap (si alg�n car�cter no es imprimible lo ignora). Si recibe una
	* cadena de m�s de 32 caracteres, muestra los �ltimos 32 en el display.
	* Modifica: (cadd)
	* Devuelve en su nombre una referencia a un basicLCD que permite
	* encascar la funci�n:
	* basicLCD lcd;
	* lcd << �Hola� << � � << �Mundo�;
	*=====================================================*/
	virtual basicLCD& operator<<(const unsigned char * c) = 0;


	/*=====================================================
	* Name: lcdMoveCursorUp
	*
	* Entra: -
	* Resulta: Pasa el cursor a la primera l�nea del display sin
	* alterar la columna en la que estaba.
	* Modifica: (cadd)
	* Devuelve en su nombre �true� si fue satisfactoria �false�
	* en caso contrario.
	*=====================================================*/
	virtual bool lcdMoveCursorUp() = 0;


	/*=====================================================
	* Name: lcdMoveCursorDown
	*
	* Entra: -
	* Resulta: Pasa el cursor a la segunda l�nea del display sin
	* alterar la columna en la que estaba.
	* Modifica: (cadd).
	* Devuelve en su nombre �true� si fue satisfactoria �false�
	* en caso contrario.
	*=====================================================*/
	virtual bool lcdMoveCursorDown() = 0;


	/*=====================================================
	* Name: lcdMoveCursorRight
	*
	* Entra: -
	* Resulta: Avanza el cursor una posici�n
	* Modifica: (cadd).
	* Devuelve en su nombre �true� si fue satisfactoria �false�
	* en caso contrario.
	*=====================================================*/
	virtual bool lcdMoveCursorRight() = 0;


	/*=====================================================
	* Name: lcdMoveCursorLeft
	*
	* Entra: -
	* Resulta: Retrocede el cursor una posici�n
	* Modifica: (cadd).
	* Devuelve en su nombre �true� si fue satisfactoria �false�
	* en caso contrario.
	*=====================================================*/
	virtual bool lcdMoveCursorLeft() = 0;


	/*=====================================================
	* Name: lcdSetCursorPosition
	* Entra: Recibe una estructura tipo cursorPosition
	* Resulta: Posiciona el cursor en la posici�n dada
	* por row y column. row[0-1] col[0-19]. Ante un valor inv�lido
	* de row y/o column ignora la instrucci�n (no hace nada).
	* Modifica: (cadd).
	* Devuelve en su nombre �true� si fue satisfactoria �false�
	* en caso contrario.
	*=====================================================*/
	virtual bool lcdSetCursorPosition(const cursorPosition pos) = 0;


	/*=====================================================
	* Name: lcdGetCursorPosition
	* Entra: -
	* Resulta: Devuelve la posici�n actual del cursor.
	* cadd = No se altera
	*
	* Devuelve una estructura tipo cursorPosition
	*=====================================================*/
	virtual cursorPosition lcdGetCursorPosition() = 0;


protected:
	/*=====================================================
	* Nota 1: cadd (cursor address) es una variable
	* que contiene la direcci�n actual del cursor en el
	* display+1. Esta variable es necesaria pues no podemos
	* leer el LCD para saber d�nde est� el cursor. Mediante
	* la funciones como lcdClear () o lcdSetCursorPosition()
	* podemos poner el cursor del display en una posici�n
	* conocida y por lo tanto sincronizarlo con cadd.
	* El constructor la inicializa y asegura su sincronismo.
	*=====================================================*/
	int cadd;


	/*=====================================================
	* Name: lcdUpdateCursor ver NOTA 2
	* Entra: -
	* Resulta: Posiciona el cursor del display en la posici�n
	* dada por (cadd)-1. (cadd) = No se altera
	*
	* El prop�sito de la funci�n lcdUpdateCursor() es
	* informarle al display del valor de cadd cada vez que es
	* alterado. Esto es necesario pues si llamamos por ejemplo a
	* lcdMoveCursorUp() esta �ltima calcular� un nuevo valor
	* para cadd. Este nuevo valor de cadd deber� ser transferido
	* al cursor del display para poder sincronizar ambos.
	*=====================================================*/
	void lcdUpdateCursor();

};