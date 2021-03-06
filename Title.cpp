﻿#pragma execution_character_set("utf-8")
#include "Title.h"
#include "Credit.h"
#include "GameScene.h"
#include "CharaResouse.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

Scene* Title::creatScene()
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
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	const auto BUTTON_SIZE = Size(visibleSize.width + origin.x, visibleSize.height / 10 + origin.y);
#pragma endregion

#pragma region SE用意
	SimpleAudioEngine::getInstance()->setEffectsVolume(0.5f);
	SimpleAudioEngine::getInstance()->preloadEffect(START_VOICE);
#pragma endregion

#pragma region タイトル表記
	auto titleLabel = Label::createWithTTF(TITLE_TEXT, JPN_FONTS, 64);
	titleLabel->setPosition(origin.x + visibleSize.width / 2, origin.y + (4 * visibleSize.height) / 5);
	this->addChild(titleLabel,4);
#pragma endregion

#pragma region 背景設定
	auto backGround = Sprite::create(BACK_GROUND);
	backGround->setContentSize(Director::getInstance()->getVisibleSize());
	backGround->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
	this->addChild(backGround,1);
#pragma endregion

#pragma region 主人公(立ち絵)の初期設定
	auto characterImage = Sprite::create(CHARACTER_IMAGE_NORMAL);
	characterImage->setScale((visibleSize.height + origin.y) / (characterImage->getContentSize().height));
	characterImage->setPosition(visibleSize.width + origin.x - (characterImage->getContentSize().width / 4 * characterImage->getScale())
		, visibleSize.height / 2 + origin.y);
	characterImage->setOpacity(200);
	characterImage->setTag(2);
	this->addChild(characterImage, 3);
#pragma endregion

#pragma region スタートボタン配置
	auto startButton = Sprite::create(START_IMAGE);
	startButton->setContentSize(BUTTON_SIZE);
	
	auto selectedStartButton = Sprite::create(START_IMAGE);
	selectedStartButton->setOpacity(128);
	selectedStartButton->setContentSize(BUTTON_SIZE);

	auto startItem = MenuItemSprite::create(startButton, selectedStartButton, CC_CALLBACK_1(Title::callGameScene, this));
	auto startMenu = Menu::create(startItem, NULL);
	startMenu->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	startMenu->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 3 - BUTTON_SIZE.height));
	
	this->addChild(startMenu,2);
#pragma endregion

#pragma region クレジットボタン配置
	auto creditButton = Sprite::create(CREDIT_IMAGE);
	creditButton->setContentSize(BUTTON_SIZE);

	auto selectedCreditButton = Sprite::create(CREDIT_IMAGE);
	selectedCreditButton->setOpacity(128);
	selectedCreditButton->setContentSize(BUTTON_SIZE);
	
	auto creditItem = MenuItemSprite::create(creditButton, selectedCreditButton, CC_CALLBACK_1(Title::callCreditScene, this));
	auto creditMenu = Menu::create(creditItem, NULL);
	creditMenu->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	creditMenu->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 4 - BUTTON_SIZE.height));
	
	this->addChild(creditMenu, 2);
#pragma endregion

#pragma region 終了ボタン配置
	auto endButton = Sprite::create(END_IMAGE);
	endButton->setContentSize(BUTTON_SIZE);
	
	auto selectedEndButton = Sprite::create(END_IMAGE);
	selectedEndButton->setOpacity(128);
	selectedEndButton->setContentSize(BUTTON_SIZE);
	
	auto endItem = MenuItemSprite::create(endButton, selectedEndButton, CC_CALLBACK_1(Title::closeGame, this));
	auto endMenu = Menu::create(endItem, NULL);
	endMenu->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	endMenu->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 5 - BUTTON_SIZE.height*1.5));
	
	this->addChild(endMenu, 2);
#pragma endregion

	return true;
}

void Title::characterImageChange()
{
	auto characterImage = (Sprite*)this->getChildByTag(2);
	characterImage->setTexture(CHARACTER_IMAGE_SMAILE);
}

void Title::callGameScene(Ref* Sender)
{
	characterImageChange();
	SimpleAudioEngine::getInstance()->playEffect(START_VOICE);
	Director::getInstance()->replaceScene(TransitionFade::create(2.0f, Game::creatScene(), Color3B::WHITE));
}

void Title::callCreditScene(Ref* Sender)
{
	characterImageChange();
	Director::getInstance()->replaceScene(TransitionFade::create(2.0f, Credit::creatScene(), Color3B::WHITE));
}

void Title::closeGame(Ref* sender)
{
	Director::getInstance()->end();
}