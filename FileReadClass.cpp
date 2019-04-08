#pragma execution_character_set("utf-8")
#include "FileReadClass.h"
#include "GenericFunction.h"

USING_NS_CC;

const int ZERO = 0;

ValueVector FileRead::readCSV(const char* fileName)
{
	ValueVector charcterWords;//List型配列
	std::string csvStr = FileUtils::getInstance()->getStringFromFile(fileName);
	ValueVector balls = this->split(csvStr,"\n");//一列ごとに切り分けて読み込み
	ValueVector keys = this->split(balls.at(ZERO).asString(), ",");	//行ごとの属性付の為のキーを設定
	balls.erase(balls.begin());//属性付用のデータの削除

	//セル毎に変数へ格納
	for each (auto var in balls)
	{
		ValueMap wordMap;//連想配列
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

std::map<std::string, std::string> FileRead::sReadFile(std::string fileName)
{
	std::map<std::string, std::string>words;
//	cocos2d::Map<std::string, std::string> words;なんか使えなかったのに使えるようになってるから、こっちにすること
	auto file = readString(fileName);
	auto rows = split(file, "\n");
	for each (auto var in rows)
	{
		auto row = split(var.asString(), ",");
		auto stringParam = row.at(1).asString();
		if (stringParam.rfind("\r") != std::string::npos )
			stringParam.erase(stringParam.size() - 1, stringParam.size());
		words[row.at(0).asString()] = stringParam;
	}

	return words;

}

std::map < std::string, int> FileRead::iReadFile(std::string fileName)
{
	std::map<std::string, int>parameter;
	auto file = readString(fileName);
	ValueVector rows = split(file, "\n");
	for each (auto var in rows)
	{
		ValueVector row = split(var.asString(), "=");
		if (row.size() < 2)//空白行が読み込まれた場合、処理をスキップする
			break;
		parameter[row.at(0).asString()] =row.at(1).asInt();
	}
	return parameter;
}

std::string FileRead::readString(std::string &fileName)
{
	auto file = FileUtils::getInstance()->getStringFromFile(fileName);
	if (file.size() <= 0)
		throw "ファイルが正常に読み込めませんでした。";
	return file;
}