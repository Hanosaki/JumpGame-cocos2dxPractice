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
	char* replaceDATtoMP3(std::string relativePath);//Windows Only!
	char* replaceMP3toDAT(std::string relativePath);//Windows Only!
	char* replaceString2Char(std::string);
	void replaceALLMP3toDAT();//Windows Only!
};


#endif