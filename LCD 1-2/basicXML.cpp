#include "basicXML.h"

void readFileToBuffer(XML_Parser P, FILE * fp)
{
	char buffer[BUFF_LEN];
	int allFileRead = 0;
	size_t buflen = 0;
	do {
		buflen = fread( buffer, 1, BUFF_LEN, fp);
		allFileRead = (buflen < BUFF_LEN)?1:0;
		if (XML_Parse(P, buffer, buflen, allFileRead) == XML_STATUS_ERROR) {
			printf("CANNOT READ MORE\n");
			break;
		}

	} while (!allFileRead);
	
}

void startTagCallback(void *userData, const XML_Char *name, const XML_Char **atts)	//< >
{
	Titulares* myData = (Titulares*)userData;
	
	if (strcmp(name, "channel") == false)
	{
		myData->setFeedState(CHANNEL);
	}
	else if (strcmp(name, "title") == false)
	{
		
		switch (myData->getFeedSate())
		{
		case CHANNEL:
			myData->setFeedState(CHANNEL_TITLE);
			break;
		case ITEM:
			myData->setFeedState(ITEM_TITLE);
			break;
		}		
	}
	else if (strcmp(name, "item") == false)
	{
		myData->setFeedState(ITEM);
		myData->addNoticia();
	}
	else if (strcmp(name, "pubDate") == false)
	{
		myData->setFeedState(ITEM_DATE);
	}
	else
		myData->setFeedState(_IGNORE);

}

void chararacterDataCallback(void *userData, const XML_Char *s, int len)
{
	Titulares* myData = (Titulares*)userData;
	
	string d(s, s + len);

	/*char *d = new char[len];

	for (int i = 0; i < len; i++) {
		d[i] = s[i];
	}*/
	switch (myData->getFeedSate())
	{
	/*case IDLE:
		break;
	case CHANNEL:
		break;
	case ITEM:
		break;*/
	case CHANNEL_TITLE:
		myData->setChTitle(d);
		break;
	
	case ITEM_TITLE:
		myData->getLastItem().setTitle(d);
		break;
	case ITEM_DATE:
		myData->getLastItem().setDate(d);
		break;
	
	case _IGNORE:
		break;
	}

	//delete[] d;
}

void endTagCallback(void *userData, const XML_Char *name)		//</ >
{
	Titulares* myData = (Titulares*)userData;

	if (strcmp(name, "/channel") == false)
	{
		myData->setFeedState(IDLE);
	}
	else if (strcmp(name, "/title") == false)
	{

		switch (myData->getFeedSate())
		{
		case CHANNEL_TITLE:
			myData->setFeedState(CHANNEL);
			break;
		case ITEM_TITLE:
			myData->setFeedState(ITEM);
			break;
		}
	}
	else if (strcmp(name, "/item") == false)
	{
		myData->setFeedState(CHANNEL);
	}
	else if (strcmp(name, "/pubDate") == false)
	{
		myData->setFeedState(ITEM);
	}
	else
		myData->setFeedState(CHANNEL);


	//myData->EndLocation(name);
}


//los cambios serias:
// channel, con un title me voy a channelTitle
//channel con un item me voy a Item
//Item con un end item vuelvo a channel
//item con un title voy a chanel title
//con un end vuelvo a title
//...
