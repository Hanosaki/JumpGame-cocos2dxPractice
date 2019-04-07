#pragma execution_character_set("utf-8")
#include "ResouceLoadScene.h"
#include "Title.h"
#include "CharaResouse.h"
#include "Converter.h"
#include "sound.h"
#include "MenuWindow.h"
#include "FileReadClass.h"

USING_NS_CC;

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
	auto se = new Sound(SE_POINT_CSV);
	progressLabel = Label::createWithTTF(LOAD_MESSEAGE +
		StringUtils::toString(progress) + "%", F_FONTS + JPN_FONTS, 48);
	progressLabel->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(progressLabel);


#pragma region 音素材のプリロード&ロード中音声再生

	se->playSE("LOAD", 0.3f);
	auto bgm = new Sound(BGM_POINT_CSV);

#pragma endregion

	Node* node = Node::create();

	auto parameter = FileRead::iReadFile(PARAMETER_INI);

	/*画像データのキャッシュ作成*/
	auto cache = Director::getInstance()->getTextureCache();
	cache->addImage(F_IMAGE + F_MAIN_CHARACTER + CHARACTER_JUMP);
	cache->addImage(F_IMAGE + F_MAIN_CHARACTER + DAMAGE_ANIME);
	cache->addImage(F_IMAGE + F_MAIN_CHARACTER + SAD);
	cache->addImage(F_IMAGE + F_MAIN_CHARACTER + SURPRISE);
	cache->addImage(F_IMAGE + F_RIVAL + SMILE);
	cache->addImage(F_IMAGE + F_UI + OP_BACK_GROUND);
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Title::createScene(), Color3B::WHITE));

	return true;

}