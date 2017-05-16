#pragma execution_character_set("utf-8")
#include "Title.h"
#include "GameScene.h"
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

#pragma region SE用意
	SimpleAudioEngine::getInstance()->setEffectsVolume(0.5f);
	SimpleAudioEngine::getInstance()->preloadEffect("start.mp3");
#pragma endregion

#pragma region タイトル表記
	auto titleLabel = Label::createWithTTF("mainCharactor RUN", "fonts/Marker Felt.ttf", 64);
	titleLabel->setPosition(origin.x + visibleSize.width / 3, origin.y + (4 * visibleSize.height) / 5);
	this->addChild(titleLabel,4);
#pragma endregion

#pragma region pushStart表記
	auto pushText = Label::createWithTTF("push start...","fonts/Marker Felt.ttf",24);
	pushText->setPosition(origin.x + visibleSize.width / 3, origin.y + visibleSize.height / 6);
	this->addChild(pushText, 4);
	/*文字点滅処理*/
	auto action = FadeTo::create(0.9f,64);
	auto action2 = FadeTo::create(0.9f,255);
	auto seq = Sequence::create(action, action2, NULL);
	auto repeat = RepeatForever::create(seq);
	pushText->runAction(repeat);
#pragma endregion

#pragma region 背景宣言
	auto backGround = Sprite::create("bg.png");
	backGround->setContentSize(Director::getInstance()->getVisibleSize());
	backGround->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
	this->addChild(backGround,1);
#pragma endregion

#pragma region 立ち絵背景の初期設定
	auto whiteBack = Sprite::create("whiteBack.png");
	whiteBack->setContentSize((Size)Vec2(visibleSize.width / 5 + origin.x, visibleSize.height + origin.y));
	whiteBack->setPosition(visibleSize.width + origin.x -
		whiteBack->getContentSize().width / 2, visibleSize.height / 2 + origin.y);
	this->addChild(whiteBack, 2);
#pragma endregion

#pragma region 主人公(立ち絵)の初期設定
	auto mainCharactor = Sprite::create("1.png");
	mainCharactor->setScale((visibleSize.height + origin.y) / (mainCharactor->getContentSize().height));
	mainCharactor->setPosition(visibleSize.width + origin.x - (mainCharactor->getContentSize().width / 4 * mainCharactor->getScale())
		, visibleSize.height / 2 + origin.y);
	mainCharactor->setTag(2);
	this->addChild(mainCharactor, 3);
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
	auto mainCharactor = (Sprite*)this->getChildByTag(2);
	mainCharactor->setTexture("start.png");
	SimpleAudioEngine::getInstance()->playEffect("start.wav");
	//TransitionFade(フェード時間，移動先のシーン，フェードアウトの色)
	Director::getInstance()->replaceScene(TransitionFade::create(2.0f, Game::creatScene(), Color3B::WHITE));
	return true;
}