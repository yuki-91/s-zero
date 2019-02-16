//-----------------------------------//
//--プレイヤー処理-------[player.cpp]//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#include "player.h"
#include "myInput.h"
#include"dash_effect.h"
#include"smoke_effect.h"
#include"drifting_effect.h"
#include"start_effect.h"
#include "kasoku_effect.h"
#include "mesh.h"
#include "manager.h"
#include "hit.h"
#include "dashboard.h"
#include "dashboard_side.h"
#include "coin.h"
#include "Enemy.h"
#include "Explosion.h"
#include "input.h"
#include <math.h>
#include "Polygon.h"
#include "renderer.h"
#include "sound.h"
#include "star_effect.h"
#include "jump_board.h"
#include "jump_effect.h"
#include "jump_board_reverse.h"
//グローバル変数
// 頂点属性(1つ目：座標、2つ目：カラー,3つ目：テクスチャー)
#define FVF_VERTEX_PLAYER (D3DFVF_XYZ|D3DFVF_DIFFUSE | D3DFVF_TEX1 )
#define ACCEL_X 0.005f
#define Brake_X 0.003f
#define Brake_Z 0.003f
#define MAX_SPEEDKASOKU 1.0f
#define MAX_GARD 0.3f
#define TURBO_COUNT 30
#define FILE_X "data/3D/harleyplay5.x"
#define VALUE_GRAVITY (0.10f) // 重力量 
LPD3DXMESH g_pMesh = NULL;		//メッシュデータ
DWORD g_nMaterialNum = 0;		//マテリアルの数
LPD3DXBUFFER g_pMaterialsBuffer = NULL;		//マテリアルのバッファー
LPD3DXBUFFER g_pMaterials = NULL;
D3DMATERIAL9*	g_pMeshMaterials = NULL;	// マテリアル情報
LPDIRECT3DTEXTURE9 pMeshTex[TEXTURE_3D_MAX] = { NULL };	// メッシュのテクスチャ

D3DXMATRIX CX_model::g_World;
D3DXMATRIX CX_model::g_Pos;		//位置の行列
D3DXVECTOR3 CX_model::g_Transmodel;		//移動
D3DXVECTOR3 CX_model::g_Dir;		//向き
D3DXMATRIX CX_model::g_Rotation, CX_model::g_mtxScale;	//回転 拡大
D3DXMATRIX CX_model::g_Shadow;		//影のワールド行列
LPDIRECT3DTEXTURE9 CX_model::m_pTextures;
float  CX_model::g_Rot = 180.0f;
LPDIRECT3DVERTEXBUFFER9 CX_model::g_pVertexBuffer = NULL;		// バーテックスバッファのポインタ
LPDIRECT3DINDEXBUFFER9 CX_model::g_pIndexBuffer = NULL;		// インデックスバッファのポインタ
bool CX_model::g_modelbUse = false;
D3DXMATRIX CX_model::m_WorldMatirix;
LPDIRECT3DDEVICE9 CX_model::pDevice;
D3DXMATRIX CX_model::t_matrix, CX_model::s_matrix, CX_model::r_matrix, CX_model::q_matrix, CX_model::z_matrix;
D3DXVECTOR3     CX_model::g_rot = D3DXVECTOR3(0, 0, 0);     //  回転   
D3DXVECTOR3     CX_model::g_pos = D3DXVECTOR3(0, 0, 20);
double CX_model::vx = 0.0f;
bool CX_model::b_deboost = false;
bool CX_model::b_boost = false;
bool CX_model::b_boost2 = false;
bool CX_model::coin0 = false;
float CX_model::max_speed = 0.5f;
float CX_model::star_speed = 0.0f;
bool CX_model::dashout = false;
int CX_model::kinoko_time = 0;
int CX_model::kinoko_time2 = 0;
int CX_model::kinoko_time3 = 0;
int CX_model::star_time = 0;
bool CX_model::kino = false;
bool CX_model::kino2 = false;
bool CX_model::kino3 = false;
bool CX_model::kino_count = false;
bool CX_model::star = false;
bool CX_model::b_startdash = false;
bool CX_model::b_startmiss = false;
bool CX_model::b_kinoko_hit = false;

bool bJump = false;	// ジャンプ中かどうか
bool bUp = false;	//上昇・下降判定
bool OnField = false;
float fJump = 0.0f;
bool bJumpAll = false;
bool pos_y = false;

float roll = 0.0f;
float jump_roll = 0.0f;
int turbo_count = 0;
int turbo_speed_count = 0;
float jump_dash = 0.0f;
bool engin_sound = false;
int pw_dash_time = 0;
bool pw_dash_derete = false;

CX_model *CX_model::Create()
{
	CX_model *m_X_model = new CX_model();
	m_X_model->InitXmodel();
	return m_X_model;
}

CX_model::CX_model()
{
	g_pMesh = NULL;
	g_nMaterialNum = 0;
	g_pMaterials = NULL;
}

CX_model::~CX_model()
{

}



