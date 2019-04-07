#pragma execution_character_set("utf-8")
#include "IntroductionScene.h"
#include "SimpleAudioEngine.h"
#include "CharaResouse.h"
#include "FileReadClass.h"
#include "GameScene.h"
#include "Converter.h"
#include "GenericFunction.h"
#include "AnimationLoad.h"

using namespace CocosDenshion;
USING_NS_CC;

const int ZERO = 0;
const int NAME_FONT_SIZE = 32;
const int WORD_FONT_SIZE = 48;

void playVoice(ValueMap valueMap);

Scene* Introduction::createScene()
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
	auto scaleFactor = directer->getContentScaleFactor();

	/*音量設定*/
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5f);
	SimpleAudioEngine::getInstance()->setEffectsVolume(0.8f);

#pragma region 背景設定
	auto backGround = Sprite::create(F_IMAGE + F_UI +OP_BACK_GROUND);
	backGround->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	backGround->setContentSize(Size(origin.x + visibleSize.width, origin.y + visibleSize.height));
	this->addChild(backGround, 1);
#pragma endregion

#pragma region スキップボタン
	
	/*ボタン画像の登録*/
	auto skipButton = Sprite::create(F_IMAGE + F_UI + SKIP_BUTTON);
	auto selectedSkipButton = Sprite::create(F_IMAGE + F_UI + SKIP_BUTTON);
	selectedSkipButton->setOpacity(128);

	/*ボタンをメニューとして登録*/
	auto skipItem = MenuItemSprite::create(skipButton, selectedSkipButton, CC_CALLBACK_1(Introduction::callGameScene, this));
	skipItem->setScale(scaleFactor - 0.5*scaleFactor);
	skipItem->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	skipItem->setPosition(origin.x + visibleSize.width, origin.y + visibleSize.height);
	auto skipMenu = Menu::create(skipItem, NULL);
	skipMenu->setPosition(Vec2::ZERO);
	skipMenu->setOpacity(128);
	const int skipMenuTag = 10;
	skipMenu->setTag(skipMenuTag);
	skipMenu->setEnabled(false);
	this->addChild(skipMenu, 3);
#pragma endregion

#pragma region 主人公立ち絵
	auto characterImage = Sprite::create(F_IMAGE + F_MAIN_CHARACTER + SMILE);
	characterImage->setScale((origin.y +  visibleSize.height) / (characterImage->getContentSize().height));
	characterImage->setPosition(origin.x + visibleSize.width / 6, Vec2::ZERO.y);
	characterImage->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	characterImage->setOpacity(128);
	characterImage->setFlippedX(true);
	characterImage->setTag(1);
	this->addChild(characterImage, 2);
#pragma endregion

#pragma region ライバル立ち絵
	auto rivalImage = Sprite::create(F_IMAGE + F_RIVAL + SMILE);
	rivalImage->setScale(characterImage->getScale());
	rivalImage->setPosition(origin.x + visibleSize.width
		- rivalImage->getContentSize().width / 2 * rivalImage->getScale(),
		0);
	rivalImage->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	rivalImage->setTag(2);
	rivalImage->setOpacity(128);
	this->addChild(rivalImage, 2);
#pragma endregion

#pragma region テキストウィンドウの設定
	auto textWindow = Sprite::create(F_IMAGE + F_UI + TEXT_WINDOW);
	textWindow->setContentSize(Size(origin.x + visibleSize.width, origin.y + visibleSize.height / 5));
	textWindow->setPosition(origin.x + visibleSize.width / 2,
		textWindow->getContentSize().height / 2);
	this->addChild(textWindow, 3);
#pragma endregion

#pragma region テキスト読み込み
	FileRead fileRead;
	wordsNum = ZERO;
	characterWordVector = fileRead.readCSV(CONVERSATION_LIST);
	characterWordMap = characterWordVector.at(wordsNum).asValueMap();
#pragma endregion

#pragma region 名前表示用ラベルの設定
	characterNameLabel = Label::createWithTTF(characterWordMap.at(CHARACTER_NAME_KEY).asString()
		, F_FONTS + JPN_FONTS, NAME_FONT_SIZE);
	characterNameLabel->setPosition(Vec2(NAME_FONT_SIZE+NAME_FONT_SIZE/3,
		textWindow->getContentSize().height - NAME_FONT_SIZE / 2));
	characterNameLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	characterNameLabel->setColor(Color3B::WHITE);
	textWindow->addChild(characterNameLabel, 1);
#pragma endregion

#pragma region セリフ用ラベルの設定
	characterWordLabel = Label::createWithTTF(characterWordMap.at(CHARACTER_WORD_KEY).asString()
		, F_FONTS + JPN_FONTS, WORD_FONT_SIZE);
	characterWordLabel->setPosition(WORD_FONT_SIZE, characterNameLabel->getPositionY()
		- (WORD_FONT_SIZE / 2 + characterNameLabel->getContentSize().height));
	characterWordLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	characterWordLabel->setColor(Color3B::WHITE);
	textWindow->addChild(characterWordLabel, 1);
