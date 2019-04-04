#ifndef __CREATE_LABEL_H__
#define __CREATE_LABEL_H__

#include "cocos2d.h"

class CreateLabel
{
public:
	static void setLabel(std::string text,std::string &fonts,int fontSize,
		cocos2d::Color4B fontColor,cocos2d::Vec2 &pos, int tag ,cocos2d::Node* node);
};

#endif