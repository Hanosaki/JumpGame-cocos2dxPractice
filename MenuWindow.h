#ifndef __MENU_WINDOW_H__
#define __MENU_WINDOW_H__

/*
Menu��ʂ�ʒm��ʂ�\�����邽�߂̂��炷
*/

#include "cocos2d.h"

class MenuWindow{
public:
	void crashBox(std::string errorMessage, cocos2d::Node* node);//���[�U�ɃG���[��ʒm����{�b�N�X��\������

private:
	void endGame(cocos2d::Ref* sender);//�����I���Ɏg�p

};

#endif