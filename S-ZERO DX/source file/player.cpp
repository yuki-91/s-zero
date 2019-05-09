//-----------------------------------//
//--�v���C���[����-------[player.cpp]//
//-----------------------------------//
//------Author:�{ �C�G-------------//
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
#include "drifting_effect_mini.h"
#include "mode_title.h"

// ���_����(1�ځF���W�A2�ځF�J���[,3�ځF�e�N�X�`���[)
#define FVF_VERTEX_PLAYER (D3DFVF_XYZ|D3DFVF_DIFFUSE | D3DFVF_TEX1 )

#define ACCEL_X 0.005f		//�A�N�Z��
#define Brake_X 0.003f		//�u���[�L
#define MAX_SPEEDKASOKU 1.0f//�}�b�N�X�����X�s�[�h
#define MAX_GARD 0.3f		//�ᑬ�X�s�[�h

#define TURBO_COUNT 30		//�^�[�{�J�E���g
#define TURBO_UP 60			//�^�[�{��������
#define TURBO_SPEED 0.1f		//�^�[�{���x

#define TURBO_MINI_COUNT 10//�~�j�^�[�{�J�E���g
#define TURBO_UP_MINI 30	//�~�j�^�[�{��������
#define TURBO_SPEED_MINI 0.05f//�~�j�^�[�{���x


#define FILE_X "data/3D/harleyplay5.x"	//�v���C���[���f��
#define VALUE_GRAVITY (0.10f)			// �d�͗�
#define VALUE_GRAVITY_DRIFT (0.10f)		//�h���t�g�W�����v�d�� 
#define HANDLE_SPEED 0.001f				//�n���h���J�E���g
#define DRIFT_ANGLE 0.0005f				//�h���t�g�ړ��p�x
#define HANDLE_DRIFT_MAX 0.03f			//�h���t�g�ړ��p�x�}�b�N�X
#define DRIFT_FORCE 0.02f				//�h���t�g���S��
#define DRIFT_FORCE_MAX 0.15f			//�h���t�g���S�̓}�b�N�X
#define PLAYER_DRIFT_ROT 0.4f			//�h���t�g�v���C���[�p�x


LPD3DXMESH g_pMesh = NULL;		//���b�V���f�[�^
DWORD g_nMaterialNum = 0;		//�}�e���A���̐�
LPD3DXBUFFER g_pMaterialsBuffer = NULL;		//�}�e���A���̃o�b�t�@�[
LPD3DXBUFFER g_pMaterials = NULL;
D3DMATERIAL9*	g_pMeshMaterials = NULL;	// �}�e���A�����
LPDIRECT3DTEXTURE9 pMeshTex[TEXTURE_3D_MAX] = { NULL };	// ���b�V���̃e�N�X�`��

D3DXMATRIX CX_model::g_World;
D3DXMATRIX CX_model::g_Pos;		//�ʒu�̍s��
D3DXVECTOR3 CX_model::g_Transmodel;		//�ړ�
D3DXVECTOR3 CX_model::g_Dir;		//����
D3DXMATRIX CX_model::g_Rotation, CX_model::g_mtxScale;	//��] �g��
D3DXMATRIX CX_model::g_Shadow;		//�e�̃��[���h�s��
LPDIRECT3DTEXTURE9 CX_model::m_pTextures;

LPDIRECT3DVERTEXBUFFER9 CX_model::g_pVertexBuffer = NULL;		// �o�[�e�b�N�X�o�b�t�@�̃|�C���^
LPDIRECT3DINDEXBUFFER9 CX_model::g_pIndexBuffer = NULL;		// �C���f�b�N�X�o�b�t�@�̃|�C���^

D3DXMATRIX CX_model::m_WorldMatirix;
LPDIRECT3DDEVICE9 CX_model::pDevice;
D3DXMATRIX CX_model::t_matrix, CX_model::s_matrix, CX_model::r_matrix, CX_model::q_matrix, CX_model::z_matrix;
D3DXVECTOR3     CX_model::g_rot = D3DXVECTOR3(0, 0, 0);     //  ��]   
D3DXVECTOR3     CX_model::g_pos = D3DXVECTOR3(0, 0, 20);	//�ʒu

float  CX_model::g_Rot = 180.0f;
float CX_model::max_speed = 0.6f;	//�R�C���l�����}�b�N�X�X�s�[�h
float CX_model::star_speed = 0.0f;	//�X�^�[�g�p���}�b�N�X�X�s�[�h

double CX_model::vx = 0.0f;		//�ړ���

bool CX_model::g_modelbUse = false;//�Q�[���X�^�[�g������

//�u�[�X�g
bool CX_model::b_deboost = false;//��]���Ă��邩�ǂ���
bool CX_model::b_boost = false;//���������Ƃ��G�ɓ���������
bool CX_model::b_boost2 = false;//�����������G�ɓ����������Q

