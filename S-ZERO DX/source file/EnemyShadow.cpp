//-----------------------------------//
//----�V���h�E����-[EnemyShadow.cpp]-//
//-----------------------------------//
//------Author:�{ �C�G-------------//
//-----------------------------------//
//�C���N���[�h��

#include "EnemyShadow.h"
#include "Enemy.h"
#include "camera.h"
#include "renderer.h"
#include "player.h"
#include "hit.h"
#include "Explosion.h"
#include "sound.h"

// ���_����(1�ځF���W�A2�ځF�J���[,3�ځF�e�N�X�`���[)
#define FVF_VERTEX_ENEMY_SHADOW (D3DFVF_XYZ|D3DFVF_DIFFUSE | D3DFVF_TEX1 )

LPDIRECT3DTEXTURE9 CShadow::g_pTexture2 = NULL;
D3DXMATRIX CShadow::g_mtxWorld_Shadow;		//���[���h�ϊ��s��
LPDIRECT3DVERTEXBUFFER9 CShadow::g_pVertexBuffer2 = NULL;		// �o�[�e�b�N�X�o�b�t�@�̃|�C���^
LPDIRECT3DINDEXBUFFER9 CShadow::g_pIndexBuffer2 = NULL;		// �C���f�b�N�X�o�b�t�@�̃|�C���^
D3DXMATRIX CShadow::g_Pos;		//�ʒu�̍s��
D3DXMATRIX CShadow::g_Shadow;		//�e�̃��[���h�s��
D3DXMATRIX CShadow::g_viewInverse;
D3DXMATRIX CShadow::g_Trans, g_Rotation;
D3DXVECTOR3 CShadow::g_TransPos[MAX_SHADOW];
int CShadow::color[MAX_SHADOW];
bool CShadow::ememy[MAX_SHADOW];
int CShadow::Life[MAX_SHADOW];

typedef struct
{
	D3DXVECTOR3 pos;		//���W
	D3DCOLOR color;			//�F
	D3DXVECTOR2 texture;	//�e�N�X�`�����W
}VERTEX_SHADOW2;

bool CShadow::InitShadow()
{

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9  pDevice = CRender::GetD3DDevice();

	if (pDevice == NULL)
	{
		return false;
	}

	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);

	HRESULT hr;


	hr = pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_SHADOW2) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_ENEMY_SHADOW,
		D3DPOOL_MANAGED,
		&g_pVertexBuffer2,
		NULL
	);

	hr = pDevice->CreateIndexBuffer
	(
		sizeof(WORD) * 6,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIndexBuffer2,
		NULL
	);


	if (FAILED(hr))
	{
		MessageBox(NULL, "�ǂݍ��߂܂���", "�G���[", MB_OK);
		return FALSE;
	}

	g_TransPos[0] = D3DXVECTOR3(0.0f, 0.5f, 0.0f); 

											//�F�ݒ�
	for (int c = 0; c < MAX_SHADOW; c++)
	{
		color[c] = c % 3;
		ememy[c] = true;
		Life[c] = 0;
	}

	VertexBuffer_Shadow2();
	IndexBuffer_Shadow2();
	D3DXCreateTextureFromFile(pDevice, "data/texture/shadow000.jpg", &g_pTexture2);

	return true;
}

void CShadow::UninitShadow()
{

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
}

void CShadow::UpdateShadow()
{
	LPDIRECT3DDEVICE9 pDevice = CRender::GetD3DDevice();

	if (pDevice == NULL) { return; }

	D3DXMatrixIdentity(&g_mtxWorld_Shadow);
	
	g_TransPos[0].x = CX_model::XmodelPos().x;
	g_TransPos[0].y = CX_model::XmodelPos().y+1;
	g_TransPos[0].z = CX_model::XmodelPos().z;

}

