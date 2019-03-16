#ifndef __FILE_READ_CLASS_H__
#define __FILE_READ_CLASS_H__

/*-------
ファイル読み込み用クラス
*/

#include "cocos2d.h"

class FileRead
{
public:
	cocos2d::ValueVector readCSV(const char* fileName);//csvファイルを読み込む用の関数
	cocos2d::ValueVector split(const std::string str, const std::string &delim);//文字列を切り取るための関数
};

#endif