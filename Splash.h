#ifndef __SPLASH_H__
#define __SPLASH_H__

/*
ロゴ画面表示用クラス
*/

#include "cocos2d.h"

class Splash : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Splash);
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);//タップしたらロード画面に移行する

private:
	void callLoadScene(float dt);//ロゴ表示が終わったら、ロード画面に遷移する

};

#endif