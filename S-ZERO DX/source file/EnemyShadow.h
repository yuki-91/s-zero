//-----------------------------------//
//------シャドウ処理-[EnemyShadow.h]-//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#ifndef _ENEMYSHADOW_H_
#define _ENEMYSHADOW_H_
#include "main.h"

#define MAX_SHADOW (1)	//ビルボードの個数

class CShadow {
public:
	static bool InitShadow();
	static void UninitShadow();
	static void UpdateShadow();
	static void DrawShadow();
private:
	static LPDIRECT3DTEXTURE9 g_pTexture2;
	static D3DXMATRIX g_mtxWorld_Shadow;		//ワールド変換行列
	static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer2;		// バーテックスバッファのポインタ
	static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer2;		// インデックスバッファのポインタ
	static D3DXMATRIX g_Pos;		//位置の行列
	static D3DXMATRIX g_Shadow;		//影のワールド行列
	static D3DXMATRIX g_viewInverse;
	static D3DXMATRIX g_Trans, g_Rotation;
	static D3DXVECTOR3 g_TransPos[MAX_SHADOW];
	static int color[MAX_SHADOW];
	static bool ememy[MAX_SHADOW];
	static int Life[MAX_SHADOW];
	static void CreateShadow2();
	static void VertexBuffer_Shadow2();
	static void IndexBuffer_Shadow2();
};
#endif 