bool CX_model::InitXmodel(void)
{
	pDevice = CRender::GetD3DDevice();	//デバイスの取得
	coin0 = false;
	vx = 0.0f;
	g_pos = D3DXVECTOR3(0.0f, 1.4f, 0.0f);
	g_Dir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	g_rot = D3DXVECTOR3(0, 0, 0);     //  回転
	g_Rot = 180.0f;
	b_deboost = false;
	b_boost = false;
	b_boost2 = false;
	max_speed = 0.5f;
	star_speed = 0.0f;
	dashout = false;
	g_modelbUse = false;
	kinoko_time = 0;
	kinoko_time2 = 0;
	kinoko_time3 = 0;
	star_time = 0;
	kino = false;
	kino2 = false;
	kino3 = false;
	kino_count = false;
	star = false;
	b_startdash = false;
	b_startmiss = false;
	b_kinoko_hit = false;
	fJump = 0.0f;
	OnField = false;
	jump_dash = 0.0f;
	pw_dash_time = 0;
	pw_dash_derete = false;
	if (pDevice == NULL)
	{
		return false;
	}

	HRESULT hr;

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
		MessageBox(NULL, "読み込めません3", "エラー", MB_OK);
		return FALSE;
	}

	LPD3DXBUFFER pAdjacency = NULL;

	//xファイル読み込み
	hr = D3DXLoadMeshFromX(
		FILE_X,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		&pAdjacency,			//隣接情報
		&g_pMaterialsBuffer,			//
		NULL,
		&g_nMaterialNum,		//マテリアルはいくつあるか
		&g_pMesh);

	if (FAILED(hr))
	{
		MessageBox(NULL, "失敗しました0", "読み込めませんでした0", MB_OK);
		return FALSE;
	}


	g_pMesh->OptimizeInplace(
		D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE,
		(DWORD*)pAdjacency->GetBufferPointer(),
		NULL,
		NULL,
		NULL
	);

	LPD3DXMESH pCloneMesh;

	D3DVERTEXELEMENT9 elements[MAXD3DDECLLENGTH + 1];

	g_pMesh->GetDeclaration(elements);
	g_pMesh->CloneMesh(D3DXMESH_MANAGED | D3DXMESH_WRITEONLY, elements, pDevice, &pCloneMesh);

	//メモをしておく
	g_pMesh = pCloneMesh;

	D3DXMATERIAL* pMaterials = (D3DXMATERIAL*)g_pMaterialsBuffer->GetBufferPointer();

	g_pMeshMaterials = new D3DMATERIAL9[g_nMaterialNum];		// メッシュ情報を確保

	for (DWORD i = 0; i < g_nMaterialNum; i++)
	{
		//マテリアル情報をセット
		g_pMeshMaterials[i] = pMaterials[i].MatD3D;

		 //使用しているテクスチャがあれば読み込む
		if (pMaterials[i].pTextureFilename != NULL && lstrlen(pMaterials[i].pTextureFilename) > 0)
		{
			// テクスチャ読み込み
			if (FAILED(D3DXCreateTextureFromFile(
				pDevice,
				pMaterials[i].pTextureFilename,
				&pMeshTex[i])))
			{
				return false;
			}
		}
	}

	return true;
}


void CX_model::Uninit()
{

	for (int i = 0; i < TEXTURE_3D_MAX; i++)
	{
		if (pMeshTex[i] != NULL)
		{
			pMeshTex[i]->Release();
			pMeshTex[i] = NULL;
		}
	}

	if (g_pVertexBuffer != NULL)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}

	if (g_pMaterials != NULL)
	{
		g_pMaterials->Release();
		g_pMaterials = NULL;
	}

	if (m_pTextures != NULL)
	{
		m_pTextures->Release();
		m_pTextures = NULL;

	}
	if (pDevice != NULL)
	{
		pDevice->Release();
		pDevice = NULL;
	}

	CX_model *m_X_model = new CX_model();
	
	delete m_X_model;
	delete g_pMeshMaterials;
}

