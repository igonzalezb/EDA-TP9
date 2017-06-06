#pragma once

#include "LCD.h"
#include "Titulares.h"

void printDisplay(Titulares data, LCD& lcd);

void showDate(LCD& lcd, string date);

void showTitle(LCD& lcd, string title);