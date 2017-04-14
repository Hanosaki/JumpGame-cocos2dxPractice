#include "Title.h"
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
#pragma endregion

#pragma region タイトル表記
	Label* titleLabel = Label::createWithTTF("ゆかりさんがぴょんぴょんするげ〜む", "fonts/Marker Felt.ttf", 24);
	titleLabel->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(titleLabel,1);
#pragma endregion

#pragma region 背景宣言
	auto backGround = Sprite::create("bg.png");
	backGround->setContentSize(Director::getInstance()->getVisibleSize());
	backGround->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
	this->addChild(backGround);
#pragma endregion

#pragma region 立ち絵背景の初期設定
	auto whiteBack = Sprite::create("whiteBack.png");
	whiteBack->setContentSize((Size)Vec2(visibleSize.width / 5 + origin.x, visibleSize.height + origin.y));
	whiteBack->setPosition(visibleSize.width + origin.x -
		whiteBack->getContentSize().width / 2, visibleSize.height / 2 + origin.y);
	this->addChild(whiteBack, 2);
#pragma endregion

#pragma region 主人公(立ち絵)の初期設定
	auto yukari2 = Sprite::create("1.png");
	yukari2->setScale((visibleSize.height + origin.y) / (yukari2->getContentSize().height));
	yukari2->setPosition(visibleSize.width + origin.x - (yukari2->getContentSize().width / 4 * yukari2->getScale())
		, visibleSize.height / 2 + origin.y);
	yukari2->setTag(2);
	this->addChild(yukari2, 3);
#pragma endregion

#pragma region クリックリスナー
	auto listner = EventListenerTouchOneByOne::create();
	listner->onTouchBegan = CC_CALLBACK_2(Title::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listner, this);
#pragma endregion

	return true;
}

bool Title::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	return true;
}