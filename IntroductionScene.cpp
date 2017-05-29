﻿#pragma execution_character_set("utf-8")
#include "IntroductionScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

Scene* Introduction::creatScene()
{
	auto scene = Scene::create();
	auto layer = Introduction::create();
	scene->addChild(layer);
	return scene;
}

bool Introduction::init()
{
	if (!Layer::init())
		return false;
	auto directer = Director::getInstance();
	auto visibleSize = directer->getVisibleSize();
	auto origin = directer->getVisibleOrigin();

#pragma region テキストウィンドウの設定
	auto textWindow = Sprite::create("textWindow.png");
	textWindow->setContentSize((Size)Vec2(visibleSize.width + origin.x, visibleSize.height / 5 + origin.y));
	textWindow->setPosition(visibleSize.width / 2 + origin.x,
		textWindow->getContentSize().height/2);
	this->addChild(textWindow);
#pragma endregion

	return true;
}