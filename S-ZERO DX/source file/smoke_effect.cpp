//-----------------------------------//
//-----スモークエフェクト処理--------//
//----[smoke_effect.cpp]--------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#include "smoke_effect.h"
#include "main.h"
#include "renderer.h"
#include "player.h"
//-------------------------------------------------------------------
//　変数宣言
//-------------------------------------------------------------------

#define FVF_VERTEX_SMOKEEFFECT (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

LPDIRECT3DTEXTURE9 CSmokeEffect::g_Textures_smoke_explosion[SMOKE_EXPLOSION_TEX_MAX] = { NULL };
SMOKE_EXPLOSION CSmokeEffect::g_smoke_explosion[SMOKE_EXPLOSION_MAX];
D3DXMATRIX CSmokeEffect::g_Worldsmoke_explosion;
D3DXMATRIX CSmokeEffect::View, CSmokeEffect::ViewInv;
D3DXMATRIX CSmokeEffect::Trans[SMOKE_EXPLOSION_MAX];
int CSmokeEffect::g_nFramecount = 0;
int CSmokeEffect::slow = 5; //アニメーションの遅延

typedef struct
{
	D3DXVECTOR3 pos;
	D3DCOLOR color;
	D3DXVECTOR2 texture;
}VERTEX_SMOKE_EXPLOSION;

//-------------------------------------------------------------------
//　関数宣言
//-------------------------------------------------------------------

void CSmokeEffect::Initsmoke_explosion(void)
{
	for (int i = 0; i < SMOKE_EXPLOSION_MAX; i++)
	{
		g_smoke_explosion[i].bUse = false;
		g_smoke_explosion[i].color = 0;
		g_smoke_explosion[i].nAnimCount = 0;
	}

	LPDIRECT3DDEVICE9  pDevice = CRender::GetD3DDevice();

	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);

	if (pDevice == NULL)
	{
		return;
	}

	HRESULT hr;

	for (int tex = 0; tex<SMOKE_EXPLOSION_TEX_MAX; tex++)
	{

		hr = D3DXCreateTextureFromFile(pDevice, Texture_smoke_explosion[tex].fileName, &g_Textures_smoke_explosion[tex]);

		if (FAILED(hr))
		{
			MessageBox(NULL, "読み込めません12", "エラー", MB_OK);
			return;
		}
	}

}
void CSmokeEffect::Uninitsmoke_explosion(void)
{

	for (int i = 0; i < SMOKE_EXPLOSION_TEX_MAX; i++)
	{
		if (g_Textures_smoke_explosion[i] != NULL)
		{
			g_Textures_smoke_explosion[i]->Release();
			g_Textures_smoke_explosion[i] = NULL;
		}
	}
}
void CSmokeEffect::Updatesmoke_explosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRender::GetD3DDevice();

	if (pDevice == NULL) { return; }

	D3DXMatrixIdentity(&g_Worldsmoke_explosion);

	pDevice->GetTransform(D3DTS_VIEW, &View);

	D3DXMatrixInverse(&ViewInv, NULL, &View);

	ViewInv._41 = ViewInv._42 = ViewInv._43 = 0.0f;

	for (int i = 0; i < SMOKE_EXPLOSION_MAX; i++)
	{
		//g_smoke_explosion[i].pos = CX_model::XmodelPos();
		//アニメーション数 * アニメーションの遅延 以上の物は削除
		if (g_smoke_explosion[i].nAnimCount > Texture_smoke_explosion[g_smoke_explosion[i].color].Acount * slow)
		{
			g_smoke_explosion[i].bUse = false;
			g_smoke_explosion[i].nAnimCount = 0;
		}

		if (g_smoke_explosion[i].bUse)
		{
			g_smoke_explosion[i].nAnimCount++;
		}
	}

}
void CSmokeEffect::Drawsmoke_explosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRender::GetD3DDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	pDevice->SetFVF(FVF_VERTEX_SMOKEEFFECT);

	//αテスト開始
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	for (int i = 0; i < SMOKE_EXPLOSION_MAX; i++)
	{

		if (g_smoke_explosion[i].bUse)
		{
			pDevice->SetTexture(0, g_Textures_smoke_explosion[g_smoke_explosion[i].color]);
			int anime = g_smoke_explosion[i].nAnimCount / slow;

			float u0 = (float)Texture_smoke_explosion[g_smoke_explosion[i].color].Xsize * (anime % Texture_smoke_explosion[g_smoke_explosion[i].color].Xcount) / Texture_smoke_explosion[g_smoke_explosion[i].color].width;
			float v0 = (float)Texture_smoke_explosion[g_smoke_explosion[i].color].Ysize * (anime / Texture_smoke_explosion[g_smoke_explosion[i].color].Xcount) / Texture_smoke_explosion[g_smoke_explosion[i].color].height;
			float u1 = (float)(Texture_smoke_explosion[g_smoke_explosion[i].color].Xsize * (anime % Texture_smoke_explosion[g_smoke_explosion[i].color].Xcount) + Texture_smoke_explosion[g_smoke_explosion[i].color].Xsize) / Texture_smoke_explosion[g_smoke_explosion[i].color].width;
			float v1 = (float)(Texture_smoke_explosion[g_smoke_explosion[i].color].Ysize * (anime / Texture_smoke_explosion[g_smoke_explosion[i].color].Xcount) + Texture_smoke_explosion[g_smoke_explosion[i].color].Ysize) / Texture_smoke_explosion[g_smoke_explosion[i].color].height;

			VERTEX_SMOKE_EXPLOSION v[] = {

				{ D3DXVECTOR3(-0.4f,  0.8f,  -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u0, v0) },
				{ D3DXVECTOR3(0.4f,  0.8f,  -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u1, v0) },
				{ D3DXVECTOR3(-0.4f, 0.2f,  -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u0, v1) },
				{ D3DXVECTOR3(0.4f, 0.2f,  -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u1, v1) },

			};

			D3DXMatrixIdentity(&g_Worldsmoke_explosion);

			D3DXMatrixTranslation(&Trans[i], g_smoke_explosion[i].pos.x, g_smoke_explosion[i].pos.y, g_smoke_explosion[i].pos.z);

			g_Worldsmoke_explosion = g_Worldsmoke_explosion * ViewInv;

			g_Worldsmoke_explosion = g_Worldsmoke_explosion * Trans[i];

			//各種行列の設定(好きなタイミングで呼ぶ)
			pDevice->SetTransform(D3DTS_WORLD, &g_Worldsmoke_explosion);

			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &v[0], sizeof(VERTEX_SMOKE_EXPLOSION));
		}
	}
}

void CSmokeEffect::Createsmoke_explosion(float x, float y, float z)
{
	for (int i = 0; i < SMOKE_EXPLOSION_MAX; i++)
	{
		if (!g_smoke_explosion[i].bUse)
		{
			g_smoke_explosion[i].bUse = true;
			g_smoke_explosion[i].nAnimCount = rand() % 100;
			g_smoke_explosion[i].pos = D3DXVECTOR3(x, y, z);
			break;
		}
	}
}
