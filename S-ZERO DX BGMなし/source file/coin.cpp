//-----------------------------------//
//----コイン処理---------[coin.cpp]--//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
//インクルード文
#include "coin.h"
#include "coin_effect.h"
#include "hit.h"
#include "camera.h"
#include "renderer.h"
#include "player.h"
#include "mode_game.h"
#include "sound.h"
#include "Enemy.h"
#include "myInput.h"

#define FVF_VERTEX_COIN (D3DFVF_XYZ|D3DFVF_DIFFUSE | D3DFVF_TEX1 )
LPDIRECT3DTEXTURE9 CCoin::g_pTextures_coin[TEXTURE_COIN_MAX] = { NULL };	//テクスチャ配列
D3DXMATRIX CCoin::g_mtxWorld_Coin;		//ワールド変換行列
LPDIRECT3DVERTEXBUFFER9 CCoin::g_pVertexBuffer = NULL;		// バーテックスバッファのポインタ
LPDIRECT3DINDEXBUFFER9 CCoin::g_pIndexBuffer = NULL;		// インデックスバッファのポインタ
D3DXMATRIX CCoin::g_viewInverse;
D3DXMATRIX CCoin::g_Trans, CCoin::g_Rotation;
D3DXVECTOR3 CCoin::g_TransPosC[MAX_COIN];
int CCoin::color[MAX_COIN];
bool CCoin::ememy[MAX_COIN];
int CCoin::Life[MAX_COIN];
float  CCoin::g_Rot7 = 10.0f;
int CCoin::score = 0;


typedef struct
{
	D3DXVECTOR3 pos;		//座標
	D3DCOLOR color;			//色
	D3DXVECTOR2 texture;	//テクスチャ座標
}VERTEX_BILLBOARD;

bool CCoin::InitCoin()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9  pDevice = CRender::GetD3DDevice();
	score = 0;

	if (pDevice == NULL)
	{
		return false;
	}

	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);

	HRESULT hr;

	for (int i = 0; i<TEXTURE_COIN_MAX; i++)
	{

		hr = D3DXCreateTextureFromFile(pDevice, g_aTexture_co[i].fileName, &g_pTextures_coin[i]);

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
		FVF_VERTEX_COIN,
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


	//色設定
	for (int c = 0; c < MAX_COIN; c++)
	{
		color[c] = c % 1;
		ememy[c] = true;
		Life[c] = 0;
	}

	VertexBuffer_Field();
	IndexBuffer_Field();

	return true;
}

