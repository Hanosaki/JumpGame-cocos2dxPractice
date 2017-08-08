#pragma execution_character_set("utf-8")
#include "GameScene.h"
#include "GameoverScene.h"
#include "CharaResouse.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

void nextScene();

const int ANIMATION_MAX_NUM = 17;
const int MAX_LIFE = 3;

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
	scoreLabel = Label::createWithTTF(SCORE_TEXT + StringUtils::toString(score), FONTS+ENG_FONTS, 24);
	scoreLabel->setPosition(Vec2(visibleSize.width / 2 +origin.x , visibleSize.height + origin.y - scoreLabel->getContentSize().height));
	this->addChild(scoreLabel,1);
#pragma endregion

#pragma region 背景初期設定
	auto backGround = Sprite::create(IMAGE+BACK_GROUND);
	backGround->setContentSize((Size)Vec2(visibleSize.width + 0.1*visibleSize.width, visibleSize.height));
	backGround->setPosition(visibleSize.width/2 + origin.x, visibleSize.height / 2 + origin.y);
	backGround->setTag(51);
	this->addChild(backGround);

	auto backGround2 = Sprite::create(IMAGE+BACK_GROUND);
	backGround2->setContentSize(backGround->getContentSize());
	backGround2->setPosition(outOfWindowBGPos);
	backGround2->setTag(52);
	this->addChild(backGround2);
#pragma endregion

#pragma region 主人公(animation)スプライトの初期設定
	auto mainCharacter = Sprite::create(ANIMATION+RUN+ANIMATION_CHARACTER_DEFAULT);
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
	auto characterImage = Sprite::create(MAIN_CHARACTER+ IMAGE + CHARACTER_IMAGE_NORMAL);
	characterImage->setScale((visibleSize.height + origin.y) / (characterImage->getContentSize().height));
	characterImage->setPosition(visibleSize.width + origin.x - (characterImage->getContentSize().width / 4 * characterImage->getScale())
						,visibleSize.height/2+origin.y) ;
	characterImage->setOpacity(200);
	characterImage->setTag(2);
	this->addChild(characterImage,3);
#pragma endregion

#pragma region 体力ゲージの初期設定
	Sprite* life[MAX_LIFE];
	for (int i = 0; i < MAX_LIFE; ++i)
	{
		life[i] = Sprite::create(IMAGE + LIFE_ICON);
		life[i]->setScale(life[i]->getContentSize().height / (visibleSize.height + origin.y));
		life[i]->setPosition(visibleSize.width/2 + origin.x - (life[i]->getContentSize().width*life[i]->getScale()*(i-1)),
			visibleSize.height + origin.y - (life[i]->getContentSize().height*life[i]->getScale()));
		life[i]->setTag(20+i);
		this->addChild(life[i],3);
	}

#pragma endregion

#pragma region 敵の初期設定
	auto enemy = Sprite::create(RIVAL + ENEMY_IMAGE);
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
		CallFunc::create([this](){this->scheduleUpdate();}), NULL));
#pragma endregion

	return true;
}

bool Game::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
#pragma region ジャンプ処理
	if (!endFlag)
	{
		auto mainCharacter = (Sprite*)this->getChildByTag(1);
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto origin = Director::getInstance()->getVisibleOrigin();
		auto maxPoint = Point(defoultPos.x, 
											origin.y + visibleSize.height - mainCharacter->getContentSize().height*mainCharacter->getScale());
		/*アクションの作成*/
		auto moveUp = MoveTo::create(0.73f, maxPoint);
		auto moveDown = MoveTo::create(0.73f, defoultPos);
		/*アニメーション状態の確認*/
		if (mainCharacter->getPosition().equals(defoultPos)){
			mainCharacter->stopActionByTag(101);
			mainCharacter->setTexture(MAIN_CHARACTER + CHARACTER_JUMP);
			/*シークエンス作成*/
			auto sequence = Sequence::create(moveUp, moveDown, CallFunc::create([this]{ setCharacterDefault(); }), NULL);
			//アニメーション開始
			mainCharacter->runAction(sequence);
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

#pragma region エネミーの行動
	auto enemy = this->getChildByTag(31);
	auto enemyPos = enemy->getPosition();
	float rand = random(0.5f, 2.0f);
	enemyPos -= 2 * moveVec*rand;
	if (enemyPos.x + enemy->getContentSize().width < 0){
		enemyPos = Vec2(enemyDefaultPos);
		++score;
		hitOnlyOne = false;
		scoreLabel->setString(SCORE_TEXT + StringUtils::toString(score));
	}
	enemy->setPosition(enemyPos);
#pragma endregion

#pragma region 接触判定
	auto mainCharacter = (Sprite*)this->getChildByTag(1);
	auto hitDetermination = (Sprite*)this->getChildByTag(11);

	hitDetermination->setPositionY(mainCharacter->getPositionY()
		+ mainCharacter->getContentSize().height / 3
		* mainCharacter->getScale());

	auto rectMainCharactor = hitDetermination->getBoundingBox();
	auto rectEnemy = enemy->getBoundingBox();

	if (rectMainCharactor.intersectsRect(rectEnemy) && !hitOnlyOne){
		SimpleAudioEngine::getInstance()->playEffect(DAMEGE_VOICE);
		auto characterImage = (Sprite*)this->getChildByTag(2);
		mainCharacter->stopActionByTag(101);
		mainCharacter->setTexture(MAIN_CHARACTER + CHARACTER_DAMAGE);
		characterImage->setTexture(MAIN_CHARACTER + IMAGE + CHARACTER_IMAGE_DAMEGE);
		this->getChildByTag(20 + hitCounter)->setVisible(false);
		++hitCounter;
		if (hitCounter >= MAX_LIFE)
		{
			auto gameoverLabel = Label::createWithTTF(GAME_OVER_TEXT, FONTS + JPN_FONTS, 24);
			gameoverLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2);
			gameoverLabel->setScale(3.0f);
			SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			this->addChild(gameoverLabel);
			this->unscheduleUpdate();
			mainCharacter->stopAllActions();
			UserDefault::getInstance()->setIntegerForKey(SCORE_KEY, score);
			UserDefault::getInstance()->flush();
			endFlag = true;
		}
		hitOnlyOne = true;
	}
#pragma endregion

#pragma region 主人公初期化
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
	auto animation = Animation::create();
	for (int i = 0; i < ANIMATION_MAX_NUM; ++i)
		animation->addSpriteFrameWithFile(ANIMATION + RUN + StringUtils::toString(i) + ".png");
	animation->setDelayPerUnit(0.04f);
	animation->setRestoreOriginalFrame(true);
	auto runAnime = Animate::create(animation);
	auto runAnimation = RepeatForever::create(runAnime);
	runAnimation->setTag(101);
	mainCharacter->runAction(runAnimation);
	try{
		if (auto characterImage = (Sprite*)getChildByTag(2))
			characterImage->setTexture(MAIN_CHARACTER + IMAGE + CHARACTER_IMAGE_NORMAL);
	}
	catch (char* messeage)
	{
		puts(messeage);
	}
}
#pragma endregion

void nextScene()
{
	Director::getInstance()->replaceScene(GameOver::creatScene());
}

