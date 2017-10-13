#pragma execution_character_set("utf-8")
#include "CharaResouse.h"

#pragma region フォルダ名
const std::string F_ANIMATION = "animation/";
const std::string F_FONTS = "fonts/";
const std::string F_IMAGE = "image/";
const std::string F_MAIN_CHARACTER = "mainCharacter/";
const std::string F_RIVAL = "rival/";
const std::string F_RUN = "run/";
const std::string F_VOICE = "voice/";
#pragma endregion

#pragma region フォント名
const std::string JPN_FONTS = "HGRPP1.TTC";
const std::string ENG_FONTS = "Marker Felt.ttf";
#pragma endregion

#pragma region 画像名
const std::string BACK_GROUND = "bg.png";
const std::string CREDIT_IMAGE = "CreditButton.png";
const std::string END_BUTTON = "CloseButton.png";
const std::string ENEMY_IMAGE = "enemy.png";
const std::string SMILE = "喜.png";
const std::string ANGRY = "怒.png";
const std::string SAD = "哀.png";
const std::string LAUGH = "楽.png";
const std::string LIFE_ICON = "Life.png";
const std::string LIFE_WINDOW = "LifeWindow.png";
const std::string OP_BACK_GROUND = "OP_BG.png";
const std::string CHARACTER_DAMAGE = "Damage.png";
const std::string DEFAULT = "0.png";
const std::string CHARACTER_JUMP = "Jump.png";
const std::string SKIP_BUTTON = "SkipButton.png";
const std::string START_BUTTON = "StartButton.png";
const std::string TEXT_WINDOW = "TextWindow.png";
#pragma endregion

#pragma region 音素材名
const char* BUTTON_SE = "SE/Button.mp3";
const char* START_VOICE = "SE/Start.mp3";
const char* DAMEGE_VOICE = "SE/Damage.mp3";
const char* GAMEOVER_SE = "SE/GameOver.mp3";
const char* JUMP_SE = "SE/Jump.mp3";
const char* JUMP_SE2 = "SE/Jump2.mp3";
const char* LOAD_SE = "SE/Loading.mp3";
const char* LOGO_SE = "SE/Logo.mp3";
const char* RIVAL_VOICE = "SE/Attack.mp3";
const char* MAIN_BGM = "BGM/main.mp3";
const char* TITLE_BGM = "BGM/Title.mp3";
const char* OP_BGM = "BGM/op.mp3";
#pragma endregion

#pragma region テキスト
const std::string COMPOSERS = "BGM";
const std::string CREDIT = "くれじっと";
const std::string RESOUCE_ERROR = "ファイルを正常に読み込むことが出来ませんでした．\n開発者にお問い合わせください．";
const std::string GAME_OVER_TEXT = "ゲームオーバー...";
const std::string LOAD_MESSEAGE = "ロード中…";
const std::string LOGO = "ゆかりさんゲーム制作委員会";
const std::string HI_SCORE_TEXT = "HIScore:";
const std::string PAINTERS = "イラスト素材";
const std::string NEW_RECORED_TEXT = "  NEW RECORED!";
const std::string NOW_RESULT_TEXT = "こんかいのきろく";
const std::string PILLS = "●";
const std::string SCORE_TEXT = "Score:";
const std::string TITLE_TEXT = "ゆかりさんDASH！";
const std::string RETF_RUN_TITLE_TEXT = "Push retrun title...";
const std::string RIVAL_NAME = "きりたん";
const std::string VOICE_ACTERS = "キャラクターボイス";
const std::string MAIN_CHARACTER_NAME = "ゆかり";
#pragma endregion

#pragma region キー
const std::string FACE_KEY = "face";
const std::string COMPOSER_KEY = "composer";
const std::string PAINTER_KEY = "painter";
const std::string VOICE_ACTER_KEY = "voiceActer";
const std::string CHARACTER_NAME_KEY = "name";
const std::string CHARACTER_WORD_KEY = "conversation";
const std::string VOICE_KEY = "voice";
const char* HI_SCORE_KEY = "hiScore";
const char* SCORE_KEY = "score";
#pragma endregion

#pragma region csvファイル
const char* CONVERSATION_LIST = "csv/ConversationList.csv";
const char* CREDIT_LIST = "csv/credit.csv";
#pragma endregion

#pragma region ゲームパラメータ
const int Parameter::ANIMATION_MAX_NUM = 17;
const int Parameter::VERY_SMALL = 24;
const int Parameter::SMALL = 36;
const int Parameter::MIDDLE = 48;
const int Parameter::LARGE = 64;

#pragma endregion
