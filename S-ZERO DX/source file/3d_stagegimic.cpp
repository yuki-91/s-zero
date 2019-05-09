//----------------------------------//
//-------ƒXƒe[ƒW3Dˆ—-------------//
//----[3d_stage_gimic.cpp]------------//
//------Author:ŽÂ‹{ —C‹G------------//
//----------------------------------//
#include "3d_stagegimic.h"
#include"renderer.h"

#define FVF_VERTEX3D	(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_NORMAL)



typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
}VERTEX3D;



CStageGimic *CStageGimic::Create()
{
	CStageGimic *scene3D = new CStageGimic();
	scene3D->Init();
	return scene3D;
}

CStageGimic::CStageGimic()
{
	C_light = new Light;
	C_light->Init();
	SetPostion(D3DXVECTOR3(20.0f, 1.011f, -80.0f));
}

CStageGimic::~CStageGimic()
{
}



void CStageGimic::Init(void)
{
	m_Device = CRender::GetD3DDevice();
	m_Device->CreateVertexBuffer(sizeof(VERTEX3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX3D, D3DPOOL_MANAGED, &m_pVertexBuffer, NULL);
	m_Device->CreateIndexBuffer(sizeof(WORD) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIndexBuffer, NULL);
	D3DXCreateTextureFromFile(m_Device, "data\\texture\\water_zone.png", &m_Texture);

	VERTEX3D v[] = {
		{ D3DXVECTOR3(-40, 0, 40),D3DXVECTOR3(0, 1, 0),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.0f) },
		{ D3DXVECTOR3(40, 0, 40),D3DXVECTOR3(0, 1, 0),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,0.0f) },
		{ D3DXVECTOR3(-40, 0,-40),D3DXVECTOR3(0, 1, 0),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0.0f,1.0f) },
		{ D3DXVECTOR3(40, 0, -40),D3DXVECTOR3(0, 1, 0),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,1.0f) },
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

void CStageGimic::Uninit(void)
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

void CStageGimic::Update(void)
{
	D3DXMatrixTranslation(&m_mtxWorld, m_Position.x, m_Position.y, m_Position.z);
}

void CStageGimic::Draw(void)
{
	m_Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_Device->SetRenderState(D3DRS_ALPHAREF, 150);
	m_Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	C_light->Draw();

	m_Device->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(VERTEX3D));
	m_Device->SetIndices(m_pIndexBuffer);


	m_Device->SetFVF(FVF_VERTEX3D);
	m_Device->SetTexture(0, m_Texture);

	m_Device->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	m_Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

}

