
#include "Titulares.h"

string formatDate(string d);

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
	this->date = formatDate(date);
	
}



void Noticias::setTitle(string title)
{
	this->title = title;
}

string Noticias::getDate()
{
	return date;
}

string Noticias::getTitle()
{
	return title;
}

Titulares::Titulares()
{
	feedState = IDLE;
	//CurrentNews = &items.back();
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

void Titulares::setChTitle(string string)
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

list<Noticias>& Titulares::getList()
{
	return items;
}

string Titulares::getChTitle()
{
	return chTitle;
}

string formatDate(string d)
{
	string _date;
	char * months[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

	size_t position = 5;
	_date = d.substr(position, 2);
	_date.append("/");
	//TENGO DD/
	position += 3;
	char current[3] = { d[position], d[position + 1], d[position + 2] };

	for (int i = 0; i < 12; i++)
	{
		if (strncmp(months[i], current, 3) == false)
		{
			switch (i)
			{
			case 9: case 10: case 11:
				_date.append(to_string(i + 1));
				_date.append("/");
				break;
			default:
				_date.append("0");
				_date.append(to_string(i + 1));
				_date.append("/");
			}
			break;
		}
	}

	//TENGO DD/MM/
	position += 6;
	_date.append(d.substr(position, 2));
	_date.append(" - ");
	//TENGO DD/MM/YY - 
	position += 3;
	_date.append(d.substr(position, 5));
	//TENGO DD/MM/YY - hh:mm
	return _date;
}