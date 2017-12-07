#ifndef __HOW_TO_H__
#define __HOW_TO_H__

#include "cocos2d.h"

class HowTo : public cocos2d::Layer
{

public:

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(HowTo);

	virtual void goTitleTimer(float dt);

	void returnTitle();
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);


	int countTimer;
	float move;
	cocos2d::Vec2 fingerLocation ,posCenter;

};


#endif