#ifndef __FILE_READ_CLASS_H__
#define __FILE_READ_CLASS_H__

/*-------
�t�@�C���ǂݍ��ݗp�N���X
*/

#include "cocos2d.h"

class FileRead
{
public:
	cocos2d::ValueVector readCSV(const char* fileName);//csv�t�@�C����ǂݍ��ޗp�̊֐�
	cocos2d::ValueVector split(const std::string str, const std::string &delim);//�������؂��邽�߂̊֐�
};

#endif