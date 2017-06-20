#pragma execution_character_set("utf-8")
#include "GameoverScene.h"
#include "CharaResouse.h"
#include "SimpleAudioEngine.h"
#include "Title.h"

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
	int score = UserDefault::getInstance()->getIntegerForKey(SCORE_KEY, 0);
	int hiScore = UserDefault::getInstance()->getIntegerForKey(HI_SCORE_KEY, 0);
#pragma endregion

#pragma region ゲームオーバー表記
	auto gameOverLabel = Label::createWithTTF(NOW_RESULT_TEXT, JPN_FONTS, 64);
	gameOverLabel->setPosition(origin.x + visibleSize.width / 3, origin.y + (4 * visibleSize.height) / 5);
	this->addChild(gameOverLabel, 4);

	auto scoreLabel = Label::createWithTTF(SCORE_TEXT + StringUtils::toString(score),ENG_FONTS, 64);
	scoreLabel->setPosition(origin.x + visibleSize.width / 3, origin.y + (3*visibleSize.height / 5));
	this->addChild(scoreLabel, 4);
	Label* hiScoreLabel;
	if (hiScore < score)
	{
		hiScoreLabel = Label::createWithTTF(HI_SCORE_TEXT + StringUtils::toString(score) + NEW_RECORED_TEXT,
			ENG_FONTS, 64);
		UserDefault::getInstance()->setIntegerForKey(HI_SCORE_KEY, score);
	}
	else
		hiScoreLabel = Label::createWithTTF(HI_SCORE_TEXT + StringUtils::toString(hiScore),
		ENG_FONTS, 64);
	hiScoreLabel->setPosition(origin.x + visibleSize.width / 3, origin.y + (2*visibleSize.height / 5));
	this->addChild(hiScoreLabel,4);
#pragma endregion

#pragma region pushEnd表記
	auto pushText = Label::createWithTTF(RETRUN_TITLE_TEXT, ENG_FONTS, 24);
	pushText->setPosition(origin.x + visibleSize.width / 3, origin.y + visibleSize.height / 8);
	this->addChild(pushText, 4);
	auto fadeOut = FadeTo::create(0.9f, 64);
	auto fadeIn = FadeTo::create(0.9f, 255);
	auto seq = Sequence::create(fadeOut, fadeIn, NULL);
	auto repeat = RepeatForever::create(seq);
	pushText->runAction(repeat);
#pragma endregion

#pragma region 背景宣言
	auto backGround = Sprite::create(BACK_GROUND);
	backGround->setContentSize(directer->getVisibleSize());
	backGround->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
	this->addChild(backGround, 1);
#pragma endregion

#pragma region 主人公(立ち絵)の初期設定
	auto charactorImage = Sprite::create(CHARACTER_IMAGE_GAMEOVER);
	charactorImage->setScale((visibleSize.height + origin.y) / (charactorImage->getContentSize().height));
	charactorImage->setPosition(visibleSize.width + origin.x - (charactorImage->getContentSize().width / 4 * charactorImage->getScale())
		, visibleSize.height / 2 + origin.y);
	charactorImage->setOpacity(200);
	charactorImage->setTag(2);
	this->addChild(charactorImage, 3);
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
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Title::creatScene(), Color3B::WHITE));
	return true;
}