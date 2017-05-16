#pragma execution_character_set("utf-8")
#include "GameScene.h"
#include "GameoverScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

void nextScene();

Scene* Game::creatScene()
{
	auto scene = Scene::create();
	auto layer = Game::create();
	scene->addChild(layer);
	return scene;
}

bool Game::init()
{

	if (!Layer::init())
	{
		return false;
	}

#pragma region �O���[�o���ϐ��̏�����
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	score = 0;
	hitCounter = 0;
	endFlag = false;
	hitOnlyOne = false;
	defoultPos = Vec2(visibleSize.width / 7 + origin.x, visibleSize.height / 5 + origin.y);
	enemyDefaultPos = Vec2(3 * visibleSize.width / 2 + origin.x, visibleSize.height / 6 + origin.y);

#pragma endregion

#pragma region BGM�̐ݒ�
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("BGM.mp3");
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0f);
#pragma endregion

#pragma region SE�̐ݒ�
	SimpleAudioEngine::getInstance()->preloadEffect("damage.mp3");
	SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);
#pragma endregion

#pragma region �X�R�A����
	label = Label::createWithTTF("score:" + StringUtils::toString(score), "fonts/Marker Felt.ttf", 24);
	label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - label->getContentSize().height));
	this->addChild(label,1);
#pragma endregion

#pragma region �w�i�����ݒ�
	auto backGround = Sprite::create("bg.png");
	backGround->setContentSize(Director::getInstance()->getVisibleSize());
	backGround->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
	backGround->setTag(51);
	this->addChild(backGround);

	auto backGround2 = Sprite::create("bg.png");
	backGround2->setContentSize(backGround->getContentSize());
	backGround2->setPosition(visibleSize.width + visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
	backGround2->setTag(52);
	this->addChild(backGround2);
#pragma endregion

#pragma region �����G�w�i�̏����ݒ�
	auto whiteBack = Sprite::create("whiteBack.png");
	whiteBack->setContentSize((Size)Vec2(visibleSize.width/5+origin.x,visibleSize.height+origin.y));
	whiteBack->setPosition(visibleSize.width + origin.x -
							whiteBack->getContentSize().width / 2, visibleSize.height / 2 + origin.y);
	this->addChild(whiteBack, 2);	
#pragma endregion

#pragma region ��l��(SD)�X�v���C�g�̏����ݒ�
	auto mainCharactor = Sprite::create("Normal.png");
	mainCharactor->setScale((visibleSize.height + origin.y) / (mainCharactor->getContentSize().height*3));
	mainCharactor->setPosition(defoultPos);
	mainCharactor->setTag(1);
	this->addChild(mainCharactor);
	auto flip = FlipX::create(true);//���E���]����
	mainCharactor->runAction(flip);
#pragma endregion

#pragma region ��l��(�����G)�̏����ݒ�
	auto characterImage = Sprite::create("1.png");
	characterImage->setScale((visibleSize.height + origin.y) / (characterImage->getContentSize().height));
	characterImage->setPosition(visibleSize.width + origin.x - (characterImage->getContentSize().width / 4 * characterImage->getScale())
						,visibleSize.height/2+origin.y) ;
	characterImage->setTag(2);
	this->addChild(characterImage,3);
#pragma endregion

#pragma region �G�̏����ݒ�
	auto enemy = Sprite::create("enemy.png");
	enemy->setPosition(enemyDefaultPos);
	enemy->setScale((visibleSize.height+origin.y) / (enemy->getContentSize().height*3));
	enemy->setTag(11);
	this->addChild(enemy);
#pragma endregion

#pragma region �N���b�N���X�i�[�̏����ݒ�
	auto listner = EventListenerTouchOneByOne::create();
	listner->onTouchBegan = CC_CALLBACK_2(Game::onTouchBegan, this);
	listner->onTouchEnded = CC_CALLBACK_2(Game::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listner, this);
#pragma endregion

#pragma region BGM�Đ�
	SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM.mp3",true);
#pragma endregion

#pragma region �J��Ԃ������̏����ݒ�
	this->runAction(Sequence::create(DelayTime::create(1), 
		CallFunc::create([this](){this->scheduleUpdate(); }), NULL));
#pragma endregion

	return true;
}

