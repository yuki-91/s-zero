//-----------------------------------//
//-------メッシュフィールド処理------//
//---------------[mesh.h]------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#ifndef _MESH_H_
#define _MESH_H_

#include <d3d9.h>
#include <d3dx9.h>

class CField
{
private:
	typedef struct
	{
		D3DXVECTOR3 Pos;//座標
		D3DXVECTOR3 Normal;//法線
		D3DCOLOR color;	//カラー
		D3DXVECTOR2 texcoord;
	}VERTEX3D;

	VERTEX3D* pV;

	static D3DXMATRIX m_mtxView;//ビュー行列
	static D3DXMATRIX m_mtxProj;//プロジェクション行列

	static int m_nVertexNum;
	static int m_nPrimitiveNum;
	static int m_nIndexNum;

	static D3DXMATRIX m_mtxMove;//平行移動行列

	VERTEX3D* m_pVertex;
	WORD* m_pIndex;

	static LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
	static LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;

	static D3DXMATRIX mtxWorld[5];

	static D3DXMATRIX m_mtxRotX;//X回転行列
	static D3DXMATRIX m_mtxRotZ;//Z回転行列

	D3DXVECTOR3 vx;
	D3DXVECTOR3 vz;
	D3DXVECTOR3 nx;
	D3DXVECTOR3 nz;
	D3DXVECTOR3 n;
	static LPDIRECT3DDEVICE9 m_Device;
	static LPDIRECT3DTEXTURE9 m_Texture;

public:
	void CreateMeshfield(float width, int divNum);
	void DestroyMeshfield(void);
	float GetHeight(D3DXVECTOR3 position);
	void DrawMeshfield(void);
};
#endif