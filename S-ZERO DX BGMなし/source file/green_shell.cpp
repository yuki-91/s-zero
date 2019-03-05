
#include "main.h"
#include "green_shell.h"
#include <time.h>
#include "input.h"
#include "camera.h"
#include "player.h"
#include "renderer.h"
#include <math.h>
#include "sound.h"
#include "myInput.h"

// 頂点属性(1つ目：座標、2つ目：カラー,3つ目：テクスチャー)
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_DIFFUSE | D3DFVF_TEX1 )

static LPDIRECT3DTEXTURE9 g_pTextures_Bullet[TEXTURE_BULLET_MAX] = { NULL };

static D3DXMATRIX g_mtxWorld_Bullet;						//ワールド変換行列

static LPDIRECT3DVERTEXBUFFER9 g_pVertexBufferBullet = NULL;		// VerTexBufferの管理者のメモ帳(?)
static LPDIRECT3DINDEXBUFFER9   g_pIndexBufferBullet = NULL;		// インデックスバッファのポインタ

static void VertexBuffer_Bullet();
static void IndexBuffer_Bullet();

static D3DXMATRIX g_viewInverse;	//ビューの逆行列

static D3DXVECTOR3 g_TransPos[BULLET_MAX];
static D3DXVECTOR3 g_TransPosBefore[BULLET_MAX];

static D3DXMATRIX g_Trans[BULLET_MAX];

static D3DXMATRIX g_Shadow;
static D3DXMATRIX g_ShadowTrans[BULLET_MAX];

static BULLET g_Bullet[BULLET_MAX];

static int g_nFramecount = 0;
float speedE = 2.25f;

static D3DXVECTOR3 ColorStock;
D3DXMATRIX t_matrix;
D3DXVECTOR3 rot;

typedef struct
{
	D3DXVECTOR3 pos;		//座標
	D3DCOLOR color;			//色
	D3DXVECTOR2 texture;	//テクスチャ座標
}VERTEX_BULLET;

static int g_BulletChange;

bool UseBullet = false;

//-------------------------------------------------------------------
//　関数定義
//-------------------------------------------------------------------

bool InitBullet(void)
{

	D3DXVECTOR3 rot(0.0f,0.0f,0.0f);

	//デバイスの取得
	LPDIRECT3DDEVICE9  pDevice = CRender::GetD3DDevice();

	if (pDevice == NULL)return false;

	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);

	HRESULT hr;

	for (int i = 0; i<TEXTURE_BULLET_MAX; i++)
	{

		hr = D3DXCreateTextureFromFile(pDevice, g_aTexture_Bullet[i].fileName, &g_pTextures_Bullet[i]);

		if (FAILED(hr))
		{
			MessageBox(NULL, "読み込めません Bullet1", "エラー", MB_OK);
			return false;
		}

	}

	hr = pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_BULLET) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVertexBufferBullet,
		NULL
	);

	if (FAILED(hr))
	{
		MessageBox(NULL, "読み込めません Bullet2", "エラー", MB_OK);
		return FALSE;
	}

	hr = pDevice->CreateIndexBuffer
	(
		sizeof(WORD) * 4,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIndexBufferBullet,
		NULL
	);


	if (FAILED(hr))
	{
		MessageBox(NULL, "読み込めません Bullet3", "エラー", MB_OK);
		return FALSE;
	}


	VertexBuffer_Bullet();
	IndexBuffer_Bullet();

	g_BulletChange = 1;

	for (int i = 0; i < BULLET_MAX; i++)
	{
		g_Bullet[i].bUse = false;

		g_Bullet[i].vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[i].vDir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_Bullet[i].color = 0;

		g_Bullet[i].nLife = 0;

		g_TransPos[i] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	}

	ColorStock = D3DXVECTOR3(50.0f, 50.0f, 50.0f);

	UseBullet = false;

	return true;

}
void UninitBullet(void)
{

	for (int i = 0; i < TEXTURE_BULLET_MAX; i++)
	{
		if (g_pTextures_Bullet[i] != NULL)
		{
			g_pTextures_Bullet[i]->Release();
			g_pTextures_Bullet[i] = NULL;
		}
	}

	if (g_pVertexBufferBullet != NULL)
	{
		g_pVertexBufferBullet->Release();
		g_pVertexBufferBullet = NULL;
	}

	if (&g_pIndexBufferBullet != NULL)
	{
		g_pIndexBufferBullet->Release();
		g_pIndexBufferBullet = NULL;
	}
}

