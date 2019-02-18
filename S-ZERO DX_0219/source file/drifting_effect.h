//-----------------------------------//
//-ドリフトエフェクト処理-[drifting_effect.cpp]-//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#ifndef _DRIFTING_H_
#define _DRIFTING_H_
#include "main.h"
#define DRIFTING_EFFECT_MAX (300)

enum TEXTURE_ENUM5
{
	DRIFTING_EFFECT_TEX_NULL = -1,
	DRIFTING_EFFECT_TEX,
	DRIFTING_EFFECT_TEX_MAX
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

}TEXTURE_DRIFTING_EFFECT;

static const TEXTURE_DRIFTING_EFFECT Texture_Drifting_effect[] =
{
	{ "data/texture/1fd332c84e90c5da8ed7defd8616a278.png",			960, 768, 192, 192, 5, 19 }
};

typedef struct
{
	bool bUse;

	int nAnimCount;

	int color;

	D3DXVECTOR3 pos;
}DRIFTING_EFFECT;

class CDriftingEffect {
public:
	static void InitDrifting_effect(void);
	static void UninitDrifting_effect(void);
	static void UpdateDrifting_effect(void);
	static void DrawDrifting_effect(void);
	static void CreateDrifting_effect(float x, float y, float z);
private:
	static LPDIRECT3DTEXTURE9 g_Textures_Drifting_effect[DRIFTING_EFFECT_TEX_MAX];
	static DRIFTING_EFFECT g_Drifting_effect[DRIFTING_EFFECT_MAX];
	static int g_nFramecount ;
	static D3DXMATRIX g_WorldDrifting_effect;
	static D3DXMATRIX View, ViewInv;
	static D3DXMATRIX Trans[DRIFTING_EFFECT_MAX];
	static int slow; //アニメーションの遅延
};

#endif 