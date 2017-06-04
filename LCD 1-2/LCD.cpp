#include "LCD.h"



LCD::LCD()
{
	cadd = 1;
	lcdInitOk();
	lcdClear();
}

LCD::~LCD()
{

}

bool LCD::lcdInitOk()
{
	bool found = false;
	for (int i = 1; (i < 10) && !found; i++)
	{
		deviceHandler = deviceHandler_lcdInit(i);
		if (deviceHandler != 0)
			found = true;
	}
	return found;
}

FT_STATUS LCD::lcdGetError()
{
	return FT_OK;
}

//bool LCD::lcdClear() //NUESTRO
//{
//	lcdWriteIR(&deviceHandler, CLEAR_DISPLAY);
//	cadd = 1;
//	return true;
//}

bool LCD::lcdClear() //RAMA
{
	//Borra el display y el cursor va a HOME. 
	//Se modifica cadd.
	bool status = true;
	cursorPosition pos;				//creamos una estructura tipo cursorPosition. 
	pos = lcdGetCursorPosition();	//Se pide a la funcion que devuelva la posicion actual del cursor. 
	lcdWriteIR(&deviceHandler, CLEAR_DISPLAY); //Se envia la instruccion de limpiar el screeen.
		pos.column = 0;								//Se pone el cursor en la primera fila, primera columna. 
		pos.row = 0;
	status &= lcdSetCursorPosition(pos); //Se actualiza el cursor del display con las nuevas coordenadas, aqui se modifica cadd.
	return status;
}

bool LCD::lcdClearToEOL()
{
	int _cadd = cadd;
	for (int i = (cadd % MAX_POSITION); i<= MAX_POSITION; i++)  //cheaquear que este bien 
	{

		//escritura(' ');
	}
	cadd = _cadd;
	lcdUpdateCursor();
	return true;
}

//basicLCD& LCD::operator<<(const unsigned char c) //NUESTRA
//{	
//	escritura(c);
//	return *this;
//}

basicLCD& LCD::operator<<(const unsigned char c) //RAMA
{
	//Pone el car�cter en la posici�n actual del cursor del display y avanza el cursor a la pr�xima
	//posici�n respetando el gap (si el car�cter no es imprimible
	//lo ignora). Se toma que la proxima posicion es a la derecha.

	//bool action_status = true;

	//Se analiza si el caracter es imprimible (segun la tabla del documento). 

	if ((c >= 0x20 && c <= 0x7F) || (c >= 0xA0 && c <= 0xFF))
	{
		//action_status = lcdWriteDR(c); //Se envia para escribir el caracter. 
		lcdWriteDR(&deviceHandler,c); //Se envia para escribir el caracter. 
		lcdMoveCursorRight(); //El cursor se despaza hacia la derecha.
		Sleep(2); //Delay.

		//if (action_status != true)
		//	cout << "Invalid character" << endl;
	}

	return *this;
}


basicLCD& LCD::operator<<(const unsigned char * c)
{
	for (int i = 0; c[i]!='\0'; i++)
	{
		*this<<(c[i]);
	}
	return *this;
}

//bool LCD::lcdMoveCursorUp() //NUESTRA
//{
//	cursorPosition Pos = lcdGetCursorPosition();
//	if (Pos.row == ROW_2)
//	{
//		Pos.row = ROW_1;
//		lcdSetCursorPosition(Pos);
//		lcdUpdateCursor();
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}

bool LCD::lcdMoveCursorUp() //RAMA
{
	// Pasa el cursor a la primera l�nea del display sin alterar la columna en la que estaba. 
	// Modifica cadd.
	bool status = true;
	cursorPosition pos; //creamos una estructura tipo cursorPosition. 
	pos = lcdGetCursorPosition(); //Se pide a la funcion que devuelva la posicion actual del cursor. 
	if (pos.row != 0) //Se fija si el cursor NO esta en la primera fila. 
	{
		pos.row--; //Si ese es el caso le resta 1 al valor de las filas. 	
		status &= lcdSetCursorPosition(pos); ////Se actualiza el cursor del display con las nuevas coordenadas, aqui se modifica cadd.
	}
	else
	{
		std::cout << "Cursor can not go up" << std::endl;
		status = false; //La accion no fue satisfactoria.
	}
	return status;
}

