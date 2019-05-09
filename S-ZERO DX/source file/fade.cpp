//-----------------------------------//
//------フェード処理 [Fade.cpp]------//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#include "fade.h"
#include "camera.h"
#include "player.h"
#include "renderer.h"

//-------------------------------------------------------------------
//変数宣言
//-------------------------------------------------------------------

#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FADE "data/texture/black.png"
//#define POSE "data/texture/black.png"
#define BACk "data/texture/black.jpg"

LPDIRECT3DTEXTURE9 CFade::g_Textures_Fade = { NULL };
//LPDIRECT3DTEXTURE9 CFade::g_Textures_Pose = { NULL };
LPDIRECT3DTEXTURE9 CFade::g_Textures_Back = { NULL };
LPDIRECT3DVERTEXBUFFER9 CFade::g_pVertexBuffer = NULL;

typedef struct
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR color;
	D3DXVECTOR2 texture;
}VERTEX_FADE;

//-------------------------------------------------------------------
//　関数宣言
//-------------------------------------------------------------------

void CFade::InitFade(void)
{

	LPDIRECT3DDEVICE9  pDevice = CRender::GetD3DDevice();

	if (pDevice == NULL) { return; }

	HRESULT hr;

	hr = D3DXCreateTextureFromFile(pDevice, FADE, &g_Textures_Fade);
	//hr = D3DXCreateTextureFromFile(pDevice, POSE, &g_Textures_Pose);
	hr = D3DXCreateTextureFromFile(pDevice, BACk, &g_Textures_Back);


	if (FAILED(hr))
	{
		MessageBox(NULL, "読み込めませんfade", "エラー", MB_OK);
		return;
	}

	hr = pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_FADE) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVertexBuffer,
		NULL
	);
	if (FAILED(hr)) {
		MessageBox(NULL, "頂点バッファの作成に失敗しました", "エラー", MB_OK);
	}

}
void CFade::UninitFade(void)
{

	if (g_pVertexBuffer)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}

	if (g_Textures_Fade != NULL)
	{
		g_Textures_Fade->Release();
		g_Textures_Fade = NULL;
	}

	//if (g_Textures_Pose != NULL)
	//{
	//	g_Textures_Pose->Release();
	//	g_Textures_Pose = NULL;
	//}

	if (g_Textures_Back != NULL)
	{
		g_Textures_Back->Release();
		g_Textures_Back = NULL;
	}


}

void CFade::CreateFade(int count, bool out, bool pose)
{
	LPDIRECT3DDEVICE9 pDevice = CRender::GetD3DDevice();

	VERTEX_FADE *pV;

	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);

	float x = (float)SCREEN_WIDTH;
	float y = (float)SCREEN_HEIGHT;

	int color;

	if (out)
	{
		color = 255 - count;
		if (pose)
		{
			color = 255;
			count = 255;
		}
	}
	else
	{
		color = count;
		count = 255 - count;


	}

	VERTEX_FADE fade[] =
	{
		{ D3DXVECTOR3(0.0f,		y, 10.0f), 10.0f, D3DCOLOR_RGBA(color, color, color, count), D3DXVECTOR2(0, 1) },
		{ D3DXVECTOR3(0.0f,  0.0f, 10.0f), 10.0f, D3DCOLOR_RGBA(color, color, color, count), D3DXVECTOR2(0, 0) },
		{ D3DXVECTOR3(x,		y, 10.0f), 10.0f, D3DCOLOR_RGBA(color, color, color, count), D3DXVECTOR2(1, 1) },
		{ D3DXVECTOR3(x,	 0.0f, 10.0f), 10.0f, D3DCOLOR_RGBA(color, color, color, count), D3DXVECTOR2(1, 0) },
	};

	pDevice->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	//テクスチャをセット
	//if (pose)
	//{
	//	pDevice->SetTexture(0, g_Textures_Pose);

		if (out)
		{
			pDevice->SetTexture(0, g_Textures_Back);
		}
	//}
	else
	{
		pDevice->SetTexture(0, g_Textures_Fade);
	}

	//ライトのON・OFF
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//FVFの設定
	//FVF->デバイスに教える
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(VERTEX_FADE));

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &fade[0], sizeof(VERTEX_FADE));

	g_pVertexBuffer->Unlock();

}
