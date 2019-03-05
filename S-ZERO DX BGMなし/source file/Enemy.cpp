//-----------------------------------//
//----------エネミー処理-[Enemy.cpp]-//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
//インクルード文

#include "Enemy.h"
#include "camera.h"
#include "renderer.h"
#include "player.h"
#include "hit.h"
#include "Explosion.h"
#include "sound.h"
#include "coin.h"

// 頂点属性(1つ目：座標、2つ目：カラー,3つ目：テクスチャー)
#define FVF_VERTEX_ENEMY (D3DFVF_XYZ|D3DFVF_DIFFUSE | D3DFVF_TEX1 )

LPDIRECT3DTEXTURE9 CBillboard::g_pTextures_bill[TEXTURE_B_MAX] = { NULL };	//テクスチャ配列
LPDIRECT3DTEXTURE9 CBillboard::g_pTexture = NULL;
D3DXMATRIX CBillboard::g_mtxWorld_Billboard;		//ワールド変換行列
LPDIRECT3DVERTEXBUFFER9 CBillboard::g_pVertexBuffer = NULL;		// バーテックスバッファのポインタ
LPDIRECT3DINDEXBUFFER9 CBillboard::g_pIndexBuffer = NULL;		// インデックスバッファのポインタ
LPDIRECT3DVERTEXBUFFER9 CBillboard::g_pVertexBuffer2 = NULL;		// バーテックスバッファのポインタ
LPDIRECT3DINDEXBUFFER9 CBillboard::g_pIndexBuffer2 = NULL;		// インデックスバッファのポインタ
D3DXMATRIX CBillboard::g_Pos;		//位置の行列
D3DXMATRIX CBillboard::g_Shadow;		//影のワールド行列
D3DXMATRIX CBillboard::g_viewInverse;
D3DXMATRIX CBillboard::g_Trans, CBillboard::g_Rotation;
D3DXVECTOR3 CBillboard::g_TransPos[MAX_BILLBOARD];
int CBillboard::color[MAX_BILLBOARD];
bool CBillboard::ememy[MAX_BILLBOARD];
int CBillboard::Life[MAX_BILLBOARD];
float  CBillboard::g_Rot2 = 10.0f;
bool  CBillboard::b_dos2 = false;
bool  CBillboard::b_dos5 = false;
bool  CBillboard::b_dos8 = false;
bool  CBillboard::b_dos11 = false;
bool  CBillboard::b_dos14 = false;
bool  CBillboard::b_dos17 = false;
bool  CBillboard::b_kuri0 = false;
bool  CBillboard::b_kuri3 = false;
bool  CBillboard::b_kuri6 = false;
bool  CBillboard::b_kuri9 = false;
bool  CBillboard::b_kuri12 = false;
bool  CBillboard::b_kame1 = false;
bool  CBillboard::b_kame4 = false;
bool  CBillboard::b_kame7 = false;
bool  CBillboard::b_kame10 = false;
bool  CBillboard::b_kame13 = false;
bool  CBillboard::b_kame16 = false;
int CBillboard::e_coin = 10;
bool CBillboard::b_hit = false;
int  CBillboard::dos_count = 0;
typedef struct
{
	D3DXVECTOR3 pos;		//座標
	D3DCOLOR color;			//色
	D3DXVECTOR2 texture;	//テクスチャ座標
}VERTEX_BILLBOARD;

typedef struct
{
	D3DXVECTOR3 pos;		//座標
	D3DCOLOR color;			//色
	D3DXVECTOR2 texture;	//テクスチャ座標
}VERTEX_SHADOW;

