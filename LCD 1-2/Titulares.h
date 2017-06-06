#pragma once
#include <iostream>
#include <list>
#include <string>



enum State{ IDLE, CHANNEL, ITEM, ITEM_DATE, ITEM_TITLE, CHANNEL_TITLE, _IGNORE };

using namespace std;

class Noticias
{
private:
	string date;
	string title;
public:
	Noticias();
	Noticias(string date, string title);
	~Noticias();
	void setDate(string date);
	void setTitle(string title);
	string getDate();
	string getTitle();
};


class Titulares
{
private:
	string chTitle; //un titulo y muchas noticias
	list<Noticias> items;
	Noticias * CurrentNews;
	State feedState;
public:
	Titulares();
	~Titulares();
	void setFeedState(State state);
	State getFeedSate();
	void setChTitle(string string);
	void addNoticia();
	Noticias& getLastItem();
	list<Noticias>& getList();
	string getChTitle();

};
