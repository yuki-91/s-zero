//-----------------------------------//
//----------ŠÅ”Âˆ—------------------//
//-------[signboard.cpp]--------------//
//------Author:ŽÂ‹{ —C‹G-------------//
//-----------------------------------//
#include "signboard.h"
#include"renderer.h"
#define FVF_VERTEXROAD	(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_NORMAL)



typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
}VERTEX3D;



CSingnBoard *CSingnBoard::Create()
{
	CSingnBoard *singnBoard = new CSingnBoard();
	singnBoard->Init();
	return singnBoard;
}

CSingnBoard::CSingnBoard()
{

}

CSingnBoard::~CSingnBoard()
{
}



void CSingnBoard::Init(void)
{
	//^‚ñ’†
	mp_Position[0] = D3DXVECTOR3(20.0f, 5.2f, -125.0f);
	mp_Position[1] = D3DXVECTOR3(0.0f, 5.2f, -65.0f);
	


	m_Device = CRender::GetD3DDevice();
	m_Device->CreateVertexBuffer(sizeof(VERTEX3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEXROAD, D3DPOOL_MANAGED, &m_pVertexBuffer, NULL);
	m_Device->CreateVertexBuffer(sizeof(VERTEX3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEXROAD, D3DPOOL_MANAGED, &m_pVertexBuffer2, NULL);
	m_Device->CreateIndexBuffer(sizeof(WORD) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIndexBuffer, NULL);
	D3DXCreateTextureFromFile(m_Device, "data\\texture\\signboard.png", &m_Texture);
	D3DXCreateTextureFromFile(m_Device, "data\\texture\\signboard2.png", &m_Texture2);
	VERTEX3D v[] = {
		{ D3DXVECTOR3(0, -5, 5),D3DXVECTOR3(0, 1, 0),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.0f) },
		{ D3DXVECTOR3(0, 5, 5),D3DXVECTOR3(0, 1, 0),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,0.0f) },
		{ D3DXVECTOR3(0, -5,-5),D3DXVECTOR3(0, 1, 0),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0.0f,1.0f) },
		{ D3DXVECTOR3(0, 5, -5),D3DXVECTOR3(0, 1, 0),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,1.0f) },
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

	VERTEX3D v2[] = {
		{ D3DXVECTOR3(-5, 5, 0),D3DXVECTOR3(0, 1, 0),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.0f) },
		{ D3DXVECTOR3(5, 5, 0),D3DXVECTOR3(0, 1, 0),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,0.0f) },
		{ D3DXVECTOR3(-5, -5,0),D3DXVECTOR3(0, 1, 0),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0.0f,1.0f) },
		{ D3DXVECTOR3(5, -5, 0),D3DXVECTOR3(0, 1, 0),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,1.0f) },
	};

	VERTEX3D* pV2;
	m_pVertexBuffer2->Lock(0, 0, (void**)&pV2, D3DLOCK_DISCARD);
	memcpy(pV2, v2, sizeof(VERTEX3D) * 4);
	m_pVertexBuffer->Unlock();


}

void CSingnBoard::Uninit(void)
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



void CSingnBoard::Update(void)
{

}

void CSingnBoard::Draw(void)
{

		D3DXMatrixIdentity(&m_mtxWorld);

		D3DXMatrixTranslation(&m_mtxWorld, mp_Position[0].x, mp_Position[0].y, mp_Position[0].z);


		m_Device->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(VERTEX3D));
		m_Device->SetIndices(m_pIndexBuffer);


		m_Device->SetFVF(FVF_VERTEXROAD);
		m_Device->SetTexture(0, m_Texture);

		m_Device->SetTransform(D3DTS_WORLD, &m_mtxWorld);
		m_Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
	

		D3DXMatrixIdentity(&m_mtxWorld);

		D3DXMatrixTranslation(&m_mtxWorld, mp_Position[1].x, mp_Position[1].y, mp_Position[1].z);


		m_Device->SetStreamSource(0, m_pVertexBuffer2, 0, sizeof(VERTEX3D));
		m_Device->SetIndices(m_pIndexBuffer);


		m_Device->SetFVF(FVF_VERTEXROAD);
		m_Device->SetTexture(0, m_Texture2);

		m_Device->SetTransform(D3DTS_WORLD, &m_mtxWorld);
		m_Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}

