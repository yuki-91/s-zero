//-----------------------------------//
//-ドリフトエフェクトミニ処理-[drifting_effect_mini.cpp]-//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#include "drifting_effect_mini.h"
#include "main.h"
#include "renderer.h"
#include "player.h"
//-------------------------------------------------------------------
//　変数宣言
//-------------------------------------------------------------------

#define FVF_VERTEX_DRIFTING_M_EFFECT (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

LPDIRECT3DTEXTURE9 CDrifting_MEffect::g_Textures_Drifting_M_effect[DRIFTING_M_EFFECT_TEX_MAX] = { NULL };
DRIFTING_M_EFFECT CDrifting_MEffect::g_Drifting_M_effect[DRIFTING_M_EFFECT_MAX];
int CDrifting_MEffect::g_nFramecount = 0;
D3DXMATRIX CDrifting_MEffect::g_WorldDrifting_M_effect;
D3DXMATRIX CDrifting_MEffect::View, CDrifting_MEffect::ViewInv;
D3DXMATRIX CDrifting_MEffect::Trans[DRIFTING_M_EFFECT_MAX];
int CDrifting_MEffect::slow = 2; //アニメーションの遅延

typedef struct
{
	D3DXVECTOR3 pos;
	D3DCOLOR color;
	D3DXVECTOR2 texture;
}VERTEX_DRIFTING_M_EFFECT;

//-------------------------------------------------------------------
//　関数宣言
//-------------------------------------------------------------------

void CDrifting_MEffect::InitDrifting_M_effect(void)
{
	for (int i = 0; i < DRIFTING_M_EFFECT_MAX; i++)
	{
		g_Drifting_M_effect[i].bUse = false;
		g_Drifting_M_effect[i].color = 0;
		g_Drifting_M_effect[i].nAnimCount = 0;
	}

	LPDIRECT3DDEVICE9  pDevice = CRender::GetD3DDevice();

	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);

	if (pDevice == NULL)
	{
		return;
	}

	HRESULT hr;

	for (int tex = 0; tex<DRIFTING_M_EFFECT_TEX_MAX; tex++)
	{

		hr = D3DXCreateTextureFromFile(pDevice, Texture_Drifting_M_effect[tex].fileName, &g_Textures_Drifting_M_effect[tex]);

		if (FAILED(hr))
		{
			MessageBox(NULL, "読み込めません12", "エラー", MB_OK);
			return;
		}
	}

}
void CDrifting_MEffect::UninitDrifting_M_effect(void)
{

	for (int i = 0; i < DRIFTING_M_EFFECT_TEX_MAX; i++)
	{
		if (g_Textures_Drifting_M_effect[i] != NULL)
		{
			g_Textures_Drifting_M_effect[i]->Release();
			g_Textures_Drifting_M_effect[i] = NULL;
		}
	}
}
void CDrifting_MEffect::UpdateDrifting_M_effect(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRender::GetD3DDevice();

	if (pDevice == NULL) { return; }

	D3DXMatrixIdentity(&g_WorldDrifting_M_effect);

	pDevice->GetTransform(D3DTS_VIEW, &View);

	D3DXMatrixInverse(&ViewInv, NULL, &View);

	ViewInv._41 = ViewInv._42 = ViewInv._43 = 0.0f;

	for (int i = 0; i < DRIFTING_M_EFFECT_MAX; i++)
	{
		g_Drifting_M_effect[i].pos = CX_model::XmodelPos();

		//アニメーション数 * アニメーションの遅延 以上の物は削除
		if (g_Drifting_M_effect[i].nAnimCount > Texture_Drifting_M_effect[g_Drifting_M_effect[i].color].Acount * slow)
		{
			g_Drifting_M_effect[i].bUse = false;
			g_Drifting_M_effect[i].nAnimCount = 0;
		}

		if (g_Drifting_M_effect[i].bUse)
		{
			g_Drifting_M_effect[i].nAnimCount++;
		}
	}


}
void CDrifting_MEffect::DrawDrifting_M_effect(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRender::GetD3DDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	pDevice->SetFVF(FVF_VERTEX_DRIFTING_M_EFFECT);

	//αテスト開始
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	for (int i = 0; i < DRIFTING_M_EFFECT_MAX; i++)
	{

		if (g_Drifting_M_effect[i].bUse)
		{
			pDevice->SetTexture(0, g_Textures_Drifting_M_effect[g_Drifting_M_effect[i].color]);

			int anime = g_Drifting_M_effect[i].nAnimCount / slow;

			float u0 = (float)Texture_Drifting_M_effect[g_Drifting_M_effect[i].color].Xsize * (anime % Texture_Drifting_M_effect[g_Drifting_M_effect[i].color].Xcount) / Texture_Drifting_M_effect[g_Drifting_M_effect[i].color].width;
			float v0 = (float)Texture_Drifting_M_effect[g_Drifting_M_effect[i].color].Ysize * (anime / Texture_Drifting_M_effect[g_Drifting_M_effect[i].color].Xcount) / Texture_Drifting_M_effect[g_Drifting_M_effect[i].color].height;
			float u1 = (float)(Texture_Drifting_M_effect[g_Drifting_M_effect[i].color].Xsize * (anime % Texture_Drifting_M_effect[g_Drifting_M_effect[i].color].Xcount) + Texture_Drifting_M_effect[g_Drifting_M_effect[i].color].Xsize) / Texture_Drifting_M_effect[g_Drifting_M_effect[i].color].width;
			float v1 = (float)(Texture_Drifting_M_effect[g_Drifting_M_effect[i].color].Ysize * (anime / Texture_Drifting_M_effect[g_Drifting_M_effect[i].color].Xcount) + Texture_Drifting_M_effect[g_Drifting_M_effect[i].color].Ysize) / Texture_Drifting_M_effect[g_Drifting_M_effect[i].color].height;

			VERTEX_DRIFTING_M_EFFECT v[] = {

				{ D3DXVECTOR3(-0.4f,  0.7f, -0.5f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u0, v0) },
				{ D3DXVECTOR3(0.4f,  0.7f,  -0.5f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u1, v0) },
				{ D3DXVECTOR3(-0.4f, -0.1f,  -0.5f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u0, v1) },
				{ D3DXVECTOR3(0.4f, -0.1f,  -0.5f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u1, v1) },

			};

			D3DXMatrixIdentity(&g_WorldDrifting_M_effect);

			D3DXMatrixTranslation(&Trans[i], g_Drifting_M_effect[i].pos.x, g_Drifting_M_effect[i].pos.y, g_Drifting_M_effect[i].pos.z);

			g_WorldDrifting_M_effect = g_WorldDrifting_M_effect * ViewInv;

			g_WorldDrifting_M_effect = g_WorldDrifting_M_effect * Trans[i];

			//各種行列の設定(好きなタイミングで呼ぶ)
			pDevice->SetTransform(D3DTS_WORLD, &g_WorldDrifting_M_effect);

			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &v[0], sizeof(VERTEX_DRIFTING_M_EFFECT));

		}

	}

}

void CDrifting_MEffect::CreateDrifting_M_effect(float x, float y, float z)
{
	for (int i = 0; i < DRIFTING_M_EFFECT_MAX; i++)
	{
		if (!g_Drifting_M_effect[i].bUse)
		{
			g_Drifting_M_effect[i].bUse = true;
			g_Drifting_M_effect[i].nAnimCount = rand() % 100;;
			g_Drifting_M_effect[i].pos = D3DXVECTOR3(x, y, z);
			break;
		}
	}
}
