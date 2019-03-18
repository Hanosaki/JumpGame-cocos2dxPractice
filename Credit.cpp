#pragma execution_character_set("utf-8")
#include "Credit.h"
#include "CharaResouse.h"
#include "Title.h"
#include "SimpleAudioEngine.h"
#include "FileReadClass.h"

using namespace CocosDenshion;
USING_NS_CC;

Label* setCredit(ValueMap valueMap, std::string columnName);
void createLabel(Label* baseLabel, const int creditNum, std::string key, ValueVector creaditValues);//ラベルを生成して、ベースラベルの子要素に追加する

#pragma region 定数宣言
const int Credit::NUM_OF_PAINTERS = 4;
const int Credit::NUM_OF_VOICE_ACTERS = 2;
const int Credit::NUM_OF_COMPOSERS = 1;
#pragma endregion

Scene* Credit::createScene()
{
	auto scene = Scene::create();
	auto layer = Credit::create();
	scene->addChild(layer);
	return scene;
}

bool Credit::init()
{
	if (!Layer::init())
		return false;

#pragma region 変数宣言
	auto directer = Director::getInstance();
	auto visibleSize = directer->getVisibleSize();
	auto origin = directer->getVisibleOrigin();
#pragma endregion

#pragma region 背景設定
	auto backGround = Sprite::create(F_IMAGE + F_UI + BACK_GROUND);
	backGround->setContentSize(directer->getVisibleSize());
	backGround->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	backGround->setColor(Color3B(128, 128, 128));//暗転させる
	this->addChild(backGround, 1);
#pragma endregion

#pragma region 画面名表記
	auto creditLabel = Label::createWithTTF(CREDIT, F_FONTS + JPN_FONTS, 64);
	creditLabel->setPosition(origin.x + visibleSize.width / 2, origin.y + (4 * visibleSize.height) / 5);
	this->addChild(creditLabel, 3);
#pragma endregion

	FileRead fileRead;
	auto creaditValues = fileRead.readCSV(CREDIT_LIST);

#pragma region 使用素材製作者表記

#pragma region イラストレーター

	auto painters = Label::createWithTTF(PAINTERS, F_FONTS + JPN_FONTS, Parameter::SMALL);
	painters->setPosition(origin.x + visibleSize.width / 6, origin.y + (3 * visibleSize.height) / 5);
	createLabel(painters, NUM_OF_PAINTERS, PAINTER_KEY, creaditValues);
	this->addChild(painters, 3);

#pragma endregion

#pragma region コンポーサー
	auto composers = Label::createWithTTF(COMPOSERS, F_FONTS + JPN_FONTS, Parameter::SMALL);
	composers->setPosition(origin.x + visibleSize.width / 2.5, origin.y + (3 * visibleSize.height) / 5);
	createLabel(composers, NUM_OF_COMPOSERS, COMPOSER_KEY, creaditValues);
	this->addChild(composers, 3);
#pragma endregion

#pragma region ボイスアクター
	auto voiceActors = Label::createWithTTF(VOICE_ACTERS, F_FONTS + JPN_FONTS, Parameter::SMALL);
	voiceActors->setPosition(origin.x + visibleSize.width - voiceActors->getContentSize().width,
		origin.y + (3 * visibleSize.height) / 5);
	createLabel(voiceActors, NUM_OF_VOICE_ACTERS, VOICE_ACTER_KEY, creaditValues);
	this->addChild(voiceActors, 3);
#pragma endregion

#pragma endregion

#pragma region クリックリスナー
	auto listner = EventListenerTouchOneByOne::create();
	listner->onTouchBegan = CC_CALLBACK_2(Credit::onTouchBegan, this);
	directer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listner, this);
#pragma endregion

	return true;

}

void createLabel(Label* baseLabel, const int creditNum, std::string key, ValueVector creaditValues)
{
	Label* credit;
	for (int i = 0; i < creditNum; ++i)
	{
		auto creditMap = creaditValues.at(i).asValueMap();
		credit = setCredit(creditMap,key);
		credit->setPosition(30, -30 * (i + 1));
		credit->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		baseLabel->addChild(credit);
	}
}

Label* setCredit(ValueMap valueMap,std::string columnName)
{
	//ラベル表示文字を設定
	auto label = Label::createWithTTF(PILLS + valueMap.at(columnName).asString(), F_FONTS + JPN_FONTS, Parameter::VERY_SMALL);
	return label;
}

bool Credit::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event*event)
{
	//画面がタップされたらタイトル画面に遷移する
	Director::getInstance()->replaceScene(TransitionFade::create(2.0f, Title::createScene(), Color3B::WHITE));
	return true;
}