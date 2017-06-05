#include "Titulares.h"

Noticias::Noticias()
{
}

Noticias::Noticias(string date, string title)
{
	this->date = date;
	this->title = title;
}

Noticias::~Noticias()
{
}

void Noticias::setDate(string date)
{
	this->date = date;
}

void Noticias::setTitle(string title)
{
	this->title = title;
}

Titulares::Titulares()
{
	feedState = IDLE;
}

Titulares::~Titulares()
{
}

void Titulares::setFeedState(State state)
{
	feedState = state;
}

State Titulares::getFeedSate()
{
	return feedState;
}

void Titulares::setChTitle(string string)	//VER
{
	chTitle = string;
}

void Titulares::addNoticia()
{
	Noticias current;
	items.push_back(current);
}

Noticias & Titulares::getLastItem()
{
	return items.back();
}
