#pragma execution_character_set("utf-8")
#include "Credit.h"
#include "CharaResouse.h"
#include "Title.h"
#include "SimpleAudioEngine.h"
#include "FileReadClass.h"

using namespace CocosDenshion;
USING_NS_CC;

Label* setCredit(ValueMap valueMap, std::string columnName);

#pragma region 定数宣言
const int Credit::NUM_OF_PAINTERS = 3;
const int Credit::NUM_OF_VOICE_ACTERS = 2;
const int Credit::NUM_OF_COMPOSERS = 1;
#pragma endregion

Scene* Credit::createScene()
{
	auto scene = Scene::create();
	auto layer = Credit::create();
	scene->addChild(layer);
	return scene;
}

bool Credit::init()
{
	if (!Layer::init())
		return false;

#pragma region 変数宣言
	auto directer = Director::getInstance();
	auto visibleSize = directer->getVisibleSize();
	auto origin = directer->getVisibleOrigin();
#pragma endregion

#pragma region SE用意
	SimpleAudioEngine::getInstance()->setEffectsVolume(0.5f);
	SimpleAudioEngine::getInstance()->preloadEffect(START_VOICE);
#pragma endregion

#pragma region 背景設定
	auto backGround = Sprite::create(F_IMAGE + BACK_GROUND);
	backGround->setContentSize(directer->getVisibleSize());
	backGround->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(backGround, 1);
#pragma endregion

#pragma region 背景を暗転させる
	auto blackEffect = Sprite::create();
	blackEffect->setColor(Color3B::BLACK);
	blackEffect->setOpacity(128);
	blackEffect->setTextureRect(backGround->getBoundingBox());
	blackEffect->setPosition(backGround->getPosition());
	this->addChild(blackEffect, 2);
#pragma endregion

#pragma region 画面名表記
	auto creditLabel = Label::createWithTTF(CREDIT, F_FONTS + JPN_FONTS, 64);
	creditLabel->setPosition(origin.x + visibleSize.width / 2, origin.y + (4 * visibleSize.height) / 5);
	this->addChild(creditLabel, 3);
#pragma endregion

#pragma region 使用素材製作者表記

#pragma region イラストレーター

	auto painters = Label::createWithTTF(PAINTERS, F_FONTS + JPN_FONTS, Parameter::SMALL);
	painters->setPosition(origin.x + visibleSize.width / 6, origin.y + (3 * visibleSize.height) / 5);
	Label* painter[NUM_OF_PAINTERS];
	FileRead fileRead;
	auto creaditValues = fileRead.readCSV(CREDIT_LIST);
	for (int i = 0; i < NUM_OF_PAINTERS; ++i)
	{
		auto creditMap = creaditValues.at(i).asValueMap();
		painter[i] = setCredit(creditMap, PAINTER_KEY);
		painter[i]->setPosition(30, -30*(i+1));
		painter[i]->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		painters->addChild(painter[i]);
	}
	this->addChild(painters, 3);

#pragma endregion

#pragma region コンポーサー
	auto composers = Label::createWithTTF(COMPOSERS, F_FONTS + JPN_FONTS, Parameter::SMALL);
	composers->setPosition(origin.x + visibleSize.width / 2.5, origin.y + (3 * visibleSize.height) / 5);
	Label* composer[NUM_OF_COMPOSERS];
	for (int i = 0; i < NUM_OF_COMPOSERS; ++i)
	{
		auto creditMap = creaditValues.at(i).asValueMap();
		composer[i] = setCredit(creditMap,COMPOSER_KEY);
		composer[i]->setPosition(30, -30 * (i + 1));
		composer[i]->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		composers->addChild(composer[i]);
	}
	this->addChild(composers, 3);
#pragma endregion

#pragma region ボイスアクター
	auto voiceActors = Label::createWithTTF(VOICE_ACTERS, F_FONTS + JPN_FONTS, Parameter::SMALL);
	voiceActors->setPosition(origin.x + visibleSize.width - voiceActors->getContentSize().width,
		origin.y + (3 * visibleSize.height) / 5);
	Label* voiceActor[NUM_OF_VOICE_ACTERS];
	for (int i = 0; i < NUM_OF_VOICE_ACTERS; ++i)
	{
		auto creditMap = creaditValues.at(i).asValueMap();
		voiceActor[i] = setCredit(creditMap,VOICE_ACTER_KEY);
		voiceActor[i]->setPosition(30, -30 * (i + 1));
		voiceActor[i]->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		voiceActors->addChild(voiceActor[i]);
	}
	this->addChild(voiceActors, 3);
#pragma endregion

#pragma endregion

#pragma region クリックリスナー
	auto listner = EventListenerTouchOneByOne::create();
	listner->onTouchBegan = CC_CALLBACK_2(Credit::onTouchBegan, this);
	directer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listner, this);
#pragma endregion

	return true;

}

Label* setCredit(ValueMap valueMap,std::string columnName)
{
	auto label = Label::createWithTTF(PILLS + valueMap.at(columnName).asString(), F_FONTS + JPN_FONTS, Parameter::VERY_SMALL);
	return label;
}

bool Credit::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event*event)
{
	Director::getInstance()->replaceScene(TransitionFade::create(2.0f, Title::createScene(), Color3B::WHITE));
	return true;
}