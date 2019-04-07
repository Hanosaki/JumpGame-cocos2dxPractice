#ifndef __RESOUCE_LOAD_SCENE_H__
#define __RESOUCE_LOAD_SCENE_H__

/*
リソースをメモリーに展開するためのクラス
*/

#include "cocos2d.h"

class ResouceLoad : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(ResouceLoad);
	void loadAnimeCache();//非同期で読み込み

private:

	cocos2d::Label* progressLabel;//読み込み進捗を表示するためのラベル

	int animationNum;//アニメーション画像の番号
	float progress;//読み込み進捗率

};

#endif