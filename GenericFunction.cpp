#pragma execution_character_set("utf-8")
#include "GenericFunction.h"
#include "CharaResouse.h"
#include "Converter.h"

USING_NS_CC;

GenericFunc::~GenericFunc()
{
	
}

Sprite* GenericFunc::setMainCharacterImage(Size visibleSize, Vec2 origin,std::string imgPath)
{
	auto characterImage = Sprite::create(imgPath);
	characterImage->setScale((origin.y + visibleSize.height) / (characterImage->getContentSize().height));
	characterImage->setPosition(origin.x + visibleSize.width - (characterImage->getContentSize().width / 4 * characterImage->getScale())
		, origin.y + visibleSize.height / 2);
	return characterImage;
}

char* GenericFunc::setVoiceName(ValueMap valueMap)
{
	std::string findVoiceName = "";//音声データを発見できなかった場合の為に、入力無しで初期化
	findVoiceName = searceVoice(valueMap);
	char* voiceName;
	//音声ファイルが見つかった場合はファイル名を、見つからなかった場合は0を返す
	if (findVoiceName != ""){
		Converter converter;
		voiceName = converter.replaceString2Char(findVoiceName);
	}
	else
		voiceName = "0";
	return voiceName;
}

std::string GenericFunc::searceVoice(ValueMap valueMap)
{
	std::string findVoice = "";//音声データを発見できなかった場合の為に、入力無しで初期化
	//キャラクターの名前がkeyに入っていた場合、音声ファイル名を探す
	if (valueMap.at(CHARACTER_NAME_KEY).asString() == RIVAL_NAME)
	{
		if (valueMap.at(VOICE_KEY).asString() != "")
			findVoice = F_SE + F_RIVAL + F_VOICE + valueMap.at(VOICE_KEY).asString();
	}
	else if (valueMap.at(CHARACTER_NAME_KEY).asString() == MAIN_CHARACTER_NAME)
	{
		if (valueMap.at(VOICE_KEY).asString() != "")
			findVoice = F_SE + F_MAIN_CHARACTER + F_VOICE + valueMap.at(VOICE_KEY).asString();
	}

	return findVoice;

}

Sprite* GenericFunc::createSprite(std::string fileName, float x, float y , int tag)
{
	auto scale = Director::getInstance()->getContentScaleFactor();
	auto sprite = Sprite::create(fileName);
	sprite->setPositionX(x);
	sprite->setPositionY(y);
	sprite->setTag(tag);
	sprite->setScale(scale);
	return sprite;
}

Sprite* GenericFunc::createSprite(std::string fileName, float x, float y, Vec2 anchor, int tag)
{
	auto scale = Director::getInstance()->getContentScaleFactor();
	auto sprite = Sprite::create(fileName);
	sprite->setAnchorPoint(anchor);
	sprite->setPositionX(x);
	sprite->setPositionY(y);
	sprite->setTag(tag);
	sprite->setScale(scale);
	return sprite;
}

Sprite* GenericFunc::createSprite(std::string fileName, float x, float y, Vec2 anchor  ,float scale, int tag )
{
	auto sprite = Sprite::create(fileName);
	sprite->setAnchorPoint(anchor);
	sprite->setPositionX(x);
	sprite->setPositionY(y);
	sprite->setTag(tag);
	sprite->setScale(scale);
	return sprite;
}

Vec2 GenericFunc::setWindowCenter()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	return Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
}


Sprite* GenericFunc::createSpriteWithRect(Rect rect, Color3B color, int tag)
{
	auto sprite = Sprite::create();
	sprite->setTextureRect(rect);
	sprite->setColor(color);
	sprite->setTag(tag);
	return sprite;
}

Sprite* GenericFunc::createSpriteWithRect(Rect rect, float x, float y, Vec2 anchor, Color3B color, int tag)
{
	auto sprite = Sprite::create();
	sprite->setTextureRect(rect);
	sprite->setAnchorPoint(anchor);
	sprite->setPositionX(x);
	sprite->setPositionY(y);
	sprite->setColor(color);
	sprite->setTag(tag);
	return sprite;
}


Menu* GenericFunc::createButton(const std::string fileName, const ccMenuCallback& callback)
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

void GenericFunc::crashBox(std::string errorMessage, Node* node)
{
	/*ウィンドウサイズの取得*/
	auto directer = Director::getInstance();
	auto visibleSize = directer->getVisibleSize();
	auto origin = directer->getVisibleOrigin();

	/*画面サイズの半分の白いボックスを中央に生成*/
	auto rect = Rect(0.f, 0.f, 3*visibleSize.width / 4 + origin.x, 3*visibleSize.height / 4 + origin.y);
	auto box = createSpriteWithRect(rect, Color3B::WHITE, 1);
	box->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	box->setPosition(setWindowCenter());
	auto text = Label::create();
	text->setString(errorMessage);
	text->setColor(Color3B::BLACK);
	text->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	text->setPosition(box->getContentSize().width/2,box->getContentSize().height/2);//下地の真ん中にテキストを設置
	text->retain();
	box->addChild(text);

	/*白ボックスの1/4の黒いボックスを生成、確認ボタンにする*/
	auto rect2 = Rect(0.f, 0.f, box->getContentSize().width / 2, box->getContentSize().height / 4);
	auto button = createSpriteWithRect(rect2,Color3B::BLUE,1);
	auto selectedButton = createSpriteWithRect(rect2, Color3B::BLUE, 2);
	selectedButton->setOpacity(128);
	auto item = MenuItemSprite::create(button, selectedButton, CC_CALLBACK_1(GenericFunc::endGame,this));
	auto menu = Menu::create(item, NULL);
	menu->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	menu->setPosition(box->getContentSize().width / 2, button->getContentSize().height / 2);
	menu->retain();
	box->addChild(menu,2);

	/*テキストの生成*/
	auto text2 = Label::create();
	text2->setString("OK");
	text2->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	text2->setColor(Color3B::RED);
	text2->setPosition(menu->getPosition());//黒ボックスの下側にテキストを設置
	text2->retain();
	box->addChild(text2,3);

	node->addChild(box,5);
	node->unscheduleAllCallbacks();//全てのループ処理を解除する

}

void GenericFunc::endGame(Ref* sender)
{
	//ゲームを終了させる
	Director::getInstance()->purgeCachedData();//キャッシュ開放
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	Converter converter;
	converter.replaceALLMP3toDAT();
#endif
	Director::getInstance()->end();

}