#pragma endregion

#pragma region 音声データをプリロード

	for (int i = 0; i < characterWordVector.size(); ++i)
	{
		characterWordMap = characterWordVector.at(i).asValueMap();
		GenericFunc genericFunc;
		auto voiceName = genericFunc.setVoiceName(characterWordMap);
		//音声ファイル名がcsvファイルから取得できた場合、同じファイル名のmp3をプリロードする
		if (strcmp(voiceName, "0")){
			Converter converter;
		#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			voiceName = converter.replaceDATtoMP3(voiceName);
		#elif(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)//Androidの場合
			voiceName = converter.replaceString2Char(voiceName + TYPE_MP3);
		#endif
			SimpleAudioEngine::getInstance()->preloadEffect(voiceName);
		}
	}

#pragma endregion

	auto thread = std::thread([this]()
	{
		AnimationLoad::load();//アニメーション画像のロード処理>
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([this]()
		{//アニメーション画像のロードが終わったら、スキップボタンを有効化
			auto skipMenu = (Menu*)this->getChildByTag(10);
			skipMenu->setEnabled(true);
			skipMenu->setOpacity(255);
			
		});
	});
	thread.detach();



	// 画面遷移の為のディレイ
	this->runAction(Sequence::create(DelayTime::create(1.5f), NULL));

#pragma region リスナー登録
	auto listner = EventListenerTouchOneByOne::create();
	listner->onTouchBegan = CC_CALLBACK_2(Introduction::onTouchBegan, this);
	listner->onTouchEnded = CC_CALLBACK_2(Introduction::onTouchEnded, this);
	directer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listner, this);
#pragma endregion

	Converter converter;
	auto bgmName = converter.replaceString2Char(F_BGM + OP_BGM + TYPE_MP3);
	SimpleAudioEngine::getInstance()->playBackgroundMusic(bgmName, true);
	
	return true;
}

#pragma region アクションパート呼び出し

void Introduction::callGameScene(Ref* Sender)
{
	Converter converter;
	auto seName = converter.replaceString2Char(F_SE + BUTTON_SE + TYPE_MP3);
	SimpleAudioEngine::getInstance()->stopAllEffects();
	SimpleAudioEngine::getInstance()->playEffect(seName);
	Director::getInstance()->replaceScene(TransitionFade::create(3.0f, Game::createScene(), Color3B::WHITE));
}

#pragma endregion

bool Introduction::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}

#pragma region 台詞進行

void Introduction::onTouchEnded(Touch* touch, Event*event)
{
	//現在の行数が、csvファイルの行数未満なら行を進め、以上になった場合、シーンを遷移する
	if (wordsNum < characterWordVector.size() - 1){
		++wordsNum;
		SimpleAudioEngine::getInstance()->stopAllEffects();
		characterWordMap = characterWordVector.at(wordsNum).asValueMap();
		auto name = characterWordMap.at(CHARACTER_NAME_KEY).asString();
		characterNameLabel->setString(name);
		spriteChange();
		playVoice(characterWordMap);
	}
	else{
		Director::getInstance()->replaceScene(TransitionFade::create(3.0f, Game::createScene(), Color3B::WHITE));
	}

	auto word = characterWordMap.at(CHARACTER_WORD_KEY).asString();
	characterWordLabel->setString(word);

}

#pragma endregion

#pragma region キャラグラ切り替え

void Introduction::spriteChange()
{
	auto characterImage = (Sprite*)this->getChildByTag(1);
	auto rivalImage = (Sprite*)this->getChildByTag(2);
	//バリューマップ内に記述されているキャラクター名に対応したキャラの画像を変更する
	if (characterWordMap.at(CHARACTER_NAME_KEY).asString() == RIVAL_NAME)
	{
		characterImage->setOpacity(128);
		rivalImage->setOpacity(255);
		rivalImage->setTexture(F_IMAGE + F_RIVAL + characterWordMap.at(FACE_KEY).asString() + ".png");
	}
	else if (characterWordMap.at(CHARACTER_NAME_KEY).asString() == MAIN_CHARACTER_NAME)
	{
		rivalImage->setOpacity(128);
		characterImage->setOpacity(255);
		characterImage->setTexture(F_IMAGE + F_MAIN_CHARACTER + characterWordMap.at(FACE_KEY).asString() + ".png");
	}
	else
	{
		rivalImage->setOpacity(128);
		characterImage->setOpacity(128);
	}

}

#pragma endregion

void playVoice(ValueMap valueMap)
{
	std::string findVoiceName = "";
	GenericFunc genericFunc;
	findVoiceName = genericFunc.searceVoice(valueMap);
	//mp3ファイルが見つかっているなら、音声を再生する。
	if (findVoiceName != ""){
		Converter converter;
		auto voiceName = converter.replaceString2Char(findVoiceName + TYPE_MP3);
		SimpleAudioEngine::getInstance()->playEffect(voiceName);
	}
}