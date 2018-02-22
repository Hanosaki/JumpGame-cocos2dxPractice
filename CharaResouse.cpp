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
const std::string F_UI = "UI/";
const std::string F_BGM = "BGM/";
const std::string F_SE = "SE/";
#pragma endregion

#pragma region 拡張子
const std::string TYPE_MP3=".mp3";
const std::string TYPE_DAT=".dat";
#pragma endregion

#pragma region フォント名
const std::string JPN_FONTS = "HGRPP1.TTC";
const std::string ENG_FONTS = "Marker Felt.ttf";
#pragma endregion

#pragma region 画像名
const std::string ANGRY = "怒.png";
const std::string BACK_GROUND = "BackGround1.jpg";
const std::string BACK_GROUND2 = "BackGround2.jpg";
const std::string BACK_GROUND3 = "BackGround3.jpg";
const std::string BACK_GROUND4 = "BackGround4.jpg";
const std::string CREDIT_IMAGE = "CreditButton.png";
const std::string CHARACTER_JUMP = "Jump.png";
const std::string DAMAGE_ANIME = "Damage.png";
const std::string FACE_AWARENESS = "察知.png";
const std::string FACE_DAMAGE = "ダメージ.png";
const std::string FACE_NORMAL = "通常.png";
const std::string DEFAULT = "0.png";
const std::string END_BUTTON = "CloseButton.png";
const std::string ENEMY_IMAGE = "enemy.png";
const std::string HOW_TO_BUTTON = "HowToButton.png";
const std::string JUMP_DESCRIPTION = "HowToImage2.png";
const std::string LAUGH = "楽.png";
const std::string LIFE_ICON = "Life.png";
const std::string OP_BACK_GROUND = "OP_BG.png";
const std::string PAUSE_BUTTON = "PauseButton.png";
const std::string RESUME_BUTTON = "ResumeButton.png";
const std::string RETURN_BUTTON = "ReturnButton.png";
const std::string SMILE = "喜.png";
const std::string SAD = "哀.png";
const std::string SURPRISE = "驚.png";
const std::string SKIP_BUTTON = "SkipButton.png";
const std::string START_BUTTON = "StartButton.png";
const std::string TEXT_WINDOW = "TextWindow.png";
const std::string UI_DESCRIPTION = "HowToImage1.png";
#pragma endregion

#pragma region 音素材名
const std::string ALERT_SE = "Alert";
const std::string BUTTON_SE = "Button";
const std::string START_VOICE = "Start";
const std::string DAMEGE_VOICE = "Damage";
const std::string GAMEOVER_SE = "GameOver";
const std::string JUMP_SE = "Jump";
const std::string JUMP_SE2 = "Jump2";
const std::string LOAD_SE = "Loading";
const std::string LOGO_SE = "Logo";
const std::string RIVAL_VOICE = "Attack";
const std::string MAIN_BGM = "main";
const std::string TITLE_BGM = "Title";
const std::string OP_BGM = "op";
#pragma endregion

#pragma region テキスト
const std::string COMPOSERS = "BGM";
const std::string CREDIT = "くれじっと";
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
const std::string RESOUCE_ERROR = "ファイルを正常に読み込むことが出来ませんでした．\n開発者にお問い合わせください．";
const std::string RETF_RUN_TITLE_TEXT = "Push retrun title...";
const std::string RETRUN_TITLE_FROM_HOWTO = "長押しでタイトル画面に戻るよ！";
const std::string HOW_TO_ANNOTATION = "スワイプでページが移動できるよ！";
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
const int Parameter::DEFOULT_GRAVITY_POWER = 0;
const int Parameter::DEFOULT_JUMP_POWER = 23;
const float Parameter::ADD_GRAVITY = 0.1f;
const float Parameter::MOVE_SPEED = 8.0f;
const float Parameter::GAME_SPEED = 0.02f;
#pragma endregion
