//-----------------------------------//
//-----木ビルボード処理--------------//
//----[tree_bill.cpp]----------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
//インクルード文
#include "main.h"
#include "tree_bill.h"
#include "camera.h"
#include "renderer.h"
#include "player.h"
#include "mode_game.h"

// 頂点属性(1つ目：座標、2つ目：カラー,3つ目：テクスチャー)


LPDIRECT3DTEXTURE9 CTreeBill::g_pTextures_bill[TEXTURE_TREE_MAX] = { NULL };	//テクスチャ配列
D3DXMATRIX CTreeBill::g_mtxWorld_TreeBill;		//ワールド変換行列
LPDIRECT3DVERTEXBUFFER9 CTreeBill::g_pVertexBuffer = NULL;		// バーテックスバッファのポインタ
LPDIRECT3DINDEXBUFFER9 CTreeBill::g_pIndexBuffer = NULL;		// インデックスバッファのポインタ
D3DXMATRIX CTreeBill::g_viewInverse;
D3DXMATRIX CTreeBill::g_Trans, CTreeBill::g_Rotation;
D3DXVECTOR3 CTreeBill::g_TransPos[MAX_TREEBILLBOARD];
int CTreeBill::color[MAX_TREEBILLBOARD];
bool CTreeBill::ememy[MAX_TREEBILLBOARD];
int CTreeBill::Life[MAX_TREEBILLBOARD];
float  CTreeBill::g_Rot3 = 10.0f;

typedef struct
{
	D3DXVECTOR3 pos;		//座標
	D3DCOLOR color;			//色
	D3DXVECTOR2 texture;	//テクスチャ座標
}VERTEX_BILLBOARD;

bool CTreeBill::InitTreeBill()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9  pDevice = CRender::GetD3DDevice();

	if (pDevice == NULL)
	{
		return false;
	}

	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);

	HRESULT hr;

	for (int i = 0; i<TEXTURE_TREE_MAX; i++)
	{

		hr = D3DXCreateTextureFromFile(pDevice, g_aTexture_t[i].fileName, &g_pTextures_bill[i]);

		if (FAILED(hr))
		{
			MessageBox(NULL, "読み込めません", "エラー", MB_OK);
			return false;
		}

	}

	hr = pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_BILLBOARD) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_TREE,
		D3DPOOL_MANAGED,
		&g_pVertexBuffer,
		NULL
	);

	if (FAILED(hr))
	{
		MessageBox(NULL, "読み込めません", "エラー", MB_OK);
		return FALSE;
	}

	hr = pDevice->CreateIndexBuffer
	(
		sizeof(WORD) * 6,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIndexBuffer,
		NULL
	);


	if (FAILED(hr))
	{
		MessageBox(NULL, "読み込めません", "エラー", MB_OK);
		return FALSE;
	}

	//色設定
	for (int c = 0; c < MAX_TREEBILLBOARD; c++)
	{
		color[c] = c % 6;
		ememy[c] = true;
		Life[c] = 0;
	}

	VertexBuffer_Field();
	IndexBuffer_Field();

	return true;
}

void CTreeBill::UninitTreeBill()
{

	for (int i = 0; i < TEXTURE_TREE_MAX; i++)
	{
		if (g_pTextures_bill[i] != NULL)
		{
			g_pTextures_bill[i]->Release();
			g_pTextures_bill[i] = NULL;
		}
	}

	if (g_pVertexBuffer != NULL)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}

	if (&g_pIndexBuffer != NULL)
	{
		g_pIndexBuffer->Release();
		g_pIndexBuffer = NULL;
	}
}

