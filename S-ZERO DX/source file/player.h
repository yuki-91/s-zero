//-----------------------------------//
//--プレイヤー処理---------[player.h]//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#ifndef _XMODEL_2H_
#define _XMODEL_2H_
#include "scene.h"
#include "main.h"


enum TEXTURE_3D_ENUM
{
	TEXTURE_3D_NULL = -1,
	TEXTURE_3D_BIKE,
	TEXTURE_3D_BIKE2,
	TEXTURE_3D_SHADOW,
	TEXTURE_3D_MAX
};


class CX_model 
{
public:
	static CX_model *Create();
	CX_model();
	~CX_model();
	bool InitXmodel(void);	//HINSTANCE hInstance, HWND hWnd, BOOL bWindow
	static void Uninit();	//終了処理
	static void Update();	//更新処理
	static void Draw();		//描画処理
	static void Input_Button();//入力処理
	static void RocketStart();//ロケットスタート処理
	static void Speed_Limit();//最速スピード処理
	static void Drift_Turbo();//ドリフトターボ処理
	static void Item_Kinoko();//アイテムキノコ処理
	static void Item_TripleKinoko();//アイテムトリプルキノコ処理
	static void Item_Star();//アイテムスター処理
	static void Item_PWKinoko();//アイテムパワフルキノコ処理
	static void Item_Coin();//コイン処理
	static void Jump_Action();//ジャンプアクション処理
	static void Move_Limit();//移動幅制限処理
	static void Drift_BGM();//BGM処理
	void Release();
	static D3DXVECTOR3 XmodelPos();
	static D3DXVECTOR3 XmodelRot();
	static bool modelUse();
	static bool CX_model::deboost();
	static bool CX_model::boost();
	static bool CX_model::boost2();
	static bool CX_model::coin00();
	static bool CX_model::Getkinoko_count();
	static D3DXVECTOR3 CX_model::GetFront();
	static bool CX_model::kinohit();
	static bool CX_model::star_muteki();
	static bool CX_model::pw_dash_dele();
	static bool CX_model::Get_b_use_pw();
	static bool CX_model::Get_posy();
private:

	static D3DXMATRIX g_World;
	static D3DXMATRIX g_Pos;		//位置の行列
	static D3DXVECTOR3 g_Transmodel;		//移動
	static D3DXVECTOR3 g_Dir;		//向き
	static D3DXMATRIX g_Rotation, g_mtxScale;	//回転 拡大
	static D3DXMATRIX g_Shadow;		//影のワールド行列
	static LPDIRECT3DTEXTURE9 m_pTextures;
	static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer ;		// バーテックスバッファのポインタ
	static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer ;		// インデックスバッファのポインタ
	static D3DXMATRIX m_WorldMatirix;
	static LPDIRECT3DDEVICE9 pDevice;
	static D3DXMATRIX t_matrix, s_matrix, r_matrix, q_matrix, z_matrix;
	static D3DXVECTOR3     g_rot;     //  回転   
	static D3DXVECTOR3     g_pos;
	static float  g_Rot;
	static bool g_modelbUse;
	static double vx ;
	static bool b_deboost ;
	static bool b_boost ;
	static bool b_boost2;
	static bool coin0 ;
	static float max_speed ;
	static float star_speed;
	static bool dashout ;

	//パワフルキノコ
	static int pw_dash_time;
	static bool pw_dash_derete;
	static bool b_use_pw;

	static int kinoko_time;
	static int kinoko_time2;
	static int kinoko_time3;
	static int star_time;
	static bool kino;
	static bool kino2;
	static bool kino3;
	static bool kino_count;
	static bool star;
	static bool b_startdash;
	static bool b_startmiss;
	static bool b_kinoko_hit;

	static bool bJump;	// ジャンプ中かどうか
	static bool bUp;	//上昇・下降判定
	static bool OnField;//地面についているか
	static bool bJumpAll;//プレイヤーを地面の高さにするか
	static bool pos_y;//高さ制限
	static bool bUp_d;	//上昇・下降判定ドリフト
	static float fJump;	//ジャンプ量

	//ターボ
	static int turbo_count_left;
	static int turbo_speed_count_left;
	static int turbo_count_right;
	static int turbo_speed_count_right;

	static float handle_left;
	static float handle_right;

	static float handle_left_drift;
	static float handle_right_drift;

	static float force_left;
	static float force_right;

	static bool drift_state_left;
	static bool drift_state_right;

	////音楽
	static bool engin_sound;
};
#endif //_XMODEL_H_