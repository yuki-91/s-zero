//-----------------------------------//
//-スターエフェクト処理-[star_effect.h]-//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#ifndef _STAR_H_
#define _STAR_H_
#include "main.h"
#define STAR_EFFECT_MAX (3)

enum TEXTURE_ENUM10
{
	STAR_EFFECT_TEX_NULL = -1,
	STAR_EFFECT_TEX,
	STAR_EFFECT_TEX_MAX
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

}TEXTURE_STAR_EFFECT;

static const TEXTURE_STAR_EFFECT Texture_Star_effect[] =
{
	{ "data/texture/star_state.png",			960, 3840, 480, 384, 2, 19 }
};

typedef struct
{
	bool bUse;

	int nAnimCount;

	int color;

	D3DXVECTOR3 pos;
}STAR_EFFECT;

class CStarEffect {
public:
	static void InitStar_effect(void);
	static void UninitStar_effect(void);
	static void UpdateStar_effect(void);
	static void DrawStar_effect(void);
	static void CreateStar_effect(float x, float y, float z);
private:
	static LPDIRECT3DTEXTURE9 g_Textures_Star_effect[STAR_EFFECT_TEX_MAX];
	static STAR_EFFECT g_Star_effect[STAR_EFFECT_MAX];
	static int g_nFramecount;
	static D3DXMATRIX g_WorldStar_effect;
	static D3DXMATRIX View, ViewInv;
	static D3DXMATRIX Trans[STAR_EFFECT_MAX];
	static int slow; //アニメーションの遅延
};

#endif 