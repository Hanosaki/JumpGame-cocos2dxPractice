#pragma execution_character_set("utf-8")
#include "FileReadClass.h"
#include "GenericFunction.h"

USING_NS_CC;

const int ZERO = 0;

ValueVector FileRead::readCSV(const char* fileName)
{
	ValueVector charcterWords;//複数行のValueMapを格納するベクトル配列
	std::string csvStr = FileUtils::getInstance()->getStringFromFile(fileName);
	ValueVector balls = this->split(csvStr,"\n");//一行ごとに文字列を読み込む
	ValueVector keys = this->split(balls.at(ZERO).asString(), ",");	//連想配列キーを設定
	balls.erase(balls.begin());//連想配列のKeyが記入されている部分を削除

	//セル毎に変数へ格納
	for(auto var : balls)
	{
		ValueMap words;//一行の文章をそれぞれの要素に分けて格納する連想配列
		auto wordVector = split(var.asString(), ",");//カンマ区切りで文字列のベクトル配列を作成
		for(int j = ZERO; j < (int)wordVector.size(); ++j)//区切られた文字列を連想配列に格納
			words[keys.at(j).asString()] = wordVector.at(j).asString();
		charcterWords.push_back((Value)words);//連想配列をベクトル配列に追加
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

ValueMap FileRead::sReadFile(std::string fileName)
{
	ValueMap words;
	Map < std::string, Sprite*> hoge;
	auto file = readString(fileName);
	auto rows = split(file, "\n");
	for (auto var : rows)
	{
		auto row = split(var.asString(), ",");
		auto stringParam = row.at(1).asString();
		if (stringParam.rfind("\r") != std::string::npos )
			stringParam.erase(stringParam.size() - 1, stringParam.size());
		words[row.at(0).asString()] = stringParam;
	}

	return words;

}

ValueMap FileRead::iReadFile(std::string fileName)
{
	ValueMap parameter;
	auto file = readString(fileName);
	ValueVector rows = split(file, "\n");
	for (auto var : rows)
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