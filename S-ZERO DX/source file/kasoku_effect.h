//-----------------------------------//
//加速エフェクト処理-[kasoku_effect.h]-//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#ifndef _KASOKUEFFECT_H_
#define _KASOKUEFFECT_H_
#include "main.h"
#define KASOKU_EFFECT_MAX (300)

enum TEXTURE_ENUM8
{
	KASOKU_EFFECT_TEX_NULL = -1,
	KASOKU_EFFECT_TEX,
	KASOKU_EFFECT_TEX_MAX
};

typedef struct
{
	char fileName[256];
	int width;
	int height;

	float Xsize;
	float Ysize;

	int Xcount;

	int Acount;

}TEXTURE_KASOKU_EFFECT;

static const TEXTURE_KASOKU_EFFECT Texture_Kasoku_effect[] =
{
	{ "data/texture/beac07392fb6280812c3133eb8917f1a_waifu2x_art_noise3_scale_tta_1.png",			1280, 768, 256, 256, 5, 14 }
};

typedef struct
{
	bool bUse;

	int nAnimCount;

	int color;

	D3DXVECTOR3 pos;
}KASOKU_EFFECT;

//-------------------------------------------------------------------
//　プロトタイプ宣言
//-------------------------------------------------------------------
class CKasokuEffect {
public:
	static void InitKasoku_effect(void);
	static void UninitKasoku_effect(void);
	static void UpdateKasoku_effect(void);
	static void DrawKasoku_effect(void);
	static void CreateKasoku_effect(float x, float y, float z);
private:
	static LPDIRECT3DTEXTURE9 g_Textures_Kasoku_effect[KASOKU_EFFECT_TEX_MAX];
	static KASOKU_EFFECT g_Kasoku_effect[KASOKU_EFFECT_MAX];
	static int g_nFramecount;
	static D3DXMATRIX g_WorldKasoku_effect;
	static D3DXMATRIX View, ViewInv;
	static D3DXMATRIX Trans[KASOKU_EFFECT_MAX];
	static int slow; //アニメーションの遅延
	static LPDIRECT3DDEVICE9  pDevice2;
};
#endif 