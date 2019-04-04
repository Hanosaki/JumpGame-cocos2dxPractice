#pragma execution_character_set("utf-8")
#include "createLabel.h"

USING_NS_CC;

void CreateLabel::setLabel(std::string text,std::string &fonts,int fontSize,Color4B color,Vec2 &pos,int tag,Node* node)
{
	auto label = Label::createWithTTF(text, fonts, fontSize);
	label->setTextColor(color);
	label->setPosition(pos);
	label->setOpacity(0);
	label->setTag(tag);
	node->addChild(label);
}