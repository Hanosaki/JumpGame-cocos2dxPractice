#ifndef __HOW_TO_H__
#define __HOW_TO_H__

#include "cocos2d.h"

class HowTo : public cocos2d::Layer
{

public:

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(HowTo);

	//bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

	void returnTitle(cocos2d::Ref* Sender);

};


#endif