//-----------------------------------//
//ジャンプエフェクト処理-[jumo_effect.cpp]-//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#include "jump_effect.h"
#include "main.h"
#include "renderer.h"
#include "player.h"
//-------------------------------------------------------------------
//　変数宣言
//-------------------------------------------------------------------
#define FVF_VERTEX_JUMP_EFFECt (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

LPDIRECT3DTEXTURE9 CJumpEffect::g_Textures_Jump_Effect[JUMP_EFFECT_TEX_MAX] = { NULL };
JUMP_EFFECT CJumpEffect::g_Jump_Effect[JUMP_EFFECT_MAX];
D3DXMATRIX CJumpEffect::g_WorldJump_Effect;
D3DXMATRIX CJumpEffect::View, CJumpEffect::ViewInv;
D3DXMATRIX CJumpEffect::Trans[JUMP_EFFECT_MAX];
int CJumpEffect::g_nFramecount = 0;
int CJumpEffect::slow = 2; //アニメーションの遅延

typedef struct
{
	D3DXVECTOR3 pos;
	D3DCOLOR color;
	D3DXVECTOR2 texture;
}VERTEX_JUMP_EFFECT;

//-------------------------------------------------------------------
//　関数宣言
//-------------------------------------------------------------------

void CJumpEffect::InitJump_Effect(void)
{
	for (int i = 0; i < JUMP_EFFECT_MAX; i++)
	{
		g_Jump_Effect[i].bUse = false;
		g_Jump_Effect[i].color = 0;
		g_Jump_Effect[i].nAnimCount = 0;
	}

	LPDIRECT3DDEVICE9  pDevice = CRender::GetD3DDevice();

	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);

	if (pDevice == NULL)
	{
		return;
	}

	HRESULT hr;

	for (int tex = 0; tex<JUMP_EFFECT_TEX_MAX; tex++)
	{

		hr = D3DXCreateTextureFromFile(pDevice, Texture_Jump_Effect[tex].fileName, &g_Textures_Jump_Effect[tex]);

		if (FAILED(hr))
		{
			MessageBox(NULL, "読み込めません12", "エラー", MB_OK);
			return;
		}
	}

}
void CJumpEffect::UninitJump_Effect(void)
{

	for (int i = 0; i < JUMP_EFFECT_TEX_MAX; i++)
	{
		if (g_Textures_Jump_Effect[i] != NULL)
		{
			g_Textures_Jump_Effect[i]->Release();
			g_Textures_Jump_Effect[i] = NULL;
		}
	}
}
void CJumpEffect::UpdateJump_Effect(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRender::GetD3DDevice();

	if (pDevice == NULL) { return; }

	D3DXMatrixIdentity(&g_WorldJump_Effect);

	pDevice->GetTransform(D3DTS_VIEW, &View);

	D3DXMatrixInverse(&ViewInv, NULL, &View);

	ViewInv._41 = ViewInv._42 = ViewInv._43 = 0.0f;

	for (int i = 0; i < JUMP_EFFECT_MAX; i++)
	{
		g_Jump_Effect[i].pos = CX_model::XmodelPos();

		g_Jump_Effect[i].pos.y = CX_model::XmodelPos().y + 0.3f;

		//アニメーション数 * アニメーションの遅延 以上の物は削除
		if (g_Jump_Effect[i].nAnimCount > Texture_Jump_Effect[g_Jump_Effect[i].color].Acount * slow)
		{
			g_Jump_Effect[i].bUse = false;
			g_Jump_Effect[i].nAnimCount = 0;
		}

		if (g_Jump_Effect[i].bUse)
		{
			g_Jump_Effect[i].nAnimCount++;
		}
	}

}
void CJumpEffect::DrawJump_Effect(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRender::GetD3DDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	pDevice->SetFVF(FVF_VERTEX_JUMP_EFFECt);

	//αテスト開始
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	for (int i = 0; i < JUMP_EFFECT_MAX; i++)
	{

		if (g_Jump_Effect[i].bUse)
		{
			pDevice->SetTexture(0, g_Textures_Jump_Effect[g_Jump_Effect[i].color]);

			int anime = g_Jump_Effect[i].nAnimCount / slow;

			float u0 = (float)Texture_Jump_Effect[g_Jump_Effect[i].color].Xsize * (anime % Texture_Jump_Effect[g_Jump_Effect[i].color].Xcount) / Texture_Jump_Effect[g_Jump_Effect[i].color].width;
			float v0 = (float)Texture_Jump_Effect[g_Jump_Effect[i].color].Ysize * (anime / Texture_Jump_Effect[g_Jump_Effect[i].color].Xcount) / Texture_Jump_Effect[g_Jump_Effect[i].color].height;
			float u1 = (float)(Texture_Jump_Effect[g_Jump_Effect[i].color].Xsize * (anime % Texture_Jump_Effect[g_Jump_Effect[i].color].Xcount) + Texture_Jump_Effect[g_Jump_Effect[i].color].Xsize) / Texture_Jump_Effect[g_Jump_Effect[i].color].width;
			float v1 = (float)(Texture_Jump_Effect[g_Jump_Effect[i].color].Ysize * (anime / Texture_Jump_Effect[g_Jump_Effect[i].color].Xcount) + Texture_Jump_Effect[g_Jump_Effect[i].color].Ysize) / Texture_Jump_Effect[g_Jump_Effect[i].color].height;

			VERTEX_JUMP_EFFECT v[] = {

				{ D3DXVECTOR3(-1.0f,  1.5f,  0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u0, v0) },
				{ D3DXVECTOR3(1.0f,  1.5f,  0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u1, v0) },
				{ D3DXVECTOR3(-1.0f, -1.0f,  0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u0, v1) },
				{ D3DXVECTOR3(1.0f, -1.0f,  0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u1, v1) },

			};

			D3DXMatrixIdentity(&g_WorldJump_Effect);

			D3DXMatrixTranslation(&Trans[i], g_Jump_Effect[i].pos.x, g_Jump_Effect[i].pos.y, g_Jump_Effect[i].pos.z);

			g_WorldJump_Effect = g_WorldJump_Effect * ViewInv;

			g_WorldJump_Effect = g_WorldJump_Effect * Trans[i];

			//各種行列の設定(好きなタイミングで呼ぶ)
			pDevice->SetTransform(D3DTS_WORLD, &g_WorldJump_Effect);

			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &v[0], sizeof(VERTEX_JUMP_EFFECT));

		}

	}

}

void CJumpEffect::CreateJump_Effect(float x, float y, float z)
{
	for (int i = 0; i < JUMP_EFFECT_MAX; i++)
	{
		if (!g_Jump_Effect[i].bUse)
		{
			g_Jump_Effect[i].bUse = true;
			g_Jump_Effect[i].nAnimCount = 0;
			g_Jump_Effect[i].pos = D3DXVECTOR3(x, y, z);
			break;
		}
	}
}
