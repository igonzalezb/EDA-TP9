
///////////////////////////////////////////////////////////////////////////////////////////// 
//
// Instituto Tecnologico de Buenos Aires  
//
// Algoritmos y Estructuras de Datos - Trabajo Práctico 9 
//
//
// Gonzalez Bigliardi Iñaki			/////////////////////////////////////////
// Lago Valentina				   // Proyecto LCD - Fases I y II
// Muller Malena				  //////////////////////////////////////////
//
//
//  El presente trabajo práctico utiliza con un display de cuarzo
// líquido (LCD) alfanumérico de 2x16 caracteres.
// El objetivo del mismo es crear una librería que permita manejar el LCD y contenga el
// driver del LCD al igual que una capa de abstracción (HAL) que le permitirán a quien 
// la utilice manipular el display.
//
// Proyecto Fase I 
//
// *Asignación de nombres a los pines del puerto 
// *Definir todas las instrucciones del LCD
// *Escribir las siguientes funciones de bajo nivel:
//
//  FT_HANDLE * deviceHandler lcdInit(int iDevice); //Inicializa el FTDI y el LCD
//
//  void lcdWriteIR(FT_HANDLE * deviceHandler, BYTE valor); //Escribe un byte al IR
//
//  void lcdWriteDR(FT_HANDLE * deviceHandler, BYTE valor); //Escribe un byte al DR
//
// Proyecto Fase II
//  
//  En esta etapa montaremos una capa sobre la anterior que nos permita una mejor
// comunicación con las capas superiores.
//
//  Abajo se incluye el prototipo de una clase abstracta a implementar junto con una
// descripción de cada una de las funciones que la componen.
//
//  Implementamos la clase basicLCD como una clase abstracta y creamos una clase concreta 
// a partir de basicLCD que contenga todas las implementaciones de las funciones descriptas 
// en basicLCD para el caso particular del display Hitachi HD44780.
//
//  Ademas realizamos un programa de prueba (main) que permita probar una
// instancia (objeto) de la clase heredada de basicLCD. 
// 
// 
/////////////////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include "LCD.h"


int main()
{
	LCD lcd;

	const unsigned char str1[] = "Finalmente ANDA."; 
	lcd << str1;
	Sleep(8);
	lcd.lcdClear();
	const unsigned char str2[] = "By group 1 :)";
	lcd << str2;
	Sleep(8);
	lcd.lcdClear();
	lcd.lcdMoveCursorDown();
	const unsigned char str3[] = "chau ;)";
	lcd << str3;

	getchar();

	return EXIT_SUCCESS;
}
