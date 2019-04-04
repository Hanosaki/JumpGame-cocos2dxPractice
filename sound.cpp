#include "sound.h"
#include "FileReadClass.h"
#include "CharaResouse.h"
#include "AudioEngine.h"

USING_NS_CC;
using namespace experimental;

Sound::Sound(std::string csvPostion,std::string seKey)
{
	auto seNames = FileRead::sReadFile(SE_POINT_CSV);
	auto seName = seNames[seKey];
	AudioEngine::preload(seName);
}

Sound::~Sound()
{
	AudioEngine::stopAll();
	AudioEngine::uncacheAll();
}

int Sound::playSE(std::string seKey,float volume)
{
	auto seNames = FileRead::sReadFile(SE_POINT_CSV);
	auto seName = seNames[seKey];
	return AudioEngine::play2d(seName, false, volume, nullptr);
}

void Sound::stopSounds()
{
	AudioEngine::stopAll();
}