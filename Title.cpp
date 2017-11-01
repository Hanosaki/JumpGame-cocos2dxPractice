﻿#pragma execution_character_set("utf-8")
#include "Title.h"
#include "Credit.h"
#include "CharaResouse.h"
#include "GenericFunction.h"
#include "SimpleAudioEngine.h"
#include "IntroductionScene.h"
#include "HowToScene.h"

using namespace CocosDenshion;
USING_NS_CC;

Scene* Title::createScene()
{
	auto scene = Scene::create();
	auto layer = Title::create();
	scene->addChild(layer);
	return scene;
}

bool Title::init()
{
	if (!Layer::init())
		return false;

#pragma region 変数宣言
	auto directer = Director::getInstance();
	auto visibleSize = directer->getVisibleSize();
	auto origin = directer->getVisibleOrigin();
	const auto BUTTON_SIZE = Size(visibleSize.width + origin.x, visibleSize.height / 10 + origin.y);
	GenericFunc genericFunc;
#pragma endregion

	//BGM設定
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.4f);
	// SE設定
	SimpleAudioEngine::getInstance()->setEffectsVolume(0.8f);

#pragma region タイトル表記
	auto titleLabel = Label::createWithTTF(TITLE_TEXT, F_FONTS + JPN_FONTS, 64);
	titleLabel->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - titleLabel->getContentSize().height*2);
	this->addChild(titleLabel, 4);
#pragma endregion

#pragma region 背景設定
	auto backGround = Sprite::create(F_IMAGE + F_UI + BACK_GROUND);
	backGround->setContentSize(directer->getVisibleSize());
	backGround->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(backGround, 1);
#pragma endregion

#pragma region 主人公(立ち絵)の初期設定
	auto characterImage = genericFunc.setMainCharacterImage(visibleSize, origin, F_IMAGE + F_MAIN_CHARACTER + SMILE);
	characterImage->setTag(2);
	this->addChild(characterImage, 3);
#pragma endregion

#pragma region スタートボタン配置
	auto startButton = Sprite::create(F_IMAGE + F_UI + START_BUTTON);
	startButton->setContentSize(BUTTON_SIZE);

	auto selectedStartButton = Sprite::create(F_IMAGE + F_UI + START_BUTTON);
	selectedStartButton->setOpacity(128);
	selectedStartButton->setContentSize(BUTTON_SIZE);

	auto startItem = MenuItemSprite::create(startButton, selectedStartButton, CC_CALLBACK_1(Title::callOPScene, this));
	auto startMenu = Menu::create(startItem, NULL);
	startMenu->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	startMenu->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height/2.4f - BUTTON_SIZE.height));

	this->addChild(startMenu, 2);
#pragma endregion

#pragma region 操作方法説明画面遷移ボタン配置
	auto howToButton = Sprite::create(F_IMAGE + F_UI + HOW_TO_BUTTON);
	howToButton->setContentSize(BUTTON_SIZE);

	auto selectedHowToButton = Sprite::create(F_IMAGE + F_UI + HOW_TO_BUTTON);
	selectedHowToButton->setOpacity(128);
	selectedHowToButton->setContentSize(BUTTON_SIZE);

	auto howToItem = MenuItemSprite::create(howToButton, selectedHowToButton, CC_CALLBACK_1(Title::callHowToScene, this));
	auto howToMenu = Menu::create(howToItem, NULL);
	howToMenu->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	howToMenu->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 3 - BUTTON_SIZE.height));

	this->addChild(howToMenu, 2);
#pragma endregion

#pragma region クレジットボタン配置
	auto creditButton = Sprite::create(F_IMAGE + F_UI + CREDIT_IMAGE);
	creditButton->setContentSize(BUTTON_SIZE);

	auto selectedCreditButton = Sprite::create(F_IMAGE + F_UI + CREDIT_IMAGE);
	selectedCreditButton->setOpacity(128);
	selectedCreditButton->setContentSize(BUTTON_SIZE);

	auto creditItem = MenuItemSprite::create(creditButton, selectedCreditButton, CC_CALLBACK_1(Title::callCreditScene, this));
	auto creditMenu = Menu::create(creditItem, NULL);
	creditMenu->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	creditMenu->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 4 - BUTTON_SIZE.height));

	this->addChild(creditMenu, 2);
#pragma endregion

#pragma region 終了ボタン配置
	auto endButton = Sprite::create(F_IMAGE + F_UI + END_BUTTON);
	endButton->setContentSize(BUTTON_SIZE);

	auto selectedEndButton = Sprite::create(F_IMAGE + F_UI + END_BUTTON);
	selectedEndButton->setOpacity(128);
	selectedEndButton->setContentSize(BUTTON_SIZE);

	auto endItem = MenuItemSprite::create(endButton, selectedEndButton, CC_CALLBACK_1(Title::closeGame, this));
	auto endMenu = Menu::create(endItem, NULL);
	endMenu->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	endMenu->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 5 - BUTTON_SIZE.height*1.5));

	this->addChild(endMenu, 2);
#pragma endregion

	SimpleAudioEngine::getInstance()->playBackgroundMusic(TITLE_BGM, true);

	return true;
}

void Title::characterImageChange()
{
	auto characterImage = (Sprite*)this->getChildByTag(2);
	characterImage->setTexture(F_IMAGE + F_MAIN_CHARACTER + LAUGH);
}

void Title::callOPScene(Ref* Sender)
{
	SimpleAudioEngine::getInstance()->playEffect(START_VOICE);
	characterImageChange();
	Director::getInstance()->replaceScene(TransitionFade::create(3.0f, Introduction::createScene(), Color3B::BLACK));
}

void Title::callCreditScene(Ref* Sender)
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->playEffect(BUTTON_SE);
	characterImageChange();
	Director::getInstance()->replaceScene(TransitionFade::create(2.0f, Credit::createScene(), Color3B::WHITE));
}

void Title::callHowToScene(Ref* sender)
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->playEffect(BUTTON_SE);
	characterImageChange();
	Director::getInstance()->replaceScene(TransitionFade::create(2.0f, HowTo::createScene(), Color3B::WHITE));
}

void Title::closeGame(Ref* sender)
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	Director::getInstance()->purgeCachedData();//キャッシュ開放
	Director::getInstance()->end();
}