﻿#pragma execution_character_set("utf-8")
#include "ResouceLoadScene.h"
#include "Title.h"
#include "CharaResouse.h"
#include "AudioEngine.h"
#include "Converter.h"

USING_NS_CC;
using namespace experimental;

Scene* ResouceLoad::createScene()
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
	auto con = new Converter();

	//ロード画面SEのプリロード
	auto audio = new AudioEngine();
	audio->preload(con->replaceDATtoMP3(F_SE + LOAD_SE));

	progressLabel = Label::createWithTTF(LOAD_MESSEAGE + 
		StringUtils::toString(progress) + "%",F_FONTS + JPN_FONTS,48);
	progressLabel->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(progressLabel);

#pragma region 音素材のプリロード&ロード中音声再生


#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)//Windowsの処理

	audio->play2d(con->replaceString2Char(F_SE + LOAD_SE + TYPE_MP3),false,0.5f,nullptr);

	audio->preload(con->replaceDATtoMP3(F_BGM + OP_BGM));
	audio->preload(con->replaceDATtoMP3(F_BGM + MAIN_BGM));
	audio->preload(con->replaceDATtoMP3(F_BGM + TITLE_BGM));
	audio->preload(con->replaceDATtoMP3(F_SE + DAMEGE_VOICE));
	audio->preload(con->replaceDATtoMP3(F_SE + RIVAL_VOICE));
	audio->preload(con->replaceDATtoMP3(F_SE + START_VOICE));
	audio->preload(con->replaceDATtoMP3(F_SE + BUTTON_SE));
	audio->preload(con->replaceDATtoMP3(F_SE + JUMP_SE));
	audio->preload(con->replaceDATtoMP3(F_SE + JUMP_SE2));
	audio->preload(con->replaceDATtoMP3(F_SE + ALERT_SE));

#elif(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)//Androidの場合

	audio->preload(F_SE + LOAD_SE+ TYPE_MP3);
	audio->play2d(F_SE + LOAD_SE + TYPE_MP3);

	audio->preload(F_BGM + OP_BGM + TYPE_MP3);
	audio->preload(F_BGM + OP_BGM + TYPE_MP3);
	audio->preload(F_BGM + OP_BGM + TYPE_MP3);
	audio->preload(F_SE + DAMEGE_VOICE + TYPE_MP3);
	audio->preload(F_SE + RIVAL_VOICE + TYPE_MP3);
	audio->preload(F_SE + START_VOICE + TYPE_MP3);
	audio->preload(F_SE + BUTTON_SE + TYPE_MP3);
	audio->preload(F_SE + JUMP_SE + TYPE_MP3);
	audio->preload(F_SE + JUMP_SE2 + TYPE_MP3);
	audio->preload(F_SE + ALERT_SE + TYPE_MP3);
#endif

#pragma endregion

	/*画像データのキャッシュ作成*/
	auto cache = Director::getInstance()->getTextureCache();
	cache->addImage(F_IMAGE + F_MAIN_CHARACTER + CHARACTER_JUMP);
	cache->addImage(F_IMAGE + F_MAIN_CHARACTER + DAMAGE_ANIME);
	cache->addImage(F_IMAGE + F_MAIN_CHARACTER + SAD);
	cache->addImage(F_IMAGE + F_MAIN_CHARACTER + SURPRISE);
	cache->addImage(F_IMAGE + F_RIVAL + SMILE);
	cache->addImage(F_IMAGE + F_UI +OP_BACK_GROUND);

	this->schedule(schedule_selector(ResouceLoad::loadAnimeCache), 0.1f, Parameter::ANIMATION_MAX_NUM - 1, 0.01f);

	return true;

}

void ResouceLoad::loadAnimeCache(float dt)
{
	auto cache = Director::getInstance()->getTextureCache()
		->addImage(F_IMAGE + F_ANIMATION + F_RUN + StringUtils::toString(animationNum) + ".png");//アニメーション画像のキャッシュを作成
	progress = ((float)animationNum / (Parameter::ANIMATION_MAX_NUM - 1)) * 100;
	progressLabel->setString(LOAD_MESSEAGE + StringUtils::toString((int)progress) + "%");
	if (animationNum >= Parameter::ANIMATION_MAX_NUM-1)
	{
		if (cache)//キャッシュの生成に成功した場合、タイトル画面へ
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Title::createScene(), Color3B::WHITE));
		else//キャッシュの生成に失敗した場合、エラー表示へ
			progressLabel->setString(RESOUCE_ERROR);
	}
	++animationNum;
}