//-----------------------------------//
//--スカイボックス処理--[sky_box.h]//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#ifndef _SKYBOX_H_
#define _SKYBOX_H_
#include"main.h"
#include "scene.h"


class CXmodel
{
private:
	static D3DXMATRIX m_mtxWorld;	//ワールド変換行列
	static LPDIRECT3DTEXTURE9 m_pTextures;
	static LPD3DXMESH m_pMesh;
	static DWORD m_nMaterialNum ;
	static LPD3DXBUFFER m_pMaterials;
	static D3DXMATRIX m_mtxScale;
	static D3DXMATRIX m_World;
	static D3DXVECTOR3 m_Position;
	static LPDIRECT3DDEVICE9 m_Device;
	static LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
	static LPDIRECT3DTEXTURE9 m_Texture;

	static D3DXMATRIX m_Pos;		//位置の行列
	static D3DXVECTOR3 m_Trans;		//移動
	static D3DXVECTOR3 m_Dir;		//向き
	static D3DXMATRIX m_Rotation;	//回転の行列
	static D3DXMATRIX m_Shadow;		//影のワールド行列
	static float  m_Rot2;
public:
	static CXmodel *Create();
	CXmodel();
	~CXmodel();
	
	bool InitXmodel();
	static void Uninit();
	static void Update();
	static void Draw();
	void Release();
    static D3DXVECTOR3 XmodelPos();

	static float XmodelRot();
};
#endif 
