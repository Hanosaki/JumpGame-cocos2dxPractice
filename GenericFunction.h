#ifndef __GENERIC_FUNCTION_H__
#define __GENERIC_FUNCTION_H__

/*---------------------
�ėp�֐����܂Ƃ߂��N���X
----------------------*/

#include "cocos2d.h"
class GenericFunc{
public:
	GenericFunc();
	cocos2d::Sprite*  setMainCharacterImage(cocos2d::Size visibleSize, cocos2d::Vec2 origin,std::string imgPath);//�����G��\������֐�
	char* setVoiceName(cocos2d::ValueMap valueMap);//�����t�@�C����Ԃ����߂̊֐�
	std::string searceVoice(cocos2d::ValueMap valueMap);//�o�����[�}�b�v���特���t�@�C������T���֐�
	cocos2d::Vec2 setWindowCenter(cocos2d::Size visibleSize,cocos2d::Vec2 origin);//�������W��Ԃ��֐�
	cocos2d::Sprite* createSprite(std::string fileName, float x, float y,int tag);//�X�v���C�g���쐬����֐�
	cocos2d::Sprite* createSprite(std::string fileName, float x, float y,cocos2d::Vec2 anchor , int tag);//�X�v���C�g���쐬����֐�(�A���J�[�w��t��)
	cocos2d::Sprite* createSprite(std::string fileName, float x, float y, cocos2d::Vec2 anchor, float scale, int tag);//�X�v���C�g���쐬����֐�(�A���J�[�w��A�\���{���w��)
	cocos2d::Sprite* createSpriteWithRect(cocos2d::Rect rect, float x, float y, cocos2d::Vec2 anchor, cocos2d::Color3B color, int tag);//�F�t���̃{�b�N�X�𐶐�����֐�
	cocos2d::Menu* createButton(const std::string fileName, const  cocos2d::ccMenuCallback& callback);//�{�^�������p�֐�


};

#endif