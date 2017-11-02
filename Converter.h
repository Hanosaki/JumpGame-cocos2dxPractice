#ifndef __CONVERTER_H__
#define __CONVERTER_H__

#include "cocos2d.h"

class Converter
{
public:
	char* replaceDATtoMP3(std::string relativePath);
	char* replaceMP3toDAT(std::string relativePath);
	char* replaceString2Char(std::string);
	void replaceALLMP3toDAT();
};


#endif