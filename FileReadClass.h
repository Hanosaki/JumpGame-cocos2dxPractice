#ifndef __FILE_READ_CLASS_H__
#define __FILE_READ_CLASS_H__

/*-------
ファイル読み込み用クラス
---------*/

#include "cocos2d.h"

class FileRead
{
public:
	cocos2d::ValueVector readCSV(const char* fileName);//csvファイルを読み込む用の関数
	static std::map <std::string, std::string> FileRead::sReadFile(std::string fileName);//縦2行のcsvを連想配列に格納するための関数
	static std::map <std::string, int> FileRead::iReadFile(std::string fileName);//縦2行のcsvを連想配列に格納するための関数


private:
	static cocos2d::ValueVector split(const std::string str, const std::string &delim);//文字列を切り取るための関数
	static std::string readString(std::string &fileName);//指定されたファイルから文字列を読み込む関数
};

#endif