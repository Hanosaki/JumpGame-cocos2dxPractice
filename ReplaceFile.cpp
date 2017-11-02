#pragma execution_character_set("utf-8")
#include "ReplaceFile.h"
#include "CharaResouse.h"

USING_NS_CC;

char* FileConverter::replaceDATtoMP3(const char* fileName)
{
	auto file = FileUtils::getInstance();
	auto path = file->fullPathForFilename(fileName);
	if (path != ""){
		auto sFileName = StringUtils::toString(fileName);
		if (sFileName.find("BGM") != std::string::npos)
		{
			sFileName.replace(0, 4, "");
		}
		else
		{
			sFileName.replace(0, 3, "");
		}

		for (int i = 0; i < sFileName.length(); ++i)
		{
			path.pop_back();
		}

		for (int i = 0; i < 3; ++i)
		{
			sFileName.pop_back();
		}

		auto fileUtil = FileUtils::getInstance();
		if (fileUtil->renameFile(path, sFileName + "dat", sFileName + "mp3"))
		{
			sFileName += "mp3";
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