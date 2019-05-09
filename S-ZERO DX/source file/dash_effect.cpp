//-----------------------------------//
//ダッシュエフェクト処理-[dash_effect.cpp]-//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#include "dash_effect.h"
#include "main.h"
#include "renderer.h"
#include "player.h"
//-------------------------------------------------------------------
//　変数宣言
//-------------------------------------------------------------------

#define FVF_VERTEX_DASH_EFFECT (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

LPDIRECT3DTEXTURE9 CDashEffect::g_Textures_dash_effect[DASH_EFFECT_TEX_MAX] = { NULL };
DASH_EFFECT CDashEffect::g_dash_effect[DASH_EFFECT_MAX];
D3DXMATRIX CDashEffect::g_Worlddash_effect;
D3DXMATRIX CDashEffect::View, CDashEffect::ViewInv;
D3DXMATRIX CDashEffect::Trans[DASH_EFFECT_MAX];
int CDashEffect::g_nFramecount = 0;
int CDashEffect::slow = 3; //アニメーションの遅延

typedef struct
{
	D3DXVECTOR3 pos;
	D3DCOLOR color;
	D3DXVECTOR2 texture;
}VERTEX_DASH_EFFECT;

//-------------------------------------------------------------------
//　関数宣言
//-------------------------------------------------------------------

void CDashEffect::Initdash_effect(void)
{
	for (int i = 0; i < DASH_EFFECT_MAX; i++)
	{
		g_dash_effect[i].bUse = false;
		g_dash_effect[i].color = 0;
		g_dash_effect[i].nAnimCount = 0;
	}

	LPDIRECT3DDEVICE9  pDevice = CRender::GetD3DDevice();

	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);

	if (pDevice == NULL)
	{
		return;
	}

	HRESULT hr;

	for (int tex = 0; tex<DASH_EFFECT_TEX_MAX; tex++)
	{

		hr = D3DXCreateTextureFromFile(pDevice, Texture_dash_effect[tex].fileName, &g_Textures_dash_effect[tex]);

		if (FAILED(hr))
		{
			MessageBox(NULL, "読み込めません12", "エラー", MB_OK);
			return;
		}
	}

}
void CDashEffect::Uninitdash_effect(void)
{

	for (int i = 0; i < DASH_EFFECT_TEX_MAX; i++)
	{
		if (g_Textures_dash_effect[i] != NULL)
		{
			g_Textures_dash_effect[i]->Release();
			g_Textures_dash_effect[i] = NULL;
		}
	}
}
void CDashEffect::Updatedash_effect(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRender::GetD3DDevice();

	if (pDevice == NULL) { return; }

	D3DXMatrixIdentity(&g_Worlddash_effect);

	pDevice->GetTransform(D3DTS_VIEW, &View);

	D3DXMatrixInverse(&ViewInv, NULL, &View);

	ViewInv._41 = ViewInv._42 = ViewInv._43 = 0.0f;

	for (int i = 0; i < DASH_EFFECT_MAX; i++)
	{
		g_dash_effect[i].pos = CX_model::XmodelPos();
		g_dash_effect[i].pos.y = CX_model::XmodelPos().y + 0.5f;
		//アニメーション数 * アニメーションの遅延 以上の物は削除
		if (g_dash_effect[i].nAnimCount > Texture_dash_effect[g_dash_effect[i].color].Acount * slow)
		{
			g_dash_effect[i].bUse = false;
			g_dash_effect[i].nAnimCount = 0;
		}

		if (g_dash_effect[i].bUse)
		{
			g_dash_effect[i].nAnimCount++;
		}
	}

}
void CDashEffect::Drawdash_effect(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRender::GetD3DDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	pDevice->SetFVF(FVF_VERTEX_DASH_EFFECT);

	//αテスト開始
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	for (int i = 0; i < DASH_EFFECT_MAX; i++)
	{

		if (g_dash_effect[i].bUse)
		{
			pDevice->SetTexture(0, g_Textures_dash_effect[g_dash_effect[i].color]);

			int anime = g_dash_effect[i].nAnimCount / slow;

			float u0 = (float)Texture_dash_effect[g_dash_effect[i].color].Xsize * (anime % Texture_dash_effect[g_dash_effect[i].color].Xcount) / Texture_dash_effect[g_dash_effect[i].color].width;
			float v0 = (float)Texture_dash_effect[g_dash_effect[i].color].Ysize * (anime / Texture_dash_effect[g_dash_effect[i].color].Xcount) / Texture_dash_effect[g_dash_effect[i].color].height;
			float u1 = (float)(Texture_dash_effect[g_dash_effect[i].color].Xsize * (anime % Texture_dash_effect[g_dash_effect[i].color].Xcount) + Texture_dash_effect[g_dash_effect[i].color].Xsize) / Texture_dash_effect[g_dash_effect[i].color].width;
			float v1 = (float)(Texture_dash_effect[g_dash_effect[i].color].Ysize * (anime / Texture_dash_effect[g_dash_effect[i].color].Xcount) + Texture_dash_effect[g_dash_effect[i].color].Ysize) / Texture_dash_effect[g_dash_effect[i].color].height;

			VERTEX_DASH_EFFECT v[] = {

				{ D3DXVECTOR3(-1.5f,  1.9f,  0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u0, v0) },
				{ D3DXVECTOR3(1.5f,  1.9f,  0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u1, v0) },
				{ D3DXVECTOR3(-1.5f, -1.1f,  0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u0, v1) },
				{ D3DXVECTOR3(1.5f, -1.1f,  0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u1, v1) },

			};

			D3DXMatrixIdentity(&g_Worlddash_effect);

			D3DXMatrixTranslation(&Trans[i], g_dash_effect[i].pos.x, g_dash_effect[i].pos.y, g_dash_effect[i].pos.z);

			g_Worlddash_effect = g_Worlddash_effect * ViewInv;

			g_Worlddash_effect = g_Worlddash_effect * Trans[i];

			//各種行列の設定(好きなタイミングで呼ぶ)
			pDevice->SetTransform(D3DTS_WORLD, &g_Worlddash_effect);

			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &v[0], sizeof(VERTEX_DASH_EFFECT));

		}
	}
}

void CDashEffect::Createdash_effect(float x, float y, float z)
{
		if (!g_dash_effect[0].bUse)
		{
			g_dash_effect[0].bUse = true;
			g_dash_effect[0].nAnimCount = 0;
			g_dash_effect[0].pos = D3DXVECTOR3(x, y, z);
	}
}
