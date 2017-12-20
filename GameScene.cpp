﻿#pragma execution_character_set("utf-8")
#include "GameScene.h"
#include "GameoverScene.h"
#include "GenericFunction.h"
#include "CharaResouse.h"
#include "SimpleAudioEngine.h"
#include "Converter.h"

using namespace CocosDenshion;
USING_NS_CC;

void nextScene();
float setEnemySpeed();

const int Game::MAX_LIFE = 3;

Scene* Game::createScene()
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
	auto director = Director::getInstance();
	visibleSize = director->getVisibleSize();
	origin = director->getVisibleOrigin();
	scaleFactor = director->getContentScaleFactor();
	score = 0;
	hitCounter = 0;
	animeSpeed = 0.04f;
	enemySpeed = 1.2f;
	endFlag = false;
	hitOnlyOne = false;
	jumpFlag = false;
	speedChangeFlag = false;
	isPause = false;
	nextSceneFlag = false;
	defoultPos = Vec2(visibleSize.width / 6 + origin.x,  origin.y);
	enemyDefaultPos = Vec2(3 * visibleSize.width / 2 + origin.x, visibleSize.height / 6 + origin.y);
	outOfWindowBGPos = Vec2(3 * visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
#pragma endregion

	/*音量設定*/
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5f);
	SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);

#pragma region スコア生成
	scoreLabel = Label::createWithTTF(SCORE_TEXT + StringUtils::toString(score), F_FONTS+ENG_FONTS, 36);
	scoreLabel->setPosition(Vec2(visibleSize.width / 2 +origin.x , visibleSize.height + origin.y - scoreLabel->getContentSize().height));
	this->addChild(scoreLabel,1);
#pragma endregion

#pragma region 背景初期設定
	auto backGround = Sprite::create(F_IMAGE + F_UI + BACK_GROUND);
	backGround->setContentSize((Size)Vec2(visibleSize.width + 0.1f*visibleSize.width, visibleSize.height));
	backGround->setPosition(visibleSize.width/2 + origin.x, visibleSize.height / 2 + origin.y);
	backGround->setTag(51);
	this->addChild(backGround);

	auto backGround2 = Sprite::create(F_IMAGE + F_UI + BACK_GROUND);
	backGround2->setContentSize(backGround->getContentSize());
	backGround2->setPosition(outOfWindowBGPos);
	backGround2->setTag(52);
	this->addChild(backGround2);
#pragma endregion

#pragma region 主人公(animation)スプライトの初期設定
	auto mainCharacter = Sprite::create(F_IMAGE +F_ANIMATION+F_RUN+DEFAULT);
	mainCharacter->setScale((origin.y + visibleSize.height) / (mainCharacter->getContentSize().height * 2));
	mainCharacter->setPosition(defoultPos);
	mainCharacter->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	mainCharacter->setTag(1);
	mainCharacter->setFlippedX(true);
	this->addChild(mainCharacter,1);
#pragma endregion

	setCharacterDefault();

#pragma region ポーズボタン

	auto pauseButton = Sprite::create(F_IMAGE + F_UI + PAUSE_BUTTON);
	pauseButton->setTag(41);
	auto selectedPauseButton = Sprite::create(F_IMAGE + F_UI + PAUSE_BUTTON);
	selectedPauseButton->setOpacity(128);
	selectedPauseButton->setTag(42);

	auto pauseItem = MenuItemSprite::create(pauseButton, selectedPauseButton, CC_CALLBACK_1(Game::pauseGame, this));
	pauseItem->setScale(scaleFactor - 0.5*scaleFactor);
	pauseItem->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	pauseItem->setPosition(origin.x + visibleSize.width, origin.y + visibleSize.height);
	pauseItem->setTag(43);
	auto pauseMenu = Menu::create(pauseItem, NULL);
	pauseMenu->setPosition(Vec2::ZERO);
	pauseMenu->setTag(44);
	this->addChild(pauseMenu, 2);

#pragma endregion

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
	auto characterImage = Sprite::create(F_IMAGE + F_MAIN_CHARACTER + FACE_AWARENESS);
	characterImage->setPosition(0 , origin.y + visibleSize.height);
	characterImage->setScale(scaleFactor - 0.6f*scaleFactor);
	characterImage->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	characterImage->setTag(2);
	this->addChild(characterImage,3);
#pragma endregion

