//-----------------------------------//
//-スターエフェクト処理-[star_effect.h]-//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#include "star_effect.h"
#include "main.h"
#include "renderer.h"
#include "player.h"
//-------------------------------------------------------------------
//　変数宣言
//-------------------------------------------------------------------

#define FVF_VERTEX_STAR_EFFECT (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

LPDIRECT3DTEXTURE9 CStarEffect::g_Textures_Star_effect[STAR_EFFECT_TEX_MAX] = { NULL };
STAR_EFFECT CStarEffect::g_Star_effect[STAR_EFFECT_MAX];
int CStarEffect::g_nFramecount = 0;
D3DXMATRIX CStarEffect::g_WorldStar_effect;
D3DXMATRIX CStarEffect::View, CStarEffect::ViewInv;
D3DXMATRIX CStarEffect::Trans[STAR_EFFECT_MAX];
int CStarEffect::slow = 4; //アニメーションの遅延

typedef struct
{
	D3DXVECTOR3 pos;
	D3DCOLOR color;
	D3DXVECTOR2 texture;
}VERTEX_STAR_EFFECT;

//-------------------------------------------------------------------
//　関数宣言
//-------------------------------------------------------------------

void CStarEffect::InitStar_effect(void)
{
	for (int i = 0; i < STAR_EFFECT_MAX; i++)
	{
		g_Star_effect[i].bUse = false;
		g_Star_effect[i].color = 0;
		g_Star_effect[i].nAnimCount = 0;
	}

	LPDIRECT3DDEVICE9  pDevice = CRender::GetD3DDevice();

	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);

	if (pDevice == NULL)
	{
		return;
	}

	HRESULT hr;

	for (int tex = 0; tex<STAR_EFFECT_TEX_MAX; tex++)
	{

		hr = D3DXCreateTextureFromFile(pDevice, Texture_Star_effect[tex].fileName, &g_Textures_Star_effect[tex]);

		if (FAILED(hr))
		{
			MessageBox(NULL, "読み込めません12", "エラー", MB_OK);
			return;
		}
	}

}
void CStarEffect::UninitStar_effect(void)
{

	for (int i = 0; i < STAR_EFFECT_TEX_MAX; i++)
	{
		if (g_Textures_Star_effect[i] != NULL)
		{
			g_Textures_Star_effect[i]->Release();
			g_Textures_Star_effect[i] = NULL;
		}
	}
}
void CStarEffect::UpdateStar_effect(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRender::GetD3DDevice();

	if (pDevice == NULL) { return; }

	D3DXMatrixIdentity(&g_WorldStar_effect);

	pDevice->GetTransform(D3DTS_VIEW, &View);

	D3DXMatrixInverse(&ViewInv, NULL, &View);

	ViewInv._41 = ViewInv._42 = ViewInv._43 = 0.0f;

	for (int i = 0; i < STAR_EFFECT_MAX; i++)
	{
		g_Star_effect[i].pos = CX_model::XmodelPos();

		//アニメーション数 * アニメーションの遅延 以上の物は削除
		if (g_Star_effect[i].nAnimCount > Texture_Star_effect[g_Star_effect[i].color].Acount * slow)
		{
			g_Star_effect[i].bUse = false;
			g_Star_effect[i].nAnimCount = 0;
		}

		if (g_Star_effect[i].bUse)
		{
			g_Star_effect[i].nAnimCount++;
		}
	}


}
void CStarEffect::DrawStar_effect(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRender::GetD3DDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	pDevice->SetFVF(FVF_VERTEX_STAR_EFFECT);

	//αテスト開始
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	for (int i = 0; i < STAR_EFFECT_MAX; i++)
	{

		if (g_Star_effect[i].bUse)
		{
			pDevice->SetTexture(0, g_Textures_Star_effect[g_Star_effect[i].color]);

			int anime = g_Star_effect[i].nAnimCount / slow;

			float u0 = (float)Texture_Star_effect[g_Star_effect[i].color].Xsize * (anime % Texture_Star_effect[g_Star_effect[i].color].Xcount) / Texture_Star_effect[g_Star_effect[i].color].width;
			float v0 = (float)Texture_Star_effect[g_Star_effect[i].color].Ysize * (anime / Texture_Star_effect[g_Star_effect[i].color].Xcount) / Texture_Star_effect[g_Star_effect[i].color].height;
			float u1 = (float)(Texture_Star_effect[g_Star_effect[i].color].Xsize * (anime % Texture_Star_effect[g_Star_effect[i].color].Xcount) + Texture_Star_effect[g_Star_effect[i].color].Xsize) / Texture_Star_effect[g_Star_effect[i].color].width;
			float v1 = (float)(Texture_Star_effect[g_Star_effect[i].color].Ysize * (anime / Texture_Star_effect[g_Star_effect[i].color].Xcount) + Texture_Star_effect[g_Star_effect[i].color].Ysize) / Texture_Star_effect[g_Star_effect[i].color].height;

			VERTEX_STAR_EFFECT v[] = {

				{ D3DXVECTOR3(-0.5f,  1.6f, -1.5f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u0, v0) },
				{ D3DXVECTOR3(0.5f,  1.6f,  -1.5f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u1, v0) },
				{ D3DXVECTOR3(-0.5f, 0.1f,  -1.5f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u0, v1) },
				{ D3DXVECTOR3(0.5f, 0.1f,  -1.5f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u1, v1) },

			};

			D3DXMatrixIdentity(&g_WorldStar_effect);

			D3DXMatrixTranslation(&Trans[i], g_Star_effect[i].pos.x, g_Star_effect[i].pos.y, g_Star_effect[i].pos.z);

			g_WorldStar_effect = g_WorldStar_effect * ViewInv;

			g_WorldStar_effect = g_WorldStar_effect * Trans[i];

			//各種行列の設定(好きなタイミングで呼ぶ)
			pDevice->SetTransform(D3DTS_WORLD, &g_WorldStar_effect);

			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &v[0], sizeof(VERTEX_STAR_EFFECT));

		}

	}

}

void CStarEffect::CreateStar_effect(float x, float y, float z)
{
	for (int i = 0; i < STAR_EFFECT_MAX; i++)
	{
		if (!g_Star_effect[i].bUse)
		{
			g_Star_effect[i].bUse = true;
			g_Star_effect[i].nAnimCount = rand() % 100;;
			g_Star_effect[i].pos = D3DXVECTOR3(x, y, z);
			break;
		}
	}
}
