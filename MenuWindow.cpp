#include "MenuWindow.h"
#include "GenericFunction.h"
#include "Converter.h"

USING_NS_CC;

void MenuWindow::crashBox(std::string errorMessage, Node* node)
{
	/*�E�B���h�E�T�C�Y�̎擾*/
	auto directer = Director::getInstance();
	auto visibleSize = directer->getVisibleSize();
	auto origin = directer->getVisibleOrigin();

	/*��ʃT�C�Y�̔����̔����{�b�N�X�𒆉��ɐ���*/
	auto rect = Rect(0.f, 0.f, 3 * visibleSize.width / 4 + origin.x, 3 * visibleSize.height / 4 + origin.y);
	auto box = GenericFunc::createSpriteWithRect(rect, Color3B::WHITE, 1);
	box->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	box->setPosition(GenericFunc::setWindowCenter());

	auto text = Label::create();
	text->setString(errorMessage);
	text->setColor(Color3B::BLACK);
	text->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	text->setPosition(box->getContentSize().width / 2, box->getContentSize().height / 2);//���n�̐^�񒆂Ƀe�L�X�g��ݒu
	text->retain();
	box->addChild(text);

	/*���{�b�N�X��1/4�̍����{�b�N�X�𐶐��A�m�F�{�^���ɂ���*/
	auto rect2 = Rect(0.f, 0.f, box->getContentSize().width / 2, box->getContentSize().height / 4);
	auto button = GenericFunc::createSpriteWithRect(rect2, Color3B::GRAY, 1);
	auto selectedButton = GenericFunc::createSpriteWithRect(rect2, Color3B::GRAY, 2);
	selectedButton->setOpacity(128);
	auto item = MenuItemSprite::create(button, selectedButton, CC_CALLBACK_1(MenuWindow::endGame, this));
	auto menu = Menu::create(item, NULL);
	menu->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	menu->setPosition(box->getContentSize().width / 2, button->getContentSize().height / 2);
	menu->retain();
	box->addChild(menu, 2);

	/*�e�L�X�g�̐���*/
	auto text2 = Label::create();
	text2->setString("OK");
	text2->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	text2->setColor(Color3B::RED);
	text2->setPosition(menu->getPosition());//���{�b�N�X�̉����Ƀe�L�X�g��ݒu
	text2->retain();
	box->addChild(text2, 3);

	node->addChild(box, 5);
	node->unscheduleAllCallbacks();//�S�Ẵ��[�v��������������

}

void MenuWindow::endGame(Ref* sender)
{
	//�Q�[�����I��������
	Director::getInstance()->purgeCachedData();//�L���b�V���J��
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	Converter::replaceALLMP3toDAT();
#endif
	Director::getInstance()->end();

}