#ifndef __GENERIC_FUNCTION_H__
#define __GENERIC_FUNCTION_H__

/*---------------------
汎用関数をまとめたクラス
----------------------*/

#include "cocos2d.h"
class GenericFunc{
public:
	GenericFunc();
	cocos2d::Sprite*  setMainCharacterImage(cocos2d::Size visibleSize, cocos2d::Vec2 origin,std::string imgPath);//立ち絵を表示する関数
	char* setVoiceName(cocos2d::ValueMap valueMap);//音声ファイルを返すための関数
	std::string searceVoice(cocos2d::ValueMap valueMap);//バリューマップから音声ファイル名を探す関数
	cocos2d::Vec2 setWindowCenter(cocos2d::Size visibleSize,cocos2d::Vec2 origin);//中央座標を返す関数
	cocos2d::Sprite* createSprite(std::string fileName, float x, float y,int tag);//スプライトを作成する関数
	cocos2d::Sprite* createSprite(std::string fileName, float x, float y,cocos2d::Vec2 anchor , int tag);//スプライトを作成する関数(アンカー指定付き)
	cocos2d::Sprite* createSprite(std::string fileName, float x, float y, cocos2d::Vec2 anchor, float scale, int tag);//スプライトを作成する関数(アンカー指定、表示倍率指定)
	cocos2d::Sprite* createSpriteWithRect(cocos2d::Rect rect, float x, float y, cocos2d::Vec2 anchor, cocos2d::Color3B color, int tag);//色付きのボックスを生成する関数
	cocos2d::Menu* createButton(const std::string fileName, const  cocos2d::ccMenuCallback& callback);//ボタン生成用関数


};

#endif