bool CBillboard::InitBillboard()
{

	//デバイスの取得
	LPDIRECT3DDEVICE9  pDevice = CRender::GetD3DDevice();

	if(pDevice == NULL)
	{
		return false;
	}

	pDevice ->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);

	HRESULT hr;

	for(int i=0 ; i<TEXTURE_B_MAX;i++)
	{

		hr = D3DXCreateTextureFromFile(pDevice,g_aTexture_b[i].fileName, &g_pTextures_bill[i]);

		if(FAILED(hr))
		{
			MessageBox(NULL, "読み込めません", "エラー", MB_OK);
			return false;
		}

	}

	hr = pDevice ->CreateVertexBuffer
		(
			sizeof(VERTEX_BILLBOARD) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_ENEMY,
			D3DPOOL_MANAGED,
			&g_pVertexBuffer,
			NULL
		);

	hr = pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_SHADOW) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_ENEMY,
		D3DPOOL_MANAGED,
		&g_pVertexBuffer2,
		NULL
	);

	if(FAILED(hr))
	{
		MessageBox(NULL, "読み込めません", "エラー", MB_OK);
		return FALSE;
	}

	 hr = pDevice ->CreateIndexBuffer
		(
			sizeof(WORD) * 6,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&g_pIndexBuffer,
			NULL
		);

	 hr = pDevice->CreateIndexBuffer
	 (
		 sizeof(WORD) * 6,
		 D3DUSAGE_WRITEONLY,
		 D3DFMT_INDEX16,
		 D3DPOOL_MANAGED,
		 &g_pIndexBuffer2 ,
		 NULL
	 );

	if(FAILED(hr))
	{
		MessageBox(NULL, "読み込めません", "エラー", MB_OK);
		return FALSE;
	}

	//配置の初期化
	g_TransPos[0] = D3DXVECTOR3(0.0f, 0.5f,  100.0f); //クリ
	g_TransPos[1] = D3DXVECTOR3(-130.0f, 0.7f, 90.0f);//カメ
	g_TransPos[2] = D3DXVECTOR3(-130.0f, 1.0f,  -130.0f);//ドス
	g_TransPos[3] = D3DXVECTOR3(-110.0f, 0.5f, -130.0f);//クリ
	g_TransPos[4] = D3DXVECTOR3(40.0f, 0.7f,  -0.0f);//カメ
	g_TransPos[5] = D3DXVECTOR3(-75.0f, 1.0f, -50.0f);//ドス
	g_TransPos[6] = D3DXVECTOR3(60.0f, 0.5f,  130.0f);//クリ
	g_TransPos[7] = D3DXVECTOR3(-70.0f, 0.7f, -0.0f);//カメ
	g_TransPos[8] = D3DXVECTOR3(130.0f, 1.0f,  -0.0f);//ドス
	g_TransPos[9] = D3DXVECTOR3(-40.0f, 0.5f, -20.0f);//クリ
	g_TransPos[10] = D3DXVECTOR3(70.0f, 0.7f, -120.0f);//カメ
	g_TransPos[11] = D3DXVECTOR3(135.0f, 1.0f, -40.0f);//ドス
	g_TransPos[12] = D3DXVECTOR3(40.0f, 0.5f, -100.0f);//クリ
	g_TransPos[13] = D3DXVECTOR3(0.0f, 0.7f, -125.0f);//カメ
	g_TransPos[14] = D3DXVECTOR3(125.0f, 1.0f, 40.0f);//ドス
	g_TransPos[15] = D3DXVECTOR3(130.0f, 0.5f, -130.0f);//クリ
	g_TransPos[16] = D3DXVECTOR3(50.0f, 0.7f, -80.0f);//カメ
	g_TransPos[17] = D3DXVECTOR3(130.0f, 1.0f, 95.0f);//ドス
	b_dos2 = false;
	b_dos5 = false;
	b_dos8 = false;
	b_dos11 = false;
	b_dos14 = false;
	b_dos17 = false;
	b_kuri0 = false;
	b_kuri3 = false;
	b_kuri6 = false;
	b_kuri9 = false;
	b_kuri12 = false;
	b_kame1 = false;
	b_kame4 = false;
	b_kame7 = false;
	b_kame10 = false;
	b_kame13 = false;
	b_kame16 = false;
	b_hit = false;

	//色設定
	for(int c = 0 ; c < MAX_BILLBOARD ; c++)
	{
		color[c] = c%3;
		ememy[c] = true;
		Life[c] = 0;
	}

	VertexBuffer_Field();
	IndexBuffer_Field();

	VertexBuffer_Shadow2();
	IndexBuffer_Shadow2();
	D3DXCreateTextureFromFile(pDevice, "data/texture/shadow000.jpg", &g_pTexture);

	return true;
}

