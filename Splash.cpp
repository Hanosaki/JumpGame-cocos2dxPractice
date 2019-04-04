#pragma execution_character_set("utf-8")
#include "Splash.h"
#include "AudioEngine.h"
#include "ResouceLoadScene.h"
#include "CharaResouse.h"
#include "Converter.h"
#include "FileReadClass.h"
#include "MenuWindow.h"
#include "createLabel.h"

USING_NS_CC;
using namespace experimental;

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

		//ロゴ表示(ラベル生成用クラスを作成する)
		CreateLabel::setLabel(LOGO,F_FONTS+JPN_FONTS,64,Color4B::WHITE,winCenter,1,this);

#pragma region ロゴアニメーション

		auto logo = (Label*)this->getChildByTag(1);
		auto logoAction = Sequence::create(FadeIn::create(1.0f), DelayTime::create(2.0f), FadeOut::create(1.0f), NULL);
		logo->runAction(logoAction);

#pragma endregion

		auto seNames = FileRead::sReadFile(SE_POINT_CSV);
		auto seName = seNames["LOGO"];
		AudioEngine::preload(seName);
		AudioEngine::play2d(seName,false,0.3f,nullptr);

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
	this->unschedule(schedule_selector(Splash::callLoadScene));
	AudioEngine::stopAll();
	Director::getInstance()->replaceScene(ResouceLoad::createScene());
	return true;
}

void Splash::callLoadScene(float dt)
{
	Director::getInstance()->replaceScene(ResouceLoad::createScene());
}

