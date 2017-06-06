
///////////////////////////////////////////////////////////////////////////////////////////// 
//
// Instituto Tecnologico de Buenos Aires  
//
// Algoritmos y Estructuras de Datos - Trabajo Pr�ctico 9 
//
//
// Gonzalez Bigliardi I�aki			    /////////////////////////////////////////
// Lago Valentina				   // Proyecto LCD - Fases I y II
// Muller Malena				  //////////////////////////////////////////
//
//
//  El presente trabajo pr�ctico utiliza con un display de cuarzo
// l�quido (LCD) alfanum�rico de 2x16 caracteres.
// El objetivo del mismo es crear una librer�a que permita manejar el LCD y contenga el
// driver del LCD al igual que una capa de abstracci�n (HAL) que le permitir�n a quien 
// la utilice manipular el display.
//
// Proyecto Fase I 
//
// *Asignaci�n de nombres a los pines del puerto 
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
// comunicaci�n con las capas superiores.
//
//  Abajo se incluye el prototipo de una clase abstracta a implementar junto con una
// descripci�n de cada una de las funciones que la componen.
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

bool allegroStartup(void);
void allegroShutdown(void);

int main(int argc, char * argv[])
{
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

		readFileToBuffer(P, fp);
		
		allegroStartup();	

		
		ALLEGRO_EVENT_QUEUE * event_queue = NULL;
		event_queue = al_create_event_queue();
		if (!event_queue)
		{
			fprintf(stderr, "Error Creating EventQueue\n");
			allegroShutdown();
			return EXIT_FAILURE;
		}
		double speed = 2.0;
		ALLEGRO_TIMER * timer = NULL;
		timer = al_create_timer(speed);
		if (!timer) {
			fprintf(stderr, "Error Creating timer\n");
			al_destroy_event_queue(event_queue);
			allegroShutdown();
			return EXIT_FAILURE;
		}
		
		ALLEGRO_DISPLAY *display = NULL;
		display = al_create_display(200, 200);
		if (!display) {
			fprintf(stderr, "Error Creating timer\n");
			al_destroy_event_queue(event_queue);
			al_destroy_timer(timer);
			allegroShutdown();
			return EXIT_FAILURE;
		}


		auto rit = data.getList().begin();
		string title = data.getChTitle() + ": " + rit->getTitle();
		showDate(lcd, rit->getDate());
		showTitle(lcd, title);


		al_register_event_source(event_queue, al_get_keyboard_event_source());
		al_register_event_source(event_queue, al_get_timer_event_source(timer));
		al_start_timer(timer);

		bool do_exit = false, redraw = false;
		
		while (!do_exit)
		{
			ALLEGRO_EVENT ev;
			al_wait_for_event(event_queue, &ev);
			
			switch (ev.type)
			{
			case ALLEGRO_EVENT_KEY_DOWN:
				switch (ev.keyboard.keycode)
				{
				case ALLEGRO_KEY_R:
					printf("r\n");
					title = data.getChTitle() + ": " + rit->getTitle();
					break;
				case ALLEGRO_KEY_S:
					printf("s\n");
					if (rit != data.getList().end()) {
						rit++;
						showDate(lcd, rit->getDate());
						title = data.getChTitle() + ": " + rit->getTitle();
					}
						
					break;
				case ALLEGRO_KEY_A:
					printf("a\n");
					if (rit != data.getList().begin()) {
						rit--;
						if (rit != data.getList().begin())
							rit--;
						showDate(lcd, rit->getDate());
						title = data.getChTitle() + ": " + rit->getTitle();
					}
						
					break;
				case ALLEGRO_KEY_Q:
					printf("q\n");
					lcd.lcdClear();
					do_exit = true;
					break;
				case ALLEGRO_KEY_EQUALS:
					printf("+\n");
					if (speed > 0.5) {
						speed -= 0.1;
						al_set_timer_speed(timer, speed);
					}
						
					break;
				case ALLEGRO_KEY_MINUS:
					printf("-\n");
					speed += 0.1;
					al_set_timer_speed(timer, speed);
					break;
				}
				break;
			case ALLEGRO_EVENT_TIMER:
				redraw = true;
				break;
			}

			if (redraw)
			{
				showTitle(lcd, title);
				if (title.length() > 0)
					title.erase(0, 1);
				else {
					if (rit != data.getList().end()) {
						rit++;
						title = data.getChTitle() + ": " + rit->getTitle();
						showDate(lcd, rit->getDate());
					}
					else
					{
						lcd.lcdClear();
						lcd << "Ultima Noticia";
					}
					
				}
				redraw = false;
			}
		}

		fclose(fp);

		al_destroy_event_queue(event_queue);
		al_destroy_timer(timer);
		al_destroy_display(display);
		allegroShutdown();

	}
	
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