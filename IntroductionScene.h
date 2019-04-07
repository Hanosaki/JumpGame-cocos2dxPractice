#ifndef __INTRODUCTION_SCENE_H__
#define __INTRODUCTION_SCENE_H__

/*--------------
会話シーンのクラス
---------------*/

#include "cocos2d.h"

class Introduction : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(Introduction);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void spriteChange();
	void callGameScene(cocos2d::Ref* Sender);
	void loadAnimeCache(cocos2d::Texture2D* texture);//非同期読み込み完了を受け付ける関数

	cocos2d::ValueVector characterWordVector;//csvファイルの内容を格納
	cocos2d::ValueMap characterWordMap;//ValueVectorから切り出したデータを格納
	cocos2d::Label* characterNameLabel;//ValueVectorから切り出したキャラクター名を格納
	cocos2d::Label* characterWordLabel;//ValueVectorから切り出した台詞を格納
	int wordsNum;//現在表示している行数(csvファイルに準拠)

};


#endif