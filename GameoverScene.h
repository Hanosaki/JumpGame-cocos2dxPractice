#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"

class GameOver : public cocos2d::Layer
{
public:
	static cocos2d::Scene* creatScene();

	virtual bool init();

	CREATE_FUNC(GameOver);

	/// <summary>
	///  ��ʂ��^�b�`���ꂽ�ۂɌĂяo�����C�}�E�X�̃N���b�N�ł��Ăяo�����D
	/// <para>�A�j���[�V�����̊J�n�������s���D</para> 
	/// </summary>
	/// <param name="touch">�w(�}�E�X)���(�����Ŏ擾�����)</param>
	/// <param name="event">������(�����Ŏ擾�����)</param>
	/// <returns>true...�^�b�`���ꂽ��Ԃ�Ԃ�</returns>
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

	/// <summary>
	/// �Q�[���I�����ɌĂяo���֐�
	/// </summary>
	void ended();

};

#endif