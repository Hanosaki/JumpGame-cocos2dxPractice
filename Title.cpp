#pragma execution_character_set("utf-8")
#include "Title.h"
#include "Credit.h"
#include "CharaResouse.h"
#include "GenericFunction.h"
#include "SimpleAudioEngine.h"
#include "IntroductionScene.h"
#include "Converter.h"

using namespace CocosDenshion;
USING_NS_CC;

void setButtonPosition(Menu* menu);//画面下部にボタンを設置
void setButtonPosition(Menu* baseMenu, Menu* addMenu);//一つ目のボタンの上に二つ目のボタンを設置

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
	GenericFunc genericFunc;
#pragma endregion

	auto audioEngine = SimpleAudioEngine::getInstance();

	//BGM設定
	audioEngine->setBackgroundMusicVolume(0.4f);
	// SE設定
	audioEngine->setEffectsVolume(0.8f);

#pragma region タイトル表記
	auto titleLabel = Label::createWithTTF(TITLE_TEXT, F_FONTS + JPN_FONTS, 64);
	titleLabel->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - titleLabel->getContentSize().height*2);
	titleLabel->setColor(Color3B::BLACK);
	this->addChild(titleLabel, 4);
#pragma endregion

#pragma region 背景設定
	auto backGround = Sprite::create(F_IMAGE + F_UI + OP_BACK_GROUND);
	backGround->setContentSize(directer->getVisibleSize());
	backGround->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(backGround, 1);
#pragma endregion

#pragma region 主人公(立ち絵)の初期設定
	auto characterImage = genericFunc.setMainCharacterImage(visibleSize, origin, F_IMAGE + F_MAIN_CHARACTER + SMILE);
	characterImage->setTag(2);
	this->addChild(characterImage, 3);
#pragma endregion

#pragma region 終了ボタン配置
	auto endButton = createButton(F_IMAGE + F_UI + END_BUTTON, CC_CALLBACK_1(Title::closeGame, this));
	setButtonPosition(endButton);
	this->addChild(endButton, 2);
#pragma endregion

#pragma region クレジットボタン配置
	auto creditButton = createButton(F_IMAGE + F_UI + CREDIT_IMAGE, CC_CALLBACK_1(Title::callCreditScene, this));
	setButtonPosition(endButton, creditButton);
	this->addChild(creditButton, 2);
#pragma endregion

#pragma region スタートボタン配置
	auto startButton = createButton(F_IMAGE + F_UI + START_BUTTON, CC_CALLBACK_1(Title::callOPScene, this));
	setButtonPosition(creditButton,startButton);
	this->addChild(startButton, 2);
#pragma endregion

	Converter converter;
	auto bgmName = converter.replaceString2Char(F_BGM + TITLE_BGM + TYPE_MP3);
	SimpleAudioEngine::getInstance()->playBackgroundMusic(bgmName, true);

	return true;
}

Menu* Title::createButton(const std::string fileName,const ccMenuCallback& callback)
{
	
	auto directer = Director::getInstance();
	auto visibleSize = directer->getVisibleSize();
	auto origin = directer->getVisibleOrigin();
	//ボタンサイズを画面サイズに合わせて設定
	auto BUTTON_SIZE = Size(visibleSize.width + origin.x, visibleSize.height / 10 + origin.y);

	auto button = Sprite::create(fileName);
	button->setContentSize(BUTTON_SIZE);

	auto selectedButton = Sprite::create(fileName);
	selectedButton->setOpacity(128);
	selectedButton->setContentSize(BUTTON_SIZE);
	
	auto item = MenuItemSprite::create(button, selectedButton, callback);
	//Menuクラスからコンテンツサイズを取得するためにタグ設定
	item->setTag(1);
	
	auto menu = Menu::create(item, NULL);
	menu->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	
	return menu;

}

void Title::characterImageChange()
{
	//キャラの立ち絵を笑顔に変更
	auto characterImage = (Sprite*)this->getChildByTag(2);
	characterImage->setTexture(F_IMAGE + F_MAIN_CHARACTER + LAUGH);
}

void Title::callOPScene(Ref* Sender)
{
	//OPシーンに遷移させる
	Converter converter;
	SimpleAudioEngine::getInstance()
		->playEffect(converter.replaceString2Char(F_SE + START_VOICE + TYPE_MP3));
	characterImageChange();
	Director::getInstance()->replaceScene(TransitionFade::create(3.0f, Introduction::createScene(), Color3B::BLACK));
}

void Title::callCreditScene(Ref* Sender)
{
	//使用素材一覧シーンに遷移させる
	Converter converter;
	auto seName = converter.replaceString2Char(F_SE + BUTTON_SE + TYPE_MP3);
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->playEffect(seName);
	characterImageChange();
	Director::getInstance()->replaceScene(TransitionFade::create(2.0f, Credit::createScene(), Color3B::WHITE));
}

void Title::closeGame(Ref* sender)
{
	//ゲームを終了させる
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	Director::getInstance()->purgeCachedData();//キャッシュ開放
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	Converter converter;
	converter.replaceALLMP3toDAT();
#endif
	Director::getInstance()->end();
}

void setButtonPosition(Menu* menu)
{
	auto directer = Director::getInstance();
	auto visibleSize = directer->getVisibleSize();
	auto origin = directer->getVisibleOrigin();
	menu->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	menu->setPosition(Vec2(origin.x + visibleSize.width / 2, menu->getChildByTag(1)->getContentSize().height / 2));

}

void setButtonPosition(Menu* baseMenu, Menu* addMenu)
{
	addMenu->setPositionX(baseMenu->getPositionX());
	addMenu->setPositionY(baseMenu->getPositionY() + addMenu->getChildByTag(1)->getContentSize().height);

}
