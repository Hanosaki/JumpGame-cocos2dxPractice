#ifndef __SOUND_H__
#define __SOUND_H__

/*
�����Đ����s���N���X
*/

#include "cocos2d.h"

class Sound
{
public:
	Sound(std::string csvFile);//�w�肳�ꂽCSV�ɋL�q����Ă��鉹���f�[�^���v�����[�h����B
	static int playSE(std::string seKey, float volume);//�w�肳�ꂽ�������Đ�����
	static void stopSound();//�Đ����Ă��鉹�������ׂĒ�~����
	static void stopSound(int audioID);//�󂯎����ID�̍Đ����~����
};

#endif