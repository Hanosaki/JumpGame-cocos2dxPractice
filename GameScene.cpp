﻿#pragma execution_character_set("utf-8")
#include "GameScene.h"
#include "GameoverScene.h"
#include "CharaResouse.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

void nextScene();
float setEnemySpeed();

const int Game::ANIMATION_MAX_NUM = 17;
const int Game::MAX_LIFE = 3;
const int Game::DEFOULT_GRAVITY_POWER = 0;
const int Game::DEFOULT_JUMP_POWER = 23;
const float Game::ADD_GRAVITY = 0.1f;
const float Game::MOVE_SPEED = 8.5f;
const float Game::GAME_SPEED = 0.02f;

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
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	score = 0;
	hitCounter = 0;
	animeSpeed = 0.04f;
	enemySpeed = setEnemySpeed();;
	endFlag = false;
	hitOnlyOne = false;
	jumpFlag = false;
	speedChangeFlag = false;
	defoultPos = Vec2(visibleSize.width / 6 + origin.x,  origin.y);
	enemyDefaultPos = Vec2(3 * visibleSize.width / 2 + origin.x, visibleSize.height / 6 + origin.y);
	outOfWindowBGPos = Vec2(-visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
#pragma endregion

#pragma region BGMのプリロード
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MAIN_BGM);
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0f);
#pragma endregion

#pragma region SEのプリロード
	SimpleAudioEngine::getInstance()->preloadEffect(DAMEGE_VOICE);
	SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);
#pragma endregion

#pragma region スコア生成
	scoreLabel = Label::createWithTTF(SCORE_TEXT + StringUtils::toString(score), F_FONTS+ENG_FONTS, 36);
	scoreLabel->setPosition(Vec2(visibleSize.width / 2 +origin.x , visibleSize.height + origin.y - scoreLabel->getContentSize().height));
	this->addChild(scoreLabel,1);
#pragma endregion

#pragma region 背景初期設定
	auto backGround = Sprite::create(F_IMAGE+BACK_GROUND);
	backGround->setContentSize((Size)Vec2(visibleSize.width + 0.1f*visibleSize.width, visibleSize.height));
	backGround->setPosition(visibleSize.width/2 + origin.x, visibleSize.height / 2 + origin.y);
	backGround->setTag(51);
	this->addChild(backGround);

	auto backGround2 = Sprite::create(F_IMAGE+BACK_GROUND);
	backGround2->setContentSize(backGround->getContentSize());
	backGround2->setPosition(outOfWindowBGPos);
	backGround2->setTag(52);
	this->addChild(backGround2);
#pragma endregion

#pragma region 主人公(animation)スプライトの初期設定
	auto mainCharacter = Sprite::create(F_ANIMATION+F_RUN+DEFAULT);
	mainCharacter->setScale((visibleSize.height + origin.y) / (mainCharacter->getContentSize().height*2));
	mainCharacter->setPosition(defoultPos);
	mainCharacter->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	mainCharacter->setTag(1);
	this->addChild(mainCharacter,1);
#pragma endregion

	setCharacterDefault();
	
#pragma region 主人公当たり判定
	auto hitDeterminationBox = Rect(0, 0,
		mainCharacter->getContentSize().width / 5.5f * mainCharacter->getScaleX(),
		mainCharacter->getContentSize().height / 2.5f * mainCharacter->getScaleY());
	auto hitDetermination = Sprite::create();
	hitDetermination->setTextureRect(hitDeterminationBox);
	hitDetermination->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	hitDetermination->setPositionX(mainCharacter->getPositionX());
	hitDetermination->setTag(11);
	hitDetermination->setColor(Color3B::BLACK);
	hitDetermination->setVisible(false);
	this->addChild(hitDetermination);
#pragma endregion

#pragma region 主人公(立ち絵)の初期設定
	auto characterImage = Sprite::create(F_MAIN_CHARACTER+ F_IMAGE + ANGRY);
	characterImage->setScale((visibleSize.height + origin.y) / (characterImage->getContentSize().height));
	characterImage->setPosition(visibleSize.width + origin.x - (characterImage->getContentSize().width / 4 * characterImage->getScale())
						,visibleSize.height/2+origin.y) ;
	characterImage->setOpacity(200);
	characterImage->setTag(2);
	this->addChild(characterImage,3);
#pragma endregion

