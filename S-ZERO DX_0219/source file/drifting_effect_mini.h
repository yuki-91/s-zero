//-----------------------------------//
//-ドリフトエフェクトミニ処理-[drifting_effect_mini.h]-//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#ifndef _DRIFTING_M_H_
#define _DRIFTING_M_H_
#include "main.h"
#define DRIFTING_M_EFFECT_MAX (300)

enum TEXTURE_ENUM18
{
	DRIFTING_M_EFFECT_TEX_NULL = -1,
	DRIFTING_M_EFFECT_TEX,
	DRIFTING_M_EFFECT_TEX_MAX
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

}TEXTURE_DRIFTING_M_EFFECT;

static const TEXTURE_DRIFTING_M_EFFECT Texture_Drifting_M_effect[] =
{
	{ "data/texture/blue_fire.png",			960, 768, 192, 192, 5, 19 }
};

typedef struct
{
	bool bUse;

	int nAnimCount;

	int color;

	D3DXVECTOR3 pos;
}DRIFTING_M_EFFECT;

class CDrifting_MEffect {
public:
	static void InitDrifting_M_effect(void);
	static void UninitDrifting_M_effect(void);
	static void UpdateDrifting_M_effect(void);
	static void DrawDrifting_M_effect(void);
	static void CreateDrifting_M_effect(float x, float y, float z);
private:
	static LPDIRECT3DTEXTURE9 g_Textures_Drifting_M_effect[DRIFTING_M_EFFECT_TEX_MAX];
	static DRIFTING_M_EFFECT g_Drifting_M_effect[DRIFTING_M_EFFECT_MAX];
	static int g_nFramecount;
	static D3DXMATRIX g_WorldDrifting_M_effect;
	static D3DXMATRIX View, ViewInv;
	static D3DXMATRIX Trans[DRIFTING_M_EFFECT_MAX];
	static int slow; //アニメーションの遅延
};

#endif 