#ifndef __SOUND_H__
#define __SOUND_H__

/*
音声再生を行うクラス
*/

#include "cocos2d.h"

class Sound
{
public:
	Sound(std::string csvFile);//指定されたCSVに記述されている音声データをプリロードする。
	static int playSE(std::string seKey, float volume);//指定された音声を再生する
	static void stopSound();//再生している音声をすべて停止する
	static void stopSound(int audioID);//受け取ったIDの再生を停止する
};

#endif