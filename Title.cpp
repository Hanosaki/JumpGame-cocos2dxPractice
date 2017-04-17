#pragma execution_character_set("utf-8")
#include "Title.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

Scene* Title::creatScene()
{
	auto scene = Scene::create();
	auto layer = Title::create();
	scene->addChild(layer);
	return scene;
}

bool Title::init()
{
	if (!Layer::init())
		return false;

#pragma region �ϐ��錾
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
#pragma endregion

#pragma region SE�p��
	SimpleAudioEngine::getInstance()->setEffectsVolume(0.5f);
	SimpleAudioEngine::getInstance()->preloadEffect("start.mp3");
#pragma endregion

#pragma region �^�C�g���\�L
	auto titleLabel = Label::createWithTTF("Yukari RUN", "fonts/Marker Felt.ttf", 64);
	titleLabel->setPosition(origin.x + visibleSize.width / 3, origin.y + (4 * visibleSize.height) / 5);
	this->addChild(titleLabel,4);
#pragma endregion

#pragma region pushStart�\�L
	auto pushText = Label::createWithTTF("push start...","fonts/Marker Felt.ttf",24);
	pushText->setPosition(origin.x + visibleSize.width / 3, origin.y + visibleSize.height / 6);
	this->addChild(pushText, 4);
	/*�����_�ŏ���*/
	auto action = FadeTo::create(0.9f,64);
	auto action2 = FadeTo::create(0.9f,255);
	auto seq = Sequence::create(action, action2, NULL);
	auto repeat = RepeatForever::create(seq);
	pushText->runAction(repeat);
#pragma endregion

#pragma region �w�i�錾
	auto backGround = Sprite::create("bg.png");
	backGround->setContentSize(Director::getInstance()->getVisibleSize());
	backGround->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
	this->addChild(backGround,1);
#pragma endregion

#pragma region �����G�w�i�̏����ݒ�
	auto whiteBack = Sprite::create("whiteBack.png");
	whiteBack->setContentSize((Size)Vec2(visibleSize.width / 5 + origin.x, visibleSize.height + origin.y));
	whiteBack->setPosition(visibleSize.width + origin.x -
		whiteBack->getContentSize().width / 2, visibleSize.height / 2 + origin.y);
	this->addChild(whiteBack, 2);
#pragma endregion

#pragma region ��l��(�����G)�̏����ݒ�
	auto yukari = Sprite::create("1.png");
	yukari->setScale((visibleSize.height + origin.y) / (yukari->getContentSize().height));
	yukari->setPosition(visibleSize.width + origin.x - (yukari->getContentSize().width / 4 * yukari->getScale())
		, visibleSize.height / 2 + origin.y);
	yukari->setTag(2);
	this->addChild(yukari, 3);
#pragma endregion

#pragma region �N���b�N���X�i�[
	auto listner = EventListenerTouchOneByOne::create();
	listner->onTouchBegan = CC_CALLBACK_2(Title::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listner, this);
#pragma endregion

	return true;
}

bool Title::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	auto yukari = (Sprite*)this->getChildByTag(2);
	yukari->setTexture("start.png");
	SimpleAudioEngine::getInstance()->playEffect("start.mp3");
	//TransitionFade(�t�F�[�h���ԁC�ړ���̃V�[���C�t�F�[�h�A�E�g�̐F)
	Director::getInstance()->replaceScene(TransitionFade::create(0.6f, Game::creatScene(), Color3B::WHITE));
	return true;
}