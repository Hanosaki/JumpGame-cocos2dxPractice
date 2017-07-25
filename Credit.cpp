#pragma execution_character_set("utf-8")
#include "Credit.h"
#include "CharaResouse.h"
#include "Title.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

#pragma region 定数宣言
const int NUM_OF_PAINTERS = 3;
const int NUM_OF_VOICE_ACTERS = 2;
#pragma endregion


Scene* Credit::creatScene()
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
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
#pragma endregion

#pragma region SE用意
	SimpleAudioEngine::getInstance()->setEffectsVolume(0.5f);
	SimpleAudioEngine::getInstance()->preloadEffect(START_VOICE);
#pragma endregion

#pragma region 背景設定
	auto backGround = Sprite::create(IMAGE + BACK_GROUND);
	backGround->setContentSize(Director::getInstance()->getVisibleSize());
	backGround->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
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
	auto creditLabel = Label::createWithTTF(CREDIT, FONTS + JPN_FONTS, 64);
	creditLabel->setPosition(origin.x + visibleSize.width / 2, origin.y + (4 * visibleSize.height) / 5);
	this->addChild(creditLabel, 3);
#pragma endregion

#pragma region 使用素材表記

#pragma region イラストレーター

	auto painters = Label::createWithTTF(PAINTERS, FONTS + JPN_FONTS, 36);
	painters->setPosition(origin.x + visibleSize.width / 6, origin.y + (3 * visibleSize.height) / 5);
	Label* painter[NUM_OF_PAINTERS];
	painter[0] = Label::createWithTTF(PAINTER_1, FONTS + JPN_FONTS, 24);
	painter[0]->setPosition(30, -30);
	painter[1] = Label::createWithTTF(PAINTER_2, FONTS + JPN_FONTS, 24);
	painter[1]->setPosition(30, -60);
	painter[2] = Label::createWithTTF(PAINTER_3, FONTS + JPN_FONTS, 24);
	painter[2]->setPosition(30, -90);
	for (int i = 0; i < NUM_OF_PAINTERS; ++i)
	{
		painter[i]->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		painters->addChild(painter[i]);
	}
	this->addChild(painters, 3);

#pragma endregion

#pragma region コンポーサー
	auto composers = Label::createWithTTF(COMPOSERS, FONTS + JPN_FONTS, 36);
	composers->setPosition(origin.x + visibleSize.width / 2.5, origin.y + (3 * visibleSize.height) / 5);
	auto composer = Label::createWithTTF(COMPOSER_1, FONTS + JPN_FONTS, 24);
	composer->setPosition(30, -30);
	composer->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	composers->addChild(composer);
	this->addChild(composers, 3);
#pragma endregion

#pragma region ボイスアクター
	auto voiceActors = Label::createWithTTF(VOICE_ACTERS, FONTS + JPN_FONTS, 36);
	voiceActors->setPosition(origin.x + visibleSize.width - voiceActors->getContentSize().width,
		origin.y + (3 * visibleSize.height) / 5);
	Label* voiceActor[NUM_OF_VOICE_ACTERS];
	voiceActor[0] = Label::createWithTTF(VOICE_ACTER_1, FONTS + JPN_FONTS, 24);
	voiceActor[0]->setPosition(30, -30);
	voiceActor[1] = Label::createWithTTF(VOICE_ACTER_2, FONTS + JPN_FONTS, 24);
	voiceActor[1]->setPosition(30, -60);
	for (int i = 0; i < NUM_OF_VOICE_ACTERS; ++i)
	{
		voiceActor[i]->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		voiceActors->addChild(voiceActor[i]);
	}
	this->addChild(voiceActors, 3);
#pragma endregion

#pragma endregion

#pragma region クリックリスナー
	auto listner = EventListenerTouchOneByOne::create();
	listner->onTouchBegan = CC_CALLBACK_2(Credit::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listner, this);
#pragma endregion

	return true;

}

bool Credit::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event*event)
{
	Director::getInstance()->replaceScene(TransitionFade::create(2.0f, Title::creatScene(), Color3B::WHITE));
	return true;
}