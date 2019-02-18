//-----------------------------------//
//------ロードサイド処理---------------//
//-------[roadside.cpp]--------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#include "road_side.h"
#include"renderer.h"
#define FVF_VERTEX3D	(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_NORMAL)


typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
}VERTEX3D;



CRoadSide3D *CRoadSide3D::Create()
{
	CRoadSide3D *road3D = new CRoadSide3D();
	road3D->Init();
	return road3D;
}

CRoadSide3D::CRoadSide3D()
{
}

CRoadSide3D::~CRoadSide3D()
{
}



void CRoadSide3D::Init(void)
{
	//左上
	mp_Position[0] = D3DXVECTOR3(-20.0f, 1.2f, 130.0f);
	mp_Position[1] = D3DXVECTOR3(-40.0f, 1.2f, 130.0f);
	mp_Position[2] = D3DXVECTOR3(-60.0f, 1.2f, 130.0f);
	mp_Position[3] = D3DXVECTOR3(-80.0f, 1.2f, 130.0f);
	mp_Position[4] = D3DXVECTOR3(-100.0f, 1.2f, 130.0f);
	//右上
	mp_Position[5] = D3DXVECTOR3(60.0f, 1.2f, 130.0f);
	mp_Position[6] = D3DXVECTOR3(80.0f, 1.2f, 130.0f);
	mp_Position[7] = D3DXVECTOR3(100.0f, 1.2f, 130.0f);
	mp_Position[8] = D3DXVECTOR3(120.0f, 1.2f, 130.0f);
	mp_Position[9] = D3DXVECTOR3(-120.0f, 1.2f, 130.0f);
	//右下
	mp_Position[10] = D3DXVECTOR3(-120.0f, 1.2f, -130.0f);
	mp_Position[11] = D3DXVECTOR3(-100.0f, 1.2f, -130.0f);
	mp_Position[12] = D3DXVECTOR3(-100.0f, 1.2f, -130.0f);

	//万
	mp_Position[13] = D3DXVECTOR3(-75.0f, 1.2f, 90.0f);
	mp_Position[14] = D3DXVECTOR3(-55.0f, 1.2f, 90.0f);
	//下
	mp_Position[15] = D3DXVECTOR3(-15.0f, 1.2f, -130.0f);
	mp_Position[16] = D3DXVECTOR3(5.0f, 1.2f, -130.0f);
	//mp_Position[17] = D3DXVECTOR3(45.0f, 1.2f, -70.0f);
	mp_Position[18] = D3DXVECTOR3(60.0f, 1.2f, -70.0f);
	mp_Position[19] = D3DXVECTOR3(90.0f, 1.2f, -130.0f);
	mp_Position[20] = D3DXVECTOR3(110.0f, 1.2f, -130.0f);
	mp_Position[21] = D3DXVECTOR3(20.0f, 1.2f, -20.0f);
	mp_Position[22] = D3DXVECTOR3(-85.0f, 1.2f, -50.0f); 

	m_Device = CRender::GetD3DDevice();
	m_Device->CreateVertexBuffer(sizeof(VERTEX3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX3D, D3DPOOL_MANAGED, &m_pVertexBuffer, NULL);
	m_Device->CreateIndexBuffer(sizeof(WORD) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIndexBuffer, NULL);
	D3DXCreateTextureFromFile(m_Device, "data\\texture\\roadtypeh2.jpg", &m_Texture);

	VERTEX3D v[] = {
		{ D3DXVECTOR3(-10, 0, 10),D3DXVECTOR3(0, 1, 0),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.0f) },
		{ D3DXVECTOR3(10, 0, 10),D3DXVECTOR3(0, 1, 0),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,0.0f) },
		{ D3DXVECTOR3(-10, 0,-10),D3DXVECTOR3(0, 1, 0),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0.0f,1.0f) },
		{ D3DXVECTOR3(10, 0, -10),D3DXVECTOR3(0, 1, 0),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,1.0f) },
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

void CRoadSide3D::Uninit(void)
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



void CRoadSide3D::Update(void)
{

}

void CRoadSide3D::Draw(void)
{

	for (int a = 0; a < MAX_ROADSIDE; a++)
	{
		D3DXMatrixIdentity(&m_mtxWorld);

		D3DXMatrixTranslation(&m_mtxWorld, mp_Position[a].x, mp_Position[a].y, mp_Position[a].z);



		m_Device->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(VERTEX3D));
		m_Device->SetIndices(m_pIndexBuffer);


		m_Device->SetFVF(FVF_VERTEX3D);
		m_Device->SetTexture(0, m_Texture);

		m_Device->SetTransform(D3DTS_WORLD, &m_mtxWorld);
		m_Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
	}
}

