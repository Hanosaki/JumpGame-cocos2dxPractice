#ifndef __CHARA_RESOUSE_H__
#define __CHARA_RESOUSE_H__

#include "cocos2d.h"

#pragma region フォルダ名
extern const std::string F_ANIMATION;
extern const std::string F_FONTS;
extern const std::string F_IMAGE;
extern const std::string F_MAIN_CHARACTER;
extern const std::string F_RIVAL;
extern const std::string F_RUN;
extern const std::string F_VOICE;
#pragma endregion

#pragma region フォント名
extern const std::string JPN_FONTS;
extern const std::string ENG_FONTS;
#pragma endregion

#pragma region 画像名
extern const std::string BACK_GROUND;
extern const std::string CREDIT_IMAGE;
extern const std::string SMILE;
extern const std::string ANGRY;
extern const std::string SAD;
extern const std::string LAUGH;
extern const std::string END_BUTTON;
extern const std::string ENEMY_IMAGE;
extern const std::string LIFE_ICON;
extern const std::string LIFE_WINDOW;
extern const std::string OP_BACK_GROUND;
extern const std::string CHARACTER_DAMAGE;
extern const std::string DEFAULT;
extern const std::string CHARACTER_JUMP;
extern const std::string SKIP_BUTTON;
extern const std::string START_BUTTON;
extern const std::string TEXT_WINDOW;
#pragma endregion

#pragma region 音素材名
/// <summary>
/// 音素材ファイルの指定，引数がchar*の為char*を使用
/// </summary>
extern const char* BUTTON_SE;
extern const char* START_VOICE;
extern const char* DAMEGE_VOICE;
extern const char* RIVAL_VOICE;
extern const char* MAIN_BGM;
extern const char* OP_BGM;
#pragma endregion

#pragma region テキスト
extern const std::string COMPOSERS;
extern const std::string CREDIT;
extern const std::string GAME_OVER_TEXT;
extern const std::string HI_SCORE_TEXT;
extern const std::string NEW_RECORED_TEXT;
extern const std::string NOW_RESULT_TEXT;
extern const std::string PAINTERS;
extern const std::string PILLS;
extern const std::string SCORE_TEXT;
extern const std::string TITLE_TEXT;
extern const std::string RETF_RUN_TITLE_TEXT;
extern const std::string RIVAL_NAME;
extern const std::string VOICE_ACTERS;
extern const std::string MAIN_CHARACTER_NAME;
#pragma endregion

#pragma region キー
/// <summary>
/// ファイル書き込み，読み込みの為のキー
/// char...プレイデータ用のキー
/// std::string...シナリオ・クレジット読み込み用キー
/// </summary>
extern const std::string FACE_KEY;
extern const std::string COMPOSER_KEY;
extern const std::string PAINTER_KEY;
extern const std::string VOICE_ACTER_KEY;
extern const std::string CHARACTER_NAME_KEY;
extern const std::string CHARACTER_WORD_KEY;
extern const std::string VOICE_KEY;
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