void CTreeBill::UpdateTreeBill()
{
	g_TransPos[0]  = D3DXVECTOR3(  0.0f, 0.0f, 138.0f);
	g_TransPos[1]  = D3DXVECTOR3( 10.0f, 0.0f, 138.0f); 
	g_TransPos[2]  = D3DXVECTOR3( 20.0f, 0.0f, 138.0f); 
	g_TransPos[3]  = D3DXVECTOR3( 30.0f, 0.0f, 138.0f); 
	g_TransPos[4]  = D3DXVECTOR3( 40.0f, 0.0f, 138.0f); 
	g_TransPos[5]  = D3DXVECTOR3( 50.0f, 0.0f, 138.0f); 
	g_TransPos[6]  = D3DXVECTOR3( 60.0f, 0.0f, 138.0f); 
	g_TransPos[7]  = D3DXVECTOR3( 70.0f, 0.0f, 138.0f); 
	g_TransPos[8]  = D3DXVECTOR3( 80.0f, 0.0f, 138.0f); 
	g_TransPos[9]  = D3DXVECTOR3( 90.0f, 0.0f, 138.0f); 
	g_TransPos[10] = D3DXVECTOR3(-10.0f, 0.0f, 138.0f);
	g_TransPos[11] = D3DXVECTOR3(-20.0f, 0.0f, 138.0f); 
	g_TransPos[12] = D3DXVECTOR3(-30.0f, 0.0f, 138.0f); 
	g_TransPos[13] = D3DXVECTOR3(-40.0f, 0.0f, 138.0f); 
	g_TransPos[14] = D3DXVECTOR3(-50.0f, 0.0f, 138.0f); 
	g_TransPos[15] = D3DXVECTOR3(-60.0f, 0.0f, 138.0f); 
	g_TransPos[16] = D3DXVECTOR3(-70.0f, 0.0f, 138.0f); 
	g_TransPos[17] = D3DXVECTOR3(-80.0f, 0.0f, 138.0f); 
	g_TransPos[18] = D3DXVECTOR3(-90.0f, 0.0f, 138.0f); 
	g_TransPos[19] = D3DXVECTOR3(-100.0f, 0.0f, 138.0f);
	g_TransPos[20] = D3DXVECTOR3(-110.0f, 0.0f, 138.0f);
	g_TransPos[21] = D3DXVECTOR3(-120.0f, 0.0f, 138.0f);
	g_TransPos[22] = D3DXVECTOR3(-130.0f, 0.0f, 138.0f);
	g_TransPos[23] = D3DXVECTOR3(100.0f, 0.0f, 138.0f);
	g_TransPos[24] = D3DXVECTOR3(110.0f, 0.0f, 138.0f);
	g_TransPos[25] = D3DXVECTOR3(120.0f, 0.0f, 138.0f);
	g_TransPos[26] = D3DXVECTOR3(130.0f, 0.0f, 138.0f);

	g_TransPos[27] = D3DXVECTOR3(138.0f, 0.0f, 138.0f);
	g_TransPos[28] = D3DXVECTOR3(138.0f, 0.0f, 128.0f);
	g_TransPos[29] = D3DXVECTOR3(138.0f, 0.0f, 118.0f);
	g_TransPos[30] = D3DXVECTOR3(138.0f, 0.0f, 108.0f);
	g_TransPos[31] = D3DXVECTOR3(138.0f, 0.0f, 98.0f);
	g_TransPos[32] = D3DXVECTOR3(138.0f, 0.0f, 88.0f);
	g_TransPos[33] = D3DXVECTOR3(138.0f, 0.0f, 78.0f);
	g_TransPos[34] = D3DXVECTOR3(138.0f, 0.0f, 68.0f);
	g_TransPos[35] = D3DXVECTOR3(138.0f, 0.0f, 58.0f);
	g_TransPos[36] = D3DXVECTOR3(138.0f, 0.0f, 48.0f);
	g_TransPos[37] = D3DXVECTOR3(138.0f, 0.0f, 38.0f);
	g_TransPos[38] = D3DXVECTOR3(138.0f, 0.0f, 28.0f);
	g_TransPos[39] = D3DXVECTOR3(138.0f, 0.0f, 18.0f);
	g_TransPos[40] = D3DXVECTOR3(138.0f, 0.0f, 8.0f);
	g_TransPos[41] = D3DXVECTOR3(138.0f, 0.0f, -2.0f);
	g_TransPos[42] = D3DXVECTOR3(138.0f, 0.0f, -12.0f);
	g_TransPos[43] = D3DXVECTOR3(138.0f, 0.0f, -22.0f);
	g_TransPos[44] = D3DXVECTOR3(138.0f, 0.0f, -32.0f);
	g_TransPos[45] = D3DXVECTOR3(138.0f, 0.0f, -42.0f);
	g_TransPos[46] = D3DXVECTOR3(138.0f, 0.0f, -52.0f);
	g_TransPos[47] = D3DXVECTOR3(138.0f, 0.0f, -62.0f);
	g_TransPos[48] = D3DXVECTOR3(138.0f, 0.0f, -72.0f);
	g_TransPos[49] = D3DXVECTOR3(138.0f, 0.0f, -82.0f);
	g_TransPos[50] = D3DXVECTOR3(138.0f, 0.0f, -92.0f);
	g_TransPos[51] = D3DXVECTOR3(138.0f, 0.0f, -102.0f);
	g_TransPos[52] = D3DXVECTOR3(138.0f, 0.0f, -112.0f);
	g_TransPos[53] = D3DXVECTOR3(138.0f, 0.0f, -122.0f);
	g_TransPos[54] = D3DXVECTOR3(138.0f, 0.0f, -132.0f);
	g_TransPos[55] = D3DXVECTOR3(138.0f, 0.0f, -142.0f);
	g_TransPos[56] = D3DXVECTOR3(138.0f, 0.0f, 88.0f);
	g_TransPos[57] = D3DXVECTOR3(138.0f, 0.0f, 88.0f);
	g_TransPos[58] = D3DXVECTOR3(138.0f, 0.0f, 88.0f);

	

	g_TransPos[59] = D3DXVECTOR3(-138.0f, 0.0f, 118.0f);
	g_TransPos[60] = D3DXVECTOR3(-138.0f, 0.0f, 108.0f);
	g_TransPos[61] = D3DXVECTOR3(-138.0f, 0.0f, 98.0f);
	g_TransPos[62] = D3DXVECTOR3(-138.0f, 0.0f, 88.0f);
	g_TransPos[63] = D3DXVECTOR3(-138.0f, 0.0f, 78.0f);
	g_TransPos[64] = D3DXVECTOR3(-138.0f, 0.0f, 68.0f);
	g_TransPos[65] = D3DXVECTOR3(-138.0f, 0.0f, 58.0f);
	g_TransPos[66] = D3DXVECTOR3(-138.0f, 0.0f, 48.0f);
	g_TransPos[67] = D3DXVECTOR3(-138.0f, 0.0f, 38.0f);
	g_TransPos[68] = D3DXVECTOR3(-138.0f, 0.0f, 28.0f);
	g_TransPos[69] = D3DXVECTOR3(-138.0f, 0.0f, 18.0f);
	g_TransPos[70] = D3DXVECTOR3(-138.0f, 0.0f, 8.0f);
	g_TransPos[71] = D3DXVECTOR3(-138.0f, 0.0f, -2.0f);
	g_TransPos[72] = D3DXVECTOR3(-138.0f, 0.0f, -12.0f);
	g_TransPos[73] = D3DXVECTOR3(-138.0f, 0.0f, -22.0f);
	g_TransPos[74] = D3DXVECTOR3(-138.0f, 0.0f, -32.0f);
	g_TransPos[75] = D3DXVECTOR3(-138.0f, 0.0f, -42.0f);
	g_TransPos[76] = D3DXVECTOR3(-138.0f, 0.0f, -52.0f);
	g_TransPos[77] = D3DXVECTOR3(-138.0f, 0.0f, -62.0f);
	g_TransPos[78] = D3DXVECTOR3(-138.0f, 0.0f, -72.0f);
	g_TransPos[79] = D3DXVECTOR3(-138.0f, 0.0f, -82.0f);
	g_TransPos[80] = D3DXVECTOR3(-138.0f, 0.0f, -92.0f);
	g_TransPos[81] = D3DXVECTOR3(-138.0f, 0.0f, -102.0f);
	g_TransPos[82] = D3DXVECTOR3(-138.0f, 0.0f, -112.0f);
	g_TransPos[83] = D3DXVECTOR3(-138.0f, 0.0f, -122.0f);
	g_TransPos[84] = D3DXVECTOR3(-138.0f, 0.0f, -132.0f);
	g_TransPos[85] = D3DXVECTOR3(-138.0f, 0.0f, -142.0f);
	g_TransPos[86] = D3DXVECTOR3(-138.0f, 0.0f, 88.0f);
	g_TransPos[87] = D3DXVECTOR3(-138.0f, 0.0f, 88.0f);
	g_TransPos[88] = D3DXVECTOR3(-138.0f, 0.0f, 88.0f);

	g_TransPos[89] = D3DXVECTOR3(138.0f, 0.0f, 138.0f);
	g_TransPos[90] = D3DXVECTOR3(138.0f, 0.0f, 128.0f);

	g_TransPos[91] = D3DXVECTOR3(-20.0f, 0.0f, 121.0f);
	g_TransPos[92] = D3DXVECTOR3(-30.0f, 0.0f, 121.0f);
	g_TransPos[93] = D3DXVECTOR3(-40.0f, 0.0f, 121.0f);
	g_TransPos[94] = D3DXVECTOR3(-50.0f, 0.0f, 121.0f);
	g_TransPos[95] = D3DXVECTOR3(-60.0f, 0.0f, 121.0f);
	g_TransPos[96] = D3DXVECTOR3(-70.0f, 0.0f, 121.0f);
	g_TransPos[97] = D3DXVECTOR3(-80.0f, 0.0f, 121.0f);
	g_TransPos[98] = D3DXVECTOR3(-90.0f, 0.0f, 121.0f);

	g_TransPos[123] = D3DXVECTOR3(-100.0f, 0.0f, 121.0f);
	g_TransPos[124] = D3DXVECTOR3(-110.0f, 0.0f, 121.0f);
	g_TransPos[125] = D3DXVECTOR3(-120.0f, 0.0f, 121.0f);

	g_TransPos[153] = D3DXVECTOR3(-10.0f, 0.0f, 122.0f);
	g_TransPos[154] = D3DXVECTOR3(-138.0f, 0.0f,128.0f);
	g_TransPos[155] = D3DXVECTOR3(-138.0f, 0.0f,138.0f);

	g_TransPos[99] = D3DXVECTOR3(-121.0f, 0.0f, 118.0f);
	g_TransPos[100] = D3DXVECTOR3(-121.0f, 0.0f, 108.0f);
	g_TransPos[101] = D3DXVECTOR3(-121.0f, 0.0f, 98.0f);
	g_TransPos[102] = D3DXVECTOR3(-121.0f, 0.0f, 88.0f);
	g_TransPos[103] = D3DXVECTOR3(-121.0f, 0.0f, 78.0f);
	g_TransPos[104] = D3DXVECTOR3(-121.0f, 0.0f, 68.0f);
	g_TransPos[105] = D3DXVECTOR3(-121.0f, 0.0f, 58.0f);
	g_TransPos[106] = D3DXVECTOR3(-121.0f, 0.0f, 48.0f);
	g_TransPos[107] = D3DXVECTOR3(-121.0f, 0.0f, 38.0f);
	g_TransPos[108] = D3DXVECTOR3(-121.0f, 0.0f, 28.0f);
	g_TransPos[109] = D3DXVECTOR3(-121.0f, 0.0f, 18.0f);
	g_TransPos[110] = D3DXVECTOR3(-121.0f, 0.0f, 8.0f);
	g_TransPos[111] = D3DXVECTOR3(-121.0f, 0.0f, -2.0f);
	g_TransPos[112] = D3DXVECTOR3(-121.0f, 0.0f, -12.0f);
	g_TransPos[113] = D3DXVECTOR3(-121.0f, 0.0f, -22.0f);
	g_TransPos[114] = D3DXVECTOR3(-121.0f, 0.0f, -32.0f);
	g_TransPos[115] = D3DXVECTOR3(-121.0f, 0.0f, -42.0f);
	g_TransPos[116] = D3DXVECTOR3(-121.0f, 0.0f, -52.0f);
	g_TransPos[117] = D3DXVECTOR3(-121.0f, 0.0f, -62.0f);
	g_TransPos[118] = D3DXVECTOR3(-121.0f, 0.0f, -72.0f);
	g_TransPos[119] = D3DXVECTOR3(-121.0f, 0.0f, -82.0f);
	g_TransPos[120] = D3DXVECTOR3(-121.0f, 0.0f, -92.0f);
	g_TransPos[121] = D3DXVECTOR3(-121.0f, 0.0f, -102.0f);
	g_TransPos[122] = D3DXVECTOR3(-121.0f, 0.0f, -112.0f);

	g_TransPos[126] = D3DXVECTOR3(-121.0f, 0.0f, 88.0f);
	g_TransPos[127] = D3DXVECTOR3(-121.0f, 0.0f, 88.0f);
	g_TransPos[128] = D3DXVECTOR3(-121.0f, 0.0f, 88.0f);


	g_TransPos[129] = D3DXVECTOR3(121.0f, 0.0f, 118.0f);
	g_TransPos[130] = D3DXVECTOR3(121.0f, 0.0f, 108.0f);
	g_TransPos[131] = D3DXVECTOR3(121.0f, 0.0f, 98.0f);
	g_TransPos[132] = D3DXVECTOR3(121.0f, 0.0f, 88.0f);
	g_TransPos[133] = D3DXVECTOR3(121.0f, 0.0f, 78.0f);
	g_TransPos[134] = D3DXVECTOR3(121.0f, 0.0f, 68.0f);
	g_TransPos[135] = D3DXVECTOR3(121.0f, 0.0f, 58.0f);
	g_TransPos[136] = D3DXVECTOR3(121.0f, 0.0f, 48.0f);
	g_TransPos[137] = D3DXVECTOR3(121.0f, 0.0f, 38.0f);
	g_TransPos[138] = D3DXVECTOR3(121.0f, 0.0f, 28.0f);
	g_TransPos[139] = D3DXVECTOR3(121.0f, 0.0f, 18.0f);
	g_TransPos[140] = D3DXVECTOR3(121.0f, 0.0f, 8.0f);
	g_TransPos[141] = D3DXVECTOR3(121.0f, 0.0f, -2.0f);
	g_TransPos[142] = D3DXVECTOR3(121.0f, 0.0f, -12.0f);
	g_TransPos[143] = D3DXVECTOR3(121.0f, 0.0f, -22.0f);
	g_TransPos[144] = D3DXVECTOR3(121.0f, 0.0f, -32.0f);
	g_TransPos[145] = D3DXVECTOR3(121.0f, 0.0f, -42.0f);
	g_TransPos[146] = D3DXVECTOR3(121.0f, 0.0f, -52.0f);
	g_TransPos[147] = D3DXVECTOR3(121.0f, 0.0f, -62.0f);
	g_TransPos[148] = D3DXVECTOR3(121.0f, 0.0f, -72.0f);
	g_TransPos[149] = D3DXVECTOR3(121.0f, 0.0f, -82.0f);
	g_TransPos[150] = D3DXVECTOR3(121.0f, 0.0f, -92.0f);
	g_TransPos[151] = D3DXVECTOR3(121.0f, 0.0f, -102.0f);
	g_TransPos[152] = D3DXVECTOR3(121.0f, 0.0f, -112.0f);
	g_TransPos[156] = D3DXVECTOR3(121.0f, 0.0f, 88.0f);
	g_TransPos[157] = D3DXVECTOR3(121.0f, 0.0f, 88.0f);
	g_TransPos[158] = D3DXVECTOR3(121.0f, 0.0f, 88.0f);


	LPDIRECT3DDEVICE9 pDevice = CRender::GetD3DDevice();

	if (pDevice == NULL) { return; }

	//g_mtxWorld_TreeBill = GetView();

	//ビューマトリックスを取得する
	pDevice->GetTransform(D3DTS_VIEW, &g_viewInverse);

	//view逆行列作成
	D3DXMatrixInverse(&g_viewInverse, NULL, &g_viewInverse);

	g_viewInverse._41 = g_viewInverse._42 = g_viewInverse._43 = 0.0f;

}

