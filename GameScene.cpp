#pragma execution_character_set("utf-8")
#include "GameScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

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
	counter = 0;
	hitCounter = 0;
	endflag = false;
	hitOnlyOne = false;
	defoultPoint = Vec2(visibleSize.width / 7 + origin.x, visibleSize.height / 5 + origin.y);
	enemyDefPoint = Vec2(3 * visibleSize.width / 2 + origin.x, visibleSize.height / 6 + origin.y);

#pragma endregion
#pragma region BGMの設定
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("BGM.mp3");
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0f);
#pragma endregion
#pragma region スコア生成
	label = Label::createWithTTF("score:" + StringUtils::toString(counter), "fonts/Marker Felt.ttf", 24);
	label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - label->getContentSize().height));
	this->addChild(label,1);
#pragma endregion
#pragma region 背景初期設定
	auto backGround = Sprite::create("bg.png");
	auto backGround2 = Sprite::create("bg.png");
	backGround->setContentSize(Director::getInstance()->getVisibleSize());
	backGround2->setContentSize(backGround->getContentSize());
	backGround->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height /2 + origin.y);
	backGround2->setPosition(visibleSize.width + visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
	backGround->setTag(51);
	backGround2->setTag(52);
	this->addChild(backGround);
	this->addChild(backGround2);
#pragma endregion
#pragma region 立ち絵背景の初期設定
	auto whiteBack = Sprite::create("whiteBack.png");
	whiteBack->setContentSize((Size)Vec2(visibleSize.width/5+origin.x,visibleSize.height+origin.y));
	whiteBack->setPosition(visibleSize.width + origin.x -
							whiteBack->getContentSize().width / 2, visibleSize.height / 2 + origin.y);
	this->addChild(whiteBack, 2);	
#pragma endregion
#pragma region 主人公(SD)スプライトの初期設定
	auto yukari = Sprite::create("Normal.png");
	yukari->setScale((visibleSize.height + origin.y) / (yukari->getContentSize().height*3));
	yukari->setPosition(defoultPoint);
	yukari->setTag(1);
	this->addChild(yukari);
	auto flip = FlipX::create(true);//左右反転処理
	yukari->runAction(flip);
#pragma endregion
#pragma region 主人公(立ち絵)の初期設定
	auto yukari2 = Sprite::create("1.png");
	yukari2->setScale((visibleSize.height + origin.y) / (yukari2->getContentSize().height));
	yukari2->setPosition(visibleSize.width + origin.x - (yukari2->getContentSize().width / 4 * yukari2->getScale())
						,visibleSize.height/2+origin.y) ;
	//yukari2->setPosition(visibleSize.width-(yukari2->getContentSize().width/1.4), 
	//					visibleSize.height-(1.5*yukari2->getContentSize().height));
	yukari2->setTag(2);
	this->addChild(yukari2,3);
#pragma endregion
#pragma region 敵の初期設定
	auto enemy = Sprite::create("enemy.png");
	enemy->setPosition(enemyDefPoint);
	enemy->setScale((visibleSize.height+origin.y) / (enemy->getContentSize().height*3));
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
	this->scheduleUpdate();
#pragma endregion
	return true;
}

bool Game::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
#pragma region ジャンプ処理
	if (!endflag)
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto origin = Director::getInstance()->getVisibleOrigin();
		auto maxPoint = Point(defoultPoint.x, origin.y + 4 * visibleSize.height / 5);
		auto defaultPointed = Point(defoultPoint);
		/*アクションの作成*/
		auto moveJump = MoveTo::create(0.73f, maxPoint);
		auto moveDown = MoveTo::create(0.73f, defaultPointed);
		/*スプライトの作成*/
		auto yukari = (Sprite*)this->getChildByTag(1);
		/*アニメーション状態の確認*/
		if (yukari->numberOfRunningActions() == 0){
			yukari->setTexture("JUMP.png");
			/*シークエンス作成*/
			auto sequence = Sequence::create(moveJump, moveDown, NULL);
			//アニメーション開始
			yukari->runAction(sequence);
		}
	}
	else
	{
		Game::ended();
	}
#pragma endregion
	return true;
}

void Game::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	auto yukari = (Sprite*)this->getChildByTag(1);
}

void Game::update(float dt)
{
#pragma region 変数の宣言
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto visibleOrigin = Director::getInstance()->getVisibleOrigin();
	auto moveVec = Vec2(-5.5f, 0);
	auto backGround = this->getChildByTag(51);
	auto backGround2 = this->getChildByTag(52);
#pragma endregion
#pragma region 背景アニメーション
	auto pos = backGround->getPosition();
	auto pos2 = backGround2->getPosition();
	pos += moveVec;
	pos2 += moveVec;

	if (pos.x + backGround->getContentSize().width / 2 < 0){
		pos = Vec2(visibleSize.width + 0.95*visibleSize.width / 2 + visibleOrigin.x, visibleSize.height / 2);
	}
	if (pos2.x + backGround2->getContentSize().width / 2 < 0){
		pos2 = Vec2(visibleSize.width + 0.95*visibleSize.width / 2 + visibleOrigin.x, visibleSize.height / 2);
	}
	backGround->setPosition(pos);
	backGround2->setPosition(pos2);
#pragma endregion
#pragma region エネミーの行動
	auto enemy = this->getChildByTag(11);
	auto enemyPos = enemy->getPosition();
	float rand = random(0.5f, 2.0f);
	enemyPos += 2 * moveVec*rand;
	if (enemyPos.x + enemy->getContentSize().width < 0){
		enemyPos = Vec2(/*visibleSize.width + visibleSize.width / 2, visibleSize.height / 6*/enemyDefPoint);
		++counter;
		hitOnlyOne = false;
		label->setString("score:" + StringUtils::toString(counter));
	}
	enemy->setPosition(enemyPos);
#pragma endregion
#pragma region 接触判定
	auto yukari = (Sprite*)this->getChildByTag(1);
	auto yukari2 = (Sprite*)this->getChildByTag(2);
	auto rectyukari = yukari->getBoundingBox();
	auto rectEnemy = enemy->getBoundingBox();
	if (rectyukari.intersectsRect(rectEnemy) && !hitOnlyOne){
		++hitCounter;
		yukari->setTexture("HIT.png");
		if (hitCounter >= 4)
		{
			auto gameoverLabel = Label::create();
			gameoverLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2);
			gameoverLabel->setScale(3.0f);
			gameoverLabel->setString("GameOver...");
			SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			this->addChild(gameoverLabel);
			this->unscheduleUpdate();
			yukari->setTexture("HIT.png");
			endflag = true;
		}
		else
		{
			switch (hitCounter)
			{
			case 1:
				yukari2->setTexture("2.png"); hitOnlyOne = true; break;
			case 2:
				yukari2->setTexture("3.png"); hitOnlyOne = true; break;
			case 3:
				yukari2->setTexture("4.png"); hitOnlyOne = true;
			default:
				break;
			}
		}
	}
#pragma endregion
#pragma region 立ち絵の更新
	if (yukari->getPosition() == defoultPoint && !hitOnlyOne && yukari->numberOfRunningActions() == 0 && !endflag)
		yukari->setTexture("Normal.png");
#pragma endregion
}

void Game::ended()
{
	Director::getInstance()->end();
}