bool LCD::lcdMoveCursorDown() //RAMA
{
	// Pasa el cursor a la segunda l�nea del display sin alterar la columna en la que estaba. 
	// Modifica cadd.

	bool action_status = true;

	cursorPosition pos; //creamos una estructura tipo cursorPosition. 
	pos = lcdGetCursorPosition(); //Se pide a la funcion que devuelva la posicion del cursor. 

	if (pos.row < 1) //Se fija si el cursor NO esta en la ultima fila. (??????????????????????)
	{
		pos.row++; //Si ese es el caso le suma 1 al valor de las filas. 
		action_status &= lcdSetCursorPosition(pos); ////Se actualiza el cursor del display con las nuevas coordenadas, aqui se modifica cadd.
	}
	else
	{
		std::cout << "Cursor can not go down" << std::endl;
		action_status = false; //La accion no fue satisfactoria.
	}

	return action_status;

}

//bool LCD::lcdMoveCursorDown()//NUESTRA
//{
//	cursorPosition Pos = lcdGetCursorPosition();
//
//	if (Pos.row == ROW_1)
//	{
//		Pos.row = ROW_2;
//		lcdSetCursorPosition(Pos);
//		lcdUpdateCursor();
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}

//bool LCD::lcdMoveCursorRight() //NUESTRA
//{
//	int columna = ((cadd - 1) % MAX_POSITION);
//	if (columna < (MAX_POSITION - 1))
//	{
//		cadd++;
//		lcdUpdateCursor();
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}

bool LCD::lcdMoveCursorRight() //RAMA
{
	// Avanza el cursor una posici�n.
	// Modifica cadd.

	bool action_status = true;

	cursorPosition pos; //creamos una estructura tipo cursorPosition. 
	pos = lcdGetCursorPosition(); //Se pide a la funcion que devuelva la posicion del cursor. 

								  //Se deben contemplar 3 casos.
								  // 1- Si el cursor no esta en la ultima posicion de cualquier fila.
								  // 2- Si el cursor esta en la ultima posicion de una fila pero no la ultima.
								  // 3- Si el cursor esta en la ultima posicion de la ultima fila.

	if (pos.column < (MAX_POSITION - 1)) //Se fija si no esta en la ultima columna de cualquier fila. No puede ser 15.
		pos.column++;	//Si ese es el caso, se incrementa la columna en 1.

	else if ((pos.column == (MAX_POSITION - 1)) && (pos.row < MAX_ROW - 1)) // Se fija si esta en la ultima posicion del display (ultima fila, ultima columna)
	{
		pos.column = 0; //Se pone el cursor en la primera posicion de la proxima fila..	
		pos.row++;
	}

	else if ((pos.column == (MAX_POSITION - 1)) && (pos.row == (MAX_ROW - 1))) // Se fija si esta en la ultima posicion del display (ultima fila, ultima columna)
	{
		pos.column = 0; //Se pone el cursor en la primera posicion del display.	
		pos.row = 0;
	}

	else
	{
		action_status = false; //Si las coordenadas estan fuera de rango, hay error. 
		//cout << "Cursor can not go right" << endl;
	}

	action_status &= lcdSetCursorPosition(pos); //Se actualiza el cursor del display con las nuevas coordenadas, aqui se modifica cadd.

	return action_status;
}

bool LCD::lcdMoveCursorLeft()//RAMA
{
	// Retrocede el cursor una posici�n.
	// Modifica cadd.

	bool action_status = true;

	cursorPosition pos; //creamos una estructura tipo cursorPosition. 
	pos = lcdGetCursorPosition(); //Se pide a la funcion que devuelva la posicion del cursor. 

								  //Se deben contemplar 3 casos.
								  // 1- Si el cursor esta no esta en la primera posicion de cualquier fila.
								  // 2- Si el cursor esta en la primera posicion de una fila pero la primera.
								  // 3- Si el cursor esta en la primera posicion de la primera fila.


	if (pos.column > 0) //Se fija si no esta en la primera columna de cualquier fila.
		pos.column--; //Si ese es el caso se decrementa en uno la columna.

	else if ((pos.column == 0) && (pos.row != 0))
	{
		pos.column = MAX_POSITION - 1; //Se pone el cursor en la ultima posicion (15).
		pos.row--; //Se decrementa en uno la fila.
	}

	else if ((pos.column == 0) && (pos.row == 0))
	{
		pos.column = MAX_POSITION - 1; //Se pone el cursor en la ultima posicion de la ultima fila.
		pos.row = MAX_ROW - 1;
	}

	else
	{
		action_status = false; //Si las coordenadas estan fuera de rango, hay error. 
		//cout << "Cursor can not go left" << endl;
	}

	action_status &= lcdSetCursorPosition(pos); //Se actualiza el cursor del display con las nuevas coordenadas, aqui se modifica cadd.

	return action_status;
}