#pragma region 体力ゲージの初期設定
	auto lifeLabel = Label::createWithTTF("LIFE:", F_FONTS + ENG_FONTS,36);
	lifeLabel->setPosition(origin.x + lifeLabel->getContentSize().width / 2,
		visibleSize.height + origin.y - lifeLabel->getContentSize().height / 2);
	lifeLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->addChild(lifeLabel, 3);

	Sprite* life[MAX_LIFE];
	for (int i = 0; i < MAX_LIFE; ++i)
	{
		life[i] = Sprite::create(F_IMAGE + LIFE_ICON);
		life[i]->setScale((visibleSize.height + origin.y) / (6 * life[i]->getContentSize().height));
		life[i]->setPosition(lifeLabel->getContentSize().width + origin.x + (life[i]->getContentSize().width * life[i]->getScale() * (MAX_LIFE - i)),
			visibleSize.height + origin.y - life[i]->getContentSize().height * life[i]->getScale() /2 );
		life[i]->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		life[i]->setTag(20+i);
		auto rollSpeed = 0.5f;
		auto angle = 25;
		auto rollLeft = RotateTo::create(rollSpeed,angle);
		auto rollRight = RotateTo::create(rollSpeed,-angle);
		auto sequence = Sequence::create(rollLeft, rollRight, NULL);
		life[i]->runAction(RepeatForever::create(sequence));
		this->addChild(life[i],3);
	}

#pragma endregion

#pragma region 敵の初期設定
	auto enemy = Sprite::create(F_RIVAL + ENEMY_IMAGE);
	enemy->setPosition(enemyDefaultPos.x*2,enemyDefaultPos.y);
	enemy->setScale((visibleSize.height+origin.y) / (enemy->getContentSize().height*5));
	enemy->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	enemy->setTag(31);
	this->addChild(enemy,1);
#pragma endregion

#pragma region クリックリスナーの初期設定
	auto listner = EventListenerTouchOneByOne::create();
	listner->onTouchBegan = CC_CALLBACK_2(Game::onTouchBegan, this);
	listner->onTouchEnded = CC_CALLBACK_2(Game::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listner, this);
#pragma endregion

#pragma region BGM再生
	SimpleAudioEngine::getInstance()->playBackgroundMusic(MAIN_BGM,true);
#pragma endregion

#pragma region 繰り返し処理の初期設定
	this->runAction(Sequence::create(DelayTime::create(1.5f), 
		CallFunc::create([this](){this->schedule(schedule_selector(Game::main),GAME_SPEED); }), NULL));
#pragma endregion

	return true;
}

bool Game::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
#pragma region ジャンプ開始
	if (!endFlag)
	{
		if (!jumpFlag && !hitOnlyOne)
		{
			auto mainCharacter = (Sprite*)this->getChildByTag(1);
			if (mainCharacter->isRunning())
			{
				mainCharacter->stopActionByTag(101);
				mainCharacter->setTexture(F_MAIN_CHARACTER + CHARACTER_JUMP);
				jumpFlag = !jumpFlag;
				jumpPower = DEFOULT_JUMP_POWER;
				gravityPoewr = DEFOULT_GRAVITY_POWER;
			}
		}
			
	}
	else
	{
		Director::getInstance()->replaceScene(GameOver::creatScene());
	}
#pragma endregion
	return true;
}