#pragma region 体力ゲージの初期設定
	Sprite* life[MAX_LIFE];
	auto lifePostionBase = characterImage->getContentSize() * characterImage->getScale();
	for (int i = 0; i < MAX_LIFE; ++i)
	{
		life[i] = Sprite::create(F_IMAGE + F_UI + LIFE_ICON);
		life[i]->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		life[i]->setScale((visibleSize.height + origin.y) / (6 * life[i]->getContentSize().height));
		life[i]->setPosition(lifePostionBase.width + origin.x + (life[i]->getContentSize().width * life[i]->getScale() * (MAX_LIFE - i)),
			origin.y + visibleSize.height - lifePostionBase.height / 2);
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
	auto enemy = Sprite::create(F_IMAGE + F_RIVAL + ENEMY_IMAGE);
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

	// BGM再生
	Converter converter;
	auto bgmName = converter.replaceString2Char(F_BGM + MAIN_BGM + TYPE_MP3);
	SimpleAudioEngine::getInstance()->playBackgroundMusic(bgmName,true);

	//SE再生
	auto seName = converter.replaceString2Char(F_SE + RIVAL_VOICE + TYPE_MP3);
	SimpleAudioEngine::getInstance()->playEffect(seName);

#pragma region 繰り返し処理の初期設定
	this->runAction(Sequence::create(DelayTime::create(1.5f), 
		CallFunc::create([this](){this->schedule(schedule_selector(Game::main), Parameter::GAME_SPEED); }),NULL));
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
				mainCharacter->setTexture(F_IMAGE + F_MAIN_CHARACTER + CHARACTER_JUMP);
				jumpFlag = !jumpFlag;
				jumpPower = Parameter::DEFOULT_JUMP_POWER;
				gravityPoewr = Parameter::DEFOULT_GRAVITY_POWER;
				srand((unsigned int)time(NULL));
				int num = rand() % 2;
				Converter converter;
				auto jumpSE1 = converter.replaceString2Char(F_SE + JUMP_SE + TYPE_MP3);
				auto jumpSE2 = converter.replaceString2Char(F_SE + JUMP_SE2 + TYPE_MP3);
				switch (num)
				{
				case 0:SimpleAudioEngine::getInstance()->playEffect(jumpSE1); break;
				case 1:SimpleAudioEngine::getInstance()->playEffect(jumpSE2); break;
				default:
					break;
				}
				auto characterImage = (Sprite*)this->getChildByTag(2);
				characterImage->setTexture(F_IMAGE + F_MAIN_CHARACTER + FACE_AWARENESS);
			}
		}
			
	}
	else if (nextSceneFlag)
	{
		Director::getInstance()->replaceScene(GameOver::createScene());
	}
#pragma endregion
	return true;
}

