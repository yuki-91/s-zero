//-----------------------------------//
//------レンダラー処理---------------//
//-------[renderer.cpp]--------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#include "renderer.h"
#include <stdio.h>
#include <Windows.h>
#include "main.h"
#include"input.h"

LPDIRECT3D9 CRender::m_D3D;
LPDIRECT3DDEVICE9 CRender::m_D3DDevice;

bool CRender::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	//Direct3Dインタフェースの作成
	m_D3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_D3D == NULL)
	{
		return false;
	}
	//return true;

	//現在のディスプレイモードを取得
	if (FAILED(m_D3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return false;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));								//中の物の初期化
	d3dpp.BackBufferWidth = SCREEN_WIDTH;							//裏画面の幅
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							//裏画面の高さ
	d3dpp.BackBufferFormat = d3ddm.Format;							//色数
	d3dpp.BackBufferCount = 1;										//バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						//映像信号の同期(DISCARDは垂直)
	d3dpp.EnableAutoDepthStencil = TRUE;							//TRUEで良い
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						//今はこの状態　上のフォーマット
	d3dpp.Windowed = bWindow;										//TRUEでウィンドウモード,FALSEでフルスクリーンモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//フルスクリーンモード時のリフレッシュレートのHz数を変更
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//モニターのHz数に応じて描画


	if (FAILED(m_D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_D3DDevice)))
	{
		return false;
	}

	m_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	//SRC		--今から描画するもの
	//DEST		--すでに描画されている画面
	//SRC_RGB * SRC_a + DEST_RGB * (1 - SRC_a)
	//今回はSRC_a = 0　だから背景色が100%表示
	m_D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	//頂点データのUV値を変更
	//テクスチャのアドレス外を参照　
	m_D3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_D3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	m_D3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//実際のサイズよりも小さくなる時のフィルタリング

	//m_D3DDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);	//実際のサイズよりも大きくなる時のフィルタリング

	//m_D3DDevice->SetSamplerState(0,D3DSAMP_MIPFILTER,D3DTEXF_LINEAR);	//ミップマップファイル間のフィルタリング　例 128*128と256*256の間



	//LINEAR--線形保管、周りの色をブレンド

	//ミップマップ--半分のサイズの画像を生成してくれる。

	InitKeyboard(hInstance, hWnd);

	return true;
}

void CRender::Uninit()
{
	if (m_D3DDevice != NULL)
	{
		m_D3DDevice->Release();
		m_D3DDevice = NULL;
	}
	if (m_D3D != NULL)
	{
		m_D3D->Release();
		m_D3D = NULL;
	}
}

void CRender::DrawBegin()
{
	m_D3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(1, 1, 1, 1), 1.0F, 0);

	m_D3DDevice->BeginScene();
	
}

void CRender::DrawEnd()
{
	m_D3DDevice->EndScene();

	m_D3DDevice->Present(NULL, NULL, NULL, NULL);
}


LPDIRECT3DDEVICE9 CRender::GetD3DDevice(void)
{
	return m_D3DDevice;
}