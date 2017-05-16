/// <summary> �Q�[���V�[���p�N���X�̒�`�t�@�C��
/// @author Sigure
/// @date 2017/04/12
/// </summary>
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include "cocos2d.h"

class Game : public cocos2d::Layer
{
public:
	/// <summary>
	/// �V�[���쐬�p�֐��C�V�[�����쐬�������ꍇ�͂��̊֐����Ăяo��
	/// </summary>
	/// <returns>�V�[��</returns>
	static cocos2d::Scene* creatScene();
	
	/// <summary>
	/// �������p�֐��C�V�[���쐬����ԍŏ��ɌĂяo�����D
	/// <para>�e��ϐ��̏������C�ċN�����̐ݒ�Ȃǂ������ōs��</para>
	/// </summary>
	/// <returns>true...������������,false...���C���[���쐬����Ă��Ȃ��ꍇ</returns>
	virtual bool init();

	CREATE_FUNC(Game);

	/// <summary>
	///  ��ʂ��^�b�`���ꂽ�ۂɌĂяo�����C�}�E�X�̃N���b�N�ł��Ăяo�����D
	/// <para>�A�j���[�V�����̊J�n�������s���D</para> 
	/// </summary>
	/// <param name="touch">�w(�}�E�X)���(�����Ŏ擾�����)</param>
	/// <param name="event">������(�����Ŏ擾�����)</param>
	/// <returns>true...�^�b�`���ꂽ��Ԃ�Ԃ�</returns>
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

	/// <summary>
	///<para> ���������֐��C���̊֐���init�ŌĂяo���ƈȍ~�֐����̏������J��Ԃ����������D</para>
	/// <para>�w�i�̈ړ��C�G�̈ړ��C�L�����N�^�[�ƓG�̐ڐG������s��.</para>
	/// </summary>
	/// <param name="dt">���s���̎���(�����I�ɗ��p��������)</param>
	void update(float dt);

	int score; //�G���悯���񐔂��i�[����
	int hitCounter; //hitCounter...�G�ƐڐG�����񐔂��i�[����
	bool endFlag; //�Q�[���I���t���O
	bool hitOnlyOne; //��x�̐ڐG�ň�x�����ڐG���Ȃ����߂̃t���O
	cocos2d::Vec2 defoultPos; //��l���X�v���C�g�̏����ʒu
	cocos2d::Vec2 enemyDefaultPos; //�G�X�v���C�g�̏����ʒu
	cocos2d::Label* label;//�w�b�_�[�Ő錾�����ϐ��́C�p���N���X�ōēx��`����K�v�͂Ȃ��D(���̎��_�ŃO���[�o���ϐ������Ă��邽��)
};

#endif