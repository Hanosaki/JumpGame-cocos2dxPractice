#pragma execution_character_set("utf-8")
#include "IntroductionScene.h"
#include "SimpleAudioEngine.h"
#include "CharaResouse.h"
#include "FileReadClass.h"
#include "GameScene.h"

using namespace CocosDenshion;
USING_NS_CC;

const int ZERO = 0;
const int NAME_FONT_SIZE = 32;
const int WORD_FONT_SIZE = 48;

char* setVoiceName(ValueMap valueMap);
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
	auto skipButton = Sprite::create(F_IMAGE + F_UI + SKIP_BUTTON);
	skipButton->setOpacity(128);
	auto selectedSkipButton = Sprite::create(F_IMAGE + F_UI + SKIP_BUTTON);
	selectedSkipButton->setOpacity(64);

	auto skipItem = MenuItemSprite::create(skipButton, selectedSkipButton, CC_CALLBACK_1(Introduction::callGameScene, this));
	skipItem->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	skipItem->setPosition(origin.x + visibleSize.width, origin.y + visibleSize.height);
	auto skipMenu = Menu::create(skipItem, NULL);
	skipMenu->setPosition(Vec2::ZERO);
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
		if (strcmp(setVoiceName(characterWordMap),"0"))
			SimpleAudioEngine::getInstance()->preloadEffect(setVoiceName(characterWordMap));
	}

#pragma endregion

	// 画面遷移の為のディレイ
	this->runAction(Sequence::create(DelayTime::create(1.5f), NULL));

#pragma region リスナー登録
	auto listner = EventListenerTouchOneByOne::create();
	listner->onTouchBegan = CC_CALLBACK_2(Introduction::onTouchBegan, this);
	listner->onTouchEnded = CC_CALLBACK_2(Introduction::onTouchEnded, this);
	directer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listner, this);
#pragma endregion

	SimpleAudioEngine::getInstance()->playBackgroundMusic(OP_BGM, true);
	
	return true;
}

#pragma region アクションパート呼び出し

void Introduction::callGameScene(Ref* Sender)
{
	SimpleAudioEngine::getInstance()->stopAllEffects();
	SimpleAudioEngine::getInstance()->playEffect(BUTTON_SE);
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

#pragma region 音声ファイル名読み込み

char* setVoiceName(ValueMap valueMap)
{
	std::string tmpVoiceName = "";

	if (valueMap.at(CHARACTER_NAME_KEY).asString() == RIVAL_NAME)
	{
		if (valueMap.at(VOICE_KEY).asString() != "")
			tmpVoiceName = F_RIVAL + F_VOICE + valueMap.at(VOICE_KEY).asString() + ".mp3";
	}
	else if (valueMap.at(CHARACTER_NAME_KEY).asString() == MAIN_CHARACTER_NAME)
	{
		if (valueMap.at(VOICE_KEY).asString() != "")
			tmpVoiceName = F_MAIN_CHARACTER + F_VOICE + valueMap.at(VOICE_KEY).asString() + ".mp3";
	}
	char* voiceName = new char[tmpVoiceName.length() + 1];
	memcpy(voiceName, tmpVoiceName.c_str(), tmpVoiceName.length() + 1);
	return voiceName;
}

#pragma endregion

void playVoice(ValueMap valueMap)
{
	SimpleAudioEngine::getInstance()->playEffect(setVoiceName(valueMap));
}