void CShadow::DrawShadow()
{
	LPDIRECT3DDEVICE9 pDevice = CRender::GetD3DDevice();
	if (pDevice == NULL) { return; }

	for (int a = 0; a < MAX_SHADOW; a++)
	{
		if (ememy[a]) {
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
			//���e�X�g
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);


			D3DXMatrixIdentity(&g_mtxWorld_Shadow);

			//FVF�̐ݒ�
			//FVF->�f�o�C�X�ɋ�����
			pDevice->SetFVF(FVF_VERTEX_ENEMY_SHADOW);

			//�e�N�X�`�����Z�b�g
			pDevice->SetTexture(0, g_pTexture2);

			//�r���{�[�h�̈ړ�
			D3DXMatrixTranslation(&g_Trans, g_TransPos[a].x, 0.6, g_TransPos[a].z);

			g_mtxWorld_Shadow = g_mtxWorld_Shadow  * g_Trans;

			//���[���h�s��̐ݒ�(�D���ȃ^�C�~���O�ŌĂ�)
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld_Shadow);

			pDevice->SetStreamSource(0, g_pVertexBuffer2, 0, sizeof(VERTEX_SHADOW2));

			pDevice->SetIndices(g_pIndexBuffer2);

			pDevice->DrawIndexedPrimitive
			(D3DPT_TRIANGLELIST,//D3DPT_TRIANGLESTRIP//D3DPT_LINESTRIP//D3DPT_TRIANGLELIST
				0,//�C���f�b�N�X�̊J�n���l
				0,
				6,					//�C���f�b�N�X�̐�
				0,
				2);					//�v���~�e�B�u��
		}

		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		//���̍����ɖ߂�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}

}


void CShadow::CreateShadow2()
{
	LPDIRECT3DDEVICE9 pDevice = CRender::GetD3DDevice();

	if (pDevice == NULL) { return; }

	for (int a = 0; a < MAX_SHADOW; a++)
	{
	
	//���C�g��ON�EOFF
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//���Z�ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	D3DXMatrixIdentity(&g_Shadow);
		//FVF�̐ݒ�
		//FVF->�f�o�C�X�ɋ�����
		pDevice->SetFVF(FVF_VERTEX_ENEMY_SHADOW);

		//�e�N�X�`�����Z�b�g
		pDevice->SetTexture(0, g_pTexture2);

		//for (int a = 0; a < 10; a++) {
		D3DXMatrixTranslation(&g_Pos, g_TransPos[a].x, 0.0f, g_TransPos[a].z);

		g_Shadow = g_Shadow * g_Pos;

		//���[���h�s��̐ݒ�(�D���ȃ^�C�~���O�ŌĂ�)
		pDevice->SetTransform(D3DTS_WORLD, &g_Shadow);

		pDevice->SetStreamSource(0, g_pVertexBuffer2, 0, sizeof(VERTEX_SHADOW2));

		pDevice->SetIndices(g_pIndexBuffer2);

		pDevice->DrawIndexedPrimitive
		(D3DPT_TRIANGLELIST,//D3DPT_TRIANGLESTRIP//D3DPT_LINESTRIP//D3DPT_TRIANGLELIST
			0,//�C���f�b�N�X�̊J�n���l
			0,
			6,					//�C���f�b�N�X�̐�
			0,
			2);					//�v���~�e�B�u��
	}
}

void CShadow::VertexBuffer_Shadow2()
{

	VERTEX_SHADOW2 s[] =
	{
		{ D3DXVECTOR3(-0.7f,  0.7f, 0.7f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(0, 0) },
		{ D3DXVECTOR3(0.7f,  0.7f, 0.7f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(1, 0) },
		{ D3DXVECTOR3(-0.7f,  0.7f, -0.7f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(0, 1) },
		{ D3DXVECTOR3(0.7f,  0.7f, -0.7f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(1, 1) },

	};

	VERTEX_SHADOW2 *pV;

	g_pVertexBuffer2->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);

	// �z����R�s�[����
	memcpy(pV, s, sizeof(s));

	g_pVertexBuffer2->Unlock();
}

void CShadow::IndexBuffer_Shadow2()
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