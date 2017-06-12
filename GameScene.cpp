#pragma execution_character_set("utf-8")
#include "GameScene.h"
#include "GameoverScene.h"
#include "Macro.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

void nextScene();

Scene* Game::creatScene()
{
	auto scene = Scene::create();
	auto layer = Game::create();
	scene->addChild(layer);
	return scene;
}

bool Game::init()
{

	if (!Layer::init())
	{
		return false;
	}

#pragma region グローバル変数の初期化
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	score = 0;
	hitCounter = 0;
	endFlag = false;
	hitOnlyOne = false;
	defoultPos = Vec2(visibleSize.width / 7 + origin.x,  origin.y);
	enemyDefaultPos = Vec2(3 * visibleSize.width / 2 + origin.x, visibleSize.height / 6 + origin.y);
	outOfWindowBGPos = Vec2(-visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

#pragma endregion

#pragma region BGMの設定
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("BGM.mp3");
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0f);
#pragma endregion

#pragma region SEの設定
	SimpleAudioEngine::getInstance()->preloadEffect(DAMEGE_VOICE);
	SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);
#pragma endregion

#pragma region スコア生成
	label = Label::createWithTTF("score:" + StringUtils::toString(score), "fonts/Marker Felt.ttf", 24);
	label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - label->getContentSize().height));
	this->addChild(label,1);
#pragma endregion

#pragma region 背景初期設定
	auto backGround = Sprite::create("bg.png");
	backGround->setContentSize((Size)Vec2(visibleSize.width + 0.1*visibleSize.width, visibleSize.height));
	backGround->setPosition(visibleSize.width/2 + origin.x, visibleSize.height / 2 + origin.y);
	backGround->setTag(51);
	this->addChild(backGround);

	auto backGround2 = Sprite::create("bg.png");
	backGround2->setContentSize(backGround->getContentSize());
	backGround2->setPosition(outOfWindowBGPos);
	backGround2->setTag(52);
	this->addChild(backGround2);
#pragma endregion

#pragma region 主人公(SD)スプライトの初期設定
	auto mainCharactor = Sprite::create(SD_NORMAL);
	mainCharactor->setScale((visibleSize.height + origin.y) / (mainCharactor->getContentSize().height*2.5));
	mainCharactor->setPosition(defoultPos);
	mainCharactor->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	mainCharactor->setTag(1);
	this->addChild(mainCharactor);
#pragma endregion

#pragma region 主人公(立ち絵)の初期設定
	auto characterImage = Sprite::create(IMAGE_NORMAL);
	characterImage->setScale((visibleSize.height + origin.y) / (characterImage->getContentSize().height));
	characterImage->setPosition(visibleSize.width + origin.x - (characterImage->getContentSize().width / 4 * characterImage->getScale())
						,visibleSize.height/2+origin.y) ;
	characterImage->setOpacity(200);
	characterImage->setTag(2);
	this->addChild(characterImage,3);
#pragma endregion

#pragma region 敵の初期設定
	auto enemy = Sprite::create("enemy.png");
	enemy->setPosition(enemyDefaultPos);
	enemy->setScale((visibleSize.height+origin.y) / (enemy->getContentSize().height*5));
	enemy->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	enemy->setTag(11);
	this->addChild(enemy);
#pragma endregion

#pragma region クリックリスナーの初期設定
	auto listner = EventListenerTouchOneByOne::create();
	listner->onTouchBegan = CC_CALLBACK_2(Game::onTouchBegan, this);
	listner->onTouchEnded = CC_CALLBACK_2(Game::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listner, this);
#pragma endregion

#pragma region BGM再生
	SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM.mp3",true);
#pragma endregion

#pragma region 繰り返し処理の初期設定
	this->runAction(Sequence::create(DelayTime::create(1), 
		CallFunc::create([this](){this->scheduleUpdate(); }), NULL));
#pragma endregion

	return true;
}

