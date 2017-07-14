#pragma execution_character_set("utf-8")
#include "IntroductionScene.h"
#include "SimpleAudioEngine.h"
#include "CharaResouse.h"

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

	/*画像配置処理*/

#pragma region 背景設定
	auto backGround = Sprite::create(OP_BACK_GROUND);
	backGround->setPosition(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);
	backGround->setContentSize(Size(visibleSize.width + origin.x, visibleSize.height + origin.y));
	this->addChild(backGround,1);
#pragma endregion

#pragma region 主人公立ち絵
	auto characterImage = Sprite::create(CHARACTER_IMAGE_NORMAL);
	characterImage->setScale((visibleSize.height + origin.y) / (characterImage->getContentSize().height));
	characterImage->setPosition(visibleSize.width / 6 + origin.x, Vec2::ZERO.y);
	characterImage->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	characterImage->setFlippedX(true);
	this->addChild(characterImage, 2);
#pragma endregion

#pragma region ライバル立ち絵
	auto rivalImage = Sprite::create(RIVAL_IMAGE);
	rivalImage->setScale(characterImage->getScale());
	rivalImage->setPosition(visibleSize.width + origin.x 
		- rivalImage->getContentSize().width / 2 * rivalImage->getScale(),
		0);
	rivalImage->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	this->addChild(rivalImage, 2);
#pragma endregion

#pragma region テキストウィンドウの設定
	auto textWindow = Sprite::create(TEXT_WINDOW);
	textWindow->setContentSize(Size(visibleSize.width + origin.x, visibleSize.height/5 + origin.y));
	textWindow->setPosition(visibleSize.width / 2 + origin.x,
		textWindow->getContentSize().height/2);
	this->addChild(textWindow,3);
#pragma endregion

	/*以下，表示テキスト処理*/

#pragma region 名前表示用ラベルの設定
	auto characterNameLabel = Label::createWithTTF("ゆかり",JPN_FONTS,32);
	characterNameLabel->setPosition(Vec2(characterNameLabel->getContentSize().width / 2,
		textWindow->getContentSize().height - characterNameLabel->getContentSize().height/2));
	characterNameLabel->setColor(Color3B::BLACK);
	textWindow->addChild(characterNameLabel,1);
#pragma endregion

#pragma region セリフ用ラベルの設定
	auto characterSpeechLabel = Label::createWithTTF("ダミーワード",JPN_FONTS,16);
	
	characterSpeechLabel->setPosition(characterNameLabel->getPositionX(),
		characterNameLabel->getPositionY() 
		- (characterSpeechLabel->getContentSize().height / 2 
		+ characterNameLabel->getContentSize().height/2));
	
	characterSpeechLabel->setColor(Color3B::BLACK);
	textWindow->addChild(characterSpeechLabel,1);
#pragma endregion

	return true;
}
