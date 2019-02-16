//-----------------------------------//
//--ポリゴン描画処理-[Polygon.cpp]---//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#include<d3d9.h>
#include<d3dx9.h>
#include<math.h>
#include"main.h"
#include"renderer.h"
#include"Polygon.h"

static const char* g_aTextureFileName[] = {
	"data/texture/number-.png",//ナンバー
	"data/texture/uturn.png",//逆走ジュゲム
	"data/texture/SuperStar.png",//スーパースター
	"data/texture/jugem_last.png",//ラストラップジュゲム
	"data/texture/cooltext293619826968831.png",//ラップ
	"data/texture/cooltext293619845881123.png",//ラップ
	"data/texture/cooltext293619859916715.png",//ラップ
	"data/texture/cooltext311012637535567.png",//goal
	"data/texture/cooltext293619627349526.png",//time
	"data/texture/cooltext293619543903220.png",//3
	"data/texture/cooltext293619550718538.png",//2
	"data/texture/cooltext293619558572596.png",//1
	"data/texture/cooltext293619307154198.png",//go
	"data/texture/coin_MK8DX.png",//coin13
	"data/texture/1271_star_l.jpg",//ブルースター
	"data/texture/509451.png",//丸
	"data/texture/hatena07_01.png",//はてな
	"data/texture/slide4-pic1.png",//きのこ
	"data/texture/0654d0d5829e3393b326fa4711695434-300x300.png",//sec
	"data/texture/cooltext296471575948172.png",//pressstartt
	"data/texture/DSC00785.png",//水
	"data/texture/cooltext297129402880300.png",//title
	"data/texture/cooltext297129458951208.png",//22
	"data/texture/rule.png",//sousa
	"data/texture/go.png",//24ジュゲム
	"data/texture/go1.png",//25
	"data/texture/go2.png",//26
	"data/texture/go3.png",//27
	"data/texture/map.png",//map
	"data/texture/mario-2.png",//mario
	"data/texture/3dashu_kinoko.png",//トリプルダッシュキノコ
	"data/texture/2dashu_kinoko.png",//ダブルダッシュキノコ
	"data/texture/guid3.png",//guid32
	"data/texture/pawaful_dash.png",//パワフルダッシュキノコ
	"data/texture/03830a7e38159ea2093564140a50b928.png",//緑甲羅34
};

static const int TEXTURE_FILE_COUNT = ARRAYCOUNT(g_aTextureFileName);
static LPDIRECT3DTEXTURE9 g_pTextures[TEXTURE_FILE_COUNT];

LPDIRECT3DDEVICE9 CPolygon::m_pDevice = NULL;
LPDIRECT3DVERTEXBUFFER9 CPolygon::g_pVertexBuffer = NULL;
float CPolygon::g_fAngle = 0.0f;
float CPolygon::g_fRotationOffsetX = 0.0f;
float CPolygon::g_fRotationOffsetY = 0.0f;
float CPolygon::g_fScaleX = 1.0f;
float CPolygon::g_fScaleY = 1.0f;
float CPolygon::g_fScaleOffsetX = 0.0f;
float CPolygon::g_fScaleOffsetY = 0.0f;
float CPolygon::g_uv;
float CPolygon::g_fScale = 1.0f;
float CPolygon::g_fScaleAdd = 0.0f;

//----------------------------------//
//----------構造体宣言--------------//
//----------------------------------//
typedef struct
{
	D3DXVECTOR4 pos;
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
}VERTEX_2D;

#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)



//----------------------------------//
//--------ポリゴン初期処理----------//
//----------------------------------//
bool CPolygon::PolygonInit2(void)
{

	m_pDevice = CRender::GetD3DDevice();//ダイレクト３Ｄデバイス
	if (m_pDevice == NULL) { return false; }

	for (int i = 0; i<TEXTURE_FILE_COUNT; i++) {
		HRESULT hr;
		hr = D3DXCreateTextureFromFile(m_pDevice, g_aTextureFileName[i], &g_pTextures[i]);
		if (FAILED(hr))
		{
			MessageBox(NULL, "テクスチャが読み込めなかった", "エラー", MB_OK);
			return false;
		}
	}
	//g_PolygonColor =0xffffff;

	HRESULT hr2;

	//hr2 = D3DXCreateTextureFromFile(pDevice,TEXTURE_FILENAME2,&pTexture2);

	hr2 = m_pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVertexBuffer,
		NULL);

	if (FAILED(hr2)) {
		MessageBox(NULL, "頂点バッファの作成に失敗しました", "エラー", MB_OK);
		return false;
	}

	return true;
}

//----------------------------------//
//-------ポリゴン終了処理-----------//
//----------------------------------//
void CPolygon::PolygonUninit2(void)
{
	int a;
	for (a = 0; a<TEXTURE_FILE_COUNT; a++)
	{
		if (g_pTextures[a] != NULL)
		{
			g_pTextures[a]->Release();
			g_pTextures[a] = NULL;
		}
	}

	if (g_pVertexBuffer != NULL)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}
}

//----------------------------------//
//--------ポリゴン更新処理----------//
//----------------------------------//
void CPolygon::PolygonUpdate2(void)
{
}

void CPolygon::SetPolygonScale2(float cx, float cy, float sx, float sy)
{

	g_fScaleOffsetX = cx;
	g_fScaleOffsetY = cy;
	g_fScaleX = sx;
	g_fScaleY = sy;

}

void CPolygon::SetPolygonRotation2(float cx, float cy, float angle)
{
	g_fRotationOffsetX = cx;
	g_fRotationOffsetY = cy;
	g_fAngle = angle;

}