//�A�C�e������
bool CX_model::coin0 = false;	//�R�C��
bool CX_model::kino = false;	//�L�m�R
bool CX_model::kino2 = false;	//�_�u���L�m�R
bool CX_model::kino3 = false;	//�g���v���L�m�R
bool CX_model::kino_count = false;//�L�m�R�J�E���g
bool CX_model::star = false;	//�X�^�[
bool CX_model::b_kinoko_hit = false;//�L�m�R�g�p����
//
//�p���t���L�m�R
int  CX_model::pw_dash_time = 0;	//�p���t���L�m�R��������
bool CX_model::pw_dash_derete = false;
bool CX_model::b_use_pw = false;

int CX_model::kinoko_time = 0;  //�L�m�R��������
int CX_model::kinoko_time2 = 0; //�_�u���L�m�R��������
int CX_model::kinoko_time3 = 0; //�g���v���L�m�R��������
int CX_model::star_time = 0;	//�X�^�[��������

////�X�^�[�g�_�b�V��
bool CX_model::dashout = false;		//���P�b�g�X�^�[�g
bool CX_model::b_startdash = false;	//���P�b�g�X�^�[�g����
bool CX_model::b_startmiss = false;	//���P�b�g�X�^�[�g���s
//
//�W�����v
bool CX_model::bJump = false;	// �W�����v�����ǂ���
bool CX_model::bUp = false;	//�㏸�E���~����
bool CX_model::OnField = false;//�n�ʂɂ��Ă��邩
bool CX_model::bJumpAll = false;//�v���C���[��n�ʂ̍����ɂ��邩
bool CX_model::pos_y = false;//��������
bool CX_model::bUp_d = false;	//�㏸�E���~����h���t�g
float CX_model::fJump = 0.0f;	//�W�����v��

//�^�[�{
int  CX_model::turbo_count_left = 0;		//���^�[�{����l
int  CX_model::turbo_speed_count_left = 0;	//���~�j�^�[�{����l
int  CX_model::turbo_count_right = 0;		//�E�^�[�{����l
int  CX_model::turbo_speed_count_right = 0; //�E�^�[�{����l

float  CX_model::handle_left = 0.0f;	//���v���C���[��]�p�x
float  CX_model::handle_right = 0.0f;	//�E�v���C���[��]�p�x
	   
float  CX_model::handle_left_drift = 0.0f;//���v���C���[��]�p�x����l
float  CX_model::handle_right_drift = 0.0f;//�E�v���C���[��]�p�x�����l
	   
float  CX_model::force_left = 0.0;		//�����S��
float  CX_model::force_right = 0.0;		//�E���S��

bool  CX_model::drift_state_left = false;//���h���t�g�g�p����
bool  CX_model::drift_state_right = false;//�E�h���t�g�g�p����

//���y
bool  CX_model::engin_sound = false;