void CX_model::Update()
{
	D3DXMatrixIdentity(&g_World);
	D3DXMatrixIdentity(&g_Shadow);
	D3DXMatrixIdentity(&t_matrix);
	D3DXMatrixIdentity(&s_matrix);
	D3DXMatrixIdentity(&q_matrix);
	D3DXMatrixIdentity(&r_matrix);
	D3DXMatrixIdentity(&z_matrix);

	float force_left = 0;
	float force_right = 0;

	engin_sound = false;

	if (g_modelbUse) {

		float t = 2.0f * 3.141592653589793f * (g_Rot + 270.0f) / 360.0f;

		g_Dir = D3DXVECTOR3((float)cos(t), 0.0f, (float)sin(t));

		D3DXVec3Normalize(&g_Dir, &g_Dir);

		//キーのベクトル
		D3DXVECTOR3 KeyVec;

		//キーの取得判定
		int KeyNumber = 0;

		if (MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_A) || GetKeyboardPress(DIK_K)) { KeyNumber += 1; }
		else {
			if (vx < 0) vx += Brake_X;
			else if (vx > 0) vx -= Brake_X;
		}
		if (Camera::Get_back_millor() == false) {
			if (MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_STAIC4) && MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_RIGHT_SHOULDER) || GetKeyboardPress(DIK_A) && GetKeyboardPress(DIK_J)) KeyNumber += 10;
			if (MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_B) || GetKeyboardPress(DIK_S)) KeyNumber += 100;
			if (MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_STAIC3) && MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_RIGHT_SHOULDER) || GetKeyboardPress(DIK_D) && GetKeyboardPress(DIK_J)) KeyNumber += 1000;
			if (MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_STAIC4) || GetKeyboardPress(DIK_A)) KeyNumber += 10000;
			if (MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_STAIC3) || GetKeyboardPress(DIK_D)) KeyNumber += 100000;
		}
		//移動したい向きのベクトル
		KeyVec = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		//「現在の向きのベクトル」と「移動したい向きのベクトル」の外積
		D3DXVec3Cross(&g_Dir, &g_Dir, &KeyVec);

		////特定の角度なら回転しない
		D3DXMatrixTranslation(&s_matrix, 0, 0, 0);    //  移動マトリクスの初期化    
		D3DXMatrixRotationYawPitchRoll(&z_matrix, 0, 0, roll);    //  回転マトリクスの作成
		D3DXMatrixTranslation(&s_matrix, 0, 0, vx);  //  移動マトリクスの作成  
		switch (KeyNumber)
		{
			//上
		case 1:
		case 1011:
			//移動量
			D3DXMatrixRotationYawPitchRoll(&z_matrix, 0, 0, roll);    //  回転マトリクスの作成
			vx -= ACCEL_X;
			engin_sound = true;
			CSmokeEffect::Createsmoke_explosion(CX_model::XmodelPos().x, CX_model::XmodelPos().y, CX_model::XmodelPos().z);
			break;

			//左ドリフト
		case 10010:
			if (vx < 0) {
				vx += Brake_Z;
			}

			force_left -= vx * vx * 2;
			if (force_left <= -0.25) {
				force_left = -0.25;
			}

			D3DXMatrixTranslation(&s_matrix, force_left, 0, vx);  //  移動マトリクスの作成  
			g_rot.y -= 0.035f;                                    //  Y軸方向に０．２ｆ分減算回転    
			D3DXMatrixRotationYawPitchRoll(&z_matrix, 0, 0, -0.3f);    //  回転マトリクスの作成

			turbo_count++;
			if (turbo_count > TURBO_COUNT)
			{
				PlaySound(SOUND_LABEL_TURBO);
				CDriftingEffect::CreateDrifting_effect(CX_model::XmodelPos().x, CX_model::XmodelPos().y, CX_model::XmodelPos().z);
			}
			break;

			//下
		case 100:
		case 1110:
		case 101:
			if (vx < 0) {
				vx += Brake_Z;
			}

			break;

			//右ドリフト
		case 101000:
			if (vx < 0) {
				vx += Brake_Z;
			}

			force_right += vx * vx * 2;
			if (force_right >= 0.25) {
				force_right = 0.25;
			}
			D3DXMatrixTranslation(&s_matrix, force_right, 0, vx);  //  移動マトリクスの作成 
			g_rot.y += 0.035f;                                    //  Y軸方向に０．２ｆ分加算回転 
			D3DXMatrixRotationYawPitchRoll(&z_matrix, 0, 0, 0.3f);    //  回転マトリクスの作成
			turbo_count++;
			if (turbo_count > TURBO_COUNT)
			{
				PlaySound(SOUND_LABEL_TURBO);
				CDriftingEffect::CreateDrifting_effect(CX_model::XmodelPos().x, CX_model::XmodelPos().y, CX_model::XmodelPos().z);
			}
			break;
			//右下上ドリフト
		case 101101:
			if (vx < 0) {
				vx += Brake_Z;
			}
			force_right += vx * vx * 2;
			if (force_right >= 0.25) {
				force_right = 0.25;
			}
			D3DXMatrixTranslation(&s_matrix, force_right, 0, vx);  //  移動マトリクスの作成 
			g_rot.y += 0.035f;                                    //  Y軸方向に０．２ｆ分加算回転 
			D3DXMatrixRotationYawPitchRoll(&z_matrix, 0, 0, 0.3f);    //  回転マトリクスの作成
			turbo_count++;
			if (turbo_count > TURBO_COUNT)
			{
				PlaySound(SOUND_LABEL_TURBO);
				CDriftingEffect::CreateDrifting_effect(CX_model::XmodelPos().x, CX_model::XmodelPos().y, CX_model::XmodelPos().z);
			}
			break;
			//左下上ドリフト
		case 10111:
			if (vx < 0) {
				vx += Brake_Z;
			}
			force_left -= vx * vx * 2;
			if (force_left <= -0.25) {
				force_left = -0.25;
			}
			D3DXMatrixTranslation(&s_matrix, force_left, 0, vx);  //  移動マトリクスの作成  
			g_rot.y -= 0.035f;                                   //  Y軸方向に０．２ｆ分減算回転    
			D3DXMatrixRotationYawPitchRoll(&z_matrix, 0, 0, -0.3f);    //  回転マトリクスの作成
			turbo_count++;
			if (turbo_count > TURBO_COUNT)
			{
				PlaySound(SOUND_LABEL_TURBO);
				CDriftingEffect::CreateDrifting_effect(CX_model::XmodelPos().x, CX_model::XmodelPos().y, CX_model::XmodelPos().z);
			}
			break;
			//右上ドリフト
		case 101001:
			if (vx < 0) {
				vx += Brake_Z;
			}
			force_right += vx * vx * 2;
			if (force_right >= 0.25) {
				force_right = 0.25;
			}
			D3DXMatrixTranslation(&s_matrix, force_right, 0, vx);  //  移動マトリクスの作成 
			g_rot.y += 0.035f;                                    //  Y軸方向に０．２ｆ分加算回転 
			D3DXMatrixRotationYawPitchRoll(&z_matrix, 0, 0, 0.3f);    //  回転マトリクスの作成
			turbo_count++;
			if (turbo_count > TURBO_COUNT)
			{
				PlaySound(SOUND_LABEL_TURBO);
				CDriftingEffect::CreateDrifting_effect(CX_model::XmodelPos().x, CX_model::XmodelPos().y, CX_model::XmodelPos().z);
			}
			CSmokeEffect::Createsmoke_explosion(CX_model::XmodelPos().x, CX_model::XmodelPos().y, CX_model::XmodelPos().z);
			break;

			//右下ドリフト
		case 101100:
			force_right += vx * vx * 2;
			if (force_right >= 0.25) {
				force_right = 0.25;
			}
			D3DXMatrixTranslation(&s_matrix, force_right, 0, vx);  //  移動マトリクスの作成 
			if (vx < 0) {
				vx += Brake_Z;
			}
			D3DXMatrixRotationYawPitchRoll(&z_matrix, 0, 0, 0.3f);    //  回転マトリクスの作成
			g_rot.y += 0.035f;
			turbo_count++;
			if (turbo_count > TURBO_COUNT)
			{
				PlaySound(SOUND_LABEL_TURBO);
				CDriftingEffect::CreateDrifting_effect(CX_model::XmodelPos().x, CX_model::XmodelPos().y, CX_model::XmodelPos().z);
			}
			break;

			//左上ドリフト
		case 10011:
			if (vx < 0) {
				vx += Brake_Z;
			}
			force_left -= vx * vx * 2;
			if (force_left <= -0.25) {
				force_left = -0.25;
			}
			D3DXMatrixTranslation(&s_matrix, force_left, 0, vx);  //  移動マトリクスの作成  
			g_rot.y -= 0.035f;                                    //  Y軸方向に０．２ｆ分減算回転      
			D3DXMatrixRotationYawPitchRoll(&z_matrix, 0, 0, -0.3f);    //  回転マトリクスの作成
			turbo_count++;
			if (turbo_count > TURBO_COUNT)
			{
				PlaySound(SOUND_LABEL_TURBO);
				CDriftingEffect::CreateDrifting_effect(CX_model::XmodelPos().x, CX_model::XmodelPos().y, CX_model::XmodelPos().z);
			}
			CSmokeEffect::Createsmoke_explosion(CX_model::XmodelPos().x, CX_model::XmodelPos().y, CX_model::XmodelPos().z);
			break;

			//左下ドリフト
		case 10110:
			force_left -= vx * vx * 2;
			if (force_left <= -0.25) {
				force_left = -0.25;
			}
			D3DXMatrixTranslation(&s_matrix, force_left, 0, vx);  //  移動マトリクスの作成  
			if (vx < 0) {
				vx += Brake_Z;
			}
			g_rot.y -= 0.035f;                                    //  Y軸方向に０．２ｆ分減算回転      
			D3DXMatrixRotationYawPitchRoll(&z_matrix, 0, 0, -0.3f);    //  回転マトリクスの作成
			turbo_count++;
			if (turbo_count > TURBO_COUNT)
			{
				PlaySound(SOUND_LABEL_TURBO);
				CDriftingEffect::CreateDrifting_effect(CX_model::XmodelPos().x, CX_model::XmodelPos().y, CX_model::XmodelPos().z);
			}
			break;

		case 1111:
			break;

			//左
		case 10000:
			if (roll > -0.2) {
				roll -= 0.005;
			}
			g_rot.y -= 0.025f;                                    //  Y軸方向に０．２ｆ分減算回転    
			D3DXMatrixRotationYawPitchRoll(&z_matrix, 0, 0, roll);    //  回転マトリクスの作成
			break;

			//右
		case 100000:
			if (roll < 0.2) {
				roll += 0.005;
			}
			D3DXMatrixTranslation(&s_matrix, 0, 0, vx);  //  移動マトリクスの作成 
			g_rot.y += 0.025f;                                    //  Y軸方向に０．２ｆ分加算回転 
			D3DXMatrixRotationYawPitchRoll(&z_matrix, 0, 0, roll);    //  回転マトリクスの作成
			break;
			//右下上
		case 100101:
			g_rot.y += 0.025f;                                    //  Y軸方向に０．２ｆ分加算回転 
			D3DXMatrixRotationYawPitchRoll(&z_matrix, 0, 0, 0.15f);    //  回転マトリクスの作成
			break;
			//左下上
		case 10101:
			g_rot.y -= 0.025f;                                    //  Y軸方向に０．２ｆ分減算回転    
			D3DXMatrixRotationYawPitchRoll(&z_matrix, 0, 0, -0.15f);    //  回転マトリクスの作成
			break;

			//右上
		case 100001:
			vx -= ACCEL_X;
			if (roll < 0.2) {
				roll += 0.005;
			}
			g_rot.y += 0.025f;                                    //  Y軸方向に０．２ｆ分加算回転 
			D3DXMatrixRotationYawPitchRoll(&z_matrix, 0, 0, roll);    //  回転マトリクスの作成
			CSmokeEffect::Createsmoke_explosion(CX_model::XmodelPos().x, CX_model::XmodelPos().y, CX_model::XmodelPos().z);
			break;

			//右下
		case 100100:
			if (vx < 0) {
				vx += Brake_Z;
			}
			D3DXMatrixRotationYawPitchRoll(&z_matrix, 0, 0, 0.15f);    //  回転マトリクスの作成
			g_rot.y += 0.025f;
			break;

			//左上
		case 10001:
			vx -= ACCEL_X;
			g_rot.y -= 0.025f;                                    //  Y軸方向に０．２ｆ分減算回転 
			if (roll > -0.2) {
				roll -= 0.005;
			}
			D3DXMatrixRotationYawPitchRoll(&z_matrix, 0, 0, roll);    //  回転マトリクスの作成
			CSmokeEffect::Createsmoke_explosion(CX_model::XmodelPos().x, CX_model::XmodelPos().y, CX_model::XmodelPos().z);
			break;

			//左下
		case 10100:
			if (vx < 0) {
				vx += Brake_Z;
			}
			g_rot.y -= 0.025f;                                    //  Y軸方向に０．２ｆ分減算回転      
			D3DXMatrixRotationYawPitchRoll(&z_matrix, 0, 0, -0.15f);    //  回転マトリクスの作成
			break;
		default:
			break;

		}
		//ハンドル操作
		if (!MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_STAIC4) && !GetKeyboardPress(DIK_A))
		{
			if (roll < 0) {
				roll += 0.002;
			}
		}
		if (!MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_STAIC3) && !GetKeyboardPress(DIK_D))
		{
			if (roll > 0) {
				roll -= 0.002;

			}
		}

		//移動幅制限
		if (g_pos.x > 148.0f)
		{
			g_pos.x = 148.0f;
		}

		if (g_pos.x < -148.0f)
		{
			g_pos.x = -148.0f;
		}

		if (g_pos.z < -148.0f)
		{
			g_pos.z = -148.0f;
		}

		if (g_pos.z > 148.0f)
		{
			g_pos.z = 148.0f;
		}

		coin0 = false;
		b_deboost = false;

		//敵に当たるかロケットスタート失敗したら
		if (CBillboard::HitPlayer() == true && star == false || b_startmiss == true)
		{
			b_kinoko_hit = true;
			coin0 = true;
			vx = 0.02f;
			g_Rot -= 8;
			//0°未満の場合
			if (g_Rot < -180)
			{
				g_Rot = 180;
				b_deboost = true;
				b_startmiss = false;
				b_kinoko_hit = false;
			}
		}

		//360°以上の場合
		if (g_Rot >= 360)
		{
			g_Rot = g_Rot - 360;
		}
	}

	//g_Rotの値を 0°~359°に制限する


	//ロケットスタートを初期化
	if (CModeGame::GetDash() > 0 && CModeGame::GetDash() < 5)
	{
		dashout = false;
		b_startdash = false;
		b_startmiss = false;
		vx = 0.0f;
	}
	//ロケットスタートカウント３のとき
	if (CModeGame::GetDash() > 5 && CModeGame::GetDash() < 105)
	{
		if (MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_A) || GetKeyboardPress(DIK_K))
		{
			dashout = true;

		}
	}
	//ロケットスタートカウント２のとき完璧タイミング
	if (CModeGame::GetDash() > 105 && CModeGame::GetDash() < 135 && dashout == false)
	{
		if (MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_A) || GetKeyboardPress(DIK_K))
		{
			vx -= 0.1f;
			b_startdash = true;
		}

	}
	//ロケットスタートカウント１のとき
	if (CModeGame::GetDash() > 135 && CModeGame::GetDash() < 190 && dashout == false && b_startdash == false)
	{
		if (MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_A) || GetKeyboardPress(DIK_K))
		{
			vx = -0.1f;

		}

	}
	//ロケットスタート成功
	if (CModeGame::GetDash() == 190 && b_startdash == true)
	{
		CKasokuEffect::CreateKasoku_effect(CX_model::XmodelPos().x, CX_model::XmodelPos().y + 1.0f, CX_model::XmodelPos().z);
	}
	//ロケットスタート失敗
	if (CModeGame::GetDash() == 190 && dashout == true)
	{
		CExplosion::CreateExplosion(CX_model::XmodelPos().x, CX_model::XmodelPos().y, CX_model::XmodelPos().z);
		b_startmiss = true;
	}

	b_boost = false;
	b_boost2 = false;
	//ダッシュボードに乗ったら
	if (CDash::HitPlayer() == true)
	{
		vx -= 0.01f;
		if (CBillboard::HitPlayer() == true)
		{
			vx = 0.0f;
			b_boost = true;
		}
		if (vx < -MAX_SPEEDKASOKU&&b_boost == false) { vx = -MAX_SPEEDKASOKU; b_boost = true; }

	}
	else if (CDashSide::HitPlayer() == true)
	{
		vx -= 0.01f;
		if (CBillboard::HitPlayer() == true)
		{
			vx = 0.0f;
			b_boost2 = true;
		}
		if (vx < -MAX_SPEEDKASOKU&&b_boost2 == false) { vx = -MAX_SPEEDKASOKU; b_boost2 = true; }

	}
	else if (vx < -max_speed - star_speed)
	{
		vx = -max_speed - star_speed;

	}

	//ターボ　車体傾き
	if (!MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_RIGHT_SHOULDER) && !GetKeyboardPress(DIK_J))
	{
		if (roll < 0)
		{
			roll += 0.002;
		}
		else
			if (roll > 0)
			{
				roll -= 0.002;
			}


		if (turbo_count > TURBO_COUNT)
		{
			vx -= 0.2f;
			turbo_speed_count++;
			if (turbo_speed_count > 40 || CBillboard::HitPlayer() == true || g_pos.y > 6.0f)
			{
				turbo_speed_count = 0;
				turbo_count = 0;
			}
		}
		else
		{
			turbo_speed_count = 0;
			turbo_count = 0;
		}
	}

	//アイテムキノコ使用
	if (MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_LEFT_SHOULDER) && (CModeGame::Getkinoko_X() == true) && b_kinoko_hit == false && pos_y == false || GetKeyboardTrigger(DIK_L) && (CModeGame::Getkinoko_X() == true) && b_kinoko_hit == false && pos_y == false)
	{
		CKasokuEffect::CreateKasoku_effect(CX_model::XmodelPos().x, CX_model::XmodelPos().y + 1.0f, CX_model::XmodelPos().z);
		kino = true;
	}
	if (kinoko_time >= 100)
	{
		kinoko_time = 0;
		kino = false;
	}

	if (kino == true && g_pos.y < 7.5f)
	{
		if (g_pos.y < 6.0f)
		{
			vx -= 0.2f;
		}
		kinoko_time++;
		if (CBillboard::HitPlayer() == true) {
			kino = false;
			kinoko_time = 0;
		}
	}

	star_speed = 0.0f;

	//アイテムスター使用
	if (MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_LEFT_SHOULDER) && (CModeGame::Getstar_X() == true) && b_kinoko_hit == false && pos_y == false || GetKeyboardTrigger(DIK_L) && (CModeGame::Getstar_X() == true) && b_kinoko_hit == false && pos_y == false)
	{
		star = true;
	}

	if (star_time >= 420)
	{
		StopSound(SOUND_LABEL_STAR);
		star_time = 0;
		star = false;
		star_speed = 0.0f;
	}

	if (star == true)
	{
		CStarEffect::CreateStar_effect(CX_model::XmodelPos().x, CX_model::XmodelPos().y, CX_model::XmodelPos().z);
		if (g_pos.y < 6.0f)
		{
			star_speed = 0.1f;
		}
		else
		{
			star_speed = 0.0f;
		}
		star_time++;
	}
	kino_count = false;

	//トリプルキノコ使用
	bool isUsedTripleKinoko = (MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_LEFT_SHOULDER) && (CModeGame::Getkinoko3_X() == true) && b_kinoko_hit == false && pos_y == false || MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_LEFT_SHOULDER) && (CModeGame::Getkinoko2_X() == true) && b_kinoko_hit == false && pos_y == false || MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_LEFT_SHOULDER) && (CModeGame::Getkinoko1_X() == true) && b_kinoko_hit == false && pos_y == false || GetKeyboardTrigger(DIK_L) && (CModeGame::Getkinoko3_X() == true) && b_kinoko_hit == false && pos_y == false || GetKeyboardTrigger(DIK_L) && (CModeGame::Getkinoko2_X() == true) && b_kinoko_hit == false && pos_y == false || GetKeyboardTrigger(DIK_L) && (CModeGame::Getkinoko1_X() == true) && b_kinoko_hit == false && pos_y == false);
	if (isUsedTripleKinoko)
	{
		CKasokuEffect::CreateKasoku_effect(CX_model::XmodelPos().x, CX_model::XmodelPos().y + 1.0f, CX_model::XmodelPos().z);
		kino3 = true;
	}
	if (kinoko_time3 >= 100)
	{
		kino_count = true;
		kino3 = false;
		kinoko_time3 = 0;

	}

	if (kino3 == true)
	{
		vx -= 0.2f;
		kinoko_time3++;
		if (CBillboard::HitPlayer() == true) {
			kino3 = false;
			kinoko_time3 = 0;
		}
	}


	//パワフルダッシュキノコ使用
	if (CModeGame::Get_Pw_kinoko_X())
	{
		pw_dash_time++;
	}
	else
	{
		pw_dash_derete = false;
	}

	if (pw_dash_time > 480)
	{
		pw_dash_derete = true;
		pw_dash_time = 0;
	}
	else if (pw_dash_time > 1)
	{
		if (MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_LEFT_SHOULDER) && b_kinoko_hit == false && pos_y == false || GetKeyboardTrigger(DIK_L) && b_kinoko_hit == false && pos_y == false)
		{
			PlaySound(SOUND_LABEL_WAHAAKINO);
			CKasokuEffect::CreateKasoku_effect(CX_model::XmodelPos().x, CX_model::XmodelPos().y + 1.0f, CX_model::XmodelPos().z);
			kino = true;
		}
		if (kinoko_time >= 100)
		{
			kinoko_time = 0;
			kino = false;
		}

		if (kino == true && g_pos.y < 7.5f)
		{
			if (g_pos.y < 6.0f)
			{
				vx -= 0.2f;
			}
			kinoko_time++;
			if (CBillboard::HitPlayer() == true) {
				kino = false;
				kinoko_time = 0;
			}
		}
	}


	//ジャンプ
	if (MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_RIGHT_SHOULDER)  && CJump::HitPlayer() || MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_RIGHT_SHOULDER) && CJump_Reverse::HitPlayer() || GetKeyboardTrigger(DIK_J) && CJump::HitPlayer() || GetKeyboardTrigger(DIK_J) && CJump_Reverse::HitPlayer())
	{
		PlaySound(SOUND_LABEL_WAHAA);
		if (bJump == false)
		{
			if (OnField)
			{
				bJump = true;
				bUp = true;
				OnField = false;
				bJumpAll = true;
				jump_roll = 0.0f;
			
			}
		}
	}

	if (bJump)
	{
		if (jump_roll < 6) {
			jump_roll += 0.2;
			
		}
		D3DXMatrixRotationYawPitchRoll(&z_matrix, 0, jump_roll, 0);    //  回転マトリクスの作成
		if (bUp)
		{
			fJump += VALUE_GRAVITY * 2;
			g_pos.y += VALUE_GRAVITY * 2;

		}
		if (jump_roll == 1)
		{
			CJumpEffect::CreateJump_Effect(CX_model::XmodelPos().x, CX_model::XmodelPos().y , CX_model::XmodelPos().z);
		}
		
	}

	if (fJump > 3.2f || GetKeyboardRelease(DIK_J) && CJump::HitPlayer()  || GetKeyboardRelease(DIK_J) && CJump_Reverse::HitPlayer()  || MyInputGamepad::GetButtonRelease(MYGAMEPAD_BUTTON_RIGHT_SHOULDER) && CJump::HitPlayer() || MyInputGamepad::GetButtonRelease(MYGAMEPAD_BUTTON_RIGHT_SHOULDER) && CJump_Reverse::HitPlayer())
	{
		bUp = false;
		fJump = 0.0f;
	}

	if (g_pos.y <= 1.0f)
	{
		bJump = false;
		OnField = true;
		fJump = 0.0f;
		g_pos.y = 1.0f;
		bJumpAll = false;
	}


	//落下判定
	if (bUp == false && OnField == false)
	{

		vx -= 0.5f;
		g_pos.y -= VALUE_GRAVITY;
	}

	if (bJumpAll == false) {
		//プレイヤーの高さ
		CField *field;
		field = CModeGame::GetField();
		g_pos.y = field->GetHeight(g_pos);
	}

	if (!kino && !star && !kino3)
	{
		if (vx < -MAX_GARD && g_pos.y > 1)
		{
			vx = -MAX_GARD;
			turbo_speed_count = 0;
			turbo_count = 0;
		}
	}

	//高さ制限
	if (pos_y == false)
	{
		if (g_pos.y > 7.0f)
		{
			vx = +0.04f;
		}
	}
	if (g_pos.y > 7.5f)
	{
		pos_y = true;
	}



	if (pos_y == true)
	{
		vx = -0.03f;
	}

	if (g_pos.y > 8.0f)
	{
		vx = +0.5f;
	}

	if (g_pos.y <= 6.9)
	{
		pos_y = false;
	}

	if (g_pos.y < 0.9f)
	{
		CStEffect::CreateStart_effect(CX_model::XmodelPos().x, CX_model::XmodelPos().y, CX_model::XmodelPos().z);
	}

	//ドリフト音
	if (MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_STAIC4) && MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_RIGHT_SHOULDER) || GetKeyboardPress(DIK_A) && GetKeyboardTrigger(DIK_J))
	{
		PlaySound(SOUND_LABEL_DRIFT);
	}

	if (MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_STAIC3) && MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_RIGHT_SHOULDER) || GetKeyboardPress(DIK_D) && GetKeyboardTrigger(DIK_J))
	{
		PlaySound(SOUND_LABEL_DRIFT);
	}

	if (MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_STAIC4) && MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_RIGHT_SHOULDER) || GetKeyboardPress(DIK_D) && GetKeyboardTrigger(DIK_J))
	{
		PlaySound(SOUND_LABEL_DRIFT);
	}

	if (MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_STAIC3) && MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_RIGHT_SHOULDER) || GetKeyboardPress(DIK_D) && GetKeyboardTrigger(DIK_J))
	{
		PlaySound(SOUND_LABEL_DRIFT);
	}

	if (MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_STAIC4) && MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_RIGHT_SHOULDER) || GetKeyboardPress(DIK_D) && GetKeyboardTrigger(DIK_J))
	{
		PlaySound(SOUND_LABEL_DRIFT);
	}

	if (MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_STAIC3) && MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_RIGHT_SHOULDER) || GetKeyboardPress(DIK_D) && GetKeyboardTrigger(DIK_J))
	{
		PlaySound(SOUND_LABEL_DRIFT);
	}

	if ( MyInputGamepad::GetButtonRelease(MYGAMEPAD_BUTTON_RIGHT_SHOULDER) || GetKeyboardRelease(DIK_J) || (MyInputGamepad::GetButtonRelease(MYGAMEPAD_BUTTON_STAIC3)) || (MyInputGamepad::GetButtonRelease(MYGAMEPAD_BUTTON_STAIC4)))
	{
		StopSound(SOUND_LABEL_DRIFT);
	}

	//コイン数で最高スピードを変える
	if (CCoin::ScoreCoin() == 1) {
		max_speed = 0.55f;
	}
	if (CCoin::ScoreCoin() == 2) {
		max_speed = 0.58f;
	}
	if (CCoin::ScoreCoin() == 3) {
		max_speed = 0.61f;
	}
	if (CCoin::ScoreCoin() == 4) {
		max_speed = 0.64f;
	}
	if (CCoin::ScoreCoin() == 5) {
		max_speed = 0.67f;
	}
	if (CCoin::ScoreCoin() == 6) {
		max_speed = 0.70f;
	}
	if (CCoin::ScoreCoin() == 7) {
		max_speed = 0.73f;
	}
	if (CCoin::ScoreCoin() == 8) {
		max_speed = 0.76f;
	}
	if (CCoin::ScoreCoin() == 9) {
		max_speed = 0.79f;
	}
	if (CCoin::ScoreCoin() == 10) {
		max_speed = 0.81f;
	}
	if (CCoin::ScoreCoin() == 11) {
		max_speed = 0.82f;
	}
	if (CCoin::ScoreCoin() == 12) {
		max_speed = 0.83f;
	}
	if (CCoin::ScoreCoin() == 13) {
		max_speed = 0.84f;
	}
	if (CCoin::ScoreCoin() == 14) {
		max_speed = 0.85f;
	}
	if (CCoin::ScoreCoin() == 15) {
		max_speed = 0.86f;
	}
	if (CCoin::ScoreCoin() == 16) {
		max_speed = 0.87f;
	}
	if (CCoin::ScoreCoin() == 17) {
		max_speed = 0.88f;
	}
	if (CCoin::ScoreCoin() == 18) {
		max_speed = 0.89f;
	}
	if (CCoin::ScoreCoin() == 19) {
		max_speed = 0.90f;
	}
	if (CCoin::ScoreCoin() == 20) {
		max_speed = 0.905f;
	}
	if (CCoin::ScoreCoin() == 21) {
		max_speed = 0.91f;
	}
	if (CCoin::ScoreCoin() == 22) {
		max_speed = 0.915f;
	}
	if (CCoin::ScoreCoin() == 23) {
		max_speed = 0.92f;
	}
	if (CCoin::ScoreCoin() == 24) {
		max_speed = 0.925f;
	}
	if (CCoin::ScoreCoin() == 25) {
		max_speed = 0.93f;
	}
	if (CCoin::ScoreCoin() == 26) {
		max_speed = 0.935f;
	}
	if (CCoin::ScoreCoin() == 27) {
		max_speed = 0.94f;
	}
	if (CCoin::ScoreCoin() == 28) {
		max_speed = 0.945f;
	}
	if (CCoin::ScoreCoin() == 29) {
		max_speed = 0.95f;
	}
	if (CCoin::ScoreCoin() == 30) {
		max_speed = 0.96f;
	}


	D3DXMatrixTranslation(&q_matrix, g_pos.x, g_pos.y, g_pos.z);              //  移動マトリクスの作成   
	g_World = q_matrix * g_World;
	D3DXMatrixRotationYawPitchRoll(&t_matrix, g_rot.y, g_rot.x, g_rot.z);    //  回転マトリクスの作成
	D3DXMatrixRotationY(&r_matrix, D3DXToRadian(-g_Rot));
	g_World = r_matrix * g_World;

	g_World = s_matrix * t_matrix  * g_World;
	g_World = z_matrix * g_World;
	D3DXMatrixScaling(&t_matrix, 0.3f, 0.3f, 0.3f);

	g_World = t_matrix * g_World;

	g_pos.x = g_World._41;

	g_pos.y = g_World._42;

	g_pos.z = g_World._43;
	
	//ゲーム処理初期化
	if (CModeGame::GetUse() == false)
	{
		coin0 = false;
		g_pos = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_Dir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		g_rot = D3DXVECTOR3(0, 0, 0);     //  回転
		g_Rot = 180.0f;
		b_deboost = false;
		b_boost = false;
		b_boost2 = false;
		max_speed = 0.5f;
		g_modelbUse = false;
	}
	else {
		g_modelbUse = true;
	}
}


