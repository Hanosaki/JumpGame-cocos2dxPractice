#ifndef __CREDIT_H__
#define __CREDIT_H__

#include "cocos2d.h"

class Credit :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Credit);

	/// <summary>
	///  画面がタッチされた際に呼び出される，マウスのクリックでも呼び出される．
	/// <para>アニメーションの開始処理を行う．</para> 
	/// </summary>
	/// <param name="touch">指(マウス)情報(自動で取得される)</param>
	/// <param name="event">操作情報(自動で取得される)</param>
	/// <returns>true...タッチされた状態を返す</returns>
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

	static const int NUM_OF_COMPOSERS;
	static const int NUM_OF_PAINTERS;
	static const int NUM_OF_VOICE_ACTERS;

};

#endif