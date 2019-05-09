//-----------------------------------//
//アイテムボックスエフェクト処理-----//
//-----[itembox_effect.h]------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#ifndef _ITEMBOXEFFECT_H_
#define _ITEMBOXEFFECT_H_
#include "main.h"
#define ITEMBOX_EFFECT_MAX (300)

enum TEXTURE_ENUM9
{
	ITEMBOX_EFFECT_TEX_NULL = -1,
	ITEMBOX_EFFECT_TEX_BLUE,
	ITEMBOX_EFFECT_TEX_RED,
	ITEMBOX_EFFECT_TEX_GREEN,
	ITEMBOX_EFFECT_TEX_MAX
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

}TEXTURE_ITEMBOX_EFFECT;

static const TEXTURE_ITEMBOX_EFFECT Texture_Itembox_Effect[] =
{
	{ "data/texture/itembox_effect.png",768, 1920, 384, 384, 2, 9 },
	{ "data/texture/itembox_effect.png",768, 1920, 384, 384, 2, 9 },
	{ "data/texture/itembox_effect.png",768, 1920, 384, 384, 2, 9 }
};

typedef struct
{
	bool bUse;

	int nAnimCount;

	int color;

	D3DXVECTOR3 pos;
}ITEMBOX_EFFECT;

//-------------------------------------------------------------------
//　プロトタイプ宣言
//-------------------------------------------------------------------
class CItemBoxEffect {
public:
	static void InitItembox_Effect(void);
	static void UninitItembox_Effect(void);
	static void UpdateItembox_Effect(void);
	static void DrawItembox_Effect(void);
	static void CreateItembox_Effect(float x, float y, float z);
private:
	static LPDIRECT3DTEXTURE9 g_Textures_Itembox_Effect[ITEMBOX_EFFECT_TEX_MAX] ;
	static ITEMBOX_EFFECT g_Itembox_Effect[ITEMBOX_EFFECT_MAX];
	static D3DXMATRIX g_WorldItembox_Effect;
	static D3DXMATRIX View, ViewInv;
	static D3DXMATRIX Trans[ITEMBOX_EFFECT_MAX];
	static int g_nFramecount ;
	static int slow ; //アニメーションの遅延
};
#endif 