//�m�b�g�X�^�e�B�b�N
float roll = 0.0f;
float jump_roll = 0.0f;


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
	pDevice = CRender::GetD3DDevice();	//�f�o�C�X�̎擾
	coin0 = false;
	vx = 0.0f;
	g_pos = D3DXVECTOR3(0.0f, 1.2f, 0.0f);
	g_Dir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	g_rot = D3DXVECTOR3(0, 0, 0);     //  ��]
	g_Rot = 180.0f;
	b_deboost = false;
	b_boost = false;
	b_boost2 = false;
	max_speed = 0.6f;
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
	pw_dash_time = 0;
	pw_dash_derete = false;
	roll = 0.0f;
	jump_roll = 0.0f;
	b_use_pw = false;
	handle_left = 0.0f;
	handle_right = 0.0f;
	handle_left_drift = 0.0f;
	handle_right_drift = 0.0f;
	drift_state_left = false;
	drift_state_right = false;
	bJump = false;

	bUp = false;	//�㏸�E���~����

	force_left = 0;
	force_right = 0;

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
		MessageBox(NULL, "�ǂݍ��߂܂���3", "�G���[", MB_OK);
		return FALSE;
	}

	LPD3DXBUFFER pAdjacency = NULL;

	//x�t�@�C���ǂݍ���
	hr = D3DXLoadMeshFromX(
		FILE_X,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		&pAdjacency,			//�אڏ��
		&g_pMaterialsBuffer,			//
		NULL,
		&g_nMaterialNum,		//�}�e���A���͂������邩
		&g_pMesh);

	if (FAILED(hr))
	{
		MessageBox(NULL, "���s���܂���0", "�ǂݍ��߂܂���ł���0", MB_OK);
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

	//���������Ă���
	g_pMesh = pCloneMesh;

	D3DXMATERIAL* pMaterials = (D3DXMATERIAL*)g_pMaterialsBuffer->GetBufferPointer();

	g_pMeshMaterials = new D3DMATERIAL9[g_nMaterialNum];		// ���b�V�������m��

	for (DWORD i = 0; i < g_nMaterialNum; i++)
	{
		//�}�e���A�������Z�b�g
		g_pMeshMaterials[i] = pMaterials[i].MatD3D;

		 //�g�p���Ă���e�N�X�`��������Γǂݍ���
		if (pMaterials[i].pTextureFilename != NULL && lstrlen(pMaterials[i].pTextureFilename) > 0)
		{
			// �e�N�X�`���ǂݍ���
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


	//�^�C�g����ʂ̃v���C���[��]
	if (CModeTitle::Get_opening_rot())
	{
		g_pos = D3DXVECTOR3(0.0f, 1.2f, 0.0f);
	}

	
	CX_model::Input_Button();

	CX_model::RocketStart();
	CX_model::Speed_Limit();
	CX_model::Drift_Turbo();

	//�A�C�e��
	CX_model::Item_Kinoko();
	CX_model::Item_TripleKinoko();
	CX_model::Item_Star();
	CX_model::Item_PWKinoko();
	CX_model::Item_Coin();

	CX_model::Jump_Action();
	
	CX_model::Move_Limit();

	CX_model::Drift_BGM();


	D3DXMatrixTranslation(&q_matrix, g_pos.x, g_pos.y, g_pos.z);              //  �ړ��}�g���N�X�̍쐬   
	g_World = q_matrix * g_World;
	D3DXMatrixRotationYawPitchRoll(&t_matrix, g_rot.y, g_rot.x, g_rot.z);    //  ��]�}�g���N�X�̍쐬
	D3DXMatrixRotationY(&r_matrix, D3DXToRadian(-g_Rot));
	g_World = r_matrix * g_World;

	g_World = s_matrix * t_matrix  * g_World;
	g_World = z_matrix * g_World;
	D3DXMatrixScaling(&t_matrix, 0.3f, 0.3f, 0.3f);

	g_World = t_matrix * g_World;

	g_pos.x = g_World._41;

	g_pos.y = g_World._42;

	g_pos.z = g_World._43;
	
	//�Q�[������������
	if (CModeGame::GetUse() == false)
	{
		coin0 = false;
		bJump = false;
		g_pos = D3DXVECTOR3(0.0f, 1.2f, 0.0f);
		g_Dir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		g_rot = D3DXVECTOR3(0, 0, 0);     //  ��]
		g_Rot = 180.0f;
		b_deboost = false;
		b_boost = false;
		b_boost2 = false;
		max_speed = 0.6f;
		g_modelbUse = false;

	}
	else {
		g_modelbUse = true;
	}
}


void CX_model::Draw()
{
	//�f�o�C�X�̎擾
	//pDevice = CRender::GetD3DDevice();	//�f�o�C�X�̎擾

	if (pDevice == NULL) { return; }
	if (g_pMesh == NULL) { return; }
	
		//���[���h�s��̐ݒ�(�D���ȃ^�C�~���O�ŌĂ�)
		pDevice->SetTransform(D3DTS_WORLD, &g_World);

		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);	//���C�g��L��
		//pDevice -> SetRenderState( D3DRS_AMBIENT, D3DXCOLOR(0.3f, 0.3f,0.3f,1.0f));	//������ݒ�

		for (int i = 0; i < 3; i++)
		{

			pDevice->SetMaterial(&g_pMeshMaterials[i]);	// �}�e���A�������Z�b�g

			pDevice->SetTexture(0, pMeshTex[i]);	//	pDevice->SetTexture( 0, pMeshTex[i] );	// �e�N�X�`�������Z�b�g

			g_pMesh->DrawSubset(i);				// ���b�V����`��

		}

}

void CX_model::Input_Button()
{
	engin_sound = false;

	if (g_modelbUse) {

		//�n���h���ړ�����
		if (!MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_STAIC4) && !GetKeyboardPress(DIK_A))
		{
			if (handle_left < 0) {
				handle_left = 0.0f;
			}
		}
		if (!MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_STAIC3) && !GetKeyboardPress(DIK_D))
		{
			if (handle_right > 0) {
				handle_right = 0.0f;
			}
		}

		if (!MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_RIGHT_SHOULDER) && !GetKeyboardPress(DIK_J))
		{
			if (handle_left_drift < 0) {
				handle_left_drift = 0.0f;
			}
			if (handle_right_drift > 0) {
				handle_right_drift = 0.0f;
			}
		}

		if (!MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_RIGHT_SHOULDER) && !GetKeyboardPress(DIK_J))
		{
			force_left = 0;
			force_right = 0;
			drift_state_left = false;
			drift_state_right = false;
		}

		if (drift_state_left && drift_state_right)
		{
			drift_state_left = false;
			drift_state_right = false;
		}


		float t = 2.0f * 3.141592653589793f * (g_Rot + 270.0f) / 360.0f;

		g_Dir = D3DXVECTOR3((float)cos(t), 0.0f, (float)sin(t));

		D3DXVec3Normalize(&g_Dir, &g_Dir);

		//�L�[�̃x�N�g��
		D3DXVECTOR3 KeyVec;

		//�L�[�̎擾����
		int KeyNumber = 0;

		if (MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_A) || GetKeyboardPress(DIK_K)) { KeyNumber += 1; }
		else {
			if (vx < 0) vx += Brake_X;
			else if (vx > 0) vx -= Brake_X;
		}
		if (Camera::Get_back_millor() == false) {

			if (MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_STAIC4) && MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_RIGHT_SHOULDER) || GetKeyboardPress(DIK_A) && !GetKeyboardPress(DIK_D) && GetKeyboardPress(DIK_J)) KeyNumber += 10;

			//if (MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_B) || GetKeyboardPress(DIK_S)) KeyNumber += 100;

			if (MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_STAIC3) && MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_RIGHT_SHOULDER) || GetKeyboardPress(DIK_D) && !GetKeyboardPress(DIK_A) &&GetKeyboardPress(DIK_J)) KeyNumber += 1000;

			if (MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_STAIC4) || GetKeyboardPress(DIK_A) && !GetKeyboardPress(DIK_D)) KeyNumber += 10000;

			if (MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_STAIC3) || GetKeyboardPress(DIK_D) && !GetKeyboardPress(DIK_A)) KeyNumber += 100000;
		}
		//�ړ������������̃x�N�g��
		KeyVec = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		//�u���݂̌����̃x�N�g���v�Ɓu�ړ������������̃x�N�g���v�̊O��
		D3DXVec3Cross(&g_Dir, &g_Dir, &KeyVec);

		////����̊p�x�Ȃ��]���Ȃ�
		D3DXMatrixTranslation(&s_matrix, 0, 0, 0);    //  �ړ��}�g���N�X�̏�����    
		D3DXMatrixRotationYawPitchRoll(&z_matrix, 0, 0, roll);    //  ��]�}�g���N�X�̍쐬
		D3DXMatrixTranslation(&s_matrix, 0, 0, vx);  //  �ړ��}�g���N�X�̍쐬  
		switch (KeyNumber)
		{
			//��
		case 1:
		case 1011:
			//�ړ���
			D3DXMatrixRotationYawPitchRoll(&z_matrix, 0, 0, roll);    //  ��]�}�g���N�X�̍쐬
			vx -= ACCEL_X;
			engin_sound = true;
			CSmokeEffect::Createsmoke_explosion(CX_model::XmodelPos().x, CX_model::XmodelPos().y, CX_model::XmodelPos().z);
			break;

			//���h���t�g
		case 10010:

			drift_state_left = true;

			break;

			//��
		case 100:
		case 1110:
		case 101:
			if (vx < 0) {
				vx += Brake_X;
			}

			break;

			//�E�h���t�g
		case 101000:
			drift_state_right = true;

			break;
			//�E����h���t�g
		case 101101:
			drift_state_right = true;

			//������h���t�g
		case 10111:
			drift_state_left = true;

			break;
			//�E��h���t�g
		case 101001:
			drift_state_right = true;

			CSmokeEffect::Createsmoke_explosion(CX_model::XmodelPos().x, CX_model::XmodelPos().y, CX_model::XmodelPos().z);
			break;

			//�E���h���t�g
		case 101100:
			drift_state_right = true;

			break;

			//����h���t�g
		case 10011:
			drift_state_left = true;

			CSmokeEffect::Createsmoke_explosion(CX_model::XmodelPos().x, CX_model::XmodelPos().y, CX_model::XmodelPos().z);
			break;

			//�����h���t�g
		case 10110:
			drift_state_left = true;

			break;

		case 1111:
			break;

			//��
		case 10000:
			if (roll > -0.2) {
				roll -= 0.005;
			}
			if (handle_left > -0.025) {
				handle_left -= HANDLE_SPEED;
			}

			g_rot.y += handle_left;                                    //  Y�������ɂO�D�Q�������Z��]    
			D3DXMatrixRotationYawPitchRoll(&z_matrix, 0, 0, roll);    //  ��]�}�g���N�X�̍쐬
			break;

			//�E
		case 100000:
			if (roll < 0.2) {
				roll += 0.005;
			}
			if (handle_right < 0.025) {
				handle_right += HANDLE_SPEED;
			}
			g_rot.y += handle_right;
			D3DXMatrixRotationYawPitchRoll(&z_matrix, 0, 0, roll);    //  ��]�}�g���N�X�̍쐬
			break;
			//�E����
		case 100101:
			g_rot.y += handle_right;                                    //  Y�������ɂO�D�Q�������Z��] 
			D3DXMatrixRotationYawPitchRoll(&z_matrix, 0, 0, 0.15f);    //  ��]�}�g���N�X�̍쐬
			break;
			//������
		case 10101:
			g_rot.y += handle_left;                                    //  Y�������ɂO�D�Q�������Z��]    
			D3DXMatrixRotationYawPitchRoll(&z_matrix, 0, 0, -0.15f);    //  ��]�}�g���N�X�̍쐬
			break;

			//�E��
		case 100001:
			vx -= ACCEL_X;
			if (roll < 0.2) {
				roll += 0.005;
			}
			if (handle_right < 0.025) {
				handle_right += HANDLE_SPEED;
			}
			g_rot.y += handle_right;
			D3DXMatrixRotationYawPitchRoll(&z_matrix, 0, 0, roll);    //  ��]�}�g���N�X�̍쐬
			CSmokeEffect::Createsmoke_explosion(CX_model::XmodelPos().x, CX_model::XmodelPos().y, CX_model::XmodelPos().z);
			break;

			//�E��
		case 100100:
			if (vx < 0) {
				vx += Brake_X;
			}
			if (handle_right < 0.025) {
				handle_right += HANDLE_SPEED;
			}
			g_rot.y += handle_right;
			D3DXMatrixRotationYawPitchRoll(&z_matrix, 0, 0, 0.15f);    //  ��]�}�g���N�X�̍쐬

			break;

			//����
		case 10001:
			vx -= ACCEL_X;

			if (roll > -0.2) {
				roll -= 0.005;
			}
			if (handle_left > -0.025) {
				handle_left -= HANDLE_SPEED;
			}
			g_rot.y += handle_left;
			D3DXMatrixRotationYawPitchRoll(&z_matrix, 0, 0, roll);    //  ��]�}�g���N�X�̍쐬
			CSmokeEffect::Createsmoke_explosion(CX_model::XmodelPos().x, CX_model::XmodelPos().y, CX_model::XmodelPos().z);
			break;

			//����
		case 10100:
			if (vx < 0) {
				vx += Brake_X;
			}
			if (handle_left > -0.025) {
				handle_left -= HANDLE_SPEED;
			}
			g_rot.y += handle_left;
			D3DXMatrixRotationYawPitchRoll(&z_matrix, 0, 0, -0.15f);    //  ��]�}�g���N�X�̍쐬
			break;
		default:
			break;

		}

		//�n���h����]����
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

	}

}

