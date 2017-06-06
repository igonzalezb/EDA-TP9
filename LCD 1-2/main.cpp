
///////////////////////////////////////////////////////////////////////////////////////////// 
//
// Instituto Tecnologico de Buenos Aires  
//
// Algoritmos y Estructuras de Datos - Trabajo Práctico 9 
//
//
// Gonzalez Bigliardi Iñaki			    /////////////////////////////////////////
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
#include "basicXML.h"
#include "Fase3.h"
#include <allegro5\allegro.h>

int main(int argc, char * argv[])
{
	/*LCD lcd;

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
	lcd << str3;*/

	if (argc == 2)
	{
		XML_Parser P = XML_ParserCreate(NULL);
		FILE * fp = fopen(argv[1], "rb");

		Titulares data;
		LCD lcd;

		XML_SetStartElementHandler(P, startTagCallback);	// funcion que va a encontrar cuando aparece un Start tag);
		XML_SetEndElementHandler(P, endTagCallback);		//funcion que va a encontrar cuando aparece un End tag);
		XML_SetCharacterDataHandler(P, chararacterDataCallback);
		XML_SetUserData(P, &data);

		char buffer[BUFF_LEN];

		readFileToBuffer(P, fp, buffer);
		
		allegroStartup();	

		
		ALLEGRO_EVENT_QUEUE * event_queue = NULL;
		event_queue = al_create_event_queue();
		if (!event_queue)
		{
			fprintf(stderr, "Error Creating EventQueue\n");
			allegroShutdown();
			return EXIT_FAILURE;
		}
		ALLEGRO_TIMER * timer = NULL;
		timer = al_create_timer(1.0 / 60.0);
		if (!timer) {
			fprintf(stderr, "Error Creating timer\n");
			al_destroy_event_queue(event_queue);
			allegroShutdown();
			return EXIT_FAILURE;
		}


		auto rit = data.getList().begin();



		al_register_event_source(event_queue, al_get_keyboard_event_source());
		al_register_event_source(event_queue, al_get_timer_event_source(timer));
		al_start_timer(timer);

		bool do_exit = false;
		while (!do_exit)
		{
			ALLEGRO_EVENT ev;
			al_wait_for_event(event_queue, &ev);
			string title = data.getChTitle() + ": " + rit->getTitle();
			switch (ev.type)
			{
			case ALLEGRO_EVENT_KEY_DOWN:
				switch (ev.keyboard.keycode)
				{
				case ALLEGRO_KEY_R:
					title = data.getChTitle() + ": " + rit->getTitle();
					break;
				case ALLEGRO_KEY_S:
					if (rit != data.getList().end()) {
						rit++;
						title = data.getChTitle() + ": " + rit->getTitle();
					}
						
					break;
				case ALLEGRO_KEY_A:
					if (rit != data.getList().begin()) {
						rit--;
						title = data.getChTitle() + ": " + rit->getTitle();
					}
						
					break;
				case ALLEGRO_KEY_Q:
					do_exit = true;
					break;
				case 43:
					
					break;
				case ALLEGRO_KEY_MINUS: case ALLEGRO_KEY_PAD_MINUS:

					break;
				}
				break;
			case ALLEGRO_EVENT_TIMER:
				showDate(lcd, rit->getDate());
				showTitle(lcd, title);

				break;
			}
		}

		fclose(fp);
		allegroShutdown();

	}
	
	getchar();

	return EXIT_SUCCESS;
}



bool allegroStartup(void)
{
	if (al_init())
	{
		if (al_install_keyboard())
		{
			return EXIT_SUCCESS;
		}
		else
			fprintf(stderr, "ERROR: Failed to initialize keyboard\n");
		al_uninstall_system();
						
	}
	else
		fprintf(stderr, "ERROR: Failed to load primitives addon \n");
	return EXIT_FAILURE;
}

void allegroShutdown(void)
{
	al_uninstall_keyboard();
	al_uninstall_system();
}