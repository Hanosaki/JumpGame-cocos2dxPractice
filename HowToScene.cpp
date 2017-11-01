#include "HowToScene.h"
#include "CharaResouse.h"
#include "Title.h"

USING_NS_CC;

Scene* HowTo::createScene()
{
	auto scene = Scene::create();
	auto layer = HowTo::create();
	scene->addChild(layer);
	return scene;
}

bool HowTo::init()
{
	if (!Layer::init())
		return false;

	auto directer = Director::getInstance();
	auto visibleSize = directer->getVisibleSize();
	auto origin = directer->getVisibleOrigin();

#pragma region –ß‚éƒ{ƒ^ƒ“

	auto returnButton = Sprite::create(F_IMAGE + F_UI + RETURN_BUTTON);
	auto selectedReturnButton = Sprite::create(F_IMAGE + F_UI + RETURN_BUTTON);
	selectedReturnButton->setOpacity(128);

	auto returnItem = MenuItemSprite::create(returnButton, selectedReturnButton, CC_CALLBACK_1(HowTo::returnTitle, this));
	returnItem->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	returnItem->setPosition(origin.x + visibleSize.width, origin.y + visibleSize.height);
	auto returnMenu = Menu::create(returnItem, NULL);
	returnMenu->setPosition(Vec2::ZERO);
	this->addChild(returnMenu, 2);

#pragma endregion


}

void HowTo::returnTitle(Ref* sender)
{
	Director::getInstance()->replaceScene(TransitionFade::create(3.0f, Title::createScene(), Color3B::WHITE));
}