void CX_model::RocketStart()
{

	coin0 = false;
	b_deboost = false;

	//�G�ɓ����邩���P�b�g�X�^�[�g���s������
	if (CBillboard::HitPlayer() == true && star == false || b_startmiss == true)
	{
		b_kinoko_hit = true;
		coin0 = true;
		vx = 0.02f;
		g_Rot -= 8;
		//0�������̏ꍇ
		if (g_Rot < -180)
		{
			g_Rot = 180;
			b_deboost = true;
			b_startmiss = false;
			b_kinoko_hit = false;
		}
	}

	//360���ȏ�̏ꍇ
	if (g_Rot >= 360)
	{
		g_Rot = g_Rot - 360;
	}

	//���P�b�g�X�^�[�g��������
	if (CModeGame::GetDash() > 0 && CModeGame::GetDash() < 5)
	{
		dashout = false;
		b_startdash = false;
		b_startmiss = false;
		vx = 0.0f;
	}
	//���P�b�g�X�^�[�g�J�E���g�R�̂Ƃ�
	if (CModeGame::GetDash() > 5 && CModeGame::GetDash() < 105)
	{
		if (MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_A) || GetKeyboardPress(DIK_K))
		{
			dashout = true;

		}
	}
	//���P�b�g�X�^�[�g�J�E���g�Q�̂Ƃ������^�C�~���O
	if (CModeGame::GetDash() > 105 && CModeGame::GetDash() < 135 && dashout == false)
	{
		if (MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_A) || GetKeyboardPress(DIK_K))
		{
			vx -= 0.1f;
			b_startdash = true;
		}

	}
	//���P�b�g�X�^�[�g�J�E���g�P�̂Ƃ�
	if (CModeGame::GetDash() > 135 && CModeGame::GetDash() < 190 && dashout == false && b_startdash == false)
	{
		if (MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_A) || GetKeyboardPress(DIK_K))
		{
			vx = -0.1f;

		}

	}
	//���P�b�g�X�^�[�g����
	if (CModeGame::GetDash() == 190 && b_startdash == true)
	{
		CKasokuEffect::CreateKasoku_effect(CX_model::XmodelPos().x, CX_model::XmodelPos().y + 1.0f, CX_model::XmodelPos().z);
	}
	//���P�b�g�X�^�[�g���s
	if (CModeGame::GetDash() == 190 && dashout == true)
	{
		CExplosion::CreateExplosion(CX_model::XmodelPos().x, CX_model::XmodelPos().y, CX_model::XmodelPos().z);
		b_startmiss = true;
	}
}

