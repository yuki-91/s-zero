//-----------------------------------//
//--�X�J�C�{�b�N�X����--[sky_box.h]//
//-----------------------------------//
//------Author:�{ �C�G-------------//
//-----------------------------------//
#ifndef _SKYBOX_H_
#define _SKYBOX_H_
#include"main.h"
#include "scene.h"


class CXmodel
{
private:
	static D3DXMATRIX m_mtxWorld;	//���[���h�ϊ��s��
	static LPDIRECT3DTEXTURE9 m_pTextures;
	static LPD3DXMESH m_pMesh;
	static DWORD m_nMaterialNum ;
	static LPD3DXBUFFER m_pMaterials;
	static D3DXMATRIX m_mtxScale;
	static D3DXMATRIX m_World;
	static D3DXVECTOR3 m_Position;
	static LPDIRECT3DDEVICE9 m_Device;
	static LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
	static LPDIRECT3DTEXTURE9 m_Texture;

	static D3DXMATRIX m_Pos;		//�ʒu�̍s��
	static D3DXVECTOR3 m_Trans;		//�ړ�
	static D3DXVECTOR3 m_Dir;		//����
	static D3DXMATRIX m_Rotation;	//��]�̍s��
	static D3DXMATRIX m_Shadow;		//�e�̃��[���h�s��
	static float  m_Rot2;
public:
	static CXmodel *Create();
	CXmodel();
	~CXmodel();
	
	bool InitXmodel();
	static void Uninit();
	static void Update();
	static void Draw();
	void Release();
    static D3DXVECTOR3 XmodelPos();

	static float XmodelRot();
};
#endif 
