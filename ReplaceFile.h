#ifndef __REPLACE_FILE_H__
#define __REPLACE_FILE_H__

#include "cocos2d.h"

class FileConverter
{
public:
	char* replaceDATtoMP3(const char* fileName);
	char* replaceMP3toDAT(const char* fileName);
};


#endif