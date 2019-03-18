#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

/*---------------------
ゲームオーバー画面のクラス
---------------------*/

#include "cocos2d.h"

class GameOver : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameOver);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

};

#endif