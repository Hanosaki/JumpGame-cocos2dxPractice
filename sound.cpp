#pragma execution_character_set("utf-8")
#include "sound.h"
#include "FileReadClass.h"
#include "CharaResouse.h"
#include "AudioEngine.h"
#include "Converter.h"

#define ERROR "ファイルを発見できませんでした"
USING_NS_CC;
using namespace experimental;

Sound::Sound(std::string csvFile)
{
	auto seNames = FileRead::sReadFile(csvFile);
	for(auto seName : seNames)
	{
		AudioEngine::preload(seName.second.asString());
	}
}

int Sound::playSE(std::string seKey,float volume)
{
	auto seNames = FileRead::sReadFile(SE_POINT_CSV);
	auto seName = seNames[seKey].asString();
	if (seName.size() <= 0)
	{
		std::string errorMessage = ERROR;
		throw errorMessage;
	}
		return AudioEngine::play2d(seName, false, volume, nullptr);
}
int Sound::playBGM(std::string bgmKey, float volume)
{
	auto bgmNames = FileRead::sReadFile(BGM_POINT_CSV);
	auto bgm = bgmNames[bgmKey].asString();
	if (bgm.size() <= 0)
	{
		std::string errorMessage = ERROR;
		throw errorMessage;
	}
		return AudioEngine::play2d(bgm, true, volume, nullptr);
}

void Sound::stopSound()
{
	AudioEngine::stopAll();//音声全停止
}

void Sound::stopSound(int audioID)
{
	AudioEngine::stop(audioID);
}