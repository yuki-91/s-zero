//-----------------------------------//
//-----モードランキング処理-----------//
//--------[ranking.cpp]-------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#include"mode_ranking.h"
#include "myInput.h"
#include "Polygon.h"
#include "main.h"
#include "fade.h"
#include"scene.h"
#include"input.h"
#include "scene.h"
#include "mode_game.h"
#include "renderer.h"
#include "mode_result.h"
#include "mode_title.h"
#include "manager.h"
#include "sound.h"

// 頂点属性(1つ目：座標、2つ目：カラー,3つ目：テクスチャー)
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE | D3DFVF_TEX1 )
#define RANKING_MAX (5)

static LPDIRECT3DTEXTURE9 g_pTextures_Rank[TEXTURE_RANK_MAX] = { NULL };	//テクスチャ配列

static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;

static int FadeRankingCount = 0;
static int RankingIn = 0;
int FadeRankCount = 0;
static bool g_bGoOver = false;
static bool g_bFirst = true;//初回だけの判定
static int OpIn = 0;

CScore *CModeRanking::m_Score2;
int CModeRanking::wall_xy;

typedef struct {
	int g_RankScore;
}RANKING;

typedef struct
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR color;
	D3DXVECTOR2 texture;
}VERTEX_RANK;

static RANKING g_nRanking[10];

static RANKING g_nPlayer;

float g_nRankin = -1.0f;

int  MyScore = 0;

int count2 = 0;

void CModeRanking::Init()
{
	count2 = 0;

	MyScore = CModeGame::SougouScore();

	FadeRankingCount = 0;

	g_nRankin = -1.0f;

	FadeRankCount = 0;

	OpIn = 0;


	if (g_bFirst == true)
	{
		for (int r = 0; r < RANKING_MAX; r++)
		{
			//g_nRanking[r].g_RankScore = 292 + (1 * r);
			g_nRanking[0].g_RankScore = 17232;
			g_nRanking[1].g_RankScore = 19666;
			g_nRanking[2].g_RankScore = 26298;
			g_nRanking[3].g_RankScore = 27044;
			g_nRanking[4].g_RankScore = 29112;
			//g_nRanking[r].g_RankScore =0;
		}

		g_bFirst = false;
	}



	if (g_nRanking[0].g_RankScore > MyScore)
	{
		g_nRanking[4].g_RankScore = g_nRanking[3].g_RankScore;
		g_nRanking[3].g_RankScore = g_nRanking[2].g_RankScore;
		g_nRanking[2].g_RankScore = g_nRanking[1].g_RankScore;
		g_nRanking[1].g_RankScore = g_nRanking[0].g_RankScore;
		g_nRanking[0].g_RankScore = MyScore;

		g_nRankin = 0;

	}
	else
	{
		if (g_nRanking[1].g_RankScore > MyScore)
		{
			g_nRanking[4].g_RankScore = g_nRanking[3].g_RankScore;
			g_nRanking[3].g_RankScore = g_nRanking[2].g_RankScore;
			g_nRanking[2].g_RankScore = g_nRanking[1].g_RankScore;
			g_nRanking[1].g_RankScore = MyScore;

			g_nRankin = 1;
		}
		else
		{

			if (g_nRanking[2].g_RankScore > MyScore)
			{
				g_nRanking[4].g_RankScore = g_nRanking[3].g_RankScore;
				g_nRanking[3].g_RankScore = g_nRanking[2].g_RankScore;
				g_nRanking[2].g_RankScore = MyScore;

				g_nRankin = 2;
			}
			else
			{
				if (g_nRanking[3].g_RankScore > MyScore)
				{
					g_nRanking[4].g_RankScore = g_nRanking[3].g_RankScore;
					g_nRanking[3].g_RankScore = MyScore;

					g_nRankin = 3;
				}
				else
				{
					if (g_nRanking[4].g_RankScore > MyScore)
					{
						g_nRanking[4].g_RankScore = MyScore;

						g_nRankin = 4;
					}
					else
					{
						g_nRankin = 5;
					}
				}
			}
		}
	}

	//デバイスの取得
	pDevice = CRender::GetD3DDevice();

	if (pDevice == NULL)
	{
		return;
	}

	HRESULT hr;

	for (int i = 0; i<TEXTURE_RANK_MAX; i++)
	{

		hr = D3DXCreateTextureFromFile(pDevice, g_aTexture_Rank[i].fileName, &g_pTextures_Rank[i]);

		if (FAILED(hr))
		{
			MessageBox(NULL, "読み込めません", "エラー", MB_OK);
			return;
		}

	}
	HRESULT hr2;
	hr2 = pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_RANK) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVertexBuffer,
		NULL
	);


	RankingIn = 0;
	g_bGoOver = false;

	//PlaySound(SOUND_LABEL_GAMEOVER);
}

