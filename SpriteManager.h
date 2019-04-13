#ifndef __SPRITE_MANAGER_H__
#define __SPRITE_MANAGER_H__

#include "cocos2d.h"

class SpriteManager
{
public:
	static cocos2d::Sprite* createSprite(std::string fileName, float pos_x, float pos_y, int tag);//スプライトを作成する関数
	static cocos2d::Sprite* createSprite(std::string fileName, float pos_x, float pos_y, cocos2d::Vec2 anchor, int tag);//スプライトを作成する関数(アンカー指定付き)
	static cocos2d::Sprite* createSprite(std::string fileName, float pos_x, float pos_y, cocos2d::Vec2 anchor, float scale, int tag);//スプライトを作成する関数(アンカー指定、表示倍率指定)

	static cocos2d::Sprite* createWithSpriteFileName(std::string fileName, float pos_x, float pos_y, cocos2d::Vec2 anchor, int &tag);//テクスチャアトラスからスプライトを作成する

private:
	static void setSpriteBasicData(cocos2d::Sprite* &sprite,float &pos_x,float &pos_y,int &tag);//スプライトの基本情報を設定する関数
};

#endif