void UpdateBullet(void)
{

	LPDIRECT3DDEVICE9  pDevice = CRender::GetD3DDevice();

	if (pDevice == NULL) { return; }

	//弾が一つでも出ているか
	UseBullet = false;

	//ビューマトリックスを取得する
	pDevice->GetTransform(D3DTS_VIEW, &g_viewInverse);

	//ビューの逆行列作成
	D3DXMatrixInverse(&g_viewInverse, NULL, &g_viewInverse);

	//無効化
	g_viewInverse._41 = g_viewInverse._42 = g_viewInverse._43 = 0.0f;

	g_BulletChange = 0;

	//if (MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_X))
	//{
	//	switch (g_BulletChange)
	//	{
	//	case 0:

	//		if (ColorStock.x > 25.0f)
	//		{
	//			CreateBullet(0.0f, 0);
	//			ColorStock.x -= 20.0f;
	//		}

	//		break;

	//	case 1:
	//		if (ColorStock.y > 25.0f)
	//		{
	//			CreateBullet(0.0f, 1);
	//			ColorStock.y -= 20.0f;
	//		}

	//		break;

	//	case 2:
	//		if (ColorStock.z > 25.0f)
	//		{

	//			CreateBullet(0.0f, 2);
	//			ColorStock.z -= 20.0f;
	//		}
	//		break;

	//	default:
	//		break;

	//	}

	//}

	//if (GetKeyboardTrigger(DIK_A))
	//{
	//	rot.y -= 0.25;
	//}

	//if (GetKeyboardTrigger(DIK_D))
	//{
	//	rot.y += 0.25;
	//}


	//弾発射
	//if (GetKeyboardTrigger(DIK_SPACE))
	//{
	//	switch (g_BulletChange)
	//	{
	//	case 0:

	//		if (ColorStock.x > 25.0f)
	//		{
	//			CreateBullet(0.0f, 0);
	//			ColorStock.x -= 20.0f;
	//		}

	//		break;

	//	case 1:
	//		if (ColorStock.y > 25.0f)
	//		{
	//			CreateBullet(0.0f, 1);
	//			ColorStock.y -= 20.0f;
	//		}

	//		break;

	//	case 2:
	//		if (ColorStock.z > 25.0f)
	//		{

	//			CreateBullet(0.0f, 2);
	//			ColorStock.z -= 20.0f;
	//		}
	//		break;

	//	default:
	//		break;

	//	}
	//}

	ColorStock.x += 0.10f;
	ColorStock.y += 0.10f;
	ColorStock.z += 0.10f;

	ColorStock.x = min(99, ColorStock.x);
	ColorStock.y = min(99, ColorStock.y);
	ColorStock.z = min(99, ColorStock.z);

	ColorStock.x = max(0, ColorStock.x);
	ColorStock.y = max(0, ColorStock.y);
	ColorStock.z = max(0, ColorStock.z);

	for (int i = 0; i < BULLET_MAX; i++)
	{

		if (g_Bullet[i].bUse)
		{

			g_TransPosBefore[i] = g_TransPos[i];

			//最新の弾の場所　=　発射位置　+　軸の成分(速さ)　*　弾の経過時間
			g_TransPos[i] = g_Bullet[i].vPos + g_Bullet[i].vDir * (float)(g_Bullet[i].nLife) * speedE;

			////壁ヒット判定
			//if (g_TransPos[i].x > GAME_MAX_RIGTH || g_TransPos[i].x < -20.0f)
			//{
			//	DestroyBullet(i);
			//}

			//弾の寿命判定
			if (g_Bullet[i].nLife > BULLET_LIFE)
			{
				DestroyBullet(i);
			}
			else
			{
				g_Bullet[i].nLife++;
			}

			UseBullet = true;

		}
	}

	g_nFramecount++;

}
void DrawBullet(void)
{

	LPDIRECT3DDEVICE9  pDevice = CRender::GetD3DDevice();

	static D3DXMATRIX g_Rotation;

	//弾自体の回転
	//D3DXMatrixRotationZ(&g_Rotation, D3DXToRadian( g_nFramecount * 6 ));

	if (pDevice == NULL)return;

	//ライトのON・OFF
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//αテスト開始
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//FVFの設定
	//FVF->デバイスに教える
	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetStreamSource(0, g_pVertexBufferBullet, 0, sizeof(VERTEX_BULLET));

	pDevice->SetIndices(g_pIndexBufferBullet);

	for (int a = 0; a < BULLET_MAX; a++)
	{
		if (UseBullet)
		{
			if (g_Bullet[a].bUse)
			{

				D3DXMatrixIdentity(&g_mtxWorld_Bullet);

				//テクスチャをセット
				pDevice->SetTexture(0, g_pTextures_Bullet[g_Bullet[a].color]);

				D3DXMatrixTranslation(&g_Trans[a], g_TransPos[a].x, g_TransPos[a].y, g_TransPos[a].z);

				//g_mtxWorld_Bullet = g_mtxWorld_Bullet * g_Rotation;
				D3DXMatrixRotationYawPitchRoll(&t_matrix, CX_model::XmodelRot().y, CX_model::XmodelRot().x, CX_model::XmodelRot().z);    //  回転マトリクスの作成

				g_mtxWorld_Bullet = g_mtxWorld_Bullet * g_viewInverse;

				g_mtxWorld_Bullet = g_mtxWorld_Bullet * g_Trans[a];

				g_mtxWorld_Bullet = g_mtxWorld_Bullet * t_matrix;

				//ワールド行列の設定(好きなタイミングで呼ぶ)
				pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld_Bullet);

				pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);
			}
		}
	}

	//影作成
	CreateBulletShadow();

}
//弾を作る関数
void CreateBullet(float radian, int color)
{

	float t = 0;

	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!g_Bullet[i].bUse)
		{
			//アングル = 2π * 角度(0~360) / 360
			//t = 2.0f * 3.14f * (CX_model::XmodelRot() + radian) / 360.0f;

			g_Bullet[i].vPos = D3DXVECTOR3(CX_model::XmodelPos().x , CX_model::XmodelPos().y + 0.9f, CX_model::XmodelPos().z);

			//g_Bullet[i].vDir = D3DXVECTOR3(cos(t), 0.0f, sin(t));

			g_Bullet[i].color = color;

			g_Bullet[i].nLife = 0;

			g_Bullet[i].bUse = true;

			break;
		}
	}

}