void CBillboard::UninitBillboard()
{

	for(int i = 0 ; i < TEXTURE_B_MAX ; i++)
	{
		if (g_pTextures_bill[i] != NULL)
		{
			g_pTextures_bill[i] ->Release();
			g_pTextures_bill[i] = NULL;
		}
	}

	if (g_pVertexBuffer != NULL)
	{
		g_pVertexBuffer ->Release();
		g_pVertexBuffer = NULL;
	}

	if (&g_pIndexBuffer != NULL)
	{
		g_pIndexBuffer ->Release();
		g_pIndexBuffer = NULL;
	}
	if (g_pVertexBuffer2 != NULL)
	{
		g_pVertexBuffer2->Release();
		g_pVertexBuffer2 = NULL;
	}

	if (&g_pIndexBuffer2 != NULL)
	{
		g_pIndexBuffer2->Release();
		g_pIndexBuffer2 = NULL;
	}
	if (g_pTexture != NULL)
	{
		g_pTexture->Release();
		g_pTexture = NULL;
	}

}

void CBillboard::UpdateBillboard()
{
	LPDIRECT3DDEVICE9 pDevice = CRender::GetD3DDevice();

	if(pDevice == NULL){return;}

	//ビューマトリックスを取得する
	pDevice -> GetTransform( D3DTS_VIEW, &g_viewInverse );

	//view逆行列作成
	D3DXMatrixInverse(&g_viewInverse, NULL, &g_viewInverse);

	g_viewInverse._41 = g_viewInverse._42 = g_viewInverse._43 = 0.0f;

	//判定サイズ
	D3DXVECTOR3 bu = D3DXVECTOR3(0.25f, 0.25f, 0.25f);
	D3DXVECTOR3 mu = D3DXVECTOR3(0.4f, 0.2f, 0.4f);


	//クリ
	if (!b_kuri0) {
		g_TransPos[0].x += 0.05f;

		if (g_TransPos[0].x >= 8.0f)
		{
			b_kuri0 = true;
		}
	}
	if (b_kuri0) {
		g_TransPos[0].x -= 0.05f;
		if (g_TransPos[0].x <= -3.0f)
		{
			b_kuri0 = false;

		}
	}

	if (!b_kuri3) {
		g_TransPos[3].z += 0.05f;

		if (g_TransPos[3].z >= -125.0f)
		{
			b_kuri3 = true;
		}
	}
	if (b_kuri3) {
		g_TransPos[3].z -= 0.05f;
		if (g_TransPos[3].z <= -135.0f)
		{
			b_kuri3 = false;

		}
	}

	if (!b_kuri6) {
		g_TransPos[6].z += 0.05f;

		if (g_TransPos[6].z >= 135.0f)
		{
			b_kuri6 = true;
		}
	}
	if (b_kuri6) {
		g_TransPos[6].z -= 0.05f;
		if (g_TransPos[6].z <= 125.0f)
		{
			b_kuri6 = false;

		}
	}

	if (!b_kuri9) {
		g_TransPos[9].x += 0.05f;

		if (g_TransPos[9].x >= -30.0f)
		{
			b_kuri9 = true;
		}
	}
	if (b_kuri9) {
		g_TransPos[9].x -= 0.05f;
		if (g_TransPos[9].x <= -40.0f)
		{
			b_kuri9 = false;

		}
	}

	if (!b_kuri12) {
		g_TransPos[12].x += 0.05f;

		if (g_TransPos[12].x >= -30.0f)
		{
			b_kuri12 = true;
		}
	}
	if (b_kuri12) {
		g_TransPos[12].x -= 0.05f;
		if (g_TransPos[12].x <= -40.0f)
		{
			b_kuri12 = false;

		}
	}

	//亀
	if (!b_kame1) {
		g_TransPos[1].x += 0.2f;

		if (g_TransPos[1].x >= -120.0f)
		{
			b_kame1 = true;
		}
	}
	if (b_kame1) {
		g_TransPos[1].x -= 0.2f;
		if (g_TransPos[1].x <= -140.0f)
		{
			b_kame1 = false;

		}
	}
	if (!b_kame4) {
		g_TransPos[4].x += 0.2f;

		if (g_TransPos[4].x >= 47.0f)
		{
			b_kame4 = true;
		}
	}
	if (b_kame4) {
		g_TransPos[4].x -= 0.2f;
		if (g_TransPos[4].x <= 33.0f)
		{
			b_kame4 = false;

		}
	}

	if (!b_kame7) {
		g_TransPos[7].x += 0.2f;

		if (g_TransPos[7].x >= -91.0f)
		{
			b_kame7 = true;
		}
	}
	if (b_kame7) {
		g_TransPos[7].x -= 0.2f;
		if (g_TransPos[7].x <= -99.0f)
		{
			b_kame7 = false;

		}
	}
	if (!b_kame10) {
		g_TransPos[10].x += 0.2f;

		if (g_TransPos[10].x >= 77.0f)
		{
			b_kame10 = true;
		}
	}
	if (b_kame10) {
		g_TransPos[10].x -= 0.2f;
		if (g_TransPos[10].x <= 63.0f)
		{
			b_kame10 = false;

		}
	}
	if (!b_kame13) {
		g_TransPos[13].x += 0.2f;

		if (g_TransPos[13].x >= 0.0f)
		{
			b_kame13 = true;
		}
	}
	if (b_kame13) {
		g_TransPos[13].x -= 0.2f;
		if (g_TransPos[13].x <= -20.0f)
		{
			b_kame13 = false;

		}
	}

	if (!b_kame16) {
		g_TransPos[16].z += 0.2f;

		if (g_TransPos[16].z >= -63.0f)
		{
			b_kame16 = true;
		}
	}
	if (b_kame16) {
		g_TransPos[16].z -= 0.2f;
		if (g_TransPos[16].z <= -77.0f)
		{
			b_kame16 = false;

		}
	}

	//ドッスン
	if (!b_dos2 && dos_count >= 100) {
		g_TransPos[2].y += 0.03f;

		if (g_TransPos[2].y >= 5.0f)
		{
			dos_count = 0;
			b_dos2 = true;
		}
	}
	 if (b_dos2) {
		g_TransPos[2].y -= 0.15f;
		if(g_TransPos[2].y <= 1.0f)
		{
			b_dos2 = false;
		}
	}
	 if (!b_dos2) {
		 dos_count++;
	 }

	 if (!b_dos5 && dos_count >= 100) {
		 g_TransPos[5].y += 0.03f;

		 if (g_TransPos[5].y >= 5.0f)
		 {
			 b_dos5 = true;
		 }
	 }
	 if (b_dos5) {
		 g_TransPos[5].y -= 0.15f;
		 if (g_TransPos[5].y <= 1.0f)
		 {
			 b_dos5 = false;
		 }
	 }


	 if (!b_dos8 && dos_count >= 100) {
		 g_TransPos[8].y += 0.03f;

		 if (g_TransPos[8].y >= 5.0f)
		 {
			 b_dos8 = true;
		 }
	 }
	 if (b_dos8) {
		 g_TransPos[8].y -= 0.15f;
		 if (g_TransPos[8].y <= 1.0f)
		 {
			 b_dos8 = false;
		 }
	 }
	
	 if (!b_dos11 && dos_count >= 100) {
		 g_TransPos[11].y += 0.03f;

		 if (g_TransPos[11].y >= 5.0f)
		 {
			 b_dos11 = true;
		 }
	 }
	 if (b_dos11) {
		 g_TransPos[11].y -= 0.15f;
		 if (g_TransPos[11].y <= 1.0f)
		 {
			 b_dos11 = false;
		 }
	 }

	 if (!b_dos14 && dos_count >= 100) {
		 g_TransPos[14].y += 0.03f;

		 if (g_TransPos[14].y >= 5.0f)
		 {
			 b_dos14 = true;
		 }
	 }
	 if (b_dos14) {
		 g_TransPos[14].y -= 0.15f;
		 if (g_TransPos[14].y <= 1.0f)
		 {
			 b_dos14 = false;
		 }
	 }


	 if (!b_dos17 && dos_count >= 100) {
		 g_TransPos[17].y += 0.03f;

		 if (g_TransPos[17].y >= 5.0f)
		 {
			 b_dos17 = true;
		 }
	 }
	 if (b_dos17) {
		 g_TransPos[17].y -= 0.15f;
		 if (g_TransPos[17].y <= 1.0f)
		 {
			 b_dos17 = false;
		 }
	 }

	 if (CX_model::deboost() == true) {
		 b_hit = false;
	 }

	 e_coin = CCoin::ScoreCoin();

	//当たり判定
	for(int Ememy = 0 ; Ememy < MAX_BILLBOARD ; Ememy++)
	{
			
			//出現
			if (ememy[Ememy])
			{
					//当たり判定
				if (CHit::AABB(D3DXVECTOR3(g_TransPos[Ememy].x - 0.4f, g_TransPos[Ememy].y - 1.0f, g_TransPos[Ememy].z - 0.4f),
					D3DXVECTOR3(g_TransPos[Ememy].x + 0.4f, g_TransPos[Ememy].y + 1.0f, g_TransPos[Ememy].z + 0.4f),
					D3DXVECTOR3(CX_model::XmodelPos().x, CX_model::XmodelPos().y - 1, CX_model::XmodelPos().z) - mu,
					D3DXVECTOR3(CX_model::XmodelPos().x, CX_model::XmodelPos().y - 1, CX_model::XmodelPos().z) + mu))
				{

					
						PlaySound(SOUND_LABEL_DAMAGE);
						CExplosion::CreateExplosion(CX_model::XmodelPos().x, CX_model::XmodelPos().y + 1.0f, CX_model::XmodelPos().z);
						ememy[Ememy] = false;

					if (CX_model::star_muteki() == false)
					{
						e_coin -= 5;
						b_hit = true;

						if (e_coin < 0)
						{
							e_coin = 0;
						}
					}
				}

		}
		else
		{
			//復活処理
			Life[Ememy]++;

			if(Life[Ememy] > 600)
			{
				ememy[Ememy] = true;
				Life[Ememy] = 0;
			}

		}
	}


}

