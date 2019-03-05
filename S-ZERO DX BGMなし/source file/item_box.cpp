//-----------------------------------//
//---アイテムボックス-[item_box.cpp]-//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
//インクルード文
#include "main.h"
#include "item_box.h"
#include "camera.h"
#include "renderer.h"
#include "player.h"
#include "mode_game.h"
#include "itembox_effect.h"
#include "hit.h"
#include "sound.h"

// 頂点属性(1つ目：座標、2つ目：カラー,3つ目：テクスチャー)
#define FVF_VERTEX_ITEM (D3DFVF_XYZ|D3DFVF_DIFFUSE | D3DFVF_TEX1 )

LPDIRECT3DTEXTURE9 CItem::g_pTextures_bill[TEXTURE_ITEM_MAX] = { NULL };	//テクスチャ配列
D3DXMATRIX CItem::g_mtxWorld_Item;		//ワールド変換行列
LPDIRECT3DVERTEXBUFFER9 CItem::g_pVertexBuffer = NULL;		// バーテックスバッファのポインタ
LPDIRECT3DINDEXBUFFER9 CItem::g_pIndexBuffer = NULL;		// インデックスバッファのポインタ
D3DXMATRIX CItem::g_viewInverse;
D3DXMATRIX CItem::g_Trans, CItem::g_Rotation;
D3DXVECTOR3 CItem::g_TransPosI[MAX_ITEMBOX];
int CItem::color[MAX_ITEMBOX];
bool CItem::ememy[MAX_ITEMBOX];
int CItem::Life[MAX_ITEMBOX];
float  CItem::g_Rot4 = 10.0f;
bool CItem::b_item = false;
bool CItem::b_item2 = false;

bool CItem::b_item_BGM = false;
typedef struct
{
	D3DXVECTOR3 pos;		//座標
	D3DCOLOR color;			//色
	D3DXVECTOR2 texture;	//テクスチャ座標
}VERTEX_BILLBOARD;

bool CItem::InitItem()
{
	b_item = false;
	b_item_BGM = false;
	//デバイスの取得
	LPDIRECT3DDEVICE9  pDevice = CRender::GetD3DDevice();

	if (pDevice == NULL)
	{
		return false;
	}

	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);

	HRESULT hr;

	for (int i = 0; i<TEXTURE_ITEM_MAX; i++)
	{

		hr = D3DXCreateTextureFromFile(pDevice, g_aTexture_i[i].fileName, &g_pTextures_bill[i]);

		if (FAILED(hr))
		{
			MessageBox(NULL, "読み込めません", "エラー", MB_OK);
			return false;
		}

	}

	hr = pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_BILLBOARD) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_ITEM,
		D3DPOOL_MANAGED,
		&g_pVertexBuffer,
		NULL
	);

	if (FAILED(hr))
	{
		MessageBox(NULL, "読み込めません", "エラー", MB_OK);
		return FALSE;
	}

	hr = pDevice->CreateIndexBuffer
	(
		sizeof(WORD) * 6,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIndexBuffer,
		NULL
	);


	if (FAILED(hr))
	{
		MessageBox(NULL, "読み込めません", "エラー", MB_OK);
		return FALSE;
	}

	g_TransPosI[0] = D3DXVECTOR3(-6.0f, 1.1f, 107.0f);
	g_TransPosI[1] = D3DXVECTOR3(-3.0f, 1.1f, 107.0f);
	g_TransPosI[2] = D3DXVECTOR3( 0.0f, 1.1f, 107.0f);
	g_TransPosI[3] = D3DXVECTOR3( 3.0f, 1.1f, 107.0f);
	g_TransPosI[4] = D3DXVECTOR3( 6.0f, 1.1f, 107.0f);

	g_TransPosI[5] = D3DXVECTOR3(-136.0f, 1.1f, 37.0f);
	g_TransPosI[6] = D3DXVECTOR3(-133.0f, 1.1f, 37.0f);
	g_TransPosI[7] = D3DXVECTOR3(-130.0f, 1.1f, 37.0f);
	g_TransPosI[8] = D3DXVECTOR3( -127.0f, 1.1f, 37.0f);
	g_TransPosI[9] = D3DXVECTOR3(-124.0f, 1.1f, 37.0f);

	g_TransPosI[10] = D3DXVECTOR3(136.0f, 1.1f, -57.0f);
	g_TransPosI[11] = D3DXVECTOR3(133.0f, 1.1f, -57.0f);
	g_TransPosI[12] = D3DXVECTOR3(130.0f, 1.1f, -57.0f);
	g_TransPosI[13] = D3DXVECTOR3(127.0f, 1.1f, -57.0f);
	g_TransPosI[14] = D3DXVECTOR3(124.0f, 1.1f, -57.0f);

	g_TransPosI[15] = D3DXVECTOR3(0.0f, 1.1f, -136.0f);
	g_TransPosI[16] = D3DXVECTOR3(0.0f, 1.1f, -133.0f);
	g_TransPosI[17] = D3DXVECTOR3(0.0f, 1.1f, -130.0f);
	g_TransPosI[18] = D3DXVECTOR3(0.0f, 1.1f, -127.0f);
	g_TransPosI[19] = D3DXVECTOR3(0.0f, 1.1f, -124.0f);


	//色設定
	for (int c = 0; c < MAX_ITEMBOX; c++)
	{
		color[c] = c % 1;
		ememy[c] = true;
		Life[c] = 0;
	}

	VertexBuffer_Field();
	IndexBuffer_Field();

	return true;
}

