﻿#pragma execution_character_set("utf-8")
#include "Splash.h"
#include "SimpleAudioEngine.h"
#include "ResouceLoadScene.h"
#include "CharaResouse.h"
#include "Converter.h"

using namespace CocosDenshion;
USING_NS_CC;

Scene* Splash::createScene()
{
	auto scene = Scene::create();
	auto layer = Splash::create();
	scene->addChild(layer);
	return scene;
}

bool Splash::init()
{
	if (!Layer::init())
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	Converter converter;
	char* seName;

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)//Windows用SEロード
	
	seName = converter.replaceDATtoMP3(F_SE + LOGO_SE);

#elif(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)//Android用SEロード処理

	seName = converter.replaceString2Char(F_SE + LOGO_SE + TYPE_MP3);

#endif
	
	SimpleAudioEngine::getInstance()->preloadEffect(seName);

#pragma region ロゴ表示
	auto logo = Label::createWithTTF(LOGO, F_FONTS + JPN_FONTS, 64);
	logo->setTextColor(Color4B::WHITE);
	logo->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	logo->setOpacity(0);
	this->addChild(logo);
#pragma endregion

#pragma region ロゴアニメーション

	auto logoAction = Sequence::create(FadeIn::create(1.0f), DelayTime::create(2.0f), FadeOut::create(1.0f), NULL);
	logo->runAction(logoAction);

#pragma endregion

	SimpleAudioEngine::getInstance()->playEffect(seName);

	this->scheduleOnce(schedule_selector(Splash::callLoadScene), 5.0f);

#pragma region クリック処理の初期設定
	auto listner = EventListenerTouchOneByOne::create();
	listner->onTouchBegan = CC_CALLBACK_2(Splash::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listner, this);
#pragma endregion

	return true;

}

bool Splash::onTouchBegan(cocos2d::Touch* touch,cocos2d::Event* event)
{
	this->unschedule(schedule_selector(Splash::callLoadScene));
	SimpleAudioEngine::getInstance()->pauseAllEffects();
	Director::getInstance()->replaceScene(ResouceLoad::createScene());
	return true;
}

void Splash::callLoadScene(float dt)
{
	Director::getInstance()->replaceScene(ResouceLoad::createScene());
}
