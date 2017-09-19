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

#pragma region BGMのプリロード
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(OP_BGM);
#pragma endregion

#pragma region SEのプリロード
	SimpleAudioEngine::getInstance()->setEffectsVolume(0.5f);
	SimpleAudioEngine::getInstance()->preloadEffect(BUTTON_SE);
#pragma endregion

#pragma region 背景設定
	auto backGround = Sprite::create(IMAGE +OP_BACK_GROUND);
	backGround->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
	backGround->setContentSize(Size(visibleSize.width + origin.x, visibleSize.height + origin.y));
	this->addChild(backGround, 1);
#pragma endregion

#pragma region スキップボタン
	auto skipButton = Sprite::create(IMAGE + SKIP_IMAGE);
	skipButton->setOpacity(128);
	auto selectedSkipButton = Sprite::create(IMAGE + SKIP_IMAGE);
	selectedSkipButton->setOpacity(64);

	auto skipItem = MenuItemSprite::create(skipButton, selectedSkipButton, CC_CALLBACK_1(Introduction::callGameScene, this));
	skipItem->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	skipItem->setPosition(visibleSize.width + origin.x,visibleSize.height + origin.y);
	auto skipMenu = Menu::create(skipItem, NULL);
	skipMenu->setPosition(Vec2::ZERO);
	this->addChild(skipMenu, 3);
#pragma endregion

#pragma region 主人公立ち絵
	auto characterImage = Sprite::create(MAIN_CHARACTER + IMAGE + CHARACTER_IMAGE_NORMAL);
	characterImage->setScale((visibleSize.height + origin.y) / (characterImage->getContentSize().height));
	characterImage->setPosition(visibleSize.width / 6 + origin.x, Vec2::ZERO.y);
	characterImage->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	characterImage->setFlippedX(true);
	characterImage->setTag(1);
	this->addChild(characterImage, 2);
#pragma endregion

#pragma region ライバル立ち絵
	auto rivalImage = Sprite::create(RIVAL + RIVAL_IMAGE);
	rivalImage->setScale(characterImage->getScale());
	rivalImage->setPosition(visibleSize.width + origin.x
		- rivalImage->getContentSize().width / 2 * rivalImage->getScale(),
		0);
	rivalImage->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	rivalImage->setTag(2);
	this->addChild(rivalImage, 2);
#pragma endregion

#pragma region テキストウィンドウの設定
	auto textWindow = Sprite::create(IMAGE + TEXT_WINDOW);
	textWindow->setContentSize(Size(visibleSize.width + origin.x, visibleSize.height / 5 + origin.y));
	textWindow->setPosition(visibleSize.width / 2 + origin.x,
		textWindow->getContentSize().height / 2);
	this->addChild(textWindow, 3);
#pragma endregion

	/*以下，表示テキスト処理*/

#pragma region テキスト読み込み
	FileRead fileRead;
	wordsNum = ZERO;
	characterWords = fileRead.readCSV(CONVERSATION_LIST);
	characterWord = characterWords.at(wordsNum).asValueMap();
#pragma endregion

#pragma region 名前表示用ラベルの設定
	characterNameLabel = Label::createWithTTF(characterWord.at(CHARACTER_NAME).asString()
		, FONTS + JPN_FONTS, NAME_FONT_SIZE);
	characterNameLabel->setPosition(Vec2(characterNameLabel->getContentSize().width / 2,
		textWindow->getContentSize().height - characterNameLabel->getContentSize().height / 2));
	characterNameLabel->setColor(Color3B::BLACK);
	textWindow->addChild(characterNameLabel, 1);
#pragma endregion

#pragma region セリフ用ラベルの設定
	characterWordLabel = Label::createWithTTF(characterWord.at(CHARACTER_WORD).asString()
		, FONTS + JPN_FONTS, 48);
	characterWordLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	characterWordLabel->setPosition(characterNameLabel->getPositionX(),
		characterNameLabel->getPositionY()
		- (characterWordLabel->getContentSize().height / 2
		+ characterNameLabel->getContentSize().height / 2));
	characterWordLabel->setColor(Color3B::BLACK);
	textWindow->addChild(characterWordLabel, 1);
#pragma endregion

	/*以上，テキスト表示処理*/

#pragma region 画面遷移の為のディレイ
	this->runAction(Sequence::create(DelayTime::create(1.5), NULL));
#pragma endregion


#pragma region リスナー登録
	auto listner = EventListenerTouchOneByOne::create();
	listner->onTouchBegan = CC_CALLBACK_2(Introduction::onTouchBegan, this);
	listner->onTouchEnded = CC_CALLBACK_2(Introduction::onTouchEnded, this);
	directer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listner, this);
#pragma endregion

	SimpleAudioEngine::getInstance()->playBackgroundMusic(OP_BGM, false);

	spriteOpacityChange(characterWord.at(CHARACTER_NAME).asString());

	return true;
}

void Introduction::callGameScene(Ref* Sender)
{
	SimpleAudioEngine::getInstance()->playEffect(BUTTON_SE);
	Director::getInstance()->replaceScene(TransitionFade::create(3.0f, Game::creatScene(), Color3B::WHITE));
}

bool Introduction::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}

void Introduction::onTouchEnded(Touch* touch, Event*event)
{
	if (wordsNum < characterWords.size() - 1){
		++wordsNum;
		characterWord = characterWords.at(wordsNum).asValueMap();
		auto name = characterWord.at(CHARACTER_NAME).asString();
		characterNameLabel->setString(name);
		spriteOpacityChange(name);
	}
	else{
		Director::getInstance()->replaceScene(TransitionFade::create(3.0f, Game::creatScene(), Color3B::WHITE));
	}

	auto word = characterWord.at(CHARACTER_WORD).asString();
	characterWordLabel->setString(word);

}

void Introduction::spriteOpacityChange(std::string name)
{
	auto characterImage = (Sprite*)this->getChildByTag(1);
	auto rivalImage = (Sprite*)this->getChildByTag(2);
	if (name == RIVAL_NAME)
	{
		characterImage->setOpacity(128);
		rivalImage->setOpacity(255);
	}
	else if (name == MAIN_CHARACTER_NAME)
	{
		rivalImage->setOpacity(128);
		characterImage->setOpacity(255);
	}

}