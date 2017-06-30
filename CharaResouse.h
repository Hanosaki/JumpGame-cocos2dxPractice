#ifndef __CHARA_RESOUSE_H__
#define __CHARA_RESOUSE_H__

#include "cocos2d.h"

#pragma region フォント名
extern const char* JPN_FONTS;
extern const char* ENG_FONTS;
#pragma endregion

#pragma region 画像名
extern const char* BACK_GROUND;
extern const char* CREDIT_IMAGE;
extern const char* CHARACTER_IMAGE_DAMEGE;
extern const char* CHARACTER_IMAGE_GAMEOVER;
extern const char* CHARACTER_IMAGE_NORMAL;
extern const char* CHARACTER_IMAGE_SMAILE;
extern const char* END_IMAGE;
extern const char* ENEMY_IMAGE;
extern const char* OP_BACK_GROUND;
extern const char* RIVAL_IMAGE;
extern const char* SD_DAMAGE;
extern const char* SD_NORMAL;
extern const char* SD_JUMP;
extern const char* START_IMAGE;
#pragma endregion

#pragma region 音素材名
extern const char* START_VOICE;
extern const char* DAMEGE_VOICE;
extern const char* BGM;
#pragma endregion

#pragma region テキスト
extern const char* GAME_OVER_TEXT;
extern const char* NEW_RECORED_TEXT;
extern const char* NOW_RESULT_TEXT;
extern const char* HI_SCORE_TEXT;
extern const char* SCORE_TEXT;
extern const char* TITLE_TEXT;
#pragma endregion

#pragma region キー
extern const char* HI_SCORE_KEY;
extern const char* RETRUN_TITLE_TEXT;
extern const char* SCORE_KEY;
#pragma endregion

void Constant_Declaration();

#endif