#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"

class GameOver : public cocos2d::Layer
{
public:
	static cocos2d::Scene* creatScene();

	virtual bool init();

	CREATE_FUNC(GameOver);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void ended();

};

#endif