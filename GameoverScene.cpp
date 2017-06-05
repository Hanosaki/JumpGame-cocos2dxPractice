#pragma execution_character_set("utf-8")
#include "GameoverScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

Scene* GameOver::creatScene()
{
	auto scene = Scene::create();
	auto layer = GameOver::create();
	scene->addChild(layer);
	return scene;
}

bool GameOver::init()
{
	if (!Layer::init())
		return false;

#pragma region 変数宣言
	auto directer = Director::getInstance();
	auto visibleSize = directer->getVisibleSize();
	auto origin = directer->getVisibleOrigin();
	int score = UserDefault::getInstance()->getIntegerForKey("score", 0);
	int hiScore = UserDefault::getInstance()->getIntegerForKey("hiScore", 0);
#pragma endregion

#pragma region ゲームオーバー表記
	auto gameOverLabel = Label::createWithTTF("こんかいのきろく", JPN_FONTS, 64);
	gameOverLabel->setPosition(origin.x + visibleSize.width / 3, origin.y + (4 * visibleSize.height) / 5);
	this->addChild(gameOverLabel, 4);

	auto scoreLabel = Label::createWithTTF("Score:" + StringUtils::toString(score),
										"fonts/Marker Felt.ttf", 64);
	scoreLabel->setPosition(origin.x + visibleSize.width / 3, origin.y + (3*visibleSize.height / 5));
	this->addChild(scoreLabel, 4);
	Label* hiScoreLabel;
	if (hiScore < score)
	{
		hiScoreLabel = Label::createWithTTF("HIScore:" + StringUtils::toString(score) + "  NEW RECORED!",
			"fonts/Marker Felt.ttf", 64);
		UserDefault::getInstance()->setIntegerForKey("hiScore", score);
	}
	else
		hiScoreLabel = Label::createWithTTF("HIScore:" + StringUtils::toString(hiScore),
		"fonts/Marker Felt.ttf", 64);
	hiScoreLabel->setPosition(origin.x + visibleSize.width / 3, origin.y + (2*visibleSize.height / 5));
	this->addChild(hiScoreLabel,4);
#pragma endregion

#pragma region pushEnd表記
	auto pushText = Label::createWithTTF("push End", "fonts/Marker Felt.ttf", 24);
	pushText->setPosition(origin.x + visibleSize.width / 3, origin.y + visibleSize.height / 8);
	this->addChild(pushText, 4);
	auto fadeOut = FadeTo::create(0.9f, 64);
	auto fadeIn = FadeTo::create(0.9f, 255);
	auto seq = Sequence::create(fadeOut, fadeIn, NULL);
	auto repeat = RepeatForever::create(seq);
	pushText->runAction(repeat);
#pragma endregion

#pragma region 背景宣言
	auto backGround = Sprite::create("bg.png");
	backGround->setContentSize(directer->getVisibleSize());
	backGround->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
	this->addChild(backGround, 1);
#pragma endregion

#pragma region 主人公(立ち絵)の初期設定
	auto mainCharactor = Sprite::create(IMAGE_GAMEOVER);
	mainCharactor->setScale((visibleSize.height + origin.y) / (mainCharactor->getContentSize().height));
	mainCharactor->setPosition(visibleSize.width + origin.x - (mainCharactor->getContentSize().width / 4 * mainCharactor->getScale())
		, visibleSize.height / 2 + origin.y);
	mainCharactor->setOpacity(200);
	mainCharactor->setTag(2);
	this->addChild(mainCharactor, 3);
#pragma endregion

#pragma region クリックリスナー
	auto listner = EventListenerTouchOneByOne::create();
	listner->onTouchBegan = CC_CALLBACK_2(GameOver::onTouchBegan, this);
	directer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listner, this);
#pragma endregion


	return true;
}

bool GameOver::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	ended();
	return true;
}

void GameOver::ended()
{
	Director::getInstance()->end();
}