void CX_model::Speed_Limit()
{
	b_boost = false;
	b_boost2 = false;
	//�_�b�V���{�[�h�ɏ������
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
	else if (turbo_count_left > TURBO_COUNT || turbo_count_right > TURBO_COUNT)
	{
		if (vx < -max_speed - star_speed - TURBO_SPEED)
		{
			vx = -max_speed - star_speed - TURBO_SPEED;
		}
	}

	else if (turbo_count_left > TURBO_MINI_COUNT || turbo_count_right > TURBO_MINI_COUNT)
	{
		if (vx < -max_speed - star_speed - TURBO_SPEED_MINI)
		{
			vx = -max_speed - star_speed - TURBO_SPEED_MINI;
		}
	}


	else if (vx < -max_speed - star_speed)
	{
		vx = -max_speed - star_speed;

	}

	//�΂Ō���
	if (!kino && !star && !kino3 && !bJump)
	{
		//��
		if (vx < -MAX_GARD && g_pos.y > 1.3)
		{
			vx = -MAX_GARD;
			turbo_speed_count_left = 0;
			turbo_count_left = 0;
		}
		//�E
		if (vx < -MAX_GARD && g_pos.y > 1.3)
		{
			vx = -MAX_GARD;
			turbo_speed_count_right = 0;
			turbo_count_right = 0;
		}
	}

}

