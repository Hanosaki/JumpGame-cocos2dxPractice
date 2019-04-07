#include "sound.h"
#include "FileReadClass.h"
#include "CharaResouse.h"
#include "AudioEngine.h"
#include "Converter.h"

USING_NS_CC;
using namespace experimental;

Sound::Sound(std::string csvFile)
{
	auto seNames = FileRead::sReadFile(csvFile);
	for each(auto i in seNames)
	{
		AudioEngine::preload(i.second);
	}
}

int Sound::playSE(std::string seKey,float volume)
{
	auto seNames = FileRead::sReadFile(SE_POINT_CSV);
	auto seName = seNames[seKey];
	return AudioEngine::play2d(seName, false, volume, nullptr);
}

void Sound::stopSound()
{
	AudioEngine::stopAll();//âπê∫ëSí‚é~
}

void Sound::stopSound(int audioID)
{
	AudioEngine::stop(audioID);
}