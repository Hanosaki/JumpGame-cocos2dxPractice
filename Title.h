#ifndef __TITLE_H__
#define __TITLE_H__

#include "cocos2d.h"

class Title : public cocos2d::Layer
{
public:
	static cocos2d::Scene* creatScene();

	virtual bool init();

	CREATE_FUNC(Title);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	

};

#endif