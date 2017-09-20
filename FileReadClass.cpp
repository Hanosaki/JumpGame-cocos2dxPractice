#pragma execution_character_set("utf-8")
#include "FileReadClass.h"

USING_NS_CC;

const int ZERO = 0;

ValueVector FileRead::readCSV(const char* fileName)
{
	ValueVector charcterWords;
	std::string csvStr = FileUtils::getInstance()->getStringFromFile(fileName);
	ValueVector balls = this->split(csvStr,"\n");
	ValueVector keys = this->split(balls.at(ZERO).asString(), ",");
	for (int i = 1; i < (int)balls.size(); ++i)
	{
		ValueMap words;
		ValueVector wordList = this->split(balls.at(i).asString(), ",");
		for (int j = ZERO; j < (int)wordList.size(); ++j)
			words[keys.at(j).asString()] = wordList.at(j).asString();
		charcterWords.push_back((Value)words);
	}
	return charcterWords;
}

ValueVector FileRead::split(const std::string str, const std::string &delim)
{
	ValueVector res;
	size_t current = ZERO, found;
	while ((found = str.find_first_of(delim, current)) != std::string::npos)
	{
		res.push_back(Value(std::string(str, current, found - current)));
		current = found + 1;
	}
	res.push_back(Value(std::string(str, current, str.size() - current)));
	return res;
}
