#ifndef __CONVERTER_H__
#define __CONVERTER_H__

#include "cocos2d.h"

/// <summary>
/// リネーム，string→char*変換を行うクラス
/// 一部Windowsのみで動作するため，Windows以外の環境では使用しないこと
/// </summary>

class Converter
{
public:
	Converter();
	static char* replaceDATtoMP3(std::string relativePath);//datファイルの拡張子をmp3にリネームする、Androidでは動作しない
	static char* replaceMP3toDAT(std::string relativePath);//mp3ファイルの拡張子をdatにリネームする、Androidでは動作しない
	static char* replaceString2Char(std::string);//string文字列をchar配列に置き換える、二バイト文字非対応
	static void replaceALLMP3toDAT();//使用されているすべてのmp3ファイルの拡張子をdatにリネームする
};


#endif