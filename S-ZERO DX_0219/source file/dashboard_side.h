//-----------------------------------//
//ダッシュボードサイド処理-[dashboard.cpp]-//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#ifndef _DASHBOARDSIDE_H_
#define _DASHBOARDSIDE_H_
#include "main.h"

// 頂点属性(1つ目：座標、2つ目：カラー,3つ目：テクスチャー)
#define MAX_DASHSIDE (6)	//ビルボードの個数

enum TEXTURE_DASH_SIDE_ENUM
{
	TEXTURE_DASH_SIDENULL = -1,
	TEXTURE_DASH_SIDEBOARD1,
	TEXTURE_DASH_SIDEBOARD2,
	TEXTURE_DASH_SIDEMAX
};

typedef struct
{
	char fileName[256];
}TEXTURE_DASH_SIDE;

static const TEXTURE_DASH_SIDE g_aTexture_e[] =
{
	{ "data/texture/dash2.png" },
	{ "data/texture/dash4.png" },
};
class CDashSide {
public:
	static bool InitItem();
	static void UninitItem();
	static void UpdateItem();
	static void DrawItem();
	static bool HitPlayer();
private:
	static LPDIRECT3DTEXTURE9 g_pTextures_dash[TEXTURE_DASH_SIDEMAX];	//テクスチャ配列
	static D3DXMATRIX g_mtxWorld_Item;		//ワールド変換行列
	static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer;		// バーテックスバッファのポインタ
	static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer;		// インデックスバッファのポインタ
	static void VertexBuffer_Field();
	static void IndexBuffer_Field();
	static D3DXMATRIX g_viewInverse;
	static D3DXMATRIX g_Trans, g_Rotation;
	static D3DXVECTOR3 g_TransPos4[MAX_DASHSIDE];
	static int color[MAX_DASHSIDE];
	static bool ememy[MAX_DASHSIDE];
	static int Life[MAX_DASHSIDE];
	static float  g_Rot6;
	static bool b_dash2;
};
#endif 