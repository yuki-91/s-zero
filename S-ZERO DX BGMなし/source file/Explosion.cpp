//-----------------------------------//
//------爆発描画処理-[explosion.cpp]-//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#include "Explosion.h"
#include "main.h"
#include "renderer.h"
//-------------------------------------------------------------------
//　変数宣言
//-------------------------------------------------------------------

#define FVF_VERTEX_EXPLOSION (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

LPDIRECT3DTEXTURE9 CExplosion::g_Textures_Explosion[EXPLOSION_TEX_MAX] = { NULL };
EXPLOSION CExplosion::g_Explosion[EXPLOSION_MAX];
int CExplosion::g_nFramecount = 0;
D3DXMATRIX CExplosion::g_WorldExplosion;
D3DXMATRIX CExplosion::View, CExplosion::ViewInv;
D3DXMATRIX CExplosion::Trans[EXPLOSION_MAX];
int CExplosion::slow = 5; //アニメーションの遅延

typedef struct
{
	D3DXVECTOR3 pos;
	D3DCOLOR color;
	D3DXVECTOR2 texture;
}VERTEX_EXPLOSION;

//-------------------------------------------------------------------
//　関数宣言
//-------------------------------------------------------------------

void CExplosion::InitExplosion(void)
{
	for (int i = 0;i < EXPLOSION_MAX;i++)
	{
		g_Explosion[i].bUse = false;
		g_Explosion[i].color = 0;
		g_Explosion[i].nAnimCount = 0;
	}

	LPDIRECT3DDEVICE9  pDevice = CRender::GetD3DDevice();

	pDevice ->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);

	if(pDevice == NULL)
	{
		return ;
	}

	HRESULT hr;

	for(int tex = 0 ; tex<EXPLOSION_TEX_MAX ; tex++)
	{

		hr = D3DXCreateTextureFromFile(pDevice,Texture_Explosion[tex].fileName, &g_Textures_Explosion[tex]);

		if(FAILED(hr))
		{
			MessageBox(NULL, "読み込めません12", "エラー", MB_OK);
			return ;
		}
	}

}
void CExplosion::UninitExplosion(void)
{

	for(int i = 0 ; i < EXPLOSION_TEX_MAX ; i++)
	{
		if (g_Textures_Explosion[i] != NULL)
		{
			g_Textures_Explosion[i] ->Release();
			g_Textures_Explosion[i] = NULL;
		}
	}
}
void CExplosion::UpdateExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRender::GetD3DDevice();

	if(pDevice == NULL){return;}

	D3DXMatrixIdentity(&g_WorldExplosion);

	pDevice -> GetTransform( D3DTS_VIEW, &View );

	D3DXMatrixInverse(&ViewInv, NULL, &View);

	ViewInv._41 = ViewInv._42 = ViewInv._43 = 0.0f;

	for (int i = 0;i < EXPLOSION_MAX;i++)
	{

		//アニメーション数 * アニメーションの遅延 以上の物は削除
		if (g_Explosion[i].nAnimCount > Texture_Explosion[g_Explosion[i].color].Acount * slow)
		{
			g_Explosion[i].bUse = false ;
			g_Explosion[i].nAnimCount = 0;
		}

		if (g_Explosion[i].bUse)
		{
			g_Explosion[i].nAnimCount++;
		}
	}

}
void CExplosion::DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRender::GetD3DDevice();

	pDevice -> SetRenderState(D3DRS_LIGHTING, FALSE);

	pDevice ->SetFVF(FVF_VERTEX_EXPLOSION);

	//αテスト開始
	pDevice -> SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice -> SetRenderState(D3DRS_ALPHAREF, 150);
	pDevice -> SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	for (int i = 0 ; i < EXPLOSION_MAX ; i++)
	{

		if (g_Explosion[i].bUse)
		{
			pDevice->SetTexture(0,g_Textures_Explosion[g_Explosion[i].color]);

			int anime = g_Explosion[i].nAnimCount / slow;

			float u0 = (float) Texture_Explosion[g_Explosion[i].color].Xsize * (anime % Texture_Explosion[g_Explosion[i].color].Xcount) / Texture_Explosion[g_Explosion[i].color].width;
			float v0 = (float) Texture_Explosion[g_Explosion[i].color].Ysize * (anime / Texture_Explosion[g_Explosion[i].color].Xcount) / Texture_Explosion[g_Explosion[i].color].height;
			float u1 = (float)(Texture_Explosion[g_Explosion[i].color].Xsize * (anime % Texture_Explosion[g_Explosion[i].color].Xcount) + Texture_Explosion[g_Explosion[i].color].Xsize) / Texture_Explosion[g_Explosion[i].color].width;	
			float v1 = (float)(Texture_Explosion[g_Explosion[i].color].Ysize * (anime / Texture_Explosion[g_Explosion[i].color].Xcount) + Texture_Explosion[g_Explosion[i].color].Ysize) / Texture_Explosion[g_Explosion[i].color].height;

			VERTEX_EXPLOSION v[] ={

				{D3DXVECTOR3( -1.2f,  1.7f,  0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u0, v0)},
				{D3DXVECTOR3(  1.2f,  1.7f,  0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u1, v0)},
				{D3DXVECTOR3( -1.2f, -1.0f,  0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u0, v1)},
				{D3DXVECTOR3(  1.2f, -1.0f,  0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(u1, v1)},

			};

			D3DXMatrixIdentity(&g_WorldExplosion);

			D3DXMatrixTranslation(&Trans[i], g_Explosion[i].pos.x , g_Explosion[i].pos.y, g_Explosion[i].pos.z);

			g_WorldExplosion = g_WorldExplosion * ViewInv;

			g_WorldExplosion = g_WorldExplosion * Trans[i];

			//各種行列の設定(好きなタイミングで呼ぶ)
			pDevice -> SetTransform(D3DTS_WORLD, &g_WorldExplosion);

			pDevice -> DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &v[0],sizeof(VERTEX_EXPLOSION));
		}

	}

}

void CExplosion::CreateExplosion(float x, float y, float z)
{
	for (int i = 0;i < EXPLOSION_MAX;i++)
	{
		if(!g_Explosion[i].bUse)
		{
			g_Explosion[i].bUse = true;
			g_Explosion[i].nAnimCount = 0;
			g_Explosion[i].pos = D3DXVECTOR3(x, y, z);
			break;
		}
	}
}
