#ifndef __TITLE_H__
#define __TITLE_H__

/*----------------------
タイトル画面のクラス
----------------------*/

#include "cocos2d.h"

class Title : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(Title);

	cocos2d::Menu* Title::createButton(const std::string fileName, const  cocos2d::ccMenuCallback& callback);//ボタン生成用関数

	void characterImageChange();//表示キャラ変更用関数
	void callOPScene(cocos2d::Ref* sender);//OPシーン呼び出し用関数
	void callCreditScene(cocos2d::Ref* sender);//使用素材表示用
	void closeGame(cocos2d::Ref* sender);//ゲーム終了ボタン用関数
	

};

#endif