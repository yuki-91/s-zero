
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_SE_KASOKU= 0,		// 加速
	SOUND_LABEL_SE_COUNTDOWN= 1,	// カウントダウン
	SOUND_LABEL_SE_COIN= 2,		// コイン
	SOUND_LABEL_DAMAGE= 3,		// ダメージ
	SOUND_LABEL_BUTTON = 4,		// ボタン
	SOUND_LABEL_LASTLAP = 5,		// ラストラップ
	SOUND_LABEL_START = 6,		// スタート
	SOUND_LABEL_STAR = 7,		// スター状態
	SOUND_LABEL_ITEMBOX = 8,		// アイテムランダム
	SOUND_LABEL_WAHAA = 9,		// キノコ使用
	SOUND_LABEL_WAHAAKINO = 10,		// キノコ使用２
	SOUND_LABEL_TURBO = 11,		// ターボ
	SOUND_LABEL_START_ENGIN = 12,		// エンジン
	SOUND_LABEL_DRIFT = 13,		// ドリフト
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