//弾を消す関数
void DestroyBullet(int num)
{
	if (g_Bullet[num].bUse)
	{
		g_Bullet[num].bUse = false;
		g_TransPos[num] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//座標を拾う関数
D3DXVECTOR3 GetBulletPos(int num)
{

	D3DXVECTOR3 BulletPos = g_Bullet[num].vPos + g_Bullet[num].vDir * (float)(g_Bullet[num].nLife) * speedE;

	return BulletPos;

}

void VertexBuffer_Bullet()
{

	VERTEX_BULLET bullet[] =
	{

		{ D3DXVECTOR3(-0.5f, -0.5f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(0, 1) },
		{ D3DXVECTOR3(-0.5f,  0.5f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(0, 0) },
		{ D3DXVECTOR3(0.5f, -0.5f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(1, 1) },
		{ D3DXVECTOR3(0.5f,  0.5f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(1, 0) },

	};

	VERTEX_BULLET *pV;

	g_pVertexBufferBullet->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);

	// 配列をコピーする
	memcpy(pV, bullet, sizeof(bullet));

	g_pVertexBufferBullet->Unlock();
}

void IndexBuffer_Bullet()
{
	WORD index_Bullet[] = { 0,1,2,3 };

	LPWORD pIndex;

	g_pIndexBufferBullet->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);

	//ヒープエラーの原因?
	//CreateIndexBuffer だと(WORD) * 4 であるため
	//memcpy(pIndex,index_Bullet,sizeof(WORD) * 6);

	memcpy(pIndex, index_Bullet, sizeof(WORD) * 4);

	g_pIndexBufferBullet->Unlock();
}

void CreateBulletShadow()
{

	LPDIRECT3DDEVICE9  pDevice = CRender::GetD3DDevice();

	if (pDevice == NULL) { return; }

	//減算設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//テクスチャをセット
	pDevice->SetTexture(0, g_pTextures_Bullet[TEXTURE_BULLET_SHADOW]);

	static D3DXMATRIX Rot;

	//テクスチャを X-Y から X-Z にする回転
	D3DXMatrixRotationX(&Rot, D3DXToRadian(90.0f));

	for (int a = 0; a < BULLET_MAX; a++)
	{
		if (g_Bullet[a].bUse)
		{

			D3DXMatrixIdentity(&g_Shadow);

			D3DXMatrixTranslation(&g_ShadowTrans[a], g_TransPos[a].x, 0.1f, g_TransPos[a].z);

			g_Shadow = g_Shadow * Rot;

			g_Shadow = g_Shadow * g_ShadowTrans[a];

			//ワールド行列の設定(好きなタイミングで呼ぶ)
			pDevice->SetTransform(D3DTS_WORLD, &g_Shadow);

			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);

		}
	}

	//元の合成に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


}

//弾の色（int）を返す
int *GetBulletColor(int BulletNumber)
{
	return &g_Bullet[BulletNumber].color;
}

//使用されているか
bool *GetBulletUse(int b)
{
	return &g_Bullet[b].bUse;
}

D3DXVECTOR3 *StockColor()
{
	return &ColorStock;
}