bool Game::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
#pragma region ジャンプ処理
	if (!endFlag)
	{
		auto mainCharactor = (Sprite*)this->getChildByTag(1);
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto origin = Director::getInstance()->getVisibleOrigin();
		auto maxPoint = Point(defoultPos.x, 
											origin.y + visibleSize.height - mainCharactor->getContentSize().height*mainCharactor->getScale());
		/*アクションの作成*/
		auto moveUp = MoveTo::create(0.73f, maxPoint);
		auto moveDown = MoveTo::create(0.73f, defoultPos);
		/*アニメーション状態の確認*/
		if (mainCharactor->getNumberOfRunningActions() == 0){
			mainCharactor->setTexture(SD_JUMP);
			/*シークエンス作成*/
			auto sequence = Sequence::create(moveUp, moveDown, NULL);
			//アニメーション開始
			mainCharactor->runAction(sequence);
		}
	}
	else
	{
		Director::getInstance()->replaceScene(GameOver::creatScene());
	}
#pragma endregion
	return true;
}

void Game::update(float dt)
{
#pragma region 変数の宣言
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto moveVec = Vec2(5.5f, 0);
	auto backGround = this->getChildByTag(51);
	auto backGround2 = this->getChildByTag(52);
#pragma endregion

#pragma region 背景アニメーション
	auto pos = backGround->getPosition();
	auto pos2 = backGround2->getPosition();
	pos += moveVec;
	pos2 += moveVec;

	if (pos.x - backGround->getContentSize().width / 2 > visibleSize.width){
		pos = Vec2(outOfWindowBGPos);
	}
	if (pos2.x - backGround2->getContentSize().width / 2 > visibleSize.width){
		pos2 = Vec2(outOfWindowBGPos);
	}
	backGround->setPosition(pos);
	backGround2->setPosition(pos2);
#pragma endregion

#pragma region エネミーの行動
	auto enemy = this->getChildByTag(11);
	auto enemyPos = enemy->getPosition();
	float rand = random(0.5f, 2.0f);
	enemyPos -= 2 * moveVec*rand;
	if (enemyPos.x + enemy->getContentSize().width < 0){
		enemyPos = Vec2(enemyDefaultPos);
		++score;
		hitOnlyOne = false;
		label->setString("score:" + StringUtils::toString(score));
	}
	enemy->setPosition(enemyPos);
#pragma endregion

#pragma region 接触判定
	auto mainCharactor = (Sprite*)this->getChildByTag(1);
	auto characterImage = (Sprite*)this->getChildByTag(2);
	auto rectmainCharactor = mainCharactor->getBoundingBox();
	auto rectEnemy = enemy->getBoundingBox();
	if (rectmainCharactor.intersectsRect(rectEnemy) && !hitOnlyOne){
		++hitCounter;
		SimpleAudioEngine::getInstance()->playEffect(DAMEGE_VOICE);
		mainCharactor->setTexture(SD_DAMAGE);
		characterImage->setTexture(IMAGE_DAMEGE);
		if (hitCounter >= 4)
		{
			auto gameoverLabel = Label::createWithTTF("ゲームオーバー...", JPN_FONTS, 24);
			gameoverLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2);
			gameoverLabel->setScale(3.0f);
			SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			this->addChild(gameoverLabel);
			this->unscheduleUpdate();
			mainCharactor->stopAllActions();
			UserDefault::getInstance()->setIntegerForKey("score", score);
			UserDefault::getInstance()->flush();
			endFlag = true;
		}
		hitOnlyOne = true;
	}
#pragma endregion

#pragma region 立ち絵の更新
	if (mainCharactor->getPosition() == defoultPos && !hitOnlyOne && mainCharactor->getNumberOfRunningActions() == 0 && !endFlag)
	{
		mainCharactor->setTexture(SD_NORMAL);
		characterImage->setTexture(IMAGE_NORMAL);
	}
#pragma endregion
}

void nextScene()
{
	Director::getInstance()->replaceScene(GameOver::creatScene());
}