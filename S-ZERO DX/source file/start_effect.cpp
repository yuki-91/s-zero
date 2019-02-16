//-----------------------------------//
//------爆発描画処理-[explosion.cpp]-//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#include "start_effect.h"
#include "main.h"
#include "renderer.h"
#include "player.h"
//-------------------------------------------------------------------
//　変数宣言
//-------------------------------------------------------------------

#define FVF_VERTEX_ST (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

static LPDIRECT3DTEXTURE9 g_Textures_Start_effect[START_EXPLOSION_TEX_MAX] = { NULL };
static START_EXPLOSION g_Start_effect[START_EXPLOSION_MAX];
static D3DXMATRIX g_WorldStart_effect;
static D3DXMATRIX View, ViewInv;
static D3DXMATRIX Trans[START_EXPLOSION_MAX];
static int g_nFramecount = 0;
static int slow = 4; //アニメーションの遅延

typedef struct
{
	D3DXVECTOR3 pos;
	D3DCOLOR color;
	D3DXVECTOR2 texture;
}VERTEX_START_EXPLOSION;

//-------------------------------------------------------------------
//　関数宣言
//-------------------------------------------------------------------

void CStEffect::InitStart_effect(void)
{
	for (int i = 0; i < START_EXPLOSION_MAX; i++)
	{
		g_Start_effect[i].bUse = false;
		g_Start_effect[i].color = 0;
		g_Start_effect[i].nAnimCount = 0;
	}

	LPDIRECT3DDEVICE9  pDevice = CRender::GetD3DDevice();

	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);

	if (pDevice == NULL)
	{
		return;
	}

	HRESULT hr;

	for (int tex = 0; tex<START_EXPLOSION_TEX_MAX; tex++)
	{

		hr = D3DXCreateTextureFromFile(pDevice, Texture_Start_effect[tex].fileName, &g_Textures_Start_effect[tex]);

		if (FAILED(hr))
		{
			MessageBox(NULL, "読み込めません12", "エラー", MB_OK);
			return;
		}
	}

}
void CStEffect::UninitStart_effect(void)
{

	for (int i = 0; i < START_EXPLOSION_TEX_MAX; i++)
	{
		if (g_Textures_Start_effect[i] != NULL)
		{
			g_Textures_Start_effect[i]->Release();
			g_Textures_Start_effect[i] = NULL;
		}
	}
}
void CStEffect::UpdateStart_effect(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRender::GetD3DDevice();

	if (pDevice == NULL) { return; }

	D3DXMatrixIdentity(&g_WorldStart_effect);

	pDevice->GetTransform(D3DTS_VIEW, &View);

	D3DXMatrixInverse(&ViewInv, NULL, &View);

	ViewInv._41 = ViewInv._42 = ViewInv._43 = 0.0f;

	for (int i = 0; i < START_EXPLOSION_MAX; i++)
	{
		g_Start_effect[i].pos = CX_model::XmodelPos();
		//アニメーション数 * アニメーションの遅延 以上の物は削除
		if (g_Start_effect[i].nAnimCount > Texture_Start_effect[g_Start_effect[i].color].Acount * slow)
		{
			g_Start_effect[i].bUse = false;
			g_Start_effect[i].nAnimCount = 0;
		}

		if (g_Start_effect[i].bUse)
		{
			g_Start_effect[i].nAnimCount++;
		}
	}

}
void CStEffect::DrawStart_effect(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRender::GetD3DDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	pDevice->SetFVF(FVF_VERTEX_ST);

	//αテスト開始
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	for (int i = 0; i < START_EXPLOSION_MAX; i++)
	{

		if (g_Start_effect[i].bUse)
		{
			pDevice->SetTexture(0, g_Textures_Start_effect[g_Start_effect[i].color]);

			int anime = g_Start_effect[i].nAnimCount / slow;

			float u0 = (float)Texture_Start_effect[g_Start_effect[i].color].Xsize * (anime % Texture_Start_effect[g_Start_effect[i].color].Xcount) / Texture_Start_effect[g_Start_effect[i].color].width;
			float v0 = (float)Texture_Start_effect[g_Start_effect[i].color].Ysize * (anime / Texture_Start_effect[g_Start_effect[i].color].Xcount) / Texture_Start_effect[g_Start_effect[i].color].height;
			float u1 = (float)(Texture_Start_effect[g_Start_effect[i].color].Xsize * (anime % Texture_Start_effect[g_Start_effect[i].color].Xcount) + Texture_Start_effect[g_Start_effect[i].color].Xsize) / Texture_Start_effect[g_Start_effect[i].color].width;
			float v1 = (float)(Texture_Start_effect[g_Start_effect[i].color].Ysize * (anime / Texture_Start_effect[g_Start_effect[i].color].Xcount) + Texture_Start_effect[g_Start_effect[i].color].Ysize) / Texture_Start_effect[g_Start_effect[i].color].height;

			VERTEX_START_EXPLOSION v[] = {

				{ D3DXVECTOR3(-2.0f,  2.5f,  0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u0, v0) },
				{ D3DXVECTOR3(2.0f,  2.5f,  0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u1, v0) },
				{ D3DXVECTOR3(-2.0f, 0.0f,  0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u0, v1) },
				{ D3DXVECTOR3(2.0f, 0.0f,  0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u1, v1) },

			};

			D3DXMatrixIdentity(&g_WorldStart_effect);

			D3DXMatrixTranslation(&Trans[i], g_Start_effect[i].pos.x, g_Start_effect[i].pos.y, g_Start_effect[i].pos.z);

			g_WorldStart_effect = g_WorldStart_effect * ViewInv;

			g_WorldStart_effect = g_WorldStart_effect * Trans[i];

			//pDevice ->SetStreamSource(0,g_pVertexBufferStart_effect,0,sizeof(VERTEX_START_EXPLOSION));

			//pDevice ->SetIndices(g_pIndexBufferStart_effect);

			//各種行列の設定(好きなタイミングで呼ぶ)
			pDevice->SetTransform(D3DTS_WORLD, &g_WorldStart_effect);

			/*
			pDevice -> DrawIndexedPrimitive
			(D3DPT_TRIANGLESTRIP,0,//インデックスの開始数値
			0,
			4,						//インデックスの数
			0,
			2);						//作成線・面の数
			*/


			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &v[0], sizeof(VERTEX_START_EXPLOSION));

		}

	}

}

void CStEffect::CreateStart_effect(float x, float y, float z)
{
		if (!g_Start_effect[0].bUse)
		{
			g_Start_effect[0].bUse = true;
			g_Start_effect[0].nAnimCount = 0;
			g_Start_effect[0].pos = D3DXVECTOR3(x, y, z);
	}
}
