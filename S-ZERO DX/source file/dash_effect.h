//-----------------------------------//
//ダッシュエフェクト処理-[dash_effect.cpp]-//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#ifndef _DASHEFFECT_H_
#define _DASHEFFECT_H_
#include "main.h"

#define DASH_EFFECT_MAX (300)

enum TEXTURE_ENUM_EFFECT
{
	DASH_EFFECT_TEX_NULL = -1,
	DASH_EFFECT_TEX_,
	DASH_EFFECT_TEX_MAX
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
	
}TEXTURE_DASH_EFFECT;

static const TEXTURE_DASH_EFFECT Texture_dash_effect[] =
{
	{ "data/texture/attackBurst.png",			584, 340, 116.8f, 113.3f, 5, 15 }
};

typedef struct
{
	bool bUse;

	int nAnimCount;

	int color;

	D3DXVECTOR3 pos;
}DASH_EFFECT;

class CDashEffect
{
public:
	static void Initdash_effect(void);
	static void Uninitdash_effect(void);
	static void Updatedash_effect(void);
	static void Drawdash_effect(void);
	static void Createdash_effect(float x, float y, float z);
private:
	static LPDIRECT3DTEXTURE9 g_Textures_dash_effect[DASH_EFFECT_TEX_MAX] ;
	static DASH_EFFECT g_dash_effect[DASH_EFFECT_MAX];
	static D3DXMATRIX g_Worlddash_effect;
	static D3DXMATRIX View, ViewInv;
	static D3DXMATRIX Trans[DASH_EFFECT_MAX];
	static int g_nFramecount;
	static int slow; //アニメーションの遅延
};
#endif 