void Game::main(float dt)
{
#pragma region 変数の宣言
	auto mainCharacter = (Sprite*)this->getChildByTag(1);
	auto moveVec = Vec2(MOVE_SPEED, 0);
	auto backGround = this->getChildByTag(51);
	auto backGround2 = this->getChildByTag(52);
#pragma endregion

#pragma region 背景アニメーション
	auto pos = backGround->getPosition();
	auto pos2 = backGround2->getPosition();
	if (!hitOnlyOne){
		pos += moveVec;
		pos2 += moveVec;
	}

	if (pos.x - backGround->getContentSize().width / 2 > visibleSize.width){
		pos = Vec2(outOfWindowBGPos);
	}
	if (pos2.x - backGround2->getContentSize().width / 2 > visibleSize.width){
		pos2 = Vec2(outOfWindowBGPos);
	}
	backGround->setPosition(pos);
	backGround2->setPosition(pos2);
#pragma endregion

#pragma region ジャンプ処理

	if (jumpFlag)
	{
		auto mainCharacterPosY = mainCharacter->getPositionY();
		mainCharacterPosY += jumpPower - (9.8f * gravityPoewr);
		gravityPoewr += ADD_GRAVITY;
		mainCharacter->setPositionY(mainCharacterPosY);
		if (mainCharacterPosY <= defoultPos.y)
		{
			jumpFlag = !jumpFlag;
			mainCharacter->setPositionY(defoultPos.y);
		}
	}

#pragma endregion

#pragma region エネミーの行動
	auto enemy = this->getChildByTag(31);
	auto enemyPos = enemy->getPosition();
	enemyPos -= 2 * moveVec*enemySpeed;
	if (enemyPos.x + enemy->getContentSize().width < 0){
		enemyPos = Vec2(enemyDefaultPos);
		if (int rand = random(0,2) == 2)
			enemyPos.y *= 3.5f;
		enemySpeed = setEnemySpeed();
		++score;
		hitOnlyOne = false;
		scoreLabel->setString(SCORE_TEXT + StringUtils::toString(score));
	}
	enemy->setPosition(enemyPos);
#pragma endregion

#pragma region 接触判定
	auto hitDetermination = (Sprite*)this->getChildByTag(11);
	hitDetermination->setPositionY(mainCharacter->getPositionY()
		+ mainCharacter->getContentSize().height / 4
		* mainCharacter->getScale());

	auto rectMainCharactor = hitDetermination->getBoundingBox();
	auto rectEnemy = enemy->getBoundingBox();

	if (rectMainCharactor.intersectsRect(rectEnemy) && !hitOnlyOne){
		jumpPower = 0;
		SimpleAudioEngine::getInstance()->playEffect(DAMEGE_VOICE);
		auto characterImage = (Sprite*)this->getChildByTag(2);
		mainCharacter->stopActionByTag(101);
		mainCharacter->setTexture(F_MAIN_CHARACTER + CHARACTER_DAMAGE);
		characterImage->setTexture(F_MAIN_CHARACTER + F_IMAGE + SAD);
		this->getChildByTag(20 + hitCounter)->setVisible(false);
		++hitCounter;
		if (hitCounter >= MAX_LIFE)
		{
			auto gameoverLabel = Label::createWithTTF(GAME_OVER_TEXT, F_FONTS + JPN_FONTS, 24);
			gameoverLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2);
			gameoverLabel->setScale(3.0f);
			SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			this->addChild(gameoverLabel);
			this->unschedule(schedule_selector(Game::main));
			mainCharacter->stopAllActions();
			UserDefault::getInstance()->setIntegerForKey(SCORE_KEY, score);
			UserDefault::getInstance()->flush();
			endFlag = true;
		}
		hitOnlyOne = true;
	}
#pragma endregion

#pragma region ゲーム速度変更
	if (score != 0 && score % 10 == 0 && !speedChangeFlag)
	{
		float acceleration = score / 5000.0f;
		if (GAME_SPEED - acceleration > 0)
		{
			speedChangeFlag = !speedChangeFlag;
			this->schedule(schedule_selector(Game::main), GAME_SPEED - acceleration);
		}
	}
	else if (score % 11 == 0 && speedChangeFlag)
		speedChangeFlag = !speedChangeFlag;
#pragma endregion

#pragma region 主人公初期化呼び出し
	if (mainCharacter->getPosition() == defoultPos && !hitOnlyOne
		&& mainCharacter->getNumberOfRunningActions() == 0 && !endFlag)
	{
		setCharacterDefault();
	}
#pragma endregion
}

#pragma region 主人公初期化設定
void Game::setCharacterDefault()
{
	auto mainCharacter = (Sprite*)this->getChildByTag(1);

	try{
		/*主人公走りモーション設定*/
		auto animation = Animation::create();
		for (int i = 0; i < ANIMATION_MAX_NUM; ++i)
			animation->addSpriteFrameWithFile(F_ANIMATION + F_RUN + StringUtils::toString(i) + ".png");
		if (score % 10 == 0)
		{
			float acceleration = score / 7500.0f;
			if (animeSpeed - acceleration > 0.02f)
				animeSpeed -= acceleration;
		}
		animation->setDelayPerUnit(animeSpeed);
		animation->setRestoreOriginalFrame(true);
		auto runAnime = Animate::create(animation);
		auto runAnimation = RepeatForever::create(runAnime);
		runAnimation->setTag(101);
		mainCharacter->runAction(runAnimation);
		/*主人公走りモーション設定*/

		if (auto characterImage = (Sprite*)getChildByTag(2))
			characterImage->setTexture(F_MAIN_CHARACTER + F_IMAGE + ANGRY);
	}
	catch (char* messeage)
	{
		puts(messeage);
	}
}
#pragma endregion

float setEnemySpeed()
{
	float enemySpeed = random(1.0f, 2.0f);
	return enemySpeed;
}

void nextScene()
{
	Director::getInstance()->replaceScene(GameOver::creatScene());
}

