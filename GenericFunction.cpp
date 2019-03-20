#pragma execution_character_set("utf-8")
#include "GenericFunction.h"
#include "CharaResouse.h"
#include "Converter.h"

USING_NS_CC;

GenericFunc::GenericFunc()
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
	std::string findVoiceName = "";//�����f�[�^�𔭌��ł��Ȃ������ꍇ�ׂ̈ɁA���͖����ŏ�����
	findVoiceName = searceVoice(valueMap);
	char* voiceName;
	//�����t�@�C�������������ꍇ�̓t�@�C�������A������Ȃ������ꍇ��0��Ԃ�
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
	std::string findVoice = "";//�����f�[�^�𔭌��ł��Ȃ������ꍇ�ׂ̈ɁA���͖����ŏ�����
	//�L�����N�^�[�̖��O��key�ɓ����Ă����ꍇ�A�����t�@�C������T��
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

Vec2 GenericFunc::setWindowCenter(Size visibleSize, Vec2 origin)
{
	return Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
}

Menu* GenericFunc::createButton(const std::string fileName, const ccMenuCallback& callback)
{

	auto directer = Director::getInstance();
	auto visibleSize = directer->getVisibleSize();
	auto origin = directer->getVisibleOrigin();
	//�{�^���T�C�Y����ʃT�C�Y�ɍ��킹�Đݒ�
	auto BUTTON_SIZE = Size(visibleSize.width + origin.x, visibleSize.height / 10 + origin.y);

	auto button = Sprite::create(fileName);
	button->setContentSize(BUTTON_SIZE);

	auto selectedButton = Sprite::create(fileName);
	selectedButton->setOpacity(128);
	selectedButton->setContentSize(BUTTON_SIZE);

	auto item = MenuItemSprite::create(button, selectedButton, callback);
	//Menu�N���X����R���e���c�T�C�Y���擾���邽�߂Ƀ^�O�ݒ�
	item->setTag(1);

	auto menu = Menu::create(item, NULL);
	menu->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	return menu;

}

