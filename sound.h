#ifndef __SOUND_H__
#define __SOUND_H__

#include "cocos2d.h"

class Sound
{
public:
	Sound(std::string csvFile);//�w�肳�ꂽCSV�ɋL�q����Ă��鉹���f�[�^���v�����[�h����B
	static int playSE(std::string seKey, float volume);
	static void stopSounds();
};

#endif