void CItem::UninitItem()
{
	StopSound(SOUND_LABEL_ITEMBOX);

	for (int i = 0; i < TEXTURE_ITEM_MAX; i++)
	{
		if (g_pTextures_bill[i] != NULL)
		{
			g_pTextures_bill[i]->Release();
			g_pTextures_bill[i] = NULL;
		}
	}

	if (g_pVertexBuffer != NULL)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}

	if (&g_pIndexBuffer != NULL)
	{
		g_pIndexBuffer->Release();
		g_pIndexBuffer = NULL;
	}
}

void CItem::UpdateItem()
{

	LPDIRECT3DDEVICE9 pDevice = CRender::GetD3DDevice();

	if (pDevice == NULL) { return; }

	//ビューマトリックスを取得する
	pDevice->GetTransform(D3DTS_VIEW, &g_viewInverse);

	//view逆行列作成
	D3DXMatrixInverse(&g_viewInverse, NULL, &g_viewInverse);

	g_viewInverse._41 = g_viewInverse._42 = g_viewInverse._43 = 0.0f;
	

	if (CModeGame::Gethatena()==true)
	{
		b_item = false;
	}

	if (CModeGame::Gethatena2() == true)
	{
		b_item2 = false;
	}

	if (CModeGame::Hatena_Change() == true)
	{
		b_item = true;
	}

	if (CModeGame::Hatena_Change2() == true)
	{
		b_item2 = false;
	}

	if (CModeGame::Hatena_end() == true)
	{
		b_item = false;
	}

	D3DXVECTOR3 mu = D3DXVECTOR3(0.4f, 0.2f, 0.4f);

	//当たり判定
	for (int Ememy = 0; Ememy < MAX_ITEMBOX; Ememy++)
	{
		//出現
		if (ememy[Ememy])
		{
			//当たり判定
			if (CHit::AABB(D3DXVECTOR3(g_TransPosI[Ememy].x - 0.5f, g_TransPosI[Ememy].y - 1.0f, g_TransPosI[Ememy].z - 0.5f),
				D3DXVECTOR3(g_TransPosI[Ememy].x + 0.5f, g_TransPosI[Ememy].y + 1.0f, g_TransPosI[Ememy].z + 0.5f),
				D3DXVECTOR3(CX_model::XmodelPos().x, CX_model::XmodelPos().y + 1, CX_model::XmodelPos().z) - mu,
				D3DXVECTOR3(CX_model::XmodelPos().x, CX_model::XmodelPos().y - 1, CX_model::XmodelPos().z) + mu) && CModeGame::GOAL() != 3)
			{
				CItemBoxEffect::CreateItembox_Effect(CX_model::XmodelPos().x, CX_model::XmodelPos().y , CX_model::XmodelPos().z);
				ememy[Ememy] = false;
				if (CModeGame::Gethatena() == false)
				{
					b_item = true;
					if (CModeGame::Hatena_Bgm() == false)
					{
						b_item_BGM = true;
					//	PlaySound(SOUND_LABEL_ITEMBOX);
					}
				}else
				if (CModeGame::Gethatena2() == false && !CModeGame::Get_Triple_seigyo())
				{
					b_item2 = true;
					if (CModeGame::Hatena_Bgm2() == false)
					{
						b_item_BGM = true;
						//PlaySound(SOUND_LABEL_ITEMBOX);
					}
				}

			}
		}
		else
		{
			//復活処理
			Life[Ememy]++;

			if (Life[Ememy] > 600)
			{
				ememy[Ememy] = true;
				Life[Ememy] = 0;
			}
		}
	}

	if (b_item_BGM)
	{
		PlaySound(SOUND_LABEL_ITEMBOX);
		b_item_BGM = false;
	}
}