void CX_model::Drift_Turbo()
{
	//�h���t�g����
	if (drift_state_left)
	{
		PlaySound(SOUND_LABEL_TURBO);
		if (MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_RIGHT_SHOULDER) || GetKeyboardPress(DIK_J))
		{
			handle_left_drift -= DRIFT_ANGLE;
			if (handle_left_drift <= -HANDLE_DRIFT_MAX) {
				handle_left_drift = -HANDLE_DRIFT_MAX;
			}

			g_rot.y += handle_left_drift;

			if (MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_A) || GetKeyboardPress(DIK_K))
			{
				if (g_pos.y < 6.0f)
				{
					force_left -= DRIFT_FORCE;
					if (force_left <= -DRIFT_FORCE_MAX) {
						force_left = -DRIFT_FORCE_MAX;
					}
					D3DXMatrixTranslation(&s_matrix, force_left, 0, vx);  //  �ړ��}�g���N�X�̍쐬  
				}
			}
			D3DXMatrixRotationYawPitchRoll(&z_matrix, 0, 0, -PLAYER_DRIFT_ROT);    //  ��]�}�g���N�X�̍쐬

			turbo_count_left++;
			if (turbo_count_left > TURBO_COUNT)

			{

				CDriftingEffect::CreateDrifting_effect(CX_model::XmodelPos().x, CX_model::XmodelPos().y, CX_model::XmodelPos().z);
			}
			else if (turbo_count_left > TURBO_MINI_COUNT)
			{
				CDrifting_MEffect::CreateDrifting_M_effect(CX_model::XmodelPos().x, CX_model::XmodelPos().y, CX_model::XmodelPos().z);
			}
		}
	}

	if (drift_state_right)
	{
		PlaySound(SOUND_LABEL_TURBO);
		if (MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_RIGHT_SHOULDER) || GetKeyboardPress(DIK_J))
		{
			handle_right_drift += DRIFT_ANGLE;
			if (handle_right_drift >= HANDLE_DRIFT_MAX) {
				handle_right_drift = HANDLE_DRIFT_MAX;
			}

			g_rot.y += handle_right_drift;
			if (MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_A) || GetKeyboardPress(DIK_K))
			{
				if (g_pos.y < 6.0f)
				{
					force_right += DRIFT_FORCE;
					if (force_right >= DRIFT_FORCE_MAX) {
						force_right = DRIFT_FORCE_MAX;
					}

					D3DXMatrixTranslation(&s_matrix, force_right, 0, vx);  //  �ړ��}�g���N�X�̍쐬 
				}
			}

			D3DXMatrixRotationYawPitchRoll(&z_matrix, 0, 0, PLAYER_DRIFT_ROT);    //  ��]�}�g���N�X�̍쐬

			turbo_count_right++;
			if (turbo_count_right > TURBO_COUNT)
			{

				CDriftingEffect::CreateDrifting_effect(CX_model::XmodelPos().x, CX_model::XmodelPos().y, CX_model::XmodelPos().z);
			}
			else if (turbo_count_right > TURBO_MINI_COUNT)
			{
				CDrifting_MEffect::CreateDrifting_M_effect(CX_model::XmodelPos().x, CX_model::XmodelPos().y, CX_model::XmodelPos().z);
			}
		}
	}


	//�^�[�{�@�ԑ̌X��
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

		//���~�j
		if (turbo_count_left > TURBO_MINI_COUNT)
		{
			vx -= TURBO_SPEED_MINI;
			turbo_speed_count_left++;
			if (turbo_speed_count_left > TURBO_UP_MINI || CBillboard::HitPlayer() == true || g_pos.y > 6.0f)
			{
				turbo_speed_count_left = 0;
				turbo_count_left = 0;
			}
		}
		else
		{
			turbo_speed_count_left = 0;
			turbo_count_left = 0;
		}

		//�E�~�j
		if (turbo_count_right > TURBO_MINI_COUNT)
		{
			vx -= TURBO_SPEED_MINI;
			turbo_speed_count_right++;
			if (turbo_speed_count_right > TURBO_UP_MINI || CBillboard::HitPlayer() == true || g_pos.y > 6.0f)
			{
				turbo_speed_count_right = 0;
				turbo_count_right = 0;
			}
		}
		else
		{
			turbo_speed_count_right = 0;
			turbo_count_right = 0;
		}

		//��
		if (turbo_count_left > TURBO_COUNT)
		{
			vx -= TURBO_SPEED;
			turbo_speed_count_left++;
			if (turbo_speed_count_left > TURBO_UP || CBillboard::HitPlayer() == true || g_pos.y > 6.0f)
			{
				turbo_speed_count_left = 0;
				turbo_count_left = 0;
			}
		}
		else
		{
			turbo_speed_count_left = 0;
			turbo_count_left = 0;
		}

		//�E
		if (turbo_count_right > TURBO_COUNT)
		{
			vx -= TURBO_SPEED;
			turbo_speed_count_right++;
			if (turbo_speed_count_right > TURBO_UP || CBillboard::HitPlayer() == true || g_pos.y > 6.0f)
			{
				turbo_speed_count_right = 0;
				turbo_count_right = 0;
			}
		}
		else
		{
			turbo_speed_count_right = 0;
			turbo_count_right = 0;
		}
	}

}

