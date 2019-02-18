//-----------------------------------//
//--�Q�[�g����-------[gate.cpp]------//
//-----------------------------------//
//------Author:�{ �C�G-------------//
//-----------------------------------//
#include "main.h"
#include "gate.h"
#include "input.h"
#include <math.h>
#include "Polygon.h"
#include "sound.h"
#include "mesh.h"
#include "renderer.h"

// ���_����(1�ځF���W�A2�ځF�J���[,3�ځF�e�N�X�`���[)
#define FVF_VERTEX_GATE (D3DFVF_XYZ|D3DFVF_DIFFUSE | D3DFVF_TEX1 )
#define FILE_G "data/3D/indiagate3.x"

LPD3DXMESH CGate::g_pMeshG = NULL;		//���b�V���f�[�^
DWORD CGate::g_nMaterialNumG = 0;		//�}�e���A���̐�
LPD3DXBUFFER CGate::g_pMaterialsGBufferG = NULL;		//�}�e���A���̃o�b�t�@�[
LPD3DXBUFFER CGate::g_pMaterialsG = NULL;
D3DMATERIAL9*	CGate::g_pMeshGMaterialsG = NULL;	// �}�e���A�����
LPDIRECT3DTEXTURE9 CGate::pMeshTex2[TEXTURE_3D_MAXG] = { NULL };	// ���b�V���̃e�N�X�`��
D3DXMATRIX CGate::g_World;
D3DXMATRIX CGate::g_Pos;		//�ʒu�̍s��
D3DXVECTOR3 CGate::g_Transmodel;		//�ړ�
D3DXVECTOR3 CGate::g_Dir;		//����
D3DXMATRIX CGate::g_RotGation, CGate::g_mtxScale;	//��] �g��
D3DXMATRIX CGate::g_Shadow;		//�e�̃��[���h�s��
float  CGate::g_RotG = 0.0f;
LPDIRECT3DVERTEXBUFFER9 CGate::g_pVertexBuffer = NULL;		// �o�[�e�b�N�X�o�b�t�@�̃|�C���^
LPDIRECT3DINDEXBUFFER9 CGate::g_pIndexBuffer = NULL;		// �C���f�b�N�X�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 CGate::pTextures;


typedef struct
{
	D3DXVECTOR3 pos;		//���W
	D3DCOLOR color;			//�F
	D3DXVECTOR2 texture;	//�e�N�X�`�����W
}VERTEX_SHADOW;

bool CGate::InitGate(void)
{

	g_Transmodel = D3DXVECTOR3(0.0f, 0.8f, 0.0f);

	g_Dir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	LPDIRECT3DDEVICE9 pDevice = CRender::GetD3DDevice();	//�f�o�C�X�̎擾

	if (pDevice == NULL)
	{
		return false;
	}

	HRESULT hr;

	hr = pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_SHADOW) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_GATE,
		D3DPOOL_MANAGED,
		&g_pVertexBuffer,
		NULL
	);

	if (FAILED(hr))
	{
		MessageBox(NULL, "�ǂݍ��߂܂���", "�G���[", MB_OK);
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
		MessageBox(NULL, "�ǂݍ��߂܂���", "�G���[", MB_OK);
		return FALSE;
	}

	LPD3DXBUFFER pAdjacency = NULL;

	//x�t�@�C���ǂݍ���
	hr = D3DXLoadMeshFromX(
		FILE_G,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		&pAdjacency,			//�אڏ��
		&g_pMaterialsGBufferG,			//
		NULL,
		&g_nMaterialNumG,		//�}�e���A���͂������邩
		&g_pMeshG);

	if (FAILED(hr))
	{
		MessageBox(NULL, "���s���܂���gate", "�ǂݍ��߂܂���ł���0", MB_OK);
		return FALSE;
	}


	g_pMeshG->OptimizeInplace(
		D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE,
		(DWORD*)pAdjacency->GetBufferPointer(),
		NULL,
		NULL,
		NULL
	);


	LPD3DXMESH pCloneMesh;

	D3DVERTEXELEMENT9 elements[MAXD3DDECLLENGTH + 1];

	g_pMeshG->GetDeclaration(elements);
	g_pMeshG->CloneMesh(D3DXMESH_MANAGED | D3DXMESH_WRITEONLY, elements, pDevice, &pCloneMesh);

	//���������Ă���
	g_pMeshG = pCloneMesh;

	D3DXMATERIAL* pMaterials = (D3DXMATERIAL*)g_pMaterialsGBufferG->GetBufferPointer();

	g_pMeshGMaterialsG = new D3DMATERIAL9[g_nMaterialNumG];		// ���b�V�������m��

	for (DWORD i = 0; i < g_nMaterialNumG; i++)
	{
		//�}�e���A�������Z�b�g
		g_pMeshGMaterialsG[i] = pMaterials[i].MatD3D;

		 //�g�p���Ă���e�N�X�`��������Γǂݍ���
		if (pMaterials[i].pTextureFilename != NULL && lstrlen(pMaterials[i].pTextureFilename) > 0)
		{
			// �e�N�X�`���ǂݍ���
			if (FAILED(D3DXCreateTextureFromFile(
				pDevice,
				pMaterials[i].pTextureFilename,
				&pMeshTex2[i])))
			{
				return false;
			}
		}
		hr = D3DXCreateTextureFromFile(pDevice, "data/texture/Block.png", &pTextures);
	}

	return true;
}


void CGate::UninitGate()
{

	for (int i = 0; i < TEXTURE_3D_MAXG; i++)
	{
		if (pMeshTex2[i] != NULL)
		{
			pMeshTex2[i]->Release();
			pMeshTex2[i] = NULL;
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

	if (g_pMeshG != NULL)
	{
		g_pMeshG->Release();
		g_pMeshG = NULL;
	}

}


void CGate::UpdateGate()
{
		D3DXMatrixIdentity(&g_World);
		D3DXMatrixIdentity(&g_Shadow);
}


void CGate::DrawGate()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRender::GetD3DDevice();

	if (pDevice == NULL) { return; }

		D3DXMatrixScaling(&g_mtxScale, 4.0, 4, 4);

		D3DXMatrixRotationY(&g_RotGation, D3DXToRadian(-g_RotG));

		D3DXMatrixTranslation(&g_Pos, g_Transmodel.x, g_Transmodel.y, g_Transmodel.z);

		g_World = g_World * g_mtxScale;

		g_World = g_World * g_RotGation;

		g_World = g_World * g_Pos;

		//���[���h�s��̐ݒ�(�D���ȃ^�C�~���O�ŌĂ�)
		pDevice->SetTransform(D3DTS_WORLD, &g_World);

		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);	//���C�g��L��
													
		 pDevice->SetTexture(0, pTextures);
		for (int i = 0; i < 3; i++)
		{

			pDevice->SetMaterial(&g_pMeshGMaterialsG[i]);	// �}�e���A�������Z�b�g

			g_pMeshG->DrawSubset(i);				// ���b�V����`��

	}
}

//�L�����̈ʒu
D3DXVECTOR3 CGate::GatePos()
{
	return g_Transmodel;
}

//�L�����̌���
float CGate::GateRot()
{
	float g_R = g_RotG + 270.0f;

	return g_R;
}