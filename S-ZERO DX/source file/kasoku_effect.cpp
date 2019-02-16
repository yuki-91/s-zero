//-----------------------------------//
//加速エフェクト処理-[kasoku_effect.cpp]-//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#include "kasoku_effect.h"
#include "main.h"
#include "renderer.h"
#include "player.h"
//-------------------------------------------------------------------
//　変数宣言
//-------------------------------------------------------------------

#define FVF_VERTEX_KASOKU_EFFECT (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

LPDIRECT3DTEXTURE9 CKasokuEffect::g_Textures_Kasoku_effect[KASOKU_EFFECT_TEX_MAX] = { NULL };
KASOKU_EFFECT CKasokuEffect::g_Kasoku_effect[KASOKU_EFFECT_MAX];
int CKasokuEffect::g_nFramecount = 0;
D3DXMATRIX CKasokuEffect::g_WorldKasoku_effect;
D3DXMATRIX CKasokuEffect::View, CKasokuEffect::ViewInv;
D3DXMATRIX CKasokuEffect::Trans[KASOKU_EFFECT_MAX];
int CKasokuEffect::slow = 3; //アニメーションの遅延
LPDIRECT3DDEVICE9  CKasokuEffect::pDevice2 = NULL;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DCOLOR color;
	D3DXVECTOR2 texture;
}VERTEX_KASOKU_EFFECT;

//-------------------------------------------------------------------
//　関数宣言
//-------------------------------------------------------------------

void CKasokuEffect::InitKasoku_effect(void)
{
	for (int i = 0; i < KASOKU_EFFECT_MAX; i++)
	{
		g_Kasoku_effect[i].bUse = false;
		g_Kasoku_effect[i].color = 0;
		g_Kasoku_effect[i].nAnimCount = 0;
	}

	
	pDevice2 = CRender::GetD3DDevice();

	pDevice2->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);

	if (pDevice2 == NULL)
	{
		return;
	}

	HRESULT hr;

	for (int tex = 0; tex<KASOKU_EFFECT_TEX_MAX; tex++)
	{

		hr = D3DXCreateTextureFromFile(pDevice2, Texture_Kasoku_effect[tex].fileName, &g_Textures_Kasoku_effect[tex]);

		if (FAILED(hr))
		{
			MessageBox(NULL, "読み込めませんkaso", "エラー", MB_OK);
			return;
		}
	}

}
void CKasokuEffect::UninitKasoku_effect(void)
{

	for (int i = 0; i < KASOKU_EFFECT_TEX_MAX; i++)
	{
		if (g_Textures_Kasoku_effect[i] != NULL)
		{
			g_Textures_Kasoku_effect[i]->Release();
			g_Textures_Kasoku_effect[i] = NULL;
		}
	}
	if (pDevice2 != NULL)
	{
		pDevice2->Release();
		pDevice2 = NULL;
	}

}
void CKasokuEffect::UpdateKasoku_effect(void)
{
	pDevice2 = CRender::GetD3DDevice();

	if (pDevice2 == NULL) { return; }

	D3DXMatrixIdentity(&g_WorldKasoku_effect);

	pDevice2->GetTransform(D3DTS_VIEW, &View);

	D3DXMatrixInverse(&ViewInv, NULL, &View);

	ViewInv._41 = ViewInv._42 = ViewInv._43 = 0.0f;

	for (int i = 0; i < KASOKU_EFFECT_MAX; i++)
	{
		g_Kasoku_effect[i].pos = CX_model::XmodelPos();
		//アニメーション数 * アニメーションの遅延 以上の物は削除
		if (g_Kasoku_effect[i].nAnimCount > Texture_Kasoku_effect[g_Kasoku_effect[i].color].Acount * slow)
		{
			g_Kasoku_effect[i].bUse = false;
			g_Kasoku_effect[i].nAnimCount = 0;
		}

		if (g_Kasoku_effect[i].bUse)
		{
			g_Kasoku_effect[i].nAnimCount++;
		}
	}

}
void CKasokuEffect::DrawKasoku_effect(void)
{
	pDevice2 = CRender::GetD3DDevice();

	pDevice2->SetRenderState(D3DRS_LIGHTING, FALSE);

	pDevice2->SetFVF(FVF_VERTEX_KASOKU_EFFECT);

	//αテスト開始
	pDevice2->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice2->SetRenderState(D3DRS_ALPHAREF, 150);
	pDevice2->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	for (int i = 0; i < KASOKU_EFFECT_MAX; i++)
	{

		if (g_Kasoku_effect[i].bUse)
		{
			pDevice2->SetTexture(0, g_Textures_Kasoku_effect[g_Kasoku_effect[i].color]);

			int anime = g_Kasoku_effect[i].nAnimCount / slow;

			float u0 = (float)Texture_Kasoku_effect[g_Kasoku_effect[i].color].Xsize * (anime % Texture_Kasoku_effect[g_Kasoku_effect[i].color].Xcount) / Texture_Kasoku_effect[g_Kasoku_effect[i].color].width;
			float v0 = (float)Texture_Kasoku_effect[g_Kasoku_effect[i].color].Ysize * (anime / Texture_Kasoku_effect[g_Kasoku_effect[i].color].Xcount) / Texture_Kasoku_effect[g_Kasoku_effect[i].color].height;
			float u1 = (float)(Texture_Kasoku_effect[g_Kasoku_effect[i].color].Xsize * (anime % Texture_Kasoku_effect[g_Kasoku_effect[i].color].Xcount) + Texture_Kasoku_effect[g_Kasoku_effect[i].color].Xsize) / Texture_Kasoku_effect[g_Kasoku_effect[i].color].width;
			float v1 = (float)(Texture_Kasoku_effect[g_Kasoku_effect[i].color].Ysize * (anime / Texture_Kasoku_effect[g_Kasoku_effect[i].color].Xcount) + Texture_Kasoku_effect[g_Kasoku_effect[i].color].Ysize) / Texture_Kasoku_effect[g_Kasoku_effect[i].color].height;

			VERTEX_KASOKU_EFFECT v[] = {

				{ D3DXVECTOR3(-5,  5,  0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u0, v0) },
				{ D3DXVECTOR3(5,  5,  0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u1, v0) },
				{ D3DXVECTOR3(-5, -5,  0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u0, v1) },
				{ D3DXVECTOR3(5, -5,  0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u1, v1) },

			};

			D3DXMatrixIdentity(&g_WorldKasoku_effect);

			D3DXMatrixTranslation(&Trans[i], g_Kasoku_effect[i].pos.x, g_Kasoku_effect[i].pos.y, g_Kasoku_effect[i].pos.z);

			g_WorldKasoku_effect = g_WorldKasoku_effect * ViewInv;

			g_WorldKasoku_effect = g_WorldKasoku_effect * Trans[i];

			//各種行列の設定(好きなタイミングで呼ぶ)
			pDevice2->SetTransform(D3DTS_WORLD, &g_WorldKasoku_effect);

			pDevice2->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &v[0], sizeof(VERTEX_KASOKU_EFFECT));
		}
	}
}

void CKasokuEffect::CreateKasoku_effect(float x, float y, float z)
{
		if (!g_Kasoku_effect[0].bUse)
		{
			g_Kasoku_effect[0].bUse = true;
			g_Kasoku_effect[0].nAnimCount = 0;
			g_Kasoku_effect[0].pos = D3DXVECTOR3(x, y, z);
	}
}
