#pragma execution_character_set("utf-8")
#include "Converter.h"
#include "CharaResouse.h"
#include "FileReadClass.h"
#include "GenericFunction.h"

USING_NS_CC;

void replaceSet(std::string& path, std::string& sFileName, std::string& tmpPath);
char* setVoiceName(ValueMap valueMap);
std::string searceVoice(ValueMap valueMap);


char* Converter::replaceDATtoMP3(std::string relativePath)
{
	auto fileUtils = FileUtils::getInstance();
	auto path = fileUtils->fullPathForFilename(relativePath + TYPE_DAT);
	auto sFileName = StringUtils::toString(relativePath + TYPE_DAT);
	
	//datでパスが見つかった場合，変換処理を行う
	if (path != "")
	{
		std::string tmpPath; 
		replaceSet(path,sFileName,tmpPath);
		auto fileUtil = FileUtils::getInstance();
		if (fileUtil->renameFile(path, sFileName + TYPE_DAT, sFileName + TYPE_MP3))
		{
			sFileName = tmpPath + sFileName + TYPE_MP3;
			auto returnFileName = new char[sFileName.length() + 1];
			memcpy(returnFileName, sFileName.c_str(), sFileName.length() + 1);
			return returnFileName;
		}
		else
		{
			return "ConvertFeild!";
		}
	}
	else //datが見つからない場合，もともとmp3の可能性があるため確認
	{	
		path = fileUtils->fullPathForFilename(relativePath+TYPE_MP3);
		if (path != "")
		{
			//見つかった場合，mp3のファイルpathを返す
			auto returnFileName = new char[sFileName.length() + 1];
			memcpy(returnFileName, sFileName.c_str(), sFileName.length() + 1);
			return returnFileName;
		}
		else
			return "FileNotFound!";
	}
}

char* Converter::replaceMP3toDAT(std::string relativePath)
{
	auto file = FileUtils::getInstance();
	auto path = file->fullPathForFilename(relativePath + TYPE_MP3);

	if (path != ""){
		auto sFileName = StringUtils::toString(relativePath + TYPE_MP3);
		std::string tmpPath;
		replaceSet(path, sFileName, tmpPath);
		auto fileUtil = FileUtils::getInstance();
		if (fileUtil->renameFile(path, sFileName +TYPE_MP3, sFileName + TYPE_DAT))
		{
			sFileName = tmpPath + sFileName + TYPE_DAT;
			auto returnFileName = new char[sFileName.length() + 1];
			memcpy(returnFileName, sFileName.c_str(), sFileName.length() + 1);
			return returnFileName;
		}
		else
		{
			return "ConvertFeild!";
		}
	}
	else
	{
		return "FileNotFound!";
	}
}

char* Converter::replaceString2Char(std::string str)
{
	auto returnFileName = new char[str.length() + 1];
	memcpy(returnFileName, str.c_str(), str.length() + 1);
	return returnFileName;
}

//暗号化処理
void Converter::replaceALLMP3toDAT()
{
	replaceMP3toDAT(F_BGM + OP_BGM);
	replaceMP3toDAT(F_BGM + MAIN_BGM);
	replaceMP3toDAT(F_BGM + TITLE_BGM);
	replaceMP3toDAT(F_SE + LOAD_SE);
	replaceMP3toDAT(F_SE + LOGO_SE);
	replaceMP3toDAT(F_SE + DAMEGE_VOICE);
	replaceMP3toDAT(F_SE + RIVAL_VOICE);
	replaceMP3toDAT(F_SE + START_VOICE);
	replaceMP3toDAT(F_SE + BUTTON_SE);
	replaceMP3toDAT(F_SE + JUMP_SE);
	replaceMP3toDAT(F_SE + JUMP_SE2);
	replaceMP3toDAT(F_SE + ALERT_SE);
	replaceMP3toDAT(F_SE + GAMEOVER_SE);
	FileRead fileRead;
	int wordsNum = 0;
	auto characterWordVector = fileRead.readCSV(CONVERSATION_LIST);
	auto characterWordMap = characterWordVector.at(wordsNum).asValueMap();
	for (int i = 0; i < characterWordVector.size(); ++i)
	{
		GenericFunc genericFunc;
		characterWordMap = characterWordVector.at(i).asValueMap();
		auto voiceName = genericFunc.setVoiceName(characterWordMap);
		if (strcmp(voiceName, "0"))
			replaceMP3toDAT(voiceName);
	}
}

void replaceSet(std::string& path, std::string& sFileName, std::string& tmpPath)
{
	if (sFileName.find("BGM") != std::string::npos)
	{
		tmpPath = F_BGM;
		sFileName.replace(0, 4, "");
	}
	else
	{
		tmpPath = F_SE;
		sFileName.replace(0, 3, "");
	}

	for (int i = 0; i < sFileName.length(); ++i)
	{
		path.pop_back();
	}

	for (int i = 0; i < 4; ++i)
	{
		sFileName.pop_back();
	}
}