//bool LCD::lcdMoveCursorLeft() //NUESTRA
//{
//	int columna = ((cadd - 1) % MAX_POSITION);
//	if (columna !=0) 
//	{
//		cadd--;
//		lcdUpdateCursor();
//		return true;
//	}
//
//	else
//	{
//		return false;
//	}
//}

//bool LCD::lcdSetCursorPosition(const cursorPosition pos) //NUESTRA
//{
//	if (pos.column < MAX_POSITION && pos.row < 2)
//	{
//		cadd = pos.column + pos.row * MAX_POSITION + 1; // +1 porque lcdUpdateCursor() 
//														// posiciona uno antes
//		lcdUpdateCursor();
//		return true;
//	}
//	else
//		return false;
//
//}

bool LCD::lcdSetCursorPosition(const cursorPosition pos) //RAMA
{
	//Posiciona el cursor en la posici�n dada por row y column. row[0-1] col[0-15]. Ante un valor inv�lido 
	//de row y/o column ignora la instrucci�n (no hace nada). Modifica (cadd). 

	bool status = true;

	//A continuacion se evalua si en la estructura enviada los valores de row y colum son validos.
	//0<row<2.
	//0<colum<15.

	if ((pos.row >= 0) && (pos.row< MAX_ROW) && (pos.column >= 0) && (pos.column< MAX_POSITION))
	{
		cadd = ((MAX_POSITION*pos.row) + pos.column) + 1; //Actualiza el cadd siempre sumando 1 mas que la posicion actual del display.
		lcdUpdateCursor(); //Se sincroniza cadd con el cursor del Display. 
	}
	else
	{
		status = false; //Si las coordenadas estan fuera de rango, hay error. 
		//cout << "Invalid coords for display" << endl;
	}

	return status;
}

cursorPosition LCD::lcdGetCursorPosition() //RAMA
{
	// Devuelve la posici�n actual del cursor del display. 
	// No altera cadd.
	// Recordar que la posicion del cursor es cadd-1.
	cursorPosition pos; //creamos una estructura tipo cursorPosition. 
	unsigned int row;
	if ((cadd - 1) < MAX_POSITION)
		row = 0;
	else
		row = 1;
	pos.column = ((cadd - 1) - (row*MAX_POSITION)); //Luego de saber cual esa la fila, obtenemos la columna. 
	pos.row = row;
	//cout << "CursorPosition-> ROW:" <<pos.row<<" COLUMN:"<<pos.column<<" CADD:"<<cadd<< endl; //Print para debug
	return pos;
}

//cursorPosition LCD::lcdGetCursorPosition()
//{
//	cursorPosition currentPosition = { cadd / MAX_POSITION , cadd % MAX_POSITION }; //fila , columna
//	return currentPosition;
//}


//void LCD::lcdUpdateCursor() //NUESTRA
//{
//	lcdWriteIR(&deviceHandler, LCD_SET_DDRAM | (cadd - 1));
//}

void LCD::lcdUpdateCursor() //RAMA
{
	//Posiciona el cursor del display en la posici�n dada por (cadd)-1. 
	//cadd No se altera.
	//Tener en cuenta que cadd-1 nunca puede ser 0.

	unsigned int row, column;

	if ((cadd - 1) < MAX_POSITION)
		row = 0;
	else
		row = 1;

	column = ((cadd - 1) - (row*MAX_POSITION)); //Luego de saber cual esa la fila, obtenemos la columna. 

	lcdWriteIR(&deviceHandler, SET_ADDRESS(column, row)); //Se actualiza el cursor del display.
										  //ATENCION: en el documento de Agustin dice que esta funcion es void, por lo que no hay control si la funcion lcdWriteIR
										  //funciono correctamente. 
}

//void LCD::escritura(const unsigned char c)
//{
//	lcdWriteDR(&deviceHandler, c);
//	cadd++;
//	lcdUpdateCursor();
//
//	cursorPosition Pos = lcdGetCursorPosition();
//
//	switch (Pos.row)
//	{
//	case ROW_1:
//	{
//		if (Pos.column == MAX_POSITION)
//		{
//			Pos.row = ROW_2;
//			Pos.column = 0;
//		}
//		else
//		{
//			Pos.column++;
//		}
//		lcdSetCursorPosition(Pos); //cambia el valor de cadd
//		lcdUpdateCursor();
//	}
//	break;
//	case ROW_2:
//	{
//		if (Pos.column == MAX_POSITION)
//		{
//			Sleep(1000);
//
//			lcdClear();
//
//			Pos.row = ROW_1;
//			Pos.column = 0;
//		}
//		else
//		{
//			Pos.column++;
//		}
//		lcdSetCursorPosition(Pos);
//		lcdUpdateCursor();
//	}
//	break;
//	}
//}
