#pragma execution_character_set("utf-8")
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
	auto seName = converter.replaceDATtoMP3(F_SE + LOGO_SE);
	SimpleAudioEngine::getInstance()->preloadEffect(seName);

	auto logo = Label::createWithTTF(LOGO, F_FONTS + JPN_FONTS, 64);
	logo->setTextColor(Color4B::WHITE);
	logo->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	logo->setOpacity(0);
	this->addChild(logo);

	auto logoAction = Sequence::create(FadeIn::create(1.0f), DelayTime::create(2.0f), FadeOut::create(1.0f), NULL);
	logo->runAction(logoAction);

	SimpleAudioEngine::getInstance()->playEffect(seName);

	this->scheduleOnce(schedule_selector(Splash::callLoadScene), 5.0f);

	return true;

}

void Splash::callLoadScene(float dt)
{
	Director::getInstance()->replaceScene(ResouceLoad::createScene());
}

