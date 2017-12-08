#include "HowToScene.h"
#include "CharaResouse.h"
#include "GenericFunction.h"
#include "Title.h"

USING_NS_CC;

std::string setPageNo(int pageNum);
const int TIME_LIMIT = 3;

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
	auto generic = new GenericFunc;
	auto imageSize = Size(visibleSize.width + origin.x, visibleSize.height + origin.y);

	posCenter = generic->setWindowCenter(visibleSize, origin);

	auto uiDescription = Sprite::create(F_IMAGE + UI_DESCRIPTION);
	uiDescription->setContentSize(imageSize);
	uiDescription->setPosition(posCenter);
	uiDescription->setTag(1);
	this->addChild(uiDescription,1);

	auto jumpDescription = Sprite::create(F_IMAGE + JUMP_DESCRIPTION);
	jumpDescription->setContentSize(imageSize);
	jumpDescription->setPosition(posCenter);
	jumpDescription->setPositionX(posCenter.x * 3);
	jumpDescription->setTag(2);
	this->addChild(jumpDescription, 1);

	auto pageNo = Label::createWithTTF(setPageNo(1), F_FONTS + JPN_FONTS, Parameter::SMALL);
	pageNo->setPosition(posCenter.x, pageNo->getContentSize().height / 2);
	pageNo->setColor(Color3B::BLACK);
	pageNo->setTag(3);
	this->addChild(pageNo, 2);

	auto label = Label::createWithTTF(RETRUN_TITLE_FROM_HOWTO, F_FONTS + JPN_FONTS, Parameter::SMALL);
	label->setPosition(posCenter);
	label->setPositionY(posCenter.y + posCenter.y / 2);
	label->setColor(Color3B::BLACK);
	auto fadeOut = FadeTo::create(1.5f, 0);
	auto fadeIn = FadeTo::create(1.5f, 255);
	auto seq = Sequence::create(fadeOut, 
		CallFunc::create([this](){HowTo::switchText();}), 
		fadeIn, NULL);
	auto repeat = RepeatForever::create(seq);
	label->runAction(repeat);
	label->setTag(4);
	this->addChild(label, 2);

#pragma region クリックリスナーの初期設定
	auto listner = EventListenerTouchOneByOne::create();
	listner->onTouchBegan = CC_CALLBACK_2(HowTo::onTouchBegan, this);
	listner->onTouchMoved = CC_CALLBACK_2(HowTo::onTouchMoved, this);
	listner->onTouchEnded = CC_CALLBACK_2(HowTo::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listner, this);
#pragma endregion

	return true;

}

bool HowTo::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	fingerLocation = touch->getLocation();
	countTimer = TIME_LIMIT;
	this->schedule(schedule_selector(HowTo::goTitleTimer), 1.0f);
	return true;
}

void HowTo::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	move = (touch->getLocation().x - fingerLocation.x) / 25;
	auto uiDescription = (Sprite*)this->getChildByTag(1);
	auto jumpDescription = (Sprite*)this->getChildByTag(2);

	uiDescription->setPositionX(uiDescription->getPositionX() + move);
	jumpDescription->setPositionX(jumpDescription->getPositionX() + move);

}

void HowTo::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	this->unschedule(schedule_selector(HowTo::goTitleTimer));
	auto pageNo = (Label*)this->getChildByTag(3);
	if (move >= 15)
	{
		this->schedule(schedule_selector(HowTo::moveImageLeft), 0.01f);
		pageNo->setString(setPageNo(1));
	}
	if (move <= -10)
	{
		this->schedule(schedule_selector(HowTo::moveImageRight), 0.01f);
		pageNo->setString(setPageNo(2));

	}

	auto uiDescription = (Sprite*)this->getChildByTag(1);
	auto jumpDescription = (Sprite*)this->getChildByTag(2);

	if (uiDescription->getPositionX() > posCenter.x)
	{
		uiDescription->setPosition(posCenter);
		jumpDescription->setPositionX(posCenter.x * 3);
		pageNo->setString(setPageNo(1));
	}
	else if (jumpDescription->getPositionX() < posCenter.x)
	{
		jumpDescription->setPosition(posCenter);
		uiDescription->setPositionX(-posCenter.x);
		pageNo->setString(setPageNo(2));
	}

	auto label = (Label*)this->getChildByTag(4);
	label->setString(RETRUN_TITLE_FROM_HOWTO);

}

void HowTo::goTitleTimer(float dt)
{
	auto label = (Label*)this->getChildByTag(4);
	label->setString(StringUtils::toString(countTimer) + "...");
	if (countTimer > 0)
		--countTimer;
	else
		returnTitle();
}

void HowTo::moveImageLeft(float dt)
{
	auto uiDescription = (Sprite*)this->getChildByTag(1);
	auto jumpDescription = (Sprite*)this->getChildByTag(2);

	if (uiDescription->getPositionX() < posCenter.x)
	{
		uiDescription->setPositionX(uiDescription->getPositionX() + move);
		jumpDescription->setPositionX(jumpDescription->getPositionX() + move);
	}
	else
	{
		uiDescription->setPosition(posCenter);
		jumpDescription->setPositionX(posCenter.x * 3);
		this->unschedule(schedule_selector(HowTo::moveImageLeft));
	}
}

void HowTo::moveImageRight(float dt)
{
	auto uiDescription = (Sprite*)this->getChildByTag(1);
	auto jumpDescription = (Sprite*)this->getChildByTag(2);

	if (jumpDescription->getPositionX() > posCenter.x)
	{
		uiDescription->setPositionX(uiDescription->getPositionX() + move);
		jumpDescription->setPositionX(jumpDescription->getPositionX() + move);
	}
	else
	{
		jumpDescription->setPosition(posCenter);
		uiDescription->setPositionX(-posCenter.x);
		this->unschedule(schedule_selector(HowTo::moveImageRight));
	}
}

void HowTo::returnTitle()
{
	this->unschedule(schedule_selector(HowTo::goTitleTimer));
	Director::getInstance()->replaceScene(TransitionFade::create(3.0f, Title::createScene(), Color3B::WHITE));
}

void HowTo::switchText()
{
	auto label = (Label*)this->getChildByTag(4);
	if (label->getString() == RETRUN_TITLE_FROM_HOWTO)
	{
		label->setString(HOW_TO_ANNOTATION);
	}
	else
	{
		label->setString(RETRUN_TITLE_FROM_HOWTO);
	}
}

std::string setPageNo(int pageNum)
{
	return "(" + StringUtils::toString(pageNum) + "/2)";
}