void CCoin::UninitCoin()
{

	for (int i = 0; i < TEXTURE_COIN_MAX; i++)
	{
		if (g_pTextures_coin[i] != NULL)
		{
			g_pTextures_coin[i]->Release();
			g_pTextures_coin[i] = NULL;
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

void CCoin::UpdateCoin()
{
	g_TransPosC[0] = D3DXVECTOR3(0.0f, 1.1f, 27.0f);
	g_TransPosC[1] = D3DXVECTOR3(5.0f, 1.1f, 29.0f);
	g_TransPosC[2] = D3DXVECTOR3(-5.0f, 1.1f, 27.0f);

	g_TransPosC[3] = D3DXVECTOR3(-135.0f, 1.1f, -57.0f);
	g_TransPosC[4] = D3DXVECTOR3(-135.0f, 1.1f, -37.0f);
	g_TransPosC[5] = D3DXVECTOR3(-135.0f, 1.1f, -17.0f);

	g_TransPosC[6] = D3DXVECTOR3(130.0f, 1.1f, 37.0f);
	g_TransPosC[7] = D3DXVECTOR3(130.0f, 1.1f, 57.0f);
	g_TransPosC[8] = D3DXVECTOR3(130.0f, 1.1f, 17.0f);

	g_TransPosC[9] = D3DXVECTOR3(-35.0f, 1.1f, -125.0f);
	g_TransPosC[10] = D3DXVECTOR3(-32.0f, 1.1f, -130.0f);
	g_TransPosC[11] = D3DXVECTOR3(-25.0f, 1.1f, -135.0f);

	g_TransPosC[12] = D3DXVECTOR3(45.0f, 1.1f, 75.0f);
	g_TransPosC[13] = D3DXVECTOR3(45.0f, 1.1f, 85.0f);
	g_TransPosC[14] = D3DXVECTOR3(45.0f, 1.1f, 95.0f);

	g_TransPosC[15] = D3DXVECTOR3(-75.0f, 1.1f, -55.0f);
	g_TransPosC[16] = D3DXVECTOR3(-75.0f, 1.1f, -65.0f);
	g_TransPosC[17] = D3DXVECTOR3(-75.0f, 1.1f, -75.0f);

	g_TransPosC[18] = D3DXVECTOR3(70.0f, 1.1f, -80.0f);
	g_TransPosC[19] = D3DXVECTOR3(67.0f, 1.1f, -77.0f);
	g_TransPosC[20] = D3DXVECTOR3(60.0f, 1.1f, -70.0f);

	g_TransPosC[21] = D3DXVECTOR3(120.0f, 1.1f, 130.0f);
	g_TransPosC[22] = D3DXVECTOR3(127.0f, 1.1f, 127.0f);
	g_TransPosC[23] = D3DXVECTOR3(130.0f, 1.1f, 120.0f);

	D3DXVECTOR3 mu = D3DXVECTOR3(0.4f, 0.2f, 0.4f);

	//当たり判定
	for (int Ememy = 0; Ememy < MAX_COIN; Ememy++)
	{
		//出現
		if (ememy[Ememy])
		{
			//当たり判定
			if (CHit::AABB(D3DXVECTOR3(g_TransPosC[Ememy].x - 1.0f, g_TransPosC[Ememy].y - 2.0f, g_TransPosC[Ememy].z - 3.0f),
				D3DXVECTOR3(g_TransPosC[Ememy].x + 1.0f, g_TransPosC[Ememy].y + 2.0f, g_TransPosC[Ememy].z + 3.0f),
				D3DXVECTOR3(CX_model::XmodelPos().x, CX_model::XmodelPos().y + 1, CX_model::XmodelPos().z) - mu,
				D3DXVECTOR3(CX_model::XmodelPos().x, CX_model::XmodelPos().y - 1, CX_model::XmodelPos().z) + mu))
			{
				CCoinEffect::CreateCoin_Effect(CX_model::XmodelPos().x, CX_model::XmodelPos().y + 2.0f, CX_model::XmodelPos().z);
				PlaySound(SOUND_LABEL_SE_COIN);
				ememy[Ememy] = false;
				
				if (score == 30)
				{
					score = 30;
				}
				else
				{
					score += 1;
				}
				if (score < 0)
				{
					score = 0;
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
	if ((MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_LEFT_SHOULDER)) && CModeGame::Getcoin_X() && !CModeGame::Hatena_Button() || GetKeyboardTrigger(DIK_L) && CModeGame::Getcoin_X() && !CModeGame::Hatena_Button())
	{
		PlaySound(SOUND_LABEL_SE_COIN);
		if (score == 30)
		{
			score = 30;
		}
		else
		{
			score += 1;
		}
	}
	if (CBillboard::HitPlayer() == true)
	{
		score = CBillboard::CoinHit();
	}

	if (CModeGame::GetUse() == false)
	{
		score = 0;
	}

	LPDIRECT3DDEVICE9 pDevice = CRender::GetD3DDevice();

	if (pDevice == NULL) { return; }

	//ビューマトリックスを取得する
	pDevice->GetTransform(D3DTS_VIEW, &g_viewInverse);

	//view逆行列作成
	D3DXMatrixInverse(&g_viewInverse, NULL, &g_viewInverse);

	g_viewInverse._41 = g_viewInverse._42 = g_viewInverse._43 = 0.0f;

	
}

void CCoin::DrawCoin()
{
	LPDIRECT3DDEVICE9 pDevice = CRender::GetD3DDevice();
	if (pDevice == NULL) { return; }

	//ライトのON・OFF
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//αテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int a = 0; a < MAX_COIN; a++)
	{
		if (ememy[a])
		{
			D3DXMatrixIdentity(&g_mtxWorld_Coin);

			//FVFの設定
			//FVF->デバイスに教える
			pDevice->SetFVF(FVF_VERTEX_COIN);

			//テクスチャをセット
			pDevice->SetTexture(0, g_pTextures_coin[color[a]]);

			D3DXMatrixRotationY(&g_Rotation, D3DXToRadian(g_Rot7));

			//ビルボードの移動
			D3DXMatrixTranslation(&g_Trans, g_TransPosC[a].x, g_TransPosC[a].y, g_TransPosC[a].z);

			//D3DXMatrixMultiply(&g_mtxWorld_Coin, &g_viewInverse, &g_mtxWorld_Coin);
			//D3DXMatrixMultiply(&g_mtxWorld_Coin, &g_Trans, &g_mtxWorld_Coin);

			g_mtxWorld_Coin = g_mtxWorld_Coin  * g_Rotation;

			g_mtxWorld_Coin = g_mtxWorld_Coin  * g_viewInverse;

			g_mtxWorld_Coin = g_mtxWorld_Coin  * g_Trans;

			//ワールド行列の設定(好きなタイミングで呼ぶ)
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld_Coin);

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

void CCoin::VertexBuffer_Field()
{

	VERTEX_BILLBOARD b[] =
	{
		{ D3DXVECTOR3(-0.5f,  1.5f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(0, 0) },
		{ D3DXVECTOR3(0.5f,  1.5f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(1, 0) },
		{ D3DXVECTOR3(-0.5f,  0.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(0, 1) },
		{ D3DXVECTOR3(0.5f,  0.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(1, 1) },
	};

	VERTEX_BILLBOARD *pV;

	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);

	// 配列をコピーする
	memcpy(pV, b, sizeof(b));

	g_pVertexBuffer->Unlock();
}

void CCoin::IndexBuffer_Field()
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

int CCoin::ScoreCoin()
{
	return score;
}