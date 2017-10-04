#pragma execution_character_set("utf-8")
#include "ResouceLoadScene.h"
#include "Title.h"
#include "CharaResouse.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

Scene* ResouceLoad::creatScene()
{
	auto scene = Scene::create();
	auto layer = ResouceLoad::create();
	scene->addChild(layer);
	return scene;
}

bool ResouceLoad::init()
{
	if (!Layer::init())
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	progress = 0;
	animationNum = 0;

	//ロード画面SEのプリロード
	SimpleAudioEngine::getInstance()->preloadEffect(LOAD_SE);

	progressLabel = Label::createWithTTF(LOAD_MESSEAGE + 
		StringUtils::toString(progress) + "%",F_FONTS + JPN_FONTS,48);
	progressLabel->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
	this->addChild(progressLabel);

	SimpleAudioEngine::getInstance()->playEffect(LOAD_SE);

#pragma region 音素材のプリロード
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(OP_BGM);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MAIN_BGM);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(TITLE_BGM);
	SimpleAudioEngine::getInstance()->preloadEffect(DAMEGE_VOICE);
	SimpleAudioEngine::getInstance()->preloadEffect(RIVAL_VOICE);
	SimpleAudioEngine::getInstance()->preloadEffect(START_VOICE);
	SimpleAudioEngine::getInstance()->preloadEffect(BUTTON_SE);
	SimpleAudioEngine::getInstance()->preloadEffect(BUTTON_SE);
#pragma endregion

	/*画像データのキャッシュ作成*/
	auto cache = Director::getInstance()->getTextureCache();
	cache->addImage(F_MAIN_CHARACTER + CHARACTER_JUMP);
	cache->addImage(F_MAIN_CHARACTER + CHARACTER_DAMAGE);
	cache->addImage(F_MAIN_CHARACTER + F_IMAGE + SAD);
	cache->addImage(F_RIVAL + SMILE);
	cache->addImage(F_IMAGE + OP_BACK_GROUND);

	this->schedule(schedule_selector(ResouceLoad::setResouseCache), 0.1f,Parameter::ANIMATION_MAX_NUM-1,0.01f);

	return true;

}

void ResouceLoad::setResouseCache(float dt)
{
	auto cache = Director::getInstance()->getTextureCache()
		->addImage(F_ANIMATION + F_RUN + StringUtils::toString(animationNum) + ".png");
	progress = ((float)animationNum / (Parameter::ANIMATION_MAX_NUM - 1)) * 100;
	progressLabel->setString(LOAD_MESSEAGE + StringUtils::toString((int)progress) + "%");
	if (animationNum >= Parameter::ANIMATION_MAX_NUM-1)
	{
		if (cache)
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Title::creatScene(), Color3B::WHITE));
		else
			progressLabel->setString(RESOUCE_ERROR);
	}
	++animationNum;
}