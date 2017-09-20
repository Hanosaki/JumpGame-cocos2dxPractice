#ifndef __CHARA_RESOUSE_H__
#define __CHARA_RESOUSE_H__

#include "cocos2d.h"

#pragma region フォルダ名
extern const std::string ANIMATION;
extern const std::string FONTS;
extern const std::string IMAGE;
extern const std::string MAIN_CHARACTER;
extern const std::string F_RIVAL;
extern const std::string RUN;
#pragma endregion


#pragma region フォント名
extern const std::string JPN_FONTS;
extern const std::string ENG_FONTS;
#pragma endregion

#pragma region 画像名
extern const std::string BACK_GROUND;
extern const std::string CREDIT_IMAGE;
extern const std::string CHARACTER_IMAGE_DAMEGE;
extern const std::string CHARACTER_IMAGE_GAMEOVER;
extern const std::string CHARACTER_IMAGE_NORMAL;
extern const std::string CHARACTER_IMAGE_SMAILE;
extern const std::string SMILE;
extern const std::string ANGRY;
extern const std::string SAD;
extern const std::string LAUGH;
extern const std::string END_IMAGE;
extern const std::string ENEMY_IMAGE;
extern const std::string LIFE_ICON;
extern const std::string OP_BACK_GROUND;
extern const std::string RIVAL_IMAGE;
extern const std::string CHARACTER_DAMAGE;
extern const std::string ANIMATION_CHARACTER_DEFAULT;
extern const std::string CHARACTER_JUMP;
extern const std::string SKIP_IMAGE;
extern const std::string START_IMAGE;
extern const std::string TEXT_WINDOW;
#pragma endregion

#pragma region 音素材名
/// <summary>
/// 音素材ファイルの指定，引数がchar*の為char*を使用
/// </summary>
extern const char* BUTTON_SE;
extern const char* START_VOICE;
extern const char* DAMEGE_VOICE;
extern const char* MAIN_BGM;
extern const char* OP_BGM;
#pragma endregion

#pragma region テキスト
extern const std::string COMPOSERS;
extern const std::string COMPOSER;
extern const std::string CREDIT;
extern const std::string FACE;
extern const std::string GAME_OVER_TEXT;
extern const std::string HI_SCORE_TEXT;
extern const std::string NEW_RECORED_TEXT;
extern const std::string NOW_RESULT_TEXT;
extern const std::string PAINTERS;
extern const std::string PAINTER;
extern const std::string PILLS;
extern const std::string SCORE_TEXT;
extern const std::string TITLE_TEXT;
extern const std::string RETRUN_TITLE_TEXT;
extern const std::string RIVAL_NAME;
extern const std::string VOICE_ACTERS;
extern const std::string VOICE_ACTER;
extern const std::string MAIN_CHARACTER_NAME;
#pragma endregion

#pragma region キー
/// <summary>
/// データを保存するためのkey，引数がchar*の為char*を使用
/// </summary>
extern const char* CHARACTER_NAME;
extern const char* CHARACTER_WORD;
extern const char* HI_SCORE_KEY;
extern const char* SCORE_KEY;
#pragma endregion

#pragma region csvファイル
/// <summary>
/// csvファイルの指定，引数がchar*の為char*を使用
/// </summary>
extern const char* CONVERSATION_LIST;
extern const char* CREDIT_LIST;
#pragma endregion

#endif