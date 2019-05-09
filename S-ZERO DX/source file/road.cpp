//-----------------------------------//
//------ƒ[ƒhˆ—---------------//
//-------[road.cpp]--------------//
//------Author:ŽÂ‹{ —C‹G-------------//
//-----------------------------------//
#include "road.h"
#include"renderer.h"
#define FVF_VERTEXROAD	(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_NORMAL)



typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
}VERTEX3D;



CRoad3D *CRoad3D::Create()
{
	CRoad3D *road3D = new CRoad3D();
	road3D->Init();
	return road3D;
}

CRoad3D::CRoad3D()
{

}

CRoad3D::~CRoad3D()
{
}



void CRoad3D::Init(void)
{
	//^‚ñ’†
	mp_Position[0] = D3DXVECTOR3(0.0f, 1.2f, 15.0f); 
	mp_Position[1] = D3DXVECTOR3(0.0f, 1.2f, 35.0f); 
	mp_Position[2] = D3DXVECTOR3(0.0f, 1.2f, 55.0f); 
	mp_Position[3] = D3DXVECTOR3(0.0f, 1.2f, 75.0f); 
	mp_Position[4] = D3DXVECTOR3(0.0f, 1.2f, 95.0f); 
	mp_Position[5] = D3DXVECTOR3(0.0f, 1.2f, 115.0f);
	mp_Position[6] = D3DXVECTOR3(0.0f, 1.2f, -15.0f);

	//¶
	mp_Position[7] = D3DXVECTOR3(-130.0f, 1.2f, 10.0f); 
	mp_Position[8] = D3DXVECTOR3(-130.0f, 1.2f, 30.0f); 
	mp_Position[9] = D3DXVECTOR3(-130.0f, 1.2f, 50.0f); 
	mp_Position[10] = D3DXVECTOR3(-130.0f, 1.2f, 70.0f);
	mp_Position[11] = D3DXVECTOR3(-130.0f, 1.2f, 90.0f);
	mp_Position[12] = D3DXVECTOR3(-130.0f, 1.2f, 110.0f);
	mp_Position[13] = D3DXVECTOR3(-130.0f, 1.2f, -10.0f); 
	mp_Position[14] = D3DXVECTOR3(-130.0f, 1.2f, -30.0f); 
	mp_Position[15] = D3DXVECTOR3(-130.0f, 1.2f, -50.0f);
	mp_Position[16] = D3DXVECTOR3(-130.0f, 1.2f, -70.0f);
	mp_Position[17] = D3DXVECTOR3(-130.0f, 1.2f, -90.0f); 
	mp_Position[18] = D3DXVECTOR3(-130.0f, 1.2f, -110.0f);
	
	//×“¹
	mp_Position[19] = D3DXVECTOR3(-95.0f, 1.2f, 75.0f);
	mp_Position[21] = D3DXVECTOR3(-95.0f, 1.2f, -5.0f);
	mp_Position[22] = D3DXVECTOR3(-95.0f, 1.2f, -25.0f);
	mp_Position[23] = D3DXVECTOR3(-95.0f, 1.2f, -45.0f);
	mp_Position[24] = D3DXVECTOR3(-70.0f, 1.2f, -65.0f);
	mp_Position[25] = D3DXVECTOR3(-70.0f, 1.2f, -85.0f);
	mp_Position[26] = D3DXVECTOR3(-90.0f, 1.2f, -105.0f);
	mp_Position[27] = D3DXVECTOR3(-90.0f, 1.2f, -125.0f);

	mp_Position[28] = D3DXVECTOR3(-95.0f, 1.2f, 15.0f);
	mp_Position[29] = D3DXVECTOR3(-95.0f, 1.2f, 35.0f);
	mp_Position[30] = D3DXVECTOR3(-95.0f, 1.2f, 55.0f);

	//ŽŸ‚Ì‰¡
	mp_Position[31] = D3DXVECTOR3(-35.0f, 1.2f, -5.0f);
	mp_Position[32] = D3DXVECTOR3(-35.0f, 1.2f, -25.0f);
	mp_Position[33] = D3DXVECTOR3(-35.0f, 1.2f, -45.0f);
	mp_Position[34] = D3DXVECTOR3(-35.0f, 1.2f, -65.0f);
	mp_Position[35] = D3DXVECTOR3(-35.0f, 1.2f, -85.0f);
	mp_Position[36] = D3DXVECTOR3(-35.0f, 1.2f, -105.0f);
	mp_Position[37] = D3DXVECTOR3(-35.0f, 1.2f, -125.0f);
	mp_Position[38] = D3DXVECTOR3(-35.0f, 1.2f, 15.0f);
	mp_Position[39] = D3DXVECTOR3(-35.0f, 1.2f, 35.0f);
	mp_Position[40] = D3DXVECTOR3(-35.0f, 1.2f, 55.0f);
	mp_Position[41] = D3DXVECTOR3(-35.0f, 1.2f, 75.0f);

	mp_Position[43] = D3DXVECTOR3(70.0f, 1.2f, -85.0f);
	mp_Position[44] = D3DXVECTOR3(70.0f, 1.2f, -105.0f);
	mp_Position[45] = D3DXVECTOR3(70.0f, 1.2f, -125.0f);

	mp_Position[47] = D3DXVECTOR3(40.0f, 1.2f, 15.0f);
	mp_Position[48] = D3DXVECTOR3(40.0f, 1.2f, 35.0f);
	mp_Position[49] = D3DXVECTOR3(40.0f, 1.2f, 55.0f);
	mp_Position[50] = D3DXVECTOR3(40.0f, 1.2f, 75.0f);
	mp_Position[51] = D3DXVECTOR3(40.0f, 1.2f, 95.0f);
	mp_Position[52] = D3DXVECTOR3(40.0f, 1.2f, 115.0f);
	mp_Position[53] = D3DXVECTOR3(40.0f, 1.2f, -5.0);

	//‰E
	mp_Position[54] = D3DXVECTOR3(130.0f, 1.2f, 15.0f);
	mp_Position[55] = D3DXVECTOR3(130.0f, 1.2f, 35.0f);
	mp_Position[56] = D3DXVECTOR3(130.0f, 1.2f, 55.0f);
	mp_Position[57] = D3DXVECTOR3(130.0f, 1.2f, 75.0f);
	mp_Position[58] = D3DXVECTOR3(130.0f, 1.2f, 95.0f);
	mp_Position[59] = D3DXVECTOR3(130.0f, 1.2f, 115.0f);
	//mp_Position[60] = D3DXVECTOR3(25.0f, 1.2f, -90.0f);
	mp_Position[61] = D3DXVECTOR3(130.0f, 1.2f, -5.0f);
	mp_Position[62] = D3DXVECTOR3(130.0f, 1.2f, -25.0f);
	mp_Position[63] = D3DXVECTOR3(130.0f, 1.2f, -45.0f);
	mp_Position[64] = D3DXVECTOR3(130.0f, 1.2f, -65.0f);
	mp_Position[65] = D3DXVECTOR3(130.0f, 1.2f, -85.0f);
	mp_Position[66] = D3DXVECTOR3(130.0f, 1.2f, -105.0f);
	mp_Position[67] = D3DXVECTOR3(130.0f, 1.2f, -125.0f);
	

	m_Device = CRender::GetD3DDevice();
	m_Device->CreateVertexBuffer(sizeof(VERTEX3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEXROAD, D3DPOOL_MANAGED, &m_pVertexBuffer, NULL);
	m_Device->CreateIndexBuffer(sizeof(WORD) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIndexBuffer, NULL);
	D3DXCreateTextureFromFile(m_Device, "data\\texture\\roadtypeh1.jpg", &m_Texture);

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

void CRoad3D::Uninit(void)
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



void CRoad3D::Update(void)
{

}

void CRoad3D::Draw(void)
{
	for (int a = 0; a < MAX_ROAD; a++)
	{
		D3DXMatrixIdentity(&m_mtxWorld);

		D3DXMatrixTranslation(&m_mtxWorld, mp_Position[a].x, mp_Position[a].y, mp_Position[a].z);


		
		m_Device->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(VERTEX3D));
		m_Device->SetIndices(m_pIndexBuffer);


		m_Device->SetFVF(FVF_VERTEXROAD);
		m_Device->SetTexture(0, m_Texture);

		m_Device->SetTransform(D3DTS_WORLD, &m_mtxWorld);
		m_Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
	}
}

