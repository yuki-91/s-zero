//-----------------------------------//
//--�v���C���[����---------[player.h]//
//-----------------------------------//
//------Author:�{ �C�G-------------//
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
	static void Uninit();	//�I������
	static void Update();	//�X�V����
	static void Draw();		//�`�揈��
	static void Input_Button();//���͏���
	static void RocketStart();//���P�b�g�X�^�[�g����
	static void Speed_Limit();//�ő��X�s�[�h����
	static void Drift_Turbo();//�h���t�g�^�[�{����
	static void Item_Kinoko();//�A�C�e���L�m�R����
	static void Item_TripleKinoko();//�A�C�e���g���v���L�m�R����
	static void Item_Star();//�A�C�e���X�^�[����
	static void Item_PWKinoko();//�A�C�e���p���t���L�m�R����
	static void Item_Coin();//�R�C������
	static void Jump_Action();//�W�����v�A�N�V��������
	static void Move_Limit();//�ړ�����������
	static void Drift_BGM();//BGM����
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
	static D3DXMATRIX g_Pos;		//�ʒu�̍s��
	static D3DXVECTOR3 g_Transmodel;		//�ړ�
	static D3DXVECTOR3 g_Dir;		//����
	static D3DXMATRIX g_Rotation, g_mtxScale;	//��] �g��
	static D3DXMATRIX g_Shadow;		//�e�̃��[���h�s��
	static LPDIRECT3DTEXTURE9 m_pTextures;
	static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer ;		// �o�[�e�b�N�X�o�b�t�@�̃|�C���^
	static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer ;		// �C���f�b�N�X�o�b�t�@�̃|�C���^
	static D3DXMATRIX m_WorldMatirix;
	static LPDIRECT3DDEVICE9 pDevice;
	static D3DXMATRIX t_matrix, s_matrix, r_matrix, q_matrix, z_matrix;
	static D3DXVECTOR3     g_rot;     //  ��]   
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

	//�p���t���L�m�R
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

	static bool bJump;	// �W�����v�����ǂ���
	static bool bUp;	//�㏸�E���~����
	static bool OnField;//�n�ʂɂ��Ă��邩
	static bool bJumpAll;//�v���C���[��n�ʂ̍����ɂ��邩
	static bool pos_y;//��������
	static bool bUp_d;	//�㏸�E���~����h���t�g
	static float fJump;	//�W�����v��

	//�^�[�{
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

	////���y
	static bool engin_sound;
};
#endif //_XMODEL_H_