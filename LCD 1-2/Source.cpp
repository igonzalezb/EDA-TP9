
//descargar de nuget expat

if (argc == 2)
{
	XML_Parser P = XML_ParseCreate(NULL);

	//tenemos que hacer las siguentes funciones callback

	XML_setStartElementHandler(P, funcion que va a encontrar cuando aparece un Start tag);
	XML_SetEnd(P, funcion que va a encontrar cuando aparece un End tag);
	XML_CharacterData(P, ...);
	XML_UserData(P, ...);


	XML_Parse(P, buffer, buflen, 1);

	fp = f_open(argv[1], "rb");
	readFileToBuffer(fp, buffer, &buflen);
	XML_Parse(p, buffer, buflen, 1); 

	//aca en user data queda grabada la hora, el titulo, etc en la clase titulares
}

//mientras se esta mostrando la noticia van a permitir apretar algunas funciones 


//RSS es un tipo de xml pensado para mostrar noticias

//dentro del channel:
//*title //titulo de la noticia, lo que vamos a pasar por el display
//*link
//*description //noticia propiamente dice
//*adicionalmente puede tener una cantidad de items


//recibimos por linea de comando un .xlm 



class Titulares
{
private:
	string chTitle; //un titulo y muchas noticias
	list<noticias> items;
	noticia CurrentNews;
	state feedState;
public:
	addTitleInfo();
};

class Noticias
{
private:
	string date;
	string titutlo;
public:

};


void startTagCallback(void* userData, char* Name, char** att)
{
	titulares* myData = (titulares*)userData;
	myData->StartTagAnalizer(name); //cada vez que recibo un item pongo en 0 la currentNews, date y titulo y me voy al estado feedState y meto esa noticia en 
									//la lista
									//cuando viene el endTag hago un push del currenNews en items

}

void chararacterDataCallback(void* userData, char* S, int len)
{
	titulares* myData = (titulares*)userData;
	myData->push(S, len);
}

EnaTagCallback(void * userData)
{
	...
	myData->EnaLocation(name);
}


//los cambios serias:
// channel, con un title me voy a channelTitle
//channel con un item me voy a Item
//Item con un end item vuelvo a channel
//item con un title voy a chanel title
//con un end vuelvo a title
//...
