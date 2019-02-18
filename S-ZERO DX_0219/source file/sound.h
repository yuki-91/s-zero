
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_SE_KASOKU= 0,		// 加速
	SOUND_LABEL_SE_COUNTDOWN,	// カウントダウン
	SOUND_LABEL_SE_COIN ,		// コイン
	SOUND_LABEL_DAMAGE,		// ダメージ
	SOUND_LABEL_BUTTON ,		// ボタン
	SOUND_LABEL_LASTLAP ,		// ラストラップ
	SOUND_LABEL_START ,		// スタート
	SOUND_LABEL_STAR ,		// スター状態
	SOUND_LABEL_ITEMBOX ,		// アイテムランダム
	SOUND_LABEL_WAHAA ,		// キノコ使用
	SOUND_LABEL_WAHAAKINO ,		// キノコ使用２
	SOUND_LABEL_TURBO ,		// ターボ
	SOUND_LABEL_START_ENGIN ,		// エンジン
	SOUND_LABEL_DRIFT ,		// ドリフト
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
