#pragma execution_character_set("utf-8")
#include "FileReadClass.h"

USING_NS_CC;

const int ZERO = 0;

ValueVector FileRead::readCSV(const char* fileName)
{
	ValueVector charcterWords;
	std::string csvStr = FileUtils::getInstance()->getStringFromFile(fileName);
	ValueVector balls = this->split(csvStr,"\n");//��񂲂Ƃɐ؂蕪���ēǂݍ���
	ValueVector keys = this->split(balls.at(ZERO).asString(), ",");	//�s���Ƃ̑����t�ׂ̈̃L�[��ݒ�
	balls.erase(balls.begin());//�����t�p�̃f�[�^�̍폜

	//�Z�����ɕϐ��֊i�[
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