void CBillboard::DrawBillboard()
{
	LPDIRECT3DDEVICE9 pDevice = CRender::GetD3DDevice();
	if(pDevice == NULL){return;}

	//ライトのON・OFF
	pDevice -> SetRenderState(D3DRS_LIGHTING, FALSE);

	//αテスト
	pDevice -> SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice -> SetRenderState(D3DRS_ALPHAREF, 150);
	pDevice -> SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for(int a = 0 ; a < MAX_BILLBOARD ; a++)
	{
		if(ememy[a])
		{
			D3DXMatrixIdentity(&g_mtxWorld_Billboard);

			//FVFの設定
			//FVF->デバイスに教える
			pDevice -> SetFVF(FVF_VERTEX_ENEMY);

			//テクスチャをセット
			pDevice -> SetTexture(0, g_pTextures_bill[ color[a] ]);

			D3DXMatrixRotationY(&g_Rotation, D3DXToRadian( g_Rot2 ));

			//ビルボードの移動
			D3DXMatrixTranslation(&g_Trans, g_TransPos[a].x , g_TransPos[a].y, g_TransPos[a].z);

			g_mtxWorld_Billboard =  g_mtxWorld_Billboard  * g_Rotation ;

			g_mtxWorld_Billboard =  g_mtxWorld_Billboard  * g_viewInverse ;

			g_mtxWorld_Billboard =  g_mtxWorld_Billboard  * g_Trans ;

			//ワールド行列の設定(好きなタイミングで呼ぶ)
			pDevice -> SetTransform(D3DTS_WORLD, &g_mtxWorld_Billboard);

			pDevice ->SetStreamSource(0,g_pVertexBuffer,0,sizeof(VERTEX_BILLBOARD));

			pDevice ->SetIndices(g_pIndexBuffer);

			pDevice -> DrawIndexedPrimitive
				(D3DPT_TRIANGLELIST,//D3DPT_TRIANGLESTRIP//D3DPT_LINESTRIP//D3DPT_TRIANGLELIST
				0,//インデックスの開始数値
				0,
				6,					//インデックスの数
				0,
				2);					//プリミティブ数
		}
	}

	pDevice -> SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//元の合成に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	for (int a = 0; a < MAX_BILLBOARD; a++)
	{
		if (ememy[a]) {
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
			//αテスト
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			D3DXMatrixIdentity(&g_Shadow);

			//FVFの設定
			//FVF->デバイスに教える
			pDevice->SetFVF(FVF_VERTEX_ENEMY);

			//テクスチャをセット
			pDevice->SetTexture(0, g_pTexture);

			//ビルボードの移動
			D3DXMatrixTranslation(&g_Trans, g_TransPos[a].x, 0.5, g_TransPos[a].z);

			g_Shadow = g_Shadow  * g_Trans;

			//ワールド行列の設定(好きなタイミングで呼ぶ)
			pDevice->SetTransform(D3DTS_WORLD, &g_Shadow);

			pDevice->SetStreamSource(0, g_pVertexBuffer2, 0, sizeof(VERTEX_SHADOW));

			pDevice->SetIndices(g_pIndexBuffer2);

			pDevice->DrawIndexedPrimitive
			(D3DPT_TRIANGLELIST,//D3DPT_TRIANGLESTRIP//D3DPT_LINESTRIP//D3DPT_TRIANGLELIST
				0,//インデックスの開始数値
				0,
				6,					//インデックスの数
				0,
				2);					//プリミティブ数
		}

		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		//元の合成に戻す
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}

}

