#pragma execution_character_set("utf-8")
#include "GenericFunction.h"
#include "CharaResouse.h"

USING_NS_CC;

Sprite* GenericFunc::setMainCharacterImage(Size visibleSize, Vec2 origin,std::string imgPath)
{
	auto cleannessBox = Sprite::create(F_IMAGE + PAUSE_BUTTON);
	auto characterImage = Sprite::create(imgPath);
	characterImage->setScale((origin.y + visibleSize.height) / (characterImage->getContentSize().height));
	characterImage->setPosition(origin.x + visibleSize.width - (characterImage->getContentSize().width / 4 * characterImage->getScale())
		, origin.y + visibleSize.height / 2 - cleannessBox->getContentSize().height);
	return characterImage;
}
