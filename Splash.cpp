#pragma execution_character_set("utf-8")
#include "Splash.h"
#include "Title.h"
#include "CharaResouse.h"
#include "Converter.h"
#include "FileReadClass.h"
#include "MenuWindow.h"
#include "createLabel.h"
#include "sound.h"

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

	try{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto origin = Director::getInstance()->getVisibleOrigin();
		auto winCenter = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

		auto sound = new Sound(SE_POINT_CSV);

		//ロゴ表示(ラベル生成用クラスを作成する)
		int logoTag = 1;
		CreateLabel::setLabel(LOGO,F_FONTS+JPN_FONTS,64,Color4B::WHITE,winCenter,logoTag,this);

#pragma region ロゴアニメーション

		auto logo = (Label*)this->getChildByTag(logoTag);
		auto logoAction = Sequence::create(FadeIn::create(1.0f), DelayTime::create(2.0f), FadeOut::create(1.0f), NULL);
		logo->runAction(logoAction);

#pragma endregion

		sound->playSE("LOGO", 0.3f);
		this->scheduleOnce(schedule_selector(Splash::callLoadScene), 5.0f);

#pragma region クリック処理の初期設定
		auto listner = EventListenerTouchOneByOne::create();
		listner->onTouchBegan = CC_CALLBACK_2(Splash::onTouchBegan, this);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listner, this);
#pragma endregion

	}
	catch (char* message)
	{
		auto mw = new MenuWindow();
		mw->crashBox(message, this);
	}

	return true;

}

bool Splash::onTouchBegan(cocos2d::Touch* touch,cocos2d::Event* event)
{
	Sound::stopSound();
	this->unscheduleAllCallbacks();//タイマー設定されたスケジュールの解除
	Director::getInstance()->replaceScene(Title::createScene());
	return true;
}

void Splash::callLoadScene(float dt)
{
	Director::getInstance()->replaceScene(Title::createScene());
}

