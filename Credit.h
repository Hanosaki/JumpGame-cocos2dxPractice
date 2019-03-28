#ifndef __CREDIT_H__
#define __CREDIT_H__

#include "cocos2d.h"

class Credit :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Credit);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

private:
	//ここ、enumにする
	static const int NUM_OF_COMPOSERS;//音素材製作者人数
	static const int NUM_OF_PAINTERS;//イラストレーター人数
	static const int NUM_OF_VOICE_ACTERS;//音声素材人数

};

#endif