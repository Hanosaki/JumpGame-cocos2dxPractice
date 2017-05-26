#ifndef __TITLE_H__
#define __TITLE_H__
#define JPN_FONTS "fonts/HGRPP1.TTC"

#include "cocos2d.h"

class Title : public cocos2d::Layer
{
public:
	static cocos2d::Scene* creatScene();

	virtual bool init();

	CREATE_FUNC(Title);

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