bool Game::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
#pragma region �W�����v����
	if (!endFlag)
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto origin = Director::getInstance()->getVisibleOrigin();
		auto maxPoint = Point(defoultPos.x, origin.y + 4 * visibleSize.height / 5);
		/*auto defaultPointed = Point(defoultPos);*/
		/*�A�N�V�����̍쐬*/
		auto moveUp = MoveTo::create(0.73f, maxPoint);
		auto moveDown = MoveTo::create(0.73f, defoultPos);
		/*�X�v���C�g�̍쐬*/
		auto mainCharactor = (Sprite*)this->getChildByTag(1);
		/*�A�j���[�V������Ԃ̊m�F*/
		if (mainCharactor->numberOfRunningActions() == 0){
			mainCharactor->setTexture("JUMP.png");
			/*�V�[�N�G���X�쐬*/
			auto sequence = Sequence::create(moveUp, moveDown, NULL);
			//�A�j���[�V�����J�n
			mainCharactor->runAction(sequence);
		}
	}
	else
	{
		Director::getInstance()->replaceScene(GameOver::creatScene());
	}
#pragma endregion
	return true;
}

void Game::update(float dt)
{
#pragma region �ϐ��̐錾
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto visibleOrigin = Director::getInstance()->getVisibleOrigin();
	auto moveVec = Vec2(-5.5f, 0);
	auto backGround = this->getChildByTag(51);
	auto backGround2 = this->getChildByTag(52);
#pragma endregion

#pragma region �w�i�A�j���[�V����
	auto pos = backGround->getPosition();
	auto pos2 = backGround2->getPosition();
	pos += moveVec;
	pos2 += moveVec;

	if (pos.x + backGround->getContentSize().width / 2 < 0){
		pos = Vec2(visibleSize.width + 0.95*visibleSize.width / 2 + visibleOrigin.x, visibleSize.height / 2);
	}
	if (pos2.x + backGround2->getContentSize().width / 2 < 0){
		pos2 = Vec2(visibleSize.width + 0.95*visibleSize.width / 2 + visibleOrigin.x, visibleSize.height / 2);
	}
	backGround->setPosition(pos);
	backGround2->setPosition(pos2);
#pragma endregion

#pragma region �G�l�~�[�̍s��
	auto enemy = this->getChildByTag(11);
	auto enemyPos = enemy->getPosition();
	float rand = random(0.5f, 2.0f);
	enemyPos += 2 * moveVec*rand;
	if (enemyPos.x + enemy->getContentSize().width < 0){
		enemyPos = Vec2(enemyDefaultPos);
		++score;
		hitOnlyOne = false;
		label->setString("score:" + StringUtils::toString(score));
	}
	enemy->setPosition(enemyPos);
#pragma endregion

#pragma region �ڐG����
	auto mainCharactor = (Sprite*)this->getChildByTag(1);
	auto characterImage = (Sprite*)this->getChildByTag(2);
	auto rectmainCharactor = mainCharactor->getBoundingBox();
	auto rectEnemy = enemy->getBoundingBox();
	if (rectmainCharactor.intersectsRect(rectEnemy) && !hitOnlyOne){
		++hitCounter;
		SimpleAudioEngine::getInstance()->playEffect("damage.mp3");
		mainCharactor->setTexture("HIT.png");
		if (hitCounter >= 4)
		{
			auto gameoverLabel = Label::create();
			gameoverLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2);
			gameoverLabel->setScale(3.0f);
			gameoverLabel->setString("GameOver...");
			SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			this->addChild(gameoverLabel);
			this->unscheduleUpdate();
			mainCharactor->setTexture("HIT.png");
			mainCharactor->stopAllActions();
			UserDefault::sharedUserDefault()->setIntegerForKey("score", score);//�X�R�A�̕ۑ�
			UserDefault::sharedUserDefault()->flush();
			endFlag = true;
		}
		else
		{
			switch (hitCounter)
			{
			case 1:
				characterImage->setTexture("2.png"); hitOnlyOne = true; break;
			case 2:
				characterImage->setTexture("3.png"); hitOnlyOne = true; break;
			case 3:
				characterImage->setTexture("4.png"); hitOnlyOne = true;
			default:
				break;
			}
		}
	}
#pragma endregion

#pragma region �����G�̍X�V
	if (mainCharactor->getPosition() == defoultPos && !hitOnlyOne && mainCharactor->numberOfRunningActions() == 0 && !endFlag)
		mainCharactor->setTexture("Normal.png");
#pragma endregion
}

void nextScene()
{
	Director::getInstance()->replaceScene(GameOver::creatScene());
}