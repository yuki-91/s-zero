//-----------------------------------//
//------爆発描画処理--[explosion.h]--//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
#include "main.h"
#define EXPLOSION_MAX (300)

enum TEXTURE_ENUM2
{
	EXPLOSION_TEX_NULL = -1,
	EXPLOSION_TEX,
	EXPLOSION_TEX_MAX
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

}TEXTURE_EXPLOSION;

static const TEXTURE_EXPLOSION Texture_Explosion[] = 
{
	{"data/texture/exp.png",			768, 192, 96, 96, 8, 15},
};

typedef struct
{
	bool bUse;

	int nAnimCount;

	int color;

	D3DXVECTOR3 pos ; 
}EXPLOSION;

//-------------------------------------------------------------------
//　プロトタイプ宣言
//-------------------------------------------------------------------

class CExplosion {
public:
	static void InitExplosion(void);
	static void UninitExplosion(void);
	static void UpdateExplosion(void);
	static void DrawExplosion(void);
	static void CreateExplosion(float x, float y, float z);
private:
	static LPDIRECT3DTEXTURE9 g_Textures_Explosion[EXPLOSION_TEX_MAX];
	static EXPLOSION g_Explosion[EXPLOSION_MAX];
	static int g_nFramecount ;
	static D3DXMATRIX g_WorldExplosion;
	static D3DXMATRIX View, ViewInv;
	static D3DXMATRIX Trans[EXPLOSION_MAX];
	static int slow; //アニメーションの遅延
};

#endif 