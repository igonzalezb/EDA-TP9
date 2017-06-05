#pragma once

extern "C"{
#include <expat.h>
};

#include "Titulares.h"

void mainFase3(int argc, char * argv[]);


void readFileToBuffer(XML_Parser P, FILE * fp, char buffer[]);

void startTagCallback(void *userData, const XML_Char *name, const XML_Char **atts);

void endTagCallback(void *userData, const XML_Char *name);

void chararacterDataCallback(void *userData, const XML_Char *s, int len);

