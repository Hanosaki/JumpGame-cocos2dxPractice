#ifndef __SOUND_H__
#define __SOUND_H__

#include "cocos2d.h"

class Sound
{
public:
	Sound(std::string csvFile);//指定されたCSVに記述されている音声データをプリロードする。
	static int playSE(std::string seKey, float volume);
	static void stopSounds();
};

#endif