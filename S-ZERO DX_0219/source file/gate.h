//-----------------------------------//
//--ゲート処理---------------[gate.h]//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#ifndef _GATE_H_
#define _GATE_H_
#include "mesh.h"

enum TEXTURE_GATE_3D_ENUM
{
	TEXTURE_3D_NULLG = -1,
	TEXTURE_3D_GATE,
	TEXTURE_3D_MAXG
};

typedef struct
{
	char fileName[256];
	int width;
	int height;
}TEXTURE_3DG;

static const TEXTURE_3DG g_aTexture3DGate[] =
{
	{ "data/texture/Block.png",2560,1600 },
};

class CGate {
public:
	static bool InitGate(void);
	static void UninitGate();
	static void UpdateGate();
	static void DrawGate();
	static D3DXVECTOR3 GatePos();
	static float GateRot();
private:
	static LPD3DXMESH g_pMeshG;	//メッシュデータ
	static DWORD g_nMaterialNumG;		//マテリアルの数
	static LPD3DXBUFFER g_pMaterialsGBufferG;		//マテリアルのバッファー
	static LPD3DXBUFFER g_pMaterialsG;
	static D3DMATERIAL9*	g_pMeshGMaterialsG;	// マテリアル情報
	static LPDIRECT3DTEXTURE9 pMeshTex2[TEXTURE_3D_MAXG];	// メッシュのテクスチャ
	static D3DXMATRIX g_World;
	static D3DXMATRIX g_Pos;		//位置の行列
	static D3DXVECTOR3 g_Transmodel;		//移動
	static D3DXVECTOR3 g_Dir;		//向き
	static D3DXMATRIX g_RotGation, g_mtxScale;	//回転 拡大
	static D3DXMATRIX g_Shadow;		//影のワールド行列
	static float  g_RotG;
	static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer;		// バーテックスバッファのポインタ
	static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer;		// インデックスバッファのポインタ
	static LPDIRECT3DTEXTURE9 pTextures;
};

#endif //_GATE_H_