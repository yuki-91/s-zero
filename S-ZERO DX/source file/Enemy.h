//-----------------------------------//
//----------エネミー処理-[Enemy.h]-//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"

#define MAX_BILLBOARD (18)	//ビルボードの個数

enum TEXTURE_B_ENUM
{
	TEXTURE_B_NULL = -1,
	TEXTURE_B_MEN_BLUE,
	TEXTURE_B_MEN_RED,
	TEXTURE_B_MEN_GREEN,
	TEXTURE_B_MAX
};


typedef struct
{
	char fileName[256];
}TEXTURE_B;

static const TEXTURE_B g_aTexture_b[] = 
{
	{ "data/texture/kribo.png" },
	{ "data/texture/green_shell.png" },
	{ "data/texture/dossun.png" }
};

class CBillboard {
public:
	static bool InitBillboard();
	static void UninitBillboard();
	static void UpdateBillboard();
	static void DrawBillboard();
	static bool HitPlayer();
	static int CoinHit();
private:
	static LPDIRECT3DTEXTURE9 g_pTextures_bill[TEXTURE_B_MAX];	//テクスチャ配列
	static LPDIRECT3DTEXTURE9 g_pTexture;
	static D3DXMATRIX g_mtxWorld_Billboard;		//ワールド変換行列
	static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer;		// バーテックスバッファのポインタ
	static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer;		// インデックスバッファのポインタ
	static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer2;		// バーテックスバッファのポインタ
	static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer2;		// インデックスバッファのポインタ
	static D3DXMATRIX g_Pos;		//位置の行列
	static void VertexBuffer_Field();
	static void IndexBuffer_Field();
	static D3DXMATRIX g_Shadow;		//影のワールド行列
	static D3DXMATRIX g_viewInverse;
	static D3DXMATRIX g_Trans, g_Rotation;
	static D3DXVECTOR3 g_TransPos[MAX_BILLBOARD];
	static int color[MAX_BILLBOARD];
	static bool ememy[MAX_BILLBOARD];
	static int Life[MAX_BILLBOARD];
	static void VertexBuffer_Shadow2();
	static void IndexBuffer_Shadow2();
	static float  g_Rot2;
	static bool  b_dos2;
	static bool  b_dos5;
	static bool  b_dos8;
	static bool  b_dos11;
	static bool  b_dos14;
	static bool  b_dos17;
	static bool  b_kuri0;
	static bool  b_kuri3;
	static bool  b_kuri6;
	static bool  b_kuri9;
	static bool  b_kuri12;
	static bool  b_kame1;
	static bool  b_kame4;
	static bool  b_kame7;
	static bool  b_kame10;
	static bool  b_kame13;
	static bool  b_kame16;
	static int e_coin;
	static bool b_hit;
	static int dos_count;
};
#endif //_BILLBOARD_H_