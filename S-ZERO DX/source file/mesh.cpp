//-----------------------------------//
//-------メッシュフィールド処理------//
//------------[mesh.cpp]------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#include "mesh.h"
#include "camera.h"
#include"renderer.h"
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_NORMAL)

D3DXMATRIX CField::m_mtxView;//ビュー行列

D3DXMATRIX CField::m_mtxProj;//プロジェクション行列
int CField::m_nVertexNum;
int CField::m_nPrimitiveNum;
int CField::m_nIndexNum;
D3DXMATRIX CField::m_mtxMove;//平行移動行列
LPDIRECT3DVERTEXBUFFER9 CField::m_pVertexBuffer = NULL;
LPDIRECT3DINDEXBUFFER9 CField::m_pIndexBuffer = NULL;
D3DXMATRIX CField::mtxWorld[5];
D3DXMATRIX CField::m_mtxRotX;//X回転行列
LPDIRECT3DDEVICE9 CField::m_Device;
LPDIRECT3DTEXTURE9 CField::m_Texture;

float m_FieldHeight[961] = {
	10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,
	10.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,10.0f,
	10.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,10.0f,
	10.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,10.0f,
	10.0f,01.0f,01.0f,01.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,10.0f,
	10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,01.0f,01.0f,01.0f,10.0f,
	10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,
	10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,
	10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,10.0f,10.0f,10.0f,10.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,
	10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,10.0f,10.0f,10.0f,10.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,
	10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,10.0f,10.0f,10.0f,10.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,
	10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,10.0f,10.0f,10.0f,10.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,
	10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,10.0f,10.0f,10.0f,10.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,
	10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,10.0f,01.0f,01.0f,10.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,
	10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,10.0f,01.0f,01.0f,10.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,
	10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,10.0f,01.0f,01.0f,10.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,
	10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,10.0f,01.0f,01.0f,10.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,
	10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,10.0f,01.0f,01.0f,10.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,
	10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,10.0f,10.0f,10.0f,10.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,
	10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,
	10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,10.0f,01.5f,01.5f,01.0f,00.5f,00.5f,00.5f,00.5f,01.0f,01.0f,01.0f,10.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,
	10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,10.0f,01.5f,01.5f,01.0f,00.5f,00.5f,00.5f,00.5f,01.0f,01.0f,01.0f,10.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,
	10.0f,01.0f,01.0f,01.0f,10.0f,10.0f,10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,10.0f,00.5f,00.5f,00.5f,00.5f,00.5f,00.5f,00.5f,01.0f,01.0f,01.0f,10.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,
	10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,10.0f,00.5f,00.5f,00.5f,01.5f,01.5f,01.5f,00.5f,01.0f,01.0f,01.0f,10.0f,01.0f,10.0f,01.0f,01.0f,01.0f,10.0f,
	10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,10.0f,00.5f,00.5f,00.5f,00.5f,01.5f,01.5f,10.0f,01.0f,01.0f,01.0f,10.0f,10.0f,10.0f,01.0f,01.0f,01.0f,10.0f,
	10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,10.0f,01.5f,01.5f,00.5f,00.5f,01.5f,01.5f,10.0f,01.0f,01.0f,01.0f,10.0f,10.0f,10.0f,01.0f,01.0f,01.0f,10.0f,
	10.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,01.0f,10.0f,10.0f,01.0f,01.0f,01.0f,00.5f,00.5f,00.5f,00.5f,01.5f,01.5f,10.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,10.0f,
	10.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,10.0f,10.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.5f,01.5f,10.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,10.0f,
	10.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,10.0f,10.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,10.0f,
	10.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,10.0f,10.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,10.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,01.0f,10.0f,
	10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,

};
void CField::CreateMeshfield(float width, int divNum)
{

	m_nVertexNum = (divNum + 1)*(divNum + 1);
	m_nIndexNum = ((divNum + 1) * 2)*divNum + 2 * (divNum - 1);
	m_nPrimitiveNum = divNum*divNum * 2 + (divNum - 1) * 4;

	m_pVertex = new VERTEX3D[m_nVertexNum];
	m_pIndex = new WORD[m_nIndexNum];

	float oneWidth = width / divNum;
	float uleftX = -(width*0.5f);
	float uleftZ = width*0.5f;
	for (int i = 0; i < m_nVertexNum; i++)
	{
		m_pVertex[i].Pos.x = uleftX + oneWidth * (i % (divNum + 1));
		m_pVertex[i].Pos.y = 0.0f;
		m_pVertex[i].Pos.z = uleftZ - oneWidth * (i / (divNum + 1));
		m_pVertex[i].Normal.x = 0.0f;
		m_pVertex[i].Normal.y = 0.5f;
		m_pVertex[i].Normal.z = 0.0f;
		m_pVertex[i].texcoord.x = (float)(i % (divNum + 1));
		m_pVertex[i].texcoord.y = (float)(i / (divNum + 1));
		m_pVertex[i].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	for (int a = 0; a < m_nVertexNum; a++) {

		m_pVertex[a].Pos.y = m_FieldHeight[a];
	}

		for (int x = 1; x < divNum; x++)
		{
			for (int z = 1; z < divNum; z++)
			{
				vx = m_pVertex[z * (divNum + 1) + x + 1].Pos
					- m_pVertex[z *  (divNum + 1) + x - 1].Pos;

				nx.x = -vx.y;
				nx.y = vx.x;
				nx.z = 0.0f;
				
				vz = m_pVertex[z *  (divNum + 1) + x + divNum].Pos
					- m_pVertex[z *  (divNum + 1) + x - divNum].Pos;

				nz.x = 0.0f;
				nz.y = vz.x;
				nz.z = -vz.y;

				n = nx + nz;

				D3DXVec3Normalize(&n, &n);
				m_pVertex[z *  (divNum + 1) + x].Normal = n;

			}
	}

	m_pIndex[0] = (divNum + 1);
	m_pIndex[1] = 0;
	int k = 2;
	for (int i = 2; i < m_nIndexNum; i++)
	{
		m_pIndex[i] = m_pIndex[i - 2] + 1;
		k++;
		if (k == 2 * (divNum + 1))//最後
		{
			if (i != m_nIndexNum - 1)//ほんとの最後じゃなければ
			{
				m_pIndex[i + 1] = m_pIndex[i];//最後の二度うち
				m_pIndex[i + 2] = m_pIndex[i - 1] + 1;//最初
				m_pIndex[i + 3] = m_pIndex[i + 2];//最初の二度うち
				m_pIndex[i + 4] = m_pIndex[i + 1] + 1;//nikome
				k = 2;
				i = i + 4;
			}
		}
	}
		
	LPDIRECT3DDEVICE9 pD3DDevice = CRender::GetD3DDevice();
	HRESULT hr;

	hr = pD3DDevice->CreateVertexBuffer(sizeof(VERTEX3D) * m_nVertexNum, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVertexBuffer, NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, "頂点バッファの作成に失敗しました", "Notion", MB_OK | MB_ICONINFORMATION);
		return;
	}
	hr = pD3DDevice->CreateIndexBuffer(sizeof(WORD) * m_nIndexNum, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIndexBuffer, NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, "インデックスバッファの作成に失敗しました", "Notion", MB_OK | MB_ICONINFORMATION);
		return;
	}

	D3DXCreateTextureFromFile(pD3DDevice, "data/texture/pattern_shibafu.png", &m_Texture);

	LPWORD pI;

	m_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);
	memcpy(pV, m_pVertex, sizeof(VERTEX3D) * m_nVertexNum);
	m_pVertexBuffer->Unlock();

	m_pIndexBuffer->Lock(0, 0, (void**)&pI, D3DLOCK_DISCARD);
	memcpy(pI, m_pIndex, sizeof(WORD) * m_nIndexNum);
	m_pIndexBuffer->Unlock();

	delete[] m_pVertex;
	delete[] m_pIndex;


	//フィールド場所変換
	{
		D3DXMatrixIdentity(&mtxWorld[0]);
	}

	{
		D3DXMatrixRotationZ(&mtxWorld[1], D3DX_PI / 2);//Z回転行列作成
		D3DXMatrixTranslation(&m_mtxMove, width / 2, width / 2, 0.0f);//平行移動行列作成

		mtxWorld[1] *= m_mtxMove;
	}

	{
		D3DXMatrixRotationZ(&mtxWorld[2], -D3DX_PI / 2);//Z回転行列作成
		D3DXMatrixTranslation(&m_mtxMove, -width / 2, width / 2, 0.0f);//平行移動行列作成

		mtxWorld[2] *= m_mtxMove;
	}

	{
		D3DXMatrixRotationX(&mtxWorld[3], -D3DX_PI / 2);//X回転行列作成
		D3DXMatrixTranslation(&m_mtxMove, 0.0f, width / 2, width / 2);//平行移動行列作成

		mtxWorld[3] *= m_mtxMove;
	}

	{
		D3DXMatrixRotationX(&mtxWorld[4], D3DX_PI / 2);//X回転行列作成
		D3DXMatrixTranslation(&m_mtxMove, 0.0f, width / 2, -width / 2);//平行移動行列作成

		mtxWorld[4] *= m_mtxMove;
	}
}