void CModeRanking::Uninit()
{


	for (int i = 0; i < TEXTURE_RANK_MAX; i++)
	{
		if (g_pTextures_Rank[i] != NULL)
		{
			g_pTextures_Rank[i]->Release();
			g_pTextures_Rank[i] = NULL;
		}
	}

	if (g_pVertexBuffer != NULL)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}
	if (pDevice != NULL)
	{
		pDevice->Release();
		pDevice = NULL;
	}


}
void CModeRanking::Update()
{
	StopSound(SOUND_LABEL_STAR);

	if (OpIn >= 255)
	{
		if (MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_B) || (MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_A)) || MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_START) || GetKeyboardTrigger(DIK_SPACE))
		{
			PlaySound(SOUND_LABEL_BUTTON);
			g_bGoOver = true;
		}
	}

	count2++;
	if (count2 < 100)
	{
		count2++;
	}

	//if (RankingIn >= 255)
	//{
	//	if (MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_X))
	//	{
	//		PlaySound(SOUND_LABEL_SE_BUTTON2);
	//		g_bGoOver = true;
	//	}

	//	if (MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_A))
	//	{
	//		PlaySound(SOUND_LABEL_SE_BUTTON2);
	//		g_bGoOver = true;
	//	}

	//	if (MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_START))
	//	{
	//		PlaySound(SOUND_LABEL_SE_BUTTON2);
	//		g_bGoOver = true;
	//	}

	//	if (GetKeyboardTrigger(DIK_RETURN))
	//	{
	//		PlaySound(SOUND_LABEL_SE_BUTTON2);
	//		g_bGoOver = true;
	//	}
	//}

	OpIn += 5;

	RankingIn += 5;


	
	wall_xy++;

	if (wall_xy > 1000)
	{
		wall_xy = 0;
	}
}
void CModeRanking::Draw()
{

	//壁
	CPolygon::PolygonDraw2(14, D3DCOLOR_RGBA(255, 255, 255, 255), -wall_xy * 0.5, -wall_xy * 0.5, 10000, 10000, 114, 150, 0, 0, 10000, 10000);

	pDevice = CRender::GetD3DDevice();

	if (pDevice == NULL) { return; }

	VERTEX_RANK *pV;

	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);

	pDevice->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	//ライトのON・OFF
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//FVFの設定
	//FVF->デバイスに教える
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(VERTEX_RANK));

	float x, y, w, h;

	//一回目は枠、二回目はランク判定
	for (int rankdraw = 1; rankdraw <= 2; rankdraw++)
	{
		if (rankdraw == 1)
		{
			x = 0.0f;
			y = 0.0f;
			w = (float)SCREEN_WIDTH;
			h = (float)SCREEN_HEIGHT;
		}
		if (rankdraw == 2)
		{
			if (g_nRankin<5)
			{
				x = 630;
				y = 90 * g_nRankin + 290;
				w = 500;
				h = 100;
			}
			else
			{
				x = 1000;
				y = 620;
				w = 350;
				h = 100;
			}

		}

		VERTEX_RANK t[] = {

			{ D3DXVECTOR3(x + 0.0f,    y + h,  0.0f), 1.0f, D3DCOLOR_RGBA(255, 255,255, 255), D3DXVECTOR2(0, 1) },
			{ D3DXVECTOR3(x + 0.0f, y + 0.0f,  0.0f), 1.0f, D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0, 0) },
			{ D3DXVECTOR3(x + w,    y + h,  0.0f), 1.0f, D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1, 1) },
			{ D3DXVECTOR3(x + w, y + 0.0f,  0.0f), 1.0f, D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1, 0) },
		};

		VERTEX_RANK t2[] = {

			{ D3DXVECTOR3(x + 0.0f,    y + h,  0.0f), 1.0f, D3DCOLOR_RGBA(255, 255,255, count2*3), D3DXVECTOR2(0, 1) },
			{ D3DXVECTOR3(x + 0.0f, y + 0.0f,  0.0f), 1.0f, D3DCOLOR_RGBA(255, 255, 255, count2*3), D3DXVECTOR2(0, 0) },
			{ D3DXVECTOR3(x + w,    y + h,  0.0f), 1.0f, D3DCOLOR_RGBA(255, 255, 255, count2*3), D3DXVECTOR2(1, 1) },
			{ D3DXVECTOR3(x + w, y + 0.0f,  0.0f), 1.0f, D3DCOLOR_RGBA(255, 255, 255, count2*3), D3DXVECTOR2(1, 0) },
		};

		if (rankdraw == 1)
		{
			for (int r = 0; r < 1; r++)
			{
				//テクスチャをセット
				pDevice->SetTexture(0, g_pTextures_Rank[r]);

				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &t[0], sizeof(VERTEX_RANK));
			};
		}

		if (rankdraw == 2)
		{
			if (g_nRankin<5)
			{
				//テクスチャをセット
				pDevice->SetTexture(0, g_pTextures_Rank[TEXTURE_IN]);
			}
			else
			{
				//テクスチャをセット
				pDevice->SetTexture(0, g_pTextures_Rank[TEXTURE_NOT]);
			}

			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &t2[0], sizeof(VERTEX_RANK));

		}

	}

	g_pVertexBuffer->Unlock();

	//ランクスコア記載
	for (int dr = 0; dr < RANKING_MAX; dr++)
	{
		m_Score2->DrawScore(g_nRanking[dr].g_RankScore, 5, 360.0f, 90.0f * (float)dr + 220, false);
	}

	//プレイヤー
	m_Score2->DrawScore(MyScore, 5, 450, 27, false);

	
	//sec
	CPolygon::PolygonDraw2(18, D3DCOLOR_RGBA(255, 255, 255, 255), 543, 140, 80, 80, 80, 80, 0, 0, 80, 80);

	CPolygon::PolygonDraw2(18, D3DCOLOR_RGBA(255, 255, 255, 255), 458, 335, 80, 80, 80, 80, 0, 0, 80, 80);
	CPolygon::PolygonDraw2(18, D3DCOLOR_RGBA(255, 255, 255, 255), 458, 425, 80, 80, 80, 80, 0, 0, 80, 80);
	CPolygon::PolygonDraw2(18, D3DCOLOR_RGBA(255, 255, 255, 255), 458, 515, 80, 80, 80, 80, 0, 0, 80, 80);
	CPolygon::PolygonDraw2(18, D3DCOLOR_RGBA(255, 255, 255, 255), 458, 605, 80, 80, 80, 80, 0, 0, 80, 80);
	CPolygon::PolygonDraw2(18, D3DCOLOR_RGBA(255, 255, 255, 255), 458, 695, 80, 80, 80, 80, 0, 0, 80, 80);

	//フェード
	if (OpIn < 255)
	{
		CFade::CreateFade(OpIn, false, false);
	}

	//タイトルへ
	if (g_bGoOver == true)
	{
		if (FadeRankCount>255)
		{
			CFade::CreateFade(255, true, false);
			CManager::SetMode(new CModeTitle());
		}
		else
		{
			CFade::CreateFade(FadeRankCount, true, false);
		}

		FadeRankCount += 5;
	}

}
