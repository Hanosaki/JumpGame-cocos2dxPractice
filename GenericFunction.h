#ifndef __GENERIC_FUNCTION_H__
#define __GENERIC_FUNCTION_H__

#include "cocos2d.h"
class GenericFunc{
public:
	cocos2d::Sprite*  setMainCharacterImage(cocos2d::Size visibleSize, cocos2d::Vec2 origin,std::string imgPath);
	char* setVoiceName(cocos2d::ValueMap valueMap);
	std::string searceVoice(cocos2d::ValueMap valueMap);
	cocos2d::Vec2 setWindowCenter(cocos2d::Size visibleSize,cocos2d::Vec2 origin);
};

#endif