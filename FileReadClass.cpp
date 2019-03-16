#pragma execution_character_set("utf-8")
#include "FileReadClass.h"

USING_NS_CC;

const int ZERO = 0;

ValueVector FileRead::readCSV(const char* fileName)
{
	ValueVector charcterWords;
	std::string csvStr = FileUtils::getInstance()->getStringFromFile(fileName);
	ValueVector balls = this->split(csvStr,"\n");//一列ごとに切り分けて読み込み
	ValueVector keys = this->split(balls.at(ZERO).asString(), ",");	//行ごとの属性付の為のキーを設定
	balls.erase(balls.begin());//属性付用のデータの削除

	//セル毎に変数へ格納
	for each (auto var in balls)
	{
		ValueMap wordMap;
		ValueVector wordVector = split(var.asString(), ",");
		for(int j = ZERO; j < (int)wordVector.size(); ++j)
			wordMap[keys.at(j).asString()] = wordVector.at(j).asString();
		charcterWords.push_back((Value)wordMap);
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