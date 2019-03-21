#pragma execution_character_set("utf-8")
#include "Title.h"
#include "Credit.h"
#include "CharaResouse.h"
#include "GenericFunction.h"
#include "AudioEngine.h"
#include "IntroductionScene.h"
#include "Converter.h"

USING_NS_CC;
using namespace experimental;

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
	GenericFunc* gf = new GenericFunc();
#pragma endregion

	auto audioEngine = new AudioEngine();

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
	auto characterImage = gf->setMainCharacterImage(visibleSize, origin, F_IMAGE + F_MAIN_CHARACTER + SMILE);
	characterImage->setTag(2);
	this->addChild(characterImage, 3);
#pragma endregion

#pragma region 終了ボタン配置
	auto endButton = gf->createButton(F_IMAGE + F_UI + END_BUTTON, CC_CALLBACK_1(Title::closeGame, this));
	setButtonPosition(endButton);
	this->addChild(endButton, 2);
#pragma endregion

#pragma region クレジットボタン配置
	auto creditButton = gf->createButton(F_IMAGE + F_UI + CREDIT_IMAGE, CC_CALLBACK_1(Title::callCreditScene, this));
	setButtonPosition(endButton, creditButton);
	this->addChild(creditButton, 2);
#pragma endregion

#pragma region スタートボタン配置
	auto startButton = gf->createButton(F_IMAGE + F_UI + START_BUTTON, CC_CALLBACK_1(Title::callOPScene, this));
	setButtonPosition(creditButton,startButton);
	this->addChild(startButton, 2);
#pragma endregion

	auto con = new Converter();
	auto bgmName = con->replaceString2Char(F_BGM + TITLE_BGM + TYPE_MP3);
	audioEngine->play2d(bgmName,true,0.4f,nullptr);

	return true;
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
	AudioEngine::stopAll();
	auto seName = Converter::replaceString2Char(F_SE + START_VOICE + TYPE_MP3);
	AudioEngine::play2d(seName,false,0.8,nullptr);
	characterImageChange();
	Director::getInstance()->replaceScene(TransitionFade::create(3.0f, Introduction::createScene(), Color3B::BLACK));
}

void Title::callCreditScene(Ref* Sender)
{
	//使用素材一覧シーンに遷移させる
	auto seName = Converter::replaceString2Char(F_SE + BUTTON_SE + TYPE_MP3);
	AudioEngine::stopAll();
	AudioEngine::play2d(seName,false,0.8,nullptr);
	characterImageChange();
	Director::getInstance()->replaceScene(TransitionFade::create(2.0f, Credit::createScene(), Color3B::WHITE));
}

void Title::closeGame(Ref* sender)
{
	//ゲームを終了させる
	AudioEngine::stopAll();
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