void CX_model::Item_Kinoko()
{
	//�A�C�e���L�m�R�g�p
	if (MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_LEFT_SHOULDER) && (CModeGame::Getkinoko_X() == true) && b_kinoko_hit == false && pos_y == false|| GetKeyboardTrigger(DIK_L) && (CModeGame::Getkinoko_X() == true) && b_kinoko_hit == false && pos_y == false )
	{
		CKasokuEffect::CreateKasoku_effect(CX_model::XmodelPos().x, CX_model::XmodelPos().y + 1.0f, CX_model::XmodelPos().z);
		kino = true;
	}
	if (kinoko_time >= 100)
	{
		kinoko_time = 0;
		kino = false;
	}

	if (kino == true && g_pos.y < 6.0f)
	{
		vx -= 0.2f;
		kinoko_time++;
		if (CBillboard::HitPlayer() == true) {
			kino = false;
			kinoko_time = 0;
		}
	}
}

void CX_model::Item_TripleKinoko()
{
	kino_count = false;

	//�g���v���L�m�R�g�p
	bool isUsedTripleKinoko = (MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_LEFT_SHOULDER) && (CModeGame::Getkinoko3_X() == true) && b_kinoko_hit == false && pos_y == false  || MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_LEFT_SHOULDER) && (CModeGame::Getkinoko2_X() == true) && b_kinoko_hit == false && pos_y == false || MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_LEFT_SHOULDER) && (CModeGame::Getkinoko1_X() == true) && b_kinoko_hit == false && pos_y == false|| GetKeyboardTrigger(DIK_L) && (CModeGame::Getkinoko3_X() == true) && b_kinoko_hit == false && pos_y == false  || GetKeyboardTrigger(DIK_L) && (CModeGame::Getkinoko2_X() == true) && b_kinoko_hit == false && pos_y == false  || GetKeyboardTrigger(DIK_L) && (CModeGame::Getkinoko1_X() == true) && b_kinoko_hit == false && pos_y == false);
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
}

void CX_model::Item_Star()
{
	star_speed = 0.0f;

	//�A�C�e���X�^�[�g�p
	if (MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_LEFT_SHOULDER) && (CModeGame::Getstar_X() == true) && b_kinoko_hit == false && pos_y == false || GetKeyboardTrigger(DIK_L) && (CModeGame::Getstar_X() == true) && b_kinoko_hit == false && pos_y == false )
	{
		star = true;
	}

	if (star_time >= 1)
	{
		CStarEffect::CreateStar_effect(CX_model::XmodelPos().x, CX_model::XmodelPos().y, CX_model::XmodelPos().z);
	}

	if (star_time >= 420)
	{
		StopSound(SOUND_LABEL_STAR);
		star_time = 0;
		star = false;
		star_speed = 0.0f;
	}

	if (star_time <= 420 && star_time >= 1)
	{
		if (MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_LEFT_SHOULDER) && (CModeGame::Getstar_X() == true) && b_kinoko_hit == false && pos_y == false || GetKeyboardTrigger(DIK_L) && (CModeGame::Getstar_X() == true) && b_kinoko_hit == false && pos_y == false)
		{
			star_time = 0;
		}
	}
	if (star == true)
	{
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
}

void CX_model::Item_PWKinoko()
{
	//�p���t���_�b�V���L�m�R�g�p
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
		b_use_pw = false;
		pw_dash_derete = true;
		pw_dash_time = 0;
	}
	else if (pw_dash_time > 1)
	{
		b_use_pw = true;
		if (MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_LEFT_SHOULDER) && b_kinoko_hit == false && pos_y == false || GetKeyboardTrigger(DIK_L) && b_kinoko_hit == false && pos_y == false )
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

}

void CX_model::Item_Coin() {
	//�R�C�����ōō��X�s�[�h��ς���
	if (CCoin::ScoreCoin() == 1) {
		max_speed = 0.605f;
	}
	if (CCoin::ScoreCoin() == 10) {
		max_speed = 0.65f;
	}
	if (CCoin::ScoreCoin() == 20) {
		max_speed = 0.7f;
	}
	if (CCoin::ScoreCoin() == 30) {
		max_speed = 0.75f;
	}
}

