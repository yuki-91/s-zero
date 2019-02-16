//-----------------------------------//
//-------スタートチェック処理--------//
//----[start_check.cpp]--------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#include "start_check.h"
#include"renderer.h"

#define FVF_VERTEX3D	(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_NORMAL)



typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
}VERTEX3D;



CScene3D *CScene3D::Create()
{
	CScene3D *scene3D = new CScene3D();
	scene3D->Init();
	return scene3D;
}

CScene3D::CScene3D()
{
	C_light = new Light;
	C_light->Init();
	SetPostion(D3DXVECTOR3(0.0f, 1.05f, 0.0f));
}

CScene3D::~CScene3D()
{
}



void CScene3D::Init(void)
{
	m_Device = CRender::GetD3DDevice();
	m_Device->CreateVertexBuffer(sizeof(VERTEX3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX3D, D3DPOOL_MANAGED, &m_pVertexBuffer, NULL);
	m_Device->CreateIndexBuffer(sizeof(WORD) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIndexBuffer, NULL);
	D3DXCreateTextureFromFile(m_Device, "data\\texture\\checkerboard.png", &m_Texture);

	VERTEX3D v[] = {
		{ D3DXVECTOR3(-10, 0, 6),D3DXVECTOR3(0, 1, 0),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.0f) },
		{ D3DXVECTOR3(10, 0, 6),D3DXVECTOR3(0, 1, 0),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,0.0f) },
		{ D3DXVECTOR3(-10, 0,-6),D3DXVECTOR3(0, 1, 0),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0.0f,1.0f) },
		{ D3DXVECTOR3(10, 0, -6),D3DXVECTOR3(0, 1, 0),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,1.0f) },
	};
	WORD index[] = {
		0,1,2,
		1,3,2
	};
	VERTEX3D* pV;
	m_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);
	memcpy(pV, v, sizeof(VERTEX3D) * 4);
	m_pVertexBuffer->Unlock();

	LPWORD pIndex;
	m_pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);
	memcpy(pIndex, index, sizeof(WORD) * 6);
	m_pIndexBuffer->Unlock();

}

void CScene3D::Uninit(void)
{
	if (m_Texture != NULL)
	{
		m_Texture->Release();
		m_Texture = NULL;
	}

	if (m_pVertexBuffer != NULL)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = NULL;
	}

	if (&m_pIndexBuffer != NULL)
	{
		m_pIndexBuffer->Release();
		m_pIndexBuffer = NULL;
	}
}

void CScene3D::Update(void)
{
	D3DXMatrixTranslation(&m_mtxWorld, m_Position.x, m_Position.y, m_Position.z);
}

void CScene3D::Draw(void)
{
	C_light->Draw();

	m_Device->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(VERTEX3D));
	m_Device->SetIndices(m_pIndexBuffer);


	m_Device->SetFVF(FVF_VERTEX3D);
	m_Device->SetTexture(0, m_Texture);

	m_Device->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	m_Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

}