void Game::main(float dt)
{
#pragma region 変数の宣言
	auto mainCharacter = (Sprite*)this->getChildByTag(1);
	auto moveVec = Vec2(Parameter::MOVE_SPEED, 0);
	auto backGround = this->getChildByTag(51);
	auto backGround2 = this->getChildByTag(52);
	auto enemy = this->getChildByTag(31);
	auto enemyPos = enemy->getPosition();
#pragma endregion

#pragma region 背景アニメーション
	auto pos = backGround->getPosition();
	auto pos2 = backGround2->getPosition();
	if (!hitOnlyOne){
		pos -= moveVec;
		pos2 -= moveVec;
	}

	if (pos.x + backGround->getContentSize().width / 2 < 0){
		pos = Vec2(outOfWindowBGPos);
	}
	if (pos2.x + backGround2->getContentSize().width / 2 <0){
		pos2 = Vec2(outOfWindowBGPos);
	}
	backGround->setPosition(pos);
	backGround2->setPosition(pos2);
#pragma endregion


	if (hitCounter >= MAX_LIFE && !endFlag)
		endFlag = !endFlag;

	if (!endFlag)
	{

	#pragma region ジャンプ処理

		if (jumpFlag)
		{
			auto mainCharacterPosY = mainCharacter->getPositionY();
			mainCharacterPosY += jumpPower - (9.8f * gravityPoewr);
			gravityPoewr += Parameter::ADD_GRAVITY;
			mainCharacter->setPositionY(mainCharacterPosY);
			if (mainCharacterPosY <= defoultPos.y)
			{
				jumpFlag = !jumpFlag;
				mainCharacter->setPositionY(defoultPos.y);
			}
		}

	#pragma endregion

	#pragma region エネミーの行動
		enemyPos -= 2 * moveVec*enemySpeed;
		if (enemyPos.x + enemy->getContentSize().width < 0){
			enemyPos = Vec2(enemyDefaultPos);
			srand((unsigned int)time(NULL));
			int num = rand() % 3;
			auto characterImage = (Sprite*)this->getChildByTag(2);
			if (num == 2)
			{
				enemyPos.y *= 3.5f;
				characterImage->setTexture(F_IMAGE + F_MAIN_CHARACTER + FACE_NORMAL);
			}
			else
			{
				characterImage->setTexture(F_IMAGE + F_MAIN_CHARACTER + FACE_AWARENESS);
				Converter converter;
				auto seName = converter.replaceString2Char(F_SE + ALERT_SE + TYPE_MP3);
				SimpleAudioEngine::getInstance()->playEffect(seName);
			}
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

		if (rectMainCharactor.intersectsRect(rectEnemy) && hitCounter < MAX_LIFE)
		{
			jumpPower = 0;
			Converter converter;
			auto seName = converter.replaceString2Char(F_SE + DAMEGE_VOICE + TYPE_MP3);
			SimpleAudioEngine::getInstance()->stopAllEffects();
			SimpleAudioEngine::getInstance()->playEffect(seName);
			auto characterImage = (Sprite*)this->getChildByTag(2);
			mainCharacter->stopActionByTag(101);
			mainCharacter->setTexture(F_IMAGE + F_MAIN_CHARACTER + DAMAGE_ANIME);
			characterImage->setTexture(F_IMAGE + F_MAIN_CHARACTER + FACE_DAMAGE);
			if (!hitOnlyOne)
			{
				this->getChildByTag(20 + hitCounter)->setVisible(false);
				hitOnlyOne = true;
				++hitCounter;
			}
		}
	#pragma endregion

	}
	else
	{
		if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		{
			SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			auto menu = (Menu*)this->getChildByTag(44);
			menu->setEnabled(false);
			menu->setOpacity(false);
			mainCharacter->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
			mainCharacter->runAction(RepeatForever::create(RotateBy::create(1.f, -360.f*5)));

		}
		enemyPos -= 2 * moveVec*enemySpeed;
		enemy->setPosition(enemyPos);
		if (score < 20)
			mainCharacter->setPositionX(mainCharacter->getPositionX() - moveVec.x * 3);
		else
			mainCharacter->setPositionX(mainCharacter->getPositionX() - moveVec.x * enemySpeed *2);

		if (enemyPos.x + enemy->getContentSize().width < 0 && 
			mainCharacter->getPositionX() < -mainCharacter->getContentSize().width/2)
		{
			auto gameoverLabel = Label::createWithTTF(GAME_OVER_TEXT, F_FONTS + JPN_FONTS, Parameter::LARGE * scaleFactor);
			gameoverLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2);
			this->addChild(gameoverLabel, 4);
			auto anotation = Label::createWithTTF("タップでスコア画面に移動", F_FONTS + JPN_FONTS, Parameter::MIDDLE * scaleFactor);
			anotation->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
			anotation->setPositionX(gameoverLabel->getPositionX());
			anotation->setPositionY(gameoverLabel->getPositionY() - anotation->getContentSize().height);
			auto sequence = Sequence::create(FadeOut::create(1.f), FadeIn::create(1.f), NULL);
			anotation->runAction(RepeatForever::create(sequence));
			this->addChild(anotation, 4);
			this->unschedule(schedule_selector(Game::main));
			mainCharacter->stopAllActions();
			UserDefault::getInstance()->setIntegerForKey(SCORE_KEY, score);
			UserDefault::getInstance()->flush();
			nextSceneFlag = true;
		}
	}
	

#pragma region ゲーム速度変更
	if (score != 0 && score % 10 == 0 && !speedChangeFlag)
	{
		float acceleration = score / 5000.0f;
		if (Parameter::GAME_SPEED - acceleration > 0)
		{
			speedChangeFlag = !speedChangeFlag;
			this->unschedule(schedule_selector(Game::main));
			this->schedule(schedule_selector(Game::main), Parameter::GAME_SPEED - acceleration);
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

#pragma region ポーズボタンの処理

void Game::pauseGame(Ref* Sender)
{
	auto mainCharacter = (Sprite*)this->getChildByTag(1);
	Sprite* life[MAX_LIFE];
	auto menuItem = (MenuItem*)this->getChildByTag(44)->getChildByTag(43);
	auto selectedButtonImage = (Sprite*)menuItem->getChildByTag(42);
	auto buttonImage = (Sprite*)menuItem->getChildByTag(41);
	if (!isPause)
	{
		this->pause();
		mainCharacter->pause();
		for (int i = 0; i < MAX_LIFE; ++i)
		{
			life[i] = (Sprite*)this->getChildByTag(20 + i);
			life[i]->pause();
		}
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		buttonImage->setTexture(F_IMAGE + F_UI + RESUME_BUTTON);
		selectedButtonImage->setTexture(F_IMAGE + F_UI + RESUME_BUTTON);
	}
	else
	{
		this->resume();
		mainCharacter->resume();
		for (int i = 0; i < MAX_LIFE; ++i)
		{
			life[i] = (Sprite*)this->getChildByTag(20 + i);
			life[i]->resume();
		}
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		buttonImage->setTexture(F_IMAGE + F_UI + PAUSE_BUTTON);
		selectedButtonImage->setTexture(F_IMAGE + F_UI + PAUSE_BUTTON);
	}
	isPause = !isPause;
}

#pragma endregion

#pragma region 主人公初期化設定
void Game::setCharacterDefault()
{
	auto mainCharacter = (Sprite*)this->getChildByTag(1);
	try{
		/*主人公走りモーション設定*/
		auto animation = Animation::create();
		for (int i = 0; i < Parameter::ANIMATION_MAX_NUM; ++i)
			animation->addSpriteFrameWithFile(F_IMAGE + F_ANIMATION + F_RUN + StringUtils::toString(i) + ".png");
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
	}
	catch (char* messeage)
	{
		puts(messeage);
	}
}
#pragma endregion

float setEnemySpeed()
{
	srand((unsigned int)time(NULL));
	float enemySpeed = random(1.0f, 2.1f);
	return enemySpeed;
}

void nextScene()
{
	Director::getInstance()->replaceScene(GameOver::createScene());
}