//----------------------------------//
//--------ポリゴン描画処理----------//
//----------------------------------//
void CPolygon::PolygonDraw2(int texnum, D3DCOLOR color, float dx, float dy, float dw, float dh, int tw, int th, int tcx, int tcy, int tcw, int tch, bool bAffine)
{
	LPDIRECT3DDEVICE9 m_Device = CRender::GetD3DDevice();
	if (m_Device == NULL) { return; }

	if (bAffine) {

		CreateVertexAffine(texnum, color, dx, dy, dw, dh, tw, th, tcx, tcy, tcw, tch);
	}
	else {
		CreateVertex(texnum, color, dx, dy, dw, dh, tw, th, tcx, tcy, tcw, tch);
	}

	m_Device->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(255, 255, 255, 255), 1.0F, 0);

	//FVF（今から使用する頂点情報）の設定
	m_Device->SetFVF(FVF_VERTEX_2D);

	m_Device->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(VERTEX_2D));

	m_Device->SetTexture(0, g_pTextures[texnum]);

	m_Device->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0, 2);

}

void CPolygon::CreateVertex(int texnum, D3DCOLOR color, float dx, float dy, float dw, float dh, int tw, int th, int tcx, int tcy, int tcw, int tch)
{
	VERTEX_2D* pV;

	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);

	pV[0].pos = D3DXVECTOR4(-0.5f + dx + 0.0f, -0.5f + dy + 0.0f, 1.0f, 1.0f);
	pV[1].pos = D3DXVECTOR4(-0.5f + dx + dw, -0.5f + dy + 0.0f, 1.0f, 1.0f);
	pV[2].pos = D3DXVECTOR4(-0.5f + dx + 0.0f, -0.5f + dy + dh, 1.0f, 1.0f);
	pV[3].pos = D3DXVECTOR4(-0.5f + dx + dw, -0.5f + dy + dh, 1.0f, 1.0f);

	pV[0].color =
		pV[1].color =
		pV[2].color =
		pV[3].color = color;


	float u0 = (float)tcx / tw;
	float v0 = (float)tcy / th;
	float u1 = (float)(tcx + tcw) / tw;
	float v1 = (float)(tcy + tch) / th;

	pV[0].texcoord = D3DXVECTOR2(u0, v0);
	pV[1].texcoord = D3DXVECTOR2(u1, v0);
	pV[2].texcoord = D3DXVECTOR2(u0, v1);
	pV[3].texcoord = D3DXVECTOR2(u1, v1);

	g_pVertexBuffer->Unlock();

}

void CPolygon::CreateVertexAffine(int texnum, D3DCOLOR color, float dx, float dy, float dw, float dh, int tw, int th, int tcx, int tcy, int tcw, int tch)
{
	VERTEX_2D* pV;

	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);

	float x = (0.0f - g_fRotationOffsetX) * g_fScaleX + (g_fRotationOffsetX * g_fScaleX);
	float x_w = (tw - g_fRotationOffsetX) * g_fScaleX + (g_fRotationOffsetX * g_fScaleX);
	float y = (0.0f - g_fRotationOffsetY) * g_fScaleY + (g_fRotationOffsetY * g_fScaleY);
	float y_h = (th - g_fRotationOffsetY) * g_fScaleY + (g_fRotationOffsetY * g_fScaleY);

	g_fRotationOffsetX = g_fRotationOffsetX * g_fScaleX;
	g_fRotationOffsetY = g_fRotationOffsetY * g_fScaleY;

	x -= g_fRotationOffsetX;
	x_w -= g_fRotationOffsetX;
	y -= g_fRotationOffsetY;
	y_h -= g_fRotationOffsetY;

	dx += g_fRotationOffsetX - 0.5f;
	dy += g_fRotationOffsetY - 0.5f;

	pV[0].pos = D3DXVECTOR4(x   * cosf(g_fAngle) - y   * sinf(g_fAngle) + dx,
		x   * sinf(g_fAngle) + y   * cosf(g_fAngle) + dy, 1.0f, 1.0f);
	pV[1].pos = D3DXVECTOR4(x_w * cosf(g_fAngle) - y   * sinf(g_fAngle) + dx,
		x_w * sinf(g_fAngle) + y   * cosf(g_fAngle) + dy, 1.0f, 1.0f);
	pV[2].pos = D3DXVECTOR4(x   * cosf(g_fAngle) - y_h * sinf(g_fAngle) + dx,
		x   * sinf(g_fAngle) + y_h * cosf(g_fAngle) + dy, 1.0f, 1.0f);
	pV[3].pos = D3DXVECTOR4(x_w * cosf(g_fAngle) - y_h * sinf(g_fAngle) + dx,
		x_w * sinf(g_fAngle) + y_h * cosf(g_fAngle) + dy, 1.0f, 1.0f);
	pV[0].color =
		pV[1].color =
		pV[2].color =
		pV[3].color = color;


	float u0 = (float)tcx / tw;
	float v0 = (float)tcy / th;
	float u1 = (float)(tcx + tcw) / tw;
	float v1 = (float)(tcy + tch) / th;

	pV[0].texcoord = D3DXVECTOR2(u0, v0);
	pV[1].texcoord = D3DXVECTOR2(u1, v0);
	pV[2].texcoord = D3DXVECTOR2(u0, v1);
	pV[3].texcoord = D3DXVECTOR2(u1, v1);

	g_pVertexBuffer->Unlock();

}