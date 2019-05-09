//-----------------------------------//
//ダッシュボード処理-[dashboard.h]-//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#ifndef _DASHBOARD_H_
#define _DASHBOARD_H_
#include "main.h"

// 頂点属性(1つ目：座標、2つ目：カラー,3つ目：テクスチャー)

#define MAX_DASH (12)	//ビルボードの個数

enum TEXTURE_DASH_ENUM
{
	TEXTURE_DASH_NULL = -1,
	TEXTURE_DASH_BOARD1,
	TEXTURE_DASH_BOARD2,
	TEXTURE_DASH_MAX
};

typedef struct
{
	char fileName[256];
}TEXTURE_DASH;

static const TEXTURE_DASH g_aTexture_d[] =
{
	{ "data/texture/dash.png" },
	{ "data/texture/dash3.png" },
};
class CDash {
public:
	static bool InitItem();
	static void UninitItem();
	static void UpdateItem();
	static void DrawItem();
	static bool HitPlayer();
private:
	static LPDIRECT3DTEXTURE9 g_pTextures_dash[TEXTURE_DASH_MAX];	//テクスチャ配列
	static D3DXMATRIX g_mtxWorld_Item;		//ワールド変換行列
	static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer;		// バーテックスバッファのポインタ
	static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer;		// インデックスバッファのポインタ
	static void VertexBuffer_Field();
	static void IndexBuffer_Field();
	static D3DXMATRIX g_viewInverse;
	static D3DXMATRIX g_Trans, g_Rotation;
	static D3DXVECTOR3 g_TransPos3[MAX_DASH];
	static int color[MAX_DASH];
	static bool ememy[MAX_DASH];
	static int Life[MAX_DASH];
	static float  g_Rot5;
	static bool b_dash;
};
#endif 