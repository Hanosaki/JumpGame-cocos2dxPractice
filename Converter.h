#ifndef __CONVERTER_H__
#define __CONVERTER_H__

#include "cocos2d.h"

/// <summary>
/// ���l�[���Cstring��char*�ϊ����s���N���X
/// �ꕔWindows�݂̂œ��삷�邽�߁CWindows�ȊO�̊��ł͎g�p���Ȃ�����
/// </summary>

class Converter
{
public:
	Converter();
	static char* replaceDATtoMP3(std::string relativePath);//dat�t�@�C���̊g���q��mp3�Ƀ��l�[������AAndroid�ł͓��삵�Ȃ�
	static char* replaceMP3toDAT(std::string relativePath);//mp3�t�@�C���̊g���q��dat�Ƀ��l�[������AAndroid�ł͓��삵�Ȃ�
	static char* replaceString2Char(std::string);//string�������char�z��ɒu��������A��o�C�g������Ή�
	static void replaceALLMP3toDAT();//�g�p����Ă��邷�ׂĂ�mp3�t�@�C���̊g���q��dat�Ƀ��l�[������
};


#endif