void CTreeBill::DrawTreeBill()
{
	LPDIRECT3DDEVICE9 pDevice = CRender::GetD3DDevice();
	if (pDevice == NULL) { return; }

	//ライトのON・OFF
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//αテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int a = 0; a < MAX_TREEBILLBOARD; a++)
	{
		if (ememy[a])
		{
			D3DXMatrixIdentity(&g_mtxWorld_TreeBill);

			//FVFの設定
			//FVF->デバイスに教える
			pDevice->SetFVF(FVF_VERTEX_TREE);

			//テクスチャをセット
			pDevice->SetTexture(0, g_pTextures_bill[color[a]]);

			D3DXMatrixRotationY(&g_Rotation, D3DXToRadian(g_Rot3));

			//ビルボードの移動
			D3DXMatrixTranslation(&g_Trans, g_TransPos[a].x, g_TransPos[a].y, g_TransPos[a].z);

			//D3DXMatrixMultiply(&g_mtxWorld_TreeBill, &g_viewInverse, &g_mtxWorld_TreeBill);
			//D3DXMatrixMultiply(&g_mtxWorld_TreeBill, &g_Trans, &g_mtxWorld_TreeBill);

			g_mtxWorld_TreeBill = g_mtxWorld_TreeBill  * g_Rotation;

			g_mtxWorld_TreeBill = g_mtxWorld_TreeBill  * g_viewInverse;

			g_mtxWorld_TreeBill = g_mtxWorld_TreeBill  * g_Trans;

			//ワールド行列の設定(好きなタイミングで呼ぶ)
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld_TreeBill);

			pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(VERTEX_BILLBOARD));

			pDevice->SetIndices(g_pIndexBuffer);

			pDevice->DrawIndexedPrimitive
			(D3DPT_TRIANGLELIST,//D3DPT_TRIANGLESTRIP//D3DPT_LINESTRIP//D3DPT_TRIANGLELIST
				0,//インデックスの開始数値
				0,
				6,					//インデックスの数
				0,
				2);					//プリミティブ数
		}
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

void CTreeBill::VertexBuffer_Field()
{

	VERTEX_BILLBOARD b[] =
	{
		{ D3DXVECTOR3(-4.0f,  8.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(0, 0) },
		{ D3DXVECTOR3( 4.0f,  8.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(1, 0) },
		{ D3DXVECTOR3(-4.0f,  0.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(0, 1) },
		{ D3DXVECTOR3( 4.0f,  0.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(1, 1) },

	};

	VERTEX_BILLBOARD *pV;

	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);

	// 配列をコピーする
	memcpy(pV, b, sizeof(b));

	g_pVertexBuffer->Unlock();
}

void CTreeBill::IndexBuffer_Field()
{
	WORD index_b[] = {

		0,1,2,
		1,3,2
	};

	LPWORD pIndex;

	g_pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);

	memcpy(pIndex, index_b, sizeof(WORD) * 6);

	g_pIndexBuffer->Unlock();
}