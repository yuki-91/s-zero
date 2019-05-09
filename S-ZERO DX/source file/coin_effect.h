//-----------------------------------//
//コインエフェクト処理-[coineffect.h]-//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//

#ifndef _COINEFFECT_H_
#define _COINEFFECT_H_
#include "main.h"
#include "effect.h"
#define COIN_EFFECT_MAX (300)

enum TEXTURE_ENUM7
{
	COIN_EFFECT_TEX_NULL = -1,
	COIN_EFFECT_TEX,
	COIN_EFFECT_TEX_MAX
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

}TEXTURE_COIN_EFFECT;

static const TEXTURE_COIN_EFFECT Texture_Coin_Effect[] =
{
	{ "data/texture/Coin_effect.png",960, 384, 194, 192, 5, 9 }
};

typedef struct
{
	bool bUse;
	int nAnimCount;
	int color;
	D3DXVECTOR3 pos;
}COIN_EFFECT;


class CCoinEffect :public CEffect{
public:
	static void InitCoin_Effect(void);
	static void UninitCoin_Effect(void);
	static void UpdateCoin_Effect(void);
	static void DrawCoin_Effect(void);
	static void CreateCoin_Effect(float x, float y, float z);
private:
	static LPDIRECT3DTEXTURE9 g_Textures_Coin_Effect[COIN_EFFECT_TEX_MAX];
	static COIN_EFFECT g_Coin_Effect[COIN_EFFECT_MAX];
	static D3DXMATRIX g_WorldCoin_Effect;
	static D3DXMATRIX View, ViewInv;
	static D3DXMATRIX Trans[COIN_EFFECT_MAX];
	static int g_nFramecount;
	static int slow ; //アニメーションの遅延

};
#endif 