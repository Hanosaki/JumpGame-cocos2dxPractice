#pragma execution_character_set("utf-8")
#include "FileReadClass.h"
#include "GenericFunction.h"

USING_NS_CC;

const int ZERO = 0;

ValueVector FileRead::readCSV(const char* fileName)
{
	ValueVector charcterWords;//�����s��ValueMap���i�[����x�N�g���z��
	std::string csvStr = FileUtils::getInstance()->getStringFromFile(fileName);
	ValueVector balls = this->split(csvStr,"\n");//��s���Ƃɕ������ǂݍ���
	ValueVector keys = this->split(balls.at(ZERO).asString(), ",");	//�A�z�z��L�[��ݒ�
	balls.erase(balls.begin());//�A�z�z���Key���L������Ă��镔�����폜

	//�Z�����ɕϐ��֊i�[
	for(auto var : balls)
	{
		ValueMap words;//��s�̕��͂����ꂼ��̗v�f�ɕ����Ċi�[����A�z�z��
		auto wordVector = split(var.asString(), ",");//�J���}��؂�ŕ�����̃x�N�g���z����쐬
		for(int j = ZERO; j < (int)wordVector.size(); ++j)//��؂�ꂽ�������A�z�z��Ɋi�[
			words[keys.at(j).asString()] = wordVector.at(j).asString();
		charcterWords.push_back((Value)words);//�A�z�z����x�N�g���z��ɒǉ�
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
		if (row.size() < 2)//�󔒍s���ǂݍ��܂ꂽ�ꍇ�A�������X�L�b�v����
			break;
		parameter[row.at(0).asString()] =row.at(1).asInt();
	}
	return parameter;
}

std::string FileRead::readString(std::string &fileName)
{
	auto file = FileUtils::getInstance()->getStringFromFile(fileName);
	if (file.size() <= 0)
		throw "�t�@�C��������ɓǂݍ��߂܂���ł����B";
	return file;
}