#pragma execution_character_set("utf-8")
#include "GameoverScene.h"
#include "CharaResouse.h"
#include "GenericFunction.h"
#include "SimpleAudioEngine.h"
#include "Title.h"
#include "Converter.h"

using namespace CocosDenshion;
USING_NS_CC;

Scene* GameOver::createScene()
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

	Converter converter;
	char* seName;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	 seName = converter.replaceDATtoMP3(F_SE + GAMEOVER_SE);
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	 seName = converter.replaceString2Char(F_SE + GAMEOVER_SE + TYPE_MP3);
#endif
	SimpleAudioEngine::getInstance()->preloadEffect(seName);

#pragma region 変数宣言
	auto directer = Director::getInstance();
	auto visibleSize = directer->getVisibleSize();
	auto origin = directer->getVisibleOrigin();
	int score = UserDefault::getInstance()->getIntegerForKey(SCORE_KEY, 0);
	int hiScore = UserDefault::getInstance()->getIntegerForKey(HI_SCORE_KEY, 0);
#pragma endregion

#pragma region ゲームオーバー表記
	auto gameOverLabel = Label::createWithTTF(NOW_RESULT_TEXT, F_FONTS + JPN_FONTS, Parameter::LARGE);
	gameOverLabel->setPosition(origin.x + visibleSize.width / 2, origin.y + (4 * visibleSize.height) / 5);
	this->addChild(gameOverLabel, 4);

	auto scoreLabel = Label::createWithTTF(SCORE_TEXT + StringUtils::toString(score), F_FONTS + ENG_FONTS, Parameter::LARGE);
	scoreLabel->setPosition(origin.x + visibleSize.width / 2, origin.y + (3 * visibleSize.height / 5));
	this->addChild(scoreLabel, 4);

	Label* hiScoreLabel;
	if (hiScore < score)
	{
		hiScoreLabel = Label::createWithTTF(HI_SCORE_TEXT + StringUtils::toString(score) + NEW_RECORED_TEXT,
			F_FONTS + ENG_FONTS, Parameter::LARGE);
		UserDefault::getInstance()->setIntegerForKey(HI_SCORE_KEY, score);
	}
	else
		hiScoreLabel = Label::createWithTTF(HI_SCORE_TEXT + StringUtils::toString(hiScore),
		F_FONTS + ENG_FONTS, Parameter::LARGE);
	hiScoreLabel->setPosition(origin.x + visibleSize.width / 2, origin.y + (2 * visibleSize.height / 5));
	this->addChild(hiScoreLabel, 4);
#pragma endregion

#pragma region pushEnd表記
	auto pushText = Label::createWithTTF(RETF_RUN_TITLE_TEXT, F_FONTS + ENG_FONTS, Parameter::VERY_SMALL);
	pushText->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 8);
	this->addChild(pushText, 4);

	auto fadeOut = FadeTo::create(0.9f, 64);
	auto fadeIn = FadeTo::create(0.9f, 255);
	auto seq = Sequence::create(fadeOut, fadeIn, NULL);
	auto repeat = RepeatForever::create(seq);
	pushText->runAction(repeat);
#pragma endregion

#pragma region 背景宣言
	auto backGround = Sprite::create(F_IMAGE + F_UI + BACK_GROUND);
	backGround->setContentSize(directer->getVisibleSize());
	backGround->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(backGround, 1);
#pragma endregion

#pragma region 主人公(立ち絵)の初期設定
	GenericFunc genericFunc;
	auto charactorImage = genericFunc.setMainCharacterImage(visibleSize, origin, F_IMAGE + F_MAIN_CHARACTER + SAD);
	charactorImage->setTag(2);
	this->addChild(charactorImage, 3);
#pragma endregion

#pragma region クリックリスナー
	auto listner = EventListenerTouchOneByOne::create();
	listner->onTouchBegan = CC_CALLBACK_2(GameOver::onTouchBegan, this);
	directer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listner, this);
#pragma endregion

	SimpleAudioEngine::getInstance()->playEffect(seName);

	return true;
}

bool GameOver::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	SimpleAudioEngine::getInstance()->stopAllEffects();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Title::createScene(), Color3B::WHITE));
	return true;
}