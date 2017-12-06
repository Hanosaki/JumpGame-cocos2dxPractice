#pragma execution_character_set("utf-8")
#include "Converter.h"
#include "CharaResouse.h"
#include "FileReadClass.h"
#include "GenericFunction.h"

USING_NS_CC;

void replaceSet(std::string& fullPath, std::string& sFileName, std::string& folderName);
char* setVoiceName(ValueMap valueMap);
std::string searceVoice(ValueMap valueMap);


char* Converter::replaceDATtoMP3(std::string relativePath)
{

	auto fileUtils = FileUtils::getInstance();
	auto sFileName = relativePath + TYPE_DAT;
	auto fullPath = fileUtils->fullPathForFilename(sFileName);

	//datでパスが見つかった場合，変換処理を行う
	if (fullPath != "")
	{
		std::string folderName; 
		replaceSet(fullPath,sFileName,folderName);
		auto fileUtil = FileUtils::getInstance();
		if (fileUtil->renameFile(fullPath, sFileName + TYPE_DAT, sFileName + TYPE_MP3))
		{
			sFileName = folderName + sFileName + TYPE_MP3;
			CCLOG("sFileName3 %s", sFileName.c_str());
			auto returnFileName = new char[sFileName.length() + 1];
			memcpy(returnFileName, sFileName.c_str(), sFileName.length() + 1);
			return returnFileName;
		}
		else
		{
			//ここでmp3の場合の処理を行う
			fullPath = fileUtils->fullPathForFilename(relativePath + TYPE_MP3);
			if (fullPath != "")
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
	else //ファイルが存在しない(既に変換済みの場合)
	{
		fullPath = fileUtils->fullPathForFilename(relativePath + TYPE_MP3);
		if (fullPath != "")
		{
			//見つかった場合，mp3のファイルpathを返す
			for (int i = 0; i < TYPE_DAT.length(); ++i)
				sFileName.pop_back();
			sFileName += TYPE_MP3;
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
	auto fullPath = file->fullPathForFilename(relativePath + TYPE_MP3);

	if (fullPath != ""){
		auto sFileName = StringUtils::toString(relativePath + TYPE_MP3);
		std::string folderName;
		replaceSet(fullPath, sFileName, folderName);
		auto fileUtil = FileUtils::getInstance();
		if (fileUtil->renameFile(fullPath, sFileName +TYPE_MP3, sFileName + TYPE_DAT))
		{
			sFileName = folderName + sFileName + TYPE_DAT;
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

void replaceSet(std::string& fullPath, std::string& sFileName, std::string& folderName)
{
	if (sFileName.find(F_VOICE) == std::string::npos)
	{

		if (sFileName.find(F_BGM) != std::string::npos)
		{
			folderName = F_BGM;
			sFileName.replace(0, 4, "");
		}
		else
		{
			folderName = F_SE;
			sFileName.replace(0, 3, "");
		}
	}
	else
	{
		if (sFileName.find(F_MAIN_CHARACTER) != std::string::npos)
		{
			folderName = F_SE + F_MAIN_CHARACTER + F_VOICE;
			sFileName.replace(0, folderName.length(), "");
		}
		else
		{
			folderName = F_SE + F_RIVAL + F_VOICE;
			sFileName.replace(0, folderName.length(), "");
		}
			
	}

	for (int i = 0; i < sFileName.length(); ++i)
	{
		fullPath.pop_back();
	}

	for (int i = 0; i < 4; ++i)
	{
		sFileName.pop_back();
	}
}