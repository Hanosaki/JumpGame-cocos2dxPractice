#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"

class GameOver : public cocos2d::Layer
{
public:
	static cocos2d::Scene* creatScene();

	virtual bool init();

	CREATE_FUNC(GameOver);

	/// <summary>
	///  画面がタッチされた際に呼び出される，マウスのクリックでも呼び出される．
	/// <para>アニメーションの開始処理を行う．</para> 
	/// </summary>
	/// <param name="touch">指(マウス)情報(自動で取得される)</param>
	/// <param name="event">操作情報(自動で取得される)</param>
	/// <returns>true...タッチされた状態を返す</returns>
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

};

#endif