void CBillboard::VertexBuffer_Field()
{

	VERTEX_BILLBOARD b[] = 
	{
		{D3DXVECTOR3( -1.5f,  3.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(0, 0)},
		{D3DXVECTOR3(  1.5f,  3.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(1, 0)},
		{D3DXVECTOR3( -1.5f,  0.3f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(0, 1)},
		{D3DXVECTOR3(  1.5f,  0.3f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(1, 1)},

	};

	VERTEX_BILLBOARD *pV;

	g_pVertexBuffer-> Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);

	// 配列をコピーする
	memcpy(pV, b, sizeof(b));

	g_pVertexBuffer->Unlock();
}

void CBillboard::IndexBuffer_Field()
{
	WORD index_b[] ={

		0,1,2,
		1,3,2
	};

	LPWORD pIndex;

	g_pIndexBuffer  -> Lock(0,0,(void**)&pIndex,D3DLOCK_DISCARD);

	memcpy(pIndex,index_b,sizeof(WORD) * 6);

	g_pIndexBuffer ->Unlock();
}

void CBillboard::VertexBuffer_Shadow2()
{

	VERTEX_SHADOW s[] =
	{
		{ D3DXVECTOR3(-1.5f,  0.9f, 1.5f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(0, 0) },
		{ D3DXVECTOR3(1.5f,  0.9f, 1.5f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(1, 0) },
		{ D3DXVECTOR3(-1.5f,  0.9f, -1.5f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(0, 1) },
		{ D3DXVECTOR3(1.5f,  0.9f, -1.5f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(1, 1) },

	};

	VERTEX_SHADOW *pV2;

	g_pVertexBuffer2->Lock(0, 0, (void**)&pV2, D3DLOCK_DISCARD);

	// 配列をコピーする
	memcpy(pV2, s, sizeof(s));

	g_pVertexBuffer2->Unlock();
}

void CBillboard::IndexBuffer_Shadow2()
{
	WORD index_s[] = {

		0,1,2,
		1,3,2
	};

	LPWORD pIndex;

	g_pIndexBuffer2->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);
	
	memcpy(pIndex, index_s, sizeof(WORD) * 6);

	g_pIndexBuffer2->Unlock();
}


bool CBillboard::HitPlayer()
{
	return b_hit;
}

int CBillboard::CoinHit()
{
	return e_coin;
}
