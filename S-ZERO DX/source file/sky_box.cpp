//-----------------------------------//
//--スカイボックス処理--[sky_box.cpp]//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#include<d3d9.h>
#include<d3dx9.h>
#include"main.h"
#include "scene.h"
#include"input.h"
#include<windows.h>
#include "sky_box.h"
#include "renderer.h"
#include "player.h"

D3DXMATRIX CXmodel::m_Pos;		//位置の行列
D3DXVECTOR3 CXmodel::m_Trans;		//移動
D3DXVECTOR3 CXmodel::m_Dir;		//向き
D3DXMATRIX CXmodel::m_Rotation;	//回転の行列
D3DXMATRIX CXmodel::m_Shadow;		//影のワールド行列
float  CXmodel::m_Rot2 = 0.0f;

D3DXMATRIX CXmodel::m_mtxWorld;	//ワールド変換行列
LPDIRECT3DTEXTURE9 CXmodel::m_pTextures;
LPD3DXMESH  CXmodel::m_pMesh;
DWORD  CXmodel::m_nMaterialNum;
LPD3DXBUFFER  CXmodel::m_pMaterials;
D3DXMATRIX  CXmodel::m_mtxScale;
D3DXMATRIX  CXmodel::m_World;
D3DXVECTOR3  CXmodel::m_Position;
LPDIRECT3DDEVICE9  CXmodel::m_Device;
LPDIRECT3DVERTEXBUFFER9  CXmodel::m_pVertexBuffer;
LPDIRECT3DTEXTURE9  CXmodel::m_Texture;


CXmodel *CXmodel::Create()
{
	CXmodel *m_Xmodel = new CXmodel();
	m_Xmodel->InitXmodel();
	return m_Xmodel;
}

CXmodel::CXmodel()
{
	m_pMesh = NULL;
	m_nMaterialNum = 0;
	m_pMaterials = NULL;
	m_Position = (D3DXVECTOR3(0.0,-5.0, 0.0));
}

CXmodel::~CXmodel()
{
}


//----------------------------------//
//--------モデル初期処理----------//
//----------------------------------//
 bool CXmodel::InitXmodel(void){
	m_Device = CRender::GetD3DDevice();
	if(m_Device == NULL) { return false; }

	m_Trans = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Dir = D3DXVECTOR3(0.0f, 0.0f, -1.0f);


	

	HRESULT hr;
	LPD3DXBUFFER pAdjacency = NULL;
	hr = D3DXLoadMeshFromX("data/3D/blueskybox4.x",
							D3DXMESH_SYSTEMMEM,
							m_Device,
							&pAdjacency,//隣接バッファー情報
							&m_pMaterials,//マテリアル情報
							NULL,
							&m_nMaterialNum,//マテリアルの数
							&m_pMesh);

	m_pMesh->OptimizeInplace(D3DXMESHOPT_COMPACT || D3DXMESHOPT_ATTRSORT || D3DXMESHOPT_VERTEXCACHE,
							(DWORD*)pAdjacency->GetBufferPointer(),
							NULL,
							NULL,
							NULL);

	LPD3DXMESH pCloneMesh;
	D3DVERTEXELEMENT9 elements[MAXD3DDECLLENGTH+1];
	m_pMesh->GetDeclaration(elements);
	hr = m_pMesh->CloneMesh(D3DXMESH_MANAGED || D3DXMESH_WRITEONLY,
						elements,
						m_Device,
						&pCloneMesh);
	m_pMesh->Release();

	m_pMesh = pCloneMesh;
	hr = D3DXCreateTextureFromFile(m_Device, "data/texture/m_skybox002.png", &m_pTextures);
	

	if(FAILED(hr))
	{
		MessageBox(NULL,"読み込めなかった","エラー",MB_OK);
	}


	return true;
}

 void CXmodel::Uninit(void)
{
	if (m_pMaterials != NULL)
	{
		m_pMaterials->Release();
		m_pMaterials = NULL;
	}
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL; 
	}
	if (m_pTextures != NULL)
	{
		m_pTextures->Release();
		m_pTextures = NULL;
	}

	if (m_pVertexBuffer != NULL)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = NULL;
	}
	if (m_Device != NULL)
	{
		m_Device->Release();
		m_Device = NULL;
	}
	
}

void CXmodel::Update(void)
{
	D3DXMatrixIdentity(&m_World);
	D3DXMatrixIdentity(&m_Shadow);


}



void CXmodel::Draw(void)
{
	m_Device = CRender::GetD3DDevice();	//ダイレクト３Ｄデバイス
	if (m_Device == NULL) { return; }
	if (m_pMaterials == NULL) { return; }
	
	LPD3DXMATERIAL pMaterials = (LPD3DXMATERIAL)m_pMaterials->GetBufferPointer();

	D3DXMatrixRotationY(&m_Rotation, D3DXToRadian(-m_Rot2));

	D3DXMatrixTranslation(&m_Pos, m_Trans.x, m_Trans.y, m_Trans.z);

	D3DXMatrixScaling(&m_mtxScale, 300, 300, 300);

	//D3DXMatrixMultiply(&m_mtxWorld_field, &m_mtxTrance_field, &m_mtxWorld_field);

	m_World = m_World * m_Rotation;

	m_World = m_World * m_Pos;
	
	m_World = m_World * m_mtxScale;

	//ワールド行列の設定(好きなタイミングで呼ぶ)
	m_Device->SetTransform(D3DTS_WORLD, &m_World);

	m_Device->SetRenderState(D3DRS_LIGHTING,FALSE);//ライティング
	
	m_Device->SetTexture(0, m_pTextures);
	//pTextureFilename パスを追加してテｋスチャロド関数へ
	for(int i = 0;i < m_nMaterialNum;i++){
		
		//pDevice->SetTexture(0,m_pTextures2);
		m_Device->SetMaterial(&pMaterials[i].MatD3D);
		m_pMesh->DrawSubset(i);
	}

}

//キャラの位置
D3DXVECTOR3 CXmodel::XmodelPos()
{
	return m_Trans;
}


//キャラの向き
float CXmodel::XmodelRot()
{
	float g_R = m_Rot2 + 270.0f;

	return g_R;
}


void CXmodel::Release()
{
	Uninit();
	delete this;		//自分自身のポインタ
}


