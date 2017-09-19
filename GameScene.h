/// <summary> ゲームシーン用クラスの定義ファイル
/// @author Sigure
/// @date 2017/04/12
/// </summary>
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include "cocos2d.h"

class Game : public cocos2d::Layer
{
public:

	static cocos2d::Scene* creatScene();
	virtual bool init();
	CREATE_FUNC(Game);
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void update(float dt);
	void setCharacterDefault();

	int score; //敵をよけた回数を格納する
	int hitCounter; //hitCounter...敵と接触した回数を格納する
	int jumpPower;//ジャンプ時の重力抵抗
	float gravityPoewr;//ジャンプ時の重力
	bool endFlag; //ゲーム終了フラグ
	bool hitOnlyOne; //一度の接触で一度しか接触しないためのフラグ
	bool jumpFlag;//ジャンプ状態のフラグ
	cocos2d::Size visibleSize;//画面サイズ
	cocos2d::Vec2 origin;
	cocos2d::Vec2 defoultPos; //主人公スプライトの初期位置
	cocos2d::Vec2 enemyDefaultPos; //敵スプライトの初期位置
	cocos2d::Vec2 outOfWindowBGPos; //画面外に生成される背景スプライトの初期位置
	cocos2d::Label* scoreLabel;//スコア表示用ラベル
	static const int ANIMATION_MAX_NUM;
	static const int MAX_LIFE;
	static const int DEFOULT_GRAVITY_POWER;
	static const int DEFOULT_JUMP_POWER;
	static const float ADD_GRAVITY;
};

#endif