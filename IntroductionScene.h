﻿#ifndef __INTRODUCTION_SCENE_H__
#define __INTRODUCTION_SCENE_H__

#include "cocos2d.h"

class Introduction : public cocos2d::Layer
{
public:
	static cocos2d::Scene* creatScene();

	virtual bool init();

	CREATE_FUNC(Introduction);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void spriteChange();
	void callGameScene(cocos2d::Ref* Sender);

	cocos2d::ValueVector characterWordVector;
	cocos2d::ValueMap characterWordMap;
	cocos2d::Label* characterNameLabel;
	cocos2d::Label* characterWordLabel;
	int wordsNum;

};


#endif