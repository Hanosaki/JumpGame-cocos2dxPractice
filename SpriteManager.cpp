#include "SpriteManager.h"

USING_NS_CC;

Sprite* SpriteManager::createSprite(std::string fileName, float pos_x, float pos_y, int tag)
{
	auto sprite = Sprite::create(fileName);
	setSpriteBasicData(sprite, pos_x, pos_y, tag);
	return sprite;
}

Sprite* SpriteManager::createSprite(std::string fileName, float pos_x, float pos_y, Vec2 anchor, int tag)
{
	auto sprite = Sprite::create(fileName);
	setSpriteBasicData(sprite, pos_x, pos_y, tag);
	sprite->setAnchorPoint(anchor);
	return sprite;
}

Sprite* SpriteManager::createSprite(std::string fileName, float pos_x, float pos_y, Vec2 anchor, float scale, int tag)
{
	auto sprite = Sprite::create(fileName);
	setSpriteBasicData(sprite, pos_x, pos_y, tag);
	sprite->setAnchorPoint(anchor);
	sprite->setScale(scale);
	return sprite;
}

Sprite* SpriteManager::createWithSpriteFileName(std::string fileName, float pos_x, float pos_y, Vec2 anchor, int &tag)
{
	auto sprite = Sprite::createWithSpriteFrameName(fileName);
	setSpriteBasicData(sprite, pos_x, pos_y, tag);
	sprite->setAnchorPoint(anchor);
	return sprite;
}

void SpriteManager::setSpriteBasicData(Sprite* &sprite,float &pos_x,float &pos_y,int &tag)
{
	sprite->setPositionX(pos_x);
	sprite->setPositionY(pos_y);
	sprite->setTag(tag);
	auto scale = Director::getInstance()->getContentScaleFactor();
	sprite->setScale(scale);
}