void CX_model::Draw()
{
	//デバイスの取得
	//pDevice = CRender::GetD3DDevice();	//デバイスの取得

	if (pDevice == NULL) { return; }
	if (g_pMesh == NULL) { return; }
	
		//ワールド行列の設定(好きなタイミングで呼ぶ)
		pDevice->SetTransform(D3DTS_WORLD, &g_World);

		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);	//ライトを有効
		//pDevice -> SetRenderState( D3DRS_AMBIENT, D3DXCOLOR(0.3f, 0.3f,0.3f,1.0f));	//環境光を設定

		for (int i = 0; i < 3; i++)
		{

			pDevice->SetMaterial(&g_pMeshMaterials[i]);	// マテリアル情報をセット

			pDevice->SetTexture(0, pMeshTex[i]);	//	pDevice->SetTexture( 0, pMeshTex[i] );	// テクスチャ情報をセット

			g_pMesh->DrawSubset(i);				// メッシュを描画

		}

}


//キャラの位置
D3DXVECTOR3 CX_model::XmodelPos()
{
	return g_pos;
}


//キャラの向き
float CX_model::XmodelRot()
{
	float g_R = g_Rot +270.0f;

	return g_R;
}

bool CX_model::pw_dash_dele()
{
	return pw_dash_derete;
}

bool CX_model::modelUse() {
	return g_modelbUse;
}

bool CX_model::deboost() {
	return b_deboost;
}

bool CX_model::boost() {
	return b_boost;
}

bool CX_model::Getkinoko_count() {
	return kino_count;
}

bool CX_model::boost2() {
	return b_boost2;
}

bool CX_model::coin00() {
	return coin0;
}

bool CX_model::kinohit() {
	return b_kinoko_hit;
}

bool CX_model::star_muteki() {
	return star;
}

void CX_model::Release()
{
	Uninit();
	delete this;		//自分自身のポインタ
}

D3DXVECTOR3 CX_model::GetFront()
{
	D3DXVECTOR3 front;
	front.x = m_WorldMatirix._31;
	front.y = m_WorldMatirix._32;
	front.z = m_WorldMatirix._33;
	return front; //           Z軸方向
}
