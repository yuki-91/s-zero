//-----------------------------------//
//ジャンプボード処理-[jump_board.h]-//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#ifndef _JUMPBOARD_H_
#define _JUMPBOARD_H_
#include "main.h"

// 頂点属性(1つ目：座標、2つ目：カラー,3つ目：テクスチャー)

#define MAX_JUMP (4)	//ビルボードの個数

enum TEXTURE_JUMP_ENUM
{
	TEXTURE_JUMP_NULL = -1,
	TEXTURE_JUMP_BOARD,
	TEXTURE_JUMP_MAX
};

typedef struct
{
	char fileName[256];
}TEXTURE_JUMP;

static const TEXTURE_JUMP g_aTexture_g[] =
{
	{ "data/texture/jumpdai.png" }
	//{ "data/texture/jumpdai2.png" },
};
class CJump {
public:
	static bool Initjump();
	static void Uninitjump();
	static void Updatejump();
	static void Drawjump();
	static bool HitPlayer();
private:
	static LPDIRECT3DTEXTURE9 g_pTextures_dash[TEXTURE_JUMP_MAX];	//テクスチャ配列
	static D3DXMATRIX g_mtxWorld_jump;		//ワールド変換行列
	static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer;		// バーテックスバッファのポインタ
	static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer;		// インデックスバッファのポインタ
	static void VertexBuffer_Field();
	static void IndexBuffer_Field();
	static D3DXMATRIX g_viewInverse;
	static D3DXMATRIX g_Trans, g_Rotation;
	static D3DXVECTOR3 g_TransPos3[MAX_JUMP];
	static int color[MAX_JUMP];
	static bool ememy[MAX_JUMP];
	static int Life[MAX_JUMP];
	static float  g_Rot5;
	static bool b_dash;
};
#endif 