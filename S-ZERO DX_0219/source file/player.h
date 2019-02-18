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
	static void Uninit();
	static void Update();
	static void Draw();
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
private:
	//static LPD3DXMESH g_pMesh ;		//���b�V���f�[�^
	//static DWORD g_nMaterialNum ;		//�}�e���A���̐�
	//static LPD3DXBUFFER g_pMaterialsBuffer;		//�}�e���A���̃o�b�t�@�[
	//static LPD3DXBUFFER g_pMaterials ;
//	static D3DMATERIAL9*	g_pMeshMaterials ;	// �}�e���A�����
	//static LPDIRECT3DTEXTURE9 pMeshTex[TEXTURE_3D_MAX] ;	// ���b�V���̃e�N�X�`��
	static D3DXMATRIX g_World;
	static D3DXMATRIX g_Pos;		//�ʒu�̍s��
	static D3DXVECTOR3 g_Transmodel;		//�ړ�
	static D3DXVECTOR3 g_Dir;		//����
	static D3DXMATRIX g_Rotation, g_mtxScale;	//��] �g��
	static D3DXMATRIX g_Shadow;		//�e�̃��[���h�s��
	static LPDIRECT3DTEXTURE9 m_pTextures;
	static float  g_Rot ;
	static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer ;		// �o�[�e�b�N�X�o�b�t�@�̃|�C���^
	static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer ;		// �C���f�b�N�X�o�b�t�@�̃|�C���^
	static bool g_modelbUse ;
	static D3DXMATRIX m_WorldMatirix;
	static LPDIRECT3DDEVICE9 pDevice;
	static D3DXMATRIX t_matrix, s_matrix, r_matrix, q_matrix, z_matrix;
	static D3DXVECTOR3     g_rot;     //  ��]   
	static D3DXVECTOR3     g_pos;
	static double vx ;
	static bool b_deboost ;
	static bool b_boost ;
	static bool b_boost2;
	static bool coin0 ;
	static float max_speed ;
	static float star_speed;
	static bool dashout ;
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
};
#endif //_XMODEL_H_