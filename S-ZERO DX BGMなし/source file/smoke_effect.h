//-----------------------------------//
//-----スモークエフェクト処理--------//
//----[smoke_effect.h]--------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#ifndef _SMOKEEFFECT_H_
#define _SMOKEEFFECT_H_
#include "main.h"
#define SMOKE_EXPLOSION_MAX (300)

enum TEXTURE_ENUM4
{
	SMOKE_EXPLOSION_TEX_NULL = -1,
	SMOKE_EXPLOSION_TEX,
	SMOKE_EXPLOSION_TEX_MAX
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

}TEXTURE_SMOKE_EXPLOSION;

static const TEXTURE_SMOKE_EXPLOSION Texture_smoke_explosion[] =
{
	{ "data/texture/smoke.png",			800, 317, 160, 158.5, 8, 10 }
};

typedef struct
{
	bool bUse;

	int nAnimCount;

	int color;

	D3DXVECTOR3 pos;
}SMOKE_EXPLOSION;

class CSmokeEffect {
public:
	static void Initsmoke_explosion(void);
	static void Uninitsmoke_explosion(void);
	static void Updatesmoke_explosion(void);
	static void Drawsmoke_explosion(void);
	static void Createsmoke_explosion(float x, float y, float z);
private:
	static LPDIRECT3DTEXTURE9 g_Textures_smoke_explosion[SMOKE_EXPLOSION_TEX_MAX];
	static SMOKE_EXPLOSION g_smoke_explosion[SMOKE_EXPLOSION_MAX];
	static D3DXMATRIX g_Worldsmoke_explosion;
	static D3DXMATRIX View, ViewInv;
	static D3DXMATRIX Trans[SMOKE_EXPLOSION_MAX];
	static int g_nFramecount;
	static int slow; //アニメーションの遅延
};
#endif 
