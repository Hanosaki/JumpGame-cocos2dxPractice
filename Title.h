#ifndef __TITLE_H__
#define __TITLE_H__

#pragma region マクロ設定
#define JPN_FONTS "fonts/HGRPP1.TTC"
#define CHARACTER_NORMAL "NormalImage.png"
#define CHARACTER_SMAILE "Start.png"
#define START_IMAGE "StartButton.png"
#define CREDIT_IMAGE "CreditButton.png"
#define END_IMAGE "CloseButton.png"
#define START_VOICE "start.wav"
#pragma endregion

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
	//bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

	void characterImageChange();
	void callGameScene(cocos2d::Ref* sender);
	void callCreditScene(cocos2d::Ref* sender);
	void closeGame(cocos2d::Ref* sender);
	

};

#endif