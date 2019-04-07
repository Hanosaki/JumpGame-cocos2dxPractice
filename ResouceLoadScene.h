#ifndef __RESOUCE_LOAD_SCENE_H__
#define __RESOUCE_LOAD_SCENE_H__

/*
リソースをメモリーに展開するためのクラス(不要の可能性あり)
*/

#include "cocos2d.h"

class ResouceLoad : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(ResouceLoad);

private:

	cocos2d::Label* progressLabel;//読み込み進捗を表示するためのラベル

	int animationNum;//アニメーション画像の番号
	float progress;//読み込み進捗率

};

#endif