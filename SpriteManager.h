#ifndef __SPRITE_MANAGER_H__
#define __SPRITE_MANAGER_H__

#include "cocos2d.h"

class SpriteManager
{
public:
	static cocos2d::Sprite* createSprite(std::string fileName, float pos_x, float pos_y, int tag);//�X�v���C�g���쐬����֐�
	static cocos2d::Sprite* createSprite(std::string fileName, float pos_x, float pos_y, cocos2d::Vec2 anchor, int tag);//�X�v���C�g���쐬����֐�(�A���J�[�w��t��)
	static cocos2d::Sprite* createSprite(std::string fileName, float pos_x, float pos_y, cocos2d::Vec2 anchor, float scale, int tag);//�X�v���C�g���쐬����֐�(�A���J�[�w��A�\���{���w��)

	static cocos2d::Sprite* createWithSpriteFileName(std::string fileName, float pos_x, float pos_y, cocos2d::Vec2 anchor, int &tag);//�e�N�X�`���A�g���X����X�v���C�g���쐬����

private:
	static void setSpriteBasicData(cocos2d::Sprite* &sprite,float &pos_x,float &pos_y,int &tag);//�X�v���C�g�̊�{����ݒ肷��֐�
};

#endif