//-----------------------------------//
//----コイン処理---------[coin.cpp]--//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#ifndef _COIN_H_
#define _COIN_H_
#include "main.h"


// 頂点属性(1つ目：座標、2つ目：カラー,3つ目：テクスチャー)

#define MAX_COIN (24)	//ビルボードの個数

enum TEXTURE_COIN_ENUM
{
	TEXTURE_COIN_NULL = -1,
	TEXTURE_COIN1,
	TEXTURE_COIN_MAX
};

typedef struct
{
	char fileName[256];
}TEXTURE_COIN;

static const TEXTURE_COIN g_aTexture_co[] =
{
	{ "data/texture/coin.png" }
};


class CCoin {
public:
	static bool InitCoin();
	static void UninitCoin();
	static void UpdateCoin();
	static void DrawCoin();
	static int ScoreCoin();
private:
	static LPDIRECT3DTEXTURE9 g_pTextures_coin[TEXTURE_COIN_MAX] ;	//テクスチャ配列
	static D3DXMATRIX g_mtxWorld_Coin;		//ワールド変換行列
	static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer;		// バーテックスバッファのポインタ
	static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer;		// インデックスバッファのポインタ
	static void VertexBuffer_Field();
	static void IndexBuffer_Field();
	static D3DXMATRIX g_viewInverse;
	static D3DXMATRIX g_Trans, g_Rotation;
	static D3DXVECTOR3 g_TransPosC[MAX_COIN];
	static int color[MAX_COIN];
	static bool ememy[MAX_COIN];
	static int Life[MAX_COIN];
	static float  g_Rot7;
	static int score;

};
#endif 