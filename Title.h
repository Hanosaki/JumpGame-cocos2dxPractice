#ifndef __TITLE_H__
#define __TITLE_H__
#define MISAKI_FONTS "fonts/misaki_gothic.ttf"

#include "cocos2d.h"

class Title : public cocos2d::Layer
{
public:
	static cocos2d::Scene* creatScene();

	virtual bool init();

	CREATE_FUNC(Title);

	/// <summary>
	///  ��ʂ��^�b�`���ꂽ�ۂɌĂяo�����C�}�E�X�̃N���b�N�ł��Ăяo�����D
	/// <para>�A�j���[�V�����̊J�n�������s���D</para> 
	/// </summary>
	/// <param name="touch">�w(�}�E�X)���(�����Ŏ擾�����)</param>
	/// <param name="event">������(�����Ŏ擾�����)</param>
	/// <returns>true...�^�b�`���ꂽ��Ԃ�Ԃ�</returns>
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	

};

#endif