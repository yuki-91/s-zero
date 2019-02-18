//-----------------------------------//
//ジャンプエフェクト処理-[jumo_effect.h]-//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//

#ifndef _JUMPEFFECT_H_
#define _JUMPEFFECT_H_
#include "main.h"
#define JUMP_EFFECT_MAX (300)

enum TEXTURE_ENUM14
{
	JUMP_EFFECT_TEX_NULL = -1,
	JUMP_EFFECT_TEX,
	JUMP_EFFECT_TEX_MAX
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

}TEXTURE_JUMP_EFFECT;

static const TEXTURE_JUMP_EFFECT Texture_Jump_Effect[] =
{
	{ "data/texture/Jump_effect.png",960, 576, 192, 192, 5, 15 }
};

typedef struct
{
	bool bUse;
	int nAnimCount;
	int color;
	D3DXVECTOR3 pos;
}JUMP_EFFECT;


class CJumpEffect {
public:
	static void InitJump_Effect(void);
	static void UninitJump_Effect(void);
	static void UpdateJump_Effect(void);
	static void DrawJump_Effect(void);
	static void CreateJump_Effect(float x, float y, float z);
private:
	static LPDIRECT3DTEXTURE9 g_Textures_Jump_Effect[JUMP_EFFECT_TEX_MAX];
	static JUMP_EFFECT g_Jump_Effect[JUMP_EFFECT_MAX];
	static D3DXMATRIX g_WorldJump_Effect;
	static D3DXMATRIX View, ViewInv;
	static D3DXMATRIX Trans[JUMP_EFFECT_MAX];
	static int g_nFramecount;
	static int slow; //アニメーションの遅延

};
#endif 