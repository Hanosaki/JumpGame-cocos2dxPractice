#ifndef __MENU_WINDOW_H__
#define __MENU_WINDOW_H__

/*
Menu画面や通知画面を表示するためのくらす
*/

#include "cocos2d.h"

class MenuWindow{
public:
	void crashBox(std::string errorMessage, cocos2d::Node* node);//ユーザにエラーを通知するボックスを表示する

private:
	void endGame(cocos2d::Ref* sender);//強制終了に使用

};

#endif