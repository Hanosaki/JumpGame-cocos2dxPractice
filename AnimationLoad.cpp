#include "AnimationLoad.h"
#include "CharaResouse.h"
#include "MenuWindow.h"
#include "FileReadClass.h"

USING_NS_CC;

void AnimationLoad::load()
{
	auto al = new AnimationLoad();
	al->animeLoad();
}

void AnimationLoad::animeLoad()
{
	auto parameter = FileRead::iReadFile(PARAMETER_INI);
	auto cache = Director::getInstance();
	for (int animeNum = 0; animeNum < parameter["ANIMATION_MAX_NUM"]; ++animeNum)
	{
		cache->getTextureCache()
			->addImage(F_IMAGE + F_ANIMATION + F_RUN + StringUtils::toString(animeNum) + ".png");//アニメーション画像のキャッシュを作成
	}

	if (!cache)//キャッシュの生成に失敗した場合、エラー表示へ
		throw RESOUCE_ERROR;
}