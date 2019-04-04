#ifndef __SOUND_H__
#define __SOUND_H__

#include "cocos2d.h"

class Sound
{
public:
	Sound(std::string csvPostion,std::string seKey);
	~Sound();
	static int playSE(std::string seKey, float volume);
	static void stopSounds();
};

#endif