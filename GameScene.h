#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class Game : public cocos2d::Layer
{
public:
	static cocos2d::Scene* creatScene();

	virtual bool init();

	CREATE_FUNC(Game);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void roop(float dt);
	void update(float dt);
	void ended();

	int counter, hitCounter;
	bool endflag, hitOnlyOne;
	cocos2d::Vec2 defoultPoint;
	cocos2d::Vec2 enemyDefPoint;
	cocos2d::Label* label;//ヘッダーで宣言した変数は，継承クラスで再度定義する必要はない．(この時点でグローバル変数化しているため)
};

#endif