void CItem::DrawItem()
{
	LPDIRECT3DDEVICE9 pDevice = CRender::GetD3DDevice();
	if (pDevice == NULL) { return; }

	//ライトのON・OFF
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//αテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int a = 0; a < MAX_ITEMBOX; a++)
	{
		if (ememy[a])
		{
			D3DXMatrixIdentity(&g_mtxWorld_Item);

			//FVFの設定
			//FVF->デバイスに教える
			pDevice->SetFVF(FVF_VERTEX_ITEM);

			//テクスチャをセット
			pDevice->SetTexture(0, g_pTextures_bill[color[a]]);

			D3DXMatrixRotationY(&g_Rotation, D3DXToRadian(g_Rot4));

			//ビルボードの移動
			D3DXMatrixTranslation(&g_Trans, g_TransPosI[a].x, g_TransPosI[a].y, g_TransPosI[a].z);

			g_mtxWorld_Item = g_mtxWorld_Item  * g_Rotation;

			g_mtxWorld_Item = g_mtxWorld_Item  * g_viewInverse;

			g_mtxWorld_Item = g_mtxWorld_Item  * g_Trans;

			//ワールド行列の設定(好きなタイミングで呼ぶ)
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld_Item);

			pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(VERTEX_BILLBOARD));

			pDevice->SetIndices(g_pIndexBuffer);

			pDevice->DrawIndexedPrimitive
			(D3DPT_TRIANGLELIST,//D3DPT_TRIANGLESTRIP//D3DPT_LINESTRIP//D3DPT_TRIANGLELIST
				0,//インデックスの開始数値
				0,
				6,					//インデックスの数
				0,
				2);					//プリミティブ数
		}
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

void CItem::VertexBuffer_Field()
{

	VERTEX_BILLBOARD b[] =
	{
		{ D3DXVECTOR3(-1.0f,  2.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(0, 0) },
		{ D3DXVECTOR3(1.0f,  2.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(1, 0) },
		{ D3DXVECTOR3(-1.0f,  0.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(0, 1) },
		{ D3DXVECTOR3(1.0f,  0.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(1, 1) },
	};

	VERTEX_BILLBOARD *pV;

	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);

	// 配列をコピーする
	memcpy(pV, b, sizeof(b));

	g_pVertexBuffer->Unlock();
}

void CItem::IndexBuffer_Field()
{
	WORD index_b[] = {

		0,1,2,
		1,3,2
	};

	LPWORD pIndex;

	g_pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);

	memcpy(pIndex, index_b, sizeof(WORD) * 6);

	g_pIndexBuffer->Unlock();
}

bool CItem::GetItem() {
	return b_item;
}

bool CItem::GetItem2() {
	return b_item2;
}

bool CItem::GetBGM() {
	return b_item_BGM;
}