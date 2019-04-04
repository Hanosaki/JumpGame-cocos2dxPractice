#ifndef __FILE_READ_CLASS_H__
#define __FILE_READ_CLASS_H__

/*-------
�t�@�C���ǂݍ��ݗp�N���X
---------*/

#include "cocos2d.h"

class FileRead
{
public:
	cocos2d::ValueVector readCSV(const char* fileName);//csv�t�@�C����ǂݍ��ޗp�̊֐�
	static std::map <std::string, std::string> FileRead::sReadFile(std::string fileName);//�c2�s��csv��A�z�z��Ɋi�[���邽�߂̊֐�
	static std::map <std::string, int> FileRead::iReadFile(std::string fileName);//�c2�s��csv��A�z�z��Ɋi�[���邽�߂̊֐�


private:
	static cocos2d::ValueVector split(const std::string str, const std::string &delim);//�������؂��邽�߂̊֐�
	static std::string readString(std::string &fileName);//�w�肳�ꂽ�t�@�C�����當�����ǂݍ��ފ֐�
};

#endif