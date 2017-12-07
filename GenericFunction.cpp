#pragma execution_character_set("utf-8")
#include "GenericFunction.h"
#include "CharaResouse.h"
#include "Converter.h"

USING_NS_CC;

Sprite* GenericFunc::setMainCharacterImage(Size visibleSize, Vec2 origin,std::string imgPath)
{
	auto cleannessBox = Sprite::create(F_IMAGE + F_UI + PAUSE_BUTTON);
	auto characterImage = Sprite::create(imgPath);
	characterImage->setScale((origin.y + visibleSize.height) / (characterImage->getContentSize().height));
	characterImage->setPosition(origin.x + visibleSize.width - (characterImage->getContentSize().width / 4 * characterImage->getScale())
		, origin.y + visibleSize.height / 2 - cleannessBox->getContentSize().height);
	return characterImage;
}

char* GenericFunc::setVoiceName(ValueMap valueMap)
{
	std::string findVoiceName = "";
	findVoiceName = searceVoice(valueMap);
	char* voiceName;
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
	std::string findVoice = "";
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

Vec2 GenericFunc::setWindowCenter(Size visibleSize, Vec2 origin)
{
	return Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
}
