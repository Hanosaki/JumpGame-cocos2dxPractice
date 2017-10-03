/// <summary> 
/// 各種リソースファイルを読み込むためのクラスのヘッダファイル
/// @author Sigure
/// @date 2017/10/03
/// </summary>
#ifndef __RESOUCE_LOAD_SCENE_H__
#define __RESOUCE_LOAD_SCENE_H__
#include "cocos2d.h"

class ResouceLoad : public cocos2d::Layer
{
public:
	static cocos2d::Scene* creatScene();
	virtual bool init();
	CREATE_FUNC(ResouceLoad);

	virtual void setResouseCache(float dt);

	cocos2d::Label* progressLabel;

	int animationNum;
	float progress;

};

#endif