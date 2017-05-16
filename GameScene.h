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
	/// <summary>
	/// シーン作成用関数，シーンを作成したい場合はこの関数を呼び出す
	/// </summary>
	/// <returns>シーン</returns>
	static cocos2d::Scene* creatScene();
	
	/// <summary>
	/// 初期化用関数，シーン作成時一番最初に呼び出される．
	/// <para>各種変数の初期化，再起処理の設定などをここで行う</para>
	/// </summary>
	/// <returns>true...初期化完了時,false...レイヤーが作成されていない場合</returns>
	virtual bool init();

	CREATE_FUNC(Game);

	/// <summary>
	///  画面がタッチされた際に呼び出される，マウスのクリックでも呼び出される．
	/// <para>アニメーションの開始処理を行う．</para> 
	/// </summary>
	/// <param name="touch">指(マウス)情報(自動で取得される)</param>
	/// <param name="event">操作情報(自動で取得される)</param>
	/// <returns>true...タッチされた状態を返す</returns>
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

	/// <summary>
	///<para> 周期処理関数，この関数をinitで呼び出すと以降関数内の処理が繰り返し処理される．</para>
	/// <para>背景の移動，敵の移動，キャラクターと敵の接触判定を行う.</para>
	/// </summary>
	/// <param name="dt">実行毎の時間(内部的に利用されるもの)</param>
	void update(float dt);

	int score; //敵をよけた回数を格納する
	int hitCounter; //hitCounter...敵と接触した回数を格納する
	bool endFlag; //ゲーム終了フラグ
	bool hitOnlyOne; //一度の接触で一度しか接触しないためのフラグ
	cocos2d::Vec2 defoultPos; //主人公スプライトの初期位置
	cocos2d::Vec2 enemyDefaultPos; //敵スプライトの初期位置
	cocos2d::Label* label;//ヘッダーで宣言した変数は，継承クラスで再度定義する必要はない．(この時点でグローバル変数化しているため)
};

#endif