void CX_model::Jump_Action() 
{

	//�W�����v
	if (MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_RIGHT_SHOULDER) && CJump::HitPlayer() || MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_RIGHT_SHOULDER) && CJump_Reverse::HitPlayer() && !bUp_d || GetKeyboardTrigger(DIK_J) && CJump::HitPlayer() || GetKeyboardTrigger(DIK_J) && CJump_Reverse::HitPlayer() && !bUp_d)
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


	//�W�����v�A�N�V����
	if (bJump)
	{
		if (jump_roll < 6)
		{
			jump_roll += 0.2;
			if (jump_roll == 1.2f)
			{
				CJumpEffect::CreateJump_Effect(CX_model::XmodelPos().x, CX_model::XmodelPos().y, CX_model::XmodelPos().z);
			}
			D3DXMatrixRotationYawPitchRoll(&z_matrix, 0, jump_roll, 0);    //  ��]�}�g���N�X�̍쐬
			fJump += VALUE_GRAVITY * 1.5;
			g_pos.y += VALUE_GRAVITY * 1.5;
		}


	}

	if (fJump > 2.2f || GetKeyboardRelease(DIK_J) && CJump::HitPlayer() || GetKeyboardRelease(DIK_J) && CJump_Reverse::HitPlayer() || MyInputGamepad::GetButtonRelease(MYGAMEPAD_BUTTON_RIGHT_SHOULDER) && CJump::HitPlayer() || MyInputGamepad::GetButtonRelease(MYGAMEPAD_BUTTON_RIGHT_SHOULDER) && CJump_Reverse::HitPlayer())
	{
		bUp = false;
		bUp_d = false;
		fJump = 0.0f;
	}

	if (g_pos.y <= 1.2f)
	{
		bJump = false;
		OnField = true;
		fJump = 0.0f;
		g_pos.y = 1.2f;
		bJumpAll = false;
		jump_roll = 0.0f;
	}

	//�h���t�g��������
	if (bUp_d == false && OnField == false)
	{
		//g_pos.y -= VALUE_GRAVITY;
	}

	//��������
	if (bUp == false && OnField == false)
	{
		//vx -= 0.5f;
		g_pos.y -= VALUE_GRAVITY;
	}

}

void CX_model::Move_Limit()
{
	//�ړ�������
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


	if (g_modelbUse) {
		if (bJumpAll == false) {
			//�v���C���[�̍���
			CField *field;
			field = CModeGame::GetField();
			g_pos.y = field->GetHeight(g_pos) + 0.2f;
		}
	}

	//��������
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
}

void CX_model::Drift_BGM() {
	//�h���t�g��
	if (MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_STAIC4) && MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_RIGHT_SHOULDER) || GetKeyboardPress(DIK_A) && GetKeyboardTrigger(DIK_J))
	{
		PlaySound(SOUND_LABEL_DRIFT);
	}

	if (MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_STAIC3) && MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_RIGHT_SHOULDER) || GetKeyboardPress(DIK_D) && GetKeyboardTrigger(DIK_J))
	{
		PlaySound(SOUND_LABEL_DRIFT);
	}

	if (MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_STAIC4) && MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_RIGHT_SHOULDER) || GetKeyboardTrigger(DIK_A) && GetKeyboardPress(DIK_J))
	{
		PlaySound(SOUND_LABEL_DRIFT);
	}

	if (MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_STAIC3) && MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_RIGHT_SHOULDER) || GetKeyboardTrigger(DIK_D) && GetKeyboardPress(DIK_J))
	{
		PlaySound(SOUND_LABEL_DRIFT);
	}

	if (MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_STAIC4) && MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_RIGHT_SHOULDER) || GetKeyboardTrigger(DIK_A) && GetKeyboardTrigger(DIK_J))
	{
		PlaySound(SOUND_LABEL_DRIFT);
	}

	if (MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_STAIC3) && MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_RIGHT_SHOULDER) || GetKeyboardTrigger(DIK_D) && GetKeyboardTrigger(DIK_J))
	{
		PlaySound(SOUND_LABEL_DRIFT);
	}

	if (MyInputGamepad::GetButtonRelease(MYGAMEPAD_BUTTON_RIGHT_SHOULDER) || GetKeyboardRelease(DIK_J) || (MyInputGamepad::GetButtonRelease(MYGAMEPAD_BUTTON_STAIC3)) || (MyInputGamepad::GetButtonRelease(MYGAMEPAD_BUTTON_STAIC4)))
	{
		StopSound(SOUND_LABEL_DRIFT);
	}
}

//�L�����̈ʒu
D3DXVECTOR3 CX_model::XmodelPos()
{
	return g_pos;
}


//�L�����̌���
D3DXVECTOR3 CX_model::XmodelRot()
{
	//D3DXVECTOR3 g_R = g_rot +90.0f;

	return g_rot;
}

bool CX_model::pw_dash_dele()
{
	return pw_dash_derete;
}

bool CX_model::Get_b_use_pw()
{
	return b_use_pw;
}

bool CX_model::Get_posy()
{
	return pos_y;
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
	delete this;		//�������g�̃|�C���^
}

D3DXVECTOR3 CX_model::GetFront()
{
	D3DXVECTOR3 front;
	front.x = m_WorldMatirix._31;
	front.y = m_WorldMatirix._32;
	front.z = m_WorldMatirix._33;
	return front; //           Z������
}