float CField::GetHeight(D3DXVECTOR3 position)//引数で場所をもらって戻り値で返す
{
	D3DXVECTOR3 V01;
	D3DXVECTOR3 V12;
	D3DXVECTOR3 V20;

	D3DXVECTOR3 V02;
	D3DXVECTOR3 V22;
	D3DXVECTOR3 V32;

	D3DXVECTOR3 V0P;
	D3DXVECTOR3 V1P;
	D3DXVECTOR3 V2P;
	D3DXVECTOR3 V3P;
	D3DXVECTOR3 V4P;
	D3DXVECTOR3 V5P;
	D3DXVECTOR3 N;
	D3DXVECTOR3 N2;
	float C0;
	float C1;
	float C2;

	float C3;
	float C4;
	float C5;

	float width = 300.0f;
	int divNum = 30;

	for (int x = 0; x < divNum; x++)
	{
		for (int z = 0; z < divNum; z++)
		{

			V01 = pV[(z + 1) * (divNum + 1) + x].Pos
				- pV[(z + 1) * (divNum + 1) + x + 1].Pos;
			V12 = pV[z * (divNum + 1) + x].Pos
				- pV[(z + 1) * (divNum + 1) + x].Pos;
			V20 = pV[(z + 1) * (divNum + 1) + x + 1].Pos
				- pV[z * (divNum + 1) + x].Pos;


			V0P = position - pV[(z + 1) * (divNum + 1) + x + 1].Pos;
			V1P = position - pV[(z + 1) * (divNum + 1) + x].Pos;
			V2P = position - pV[z * (divNum + 1) + x].Pos;

			
			C0 = V01.x * V0P.z - V01.z * V0P.x; //出てくるのはfloat
			C1 = V12.x * V1P.z - V12.z * V1P.x; //出てくるのはfloat
			C2 = V20.x * V2P.z - V20.z * V2P.x; //出てくるのはfloat

				if (C0 <= 0.0f && C1 <= 0.0f && C2 <= 0.0f)
			{

				D3DXVec3Cross(&N, &V01, &V12);
				position.y = pV[z * (divNum + 1) + x].Pos.y - (N.x * (position.x - pV[z * (divNum + 1) + x ].Pos.x) + N.z * (position.z - pV[z * (divNum + 1) + x ].Pos.z)) / N.y;
					
			}

				V02 = pV[z * (divNum + 1) + x].Pos
					- pV[(z + 1) * (divNum + 1) + x + 1].Pos;
				V22 = pV[z * (divNum + 1) + x + 1].Pos
					- pV[z * (divNum + 1) + x].Pos;
				V32 = pV[(z + 1) * (divNum + 1) + x + 1].Pos
					- pV[z * (divNum + 1) + x + 1].Pos;

				V3P = position - pV[(z + 1) * (divNum + 1) + x + 1].Pos;
				V4P = position - pV[z * (divNum + 1) + x].Pos;
				V5P = position - pV[z * (divNum + 1) + x + 1].Pos;

				C3 = V02.x * V3P.z - V02.z * V3P.x; //出てくるのはfloat
				C4 = V22.x * V4P.z - V22.z * V4P.x; //出てくるのはfloat
				C5 = V32.x * V5P.z - V32.z * V5P.x; //出てくるのはfloaty

				if (C3 <= 0.0f && C4 <= 0.0f && C5 <= 0.0f)
				{

					D3DXVec3Cross(&N2, &V22, &V32);
					position.y = pV[z * (divNum + 1) + x + 1].Pos.y - (N2.x * (position.x - pV[z * (divNum + 1) + x + 1].Pos.x) + N2.z * (position.z - pV[z * (divNum + 1) + x + 1].Pos.z)) / N2.y;
					
				}
		}
	}
	return position.y;
}


void CField::DrawMeshfield(void)
{
	LPDIRECT3DDEVICE9 pD3DDevice = CRender::GetD3DDevice();
	pD3DDevice->SetFVF(FVF_VERTEX_3D);
	pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pD3DDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(VERTEX3D));
	pD3DDevice->SetIndices(m_pIndexBuffer);
	pD3DDevice->SetTexture(0, m_Texture);
	pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld[0]);
	pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nVertexNum, 0, m_nPrimitiveNum);

	pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

}

void CField::DestroyMeshfield(void)
{
	m_pVertexBuffer->Release();
	m_pIndexBuffer->Release();
}