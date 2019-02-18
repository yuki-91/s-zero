//-----------------------------------//
//�_�b�V���{�[�h�T�C�h����-[dashboard.cpp]-//
//-----------------------------------//
//------Author:�{ �C�G-------------//
//-----------------------------------//
//�C���N���[�h��

#include "dashboard_side.h"
#include "dash_effect.h"
#include"kasoku_effect.h"
#include "hit.h"
#include "camera.h"
#include "renderer.h"
#include "player.h"
#include "mode_game.h"
#include "sound.h"
#define FVF_VERTEX_DASHSIDE (D3DFVF_XYZ|D3DFVF_DIFFUSE | D3DFVF_TEX1 )

LPDIRECT3DTEXTURE9 CDashSide::g_pTextures_dash[TEXTURE_DASH_SIDEMAX] = { NULL };	//�e�N�X�`���z��
D3DXMATRIX CDashSide::g_mtxWorld_Item;		//���[���h�ϊ��s��
LPDIRECT3DVERTEXBUFFER9 CDashSide::g_pVertexBuffer = NULL;		// �o�[�e�b�N�X�o�b�t�@�̃|�C���^
LPDIRECT3DINDEXBUFFER9 CDashSide::g_pIndexBuffer = NULL;		// �C���f�b�N�X�o�b�t�@�̃|�C���^
D3DXMATRIX CDashSide::g_viewInverse;
D3DXMATRIX CDashSide::g_Trans, CDashSide::g_Rotation;
D3DXVECTOR3 CDashSide::g_TransPos4[MAX_DASHSIDE];
int CDashSide::color[MAX_DASHSIDE];
bool CDashSide::ememy[MAX_DASHSIDE];
int CDashSide::Life[MAX_DASHSIDE];
float  CDashSide::g_Rot6 = 0.0f;
bool CDashSide::b_dash2 = false;

typedef struct
{
	D3DXVECTOR3 pos;		//���W
	D3DCOLOR color;			//�F
	D3DXVECTOR2 texture;	//�e�N�X�`�����W
}VERTEX_BILLBOARD;

bool CDashSide::InitItem()
{
	b_dash2 = false;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9  pDevice = CRender::GetD3DDevice();

	if (pDevice == NULL)
	{
		return false;
	}

	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);

	HRESULT hr;

	for (int i = 0; i<TEXTURE_DASH_SIDEMAX; i++)
	{

		hr = D3DXCreateTextureFromFile(pDevice, g_aTexture_e[i].fileName, &g_pTextures_dash[i]);

		if (FAILED(hr))
		{
			MessageBox(NULL, "�ǂݍ��߂܂���", "�G���[", MB_OK);
			return false;
		}

	}

	hr = pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_BILLBOARD) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_DASHSIDE,
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


	g_TransPos4[0] = D3DXVECTOR3(-45.0f, 1.4f, 135.0f);
	g_TransPos4[2] = D3DXVECTOR3(-50.0f, 1.4f, 130.0f);
	g_TransPos4[4] = D3DXVECTOR3(-55.0f, 1.4f, 125.0f);
	
	g_TransPos4[1] = D3DXVECTOR3(-25.0f, 1.4f, -135.0f);
	g_TransPos4[3] = D3DXVECTOR3(-20.0f, 1.4f, -130.0f);
	g_TransPos4[5] = D3DXVECTOR3(85.0f, 1.4f, -125.0f);

	//�F�ݒ�
	for (int c = 0; c < MAX_DASHSIDE; c++)
	{
		color[c] = c % 2;
		ememy[c] = true;
		Life[c] = 0;
	}

	VertexBuffer_Field();
	IndexBuffer_Field();

	return true;
}

void CDashSide::UninitItem()
{

	for (int i = 0; i < TEXTURE_DASH_SIDEMAX; i++)
	{
		if (g_pTextures_dash[i] != NULL)
		{
			g_pTextures_dash[i]->Release();
			g_pTextures_dash[i] = NULL;
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

void CDashSide::UpdateItem()
{
	D3DXVECTOR3 mu = D3DXVECTOR3(0.5f, 0.5f, 0.5f);

	//�����蔻��
	for (int Ememy = 0; Ememy < MAX_DASHSIDE; Ememy++)
	{
		//�o�����Ă��邩
		if (ememy[Ememy])
		{
			//�o��
			if (ememy[Ememy])
			{
				//�����蔻��
				if (CHit::AABB(D3DXVECTOR3(g_TransPos4[Ememy].x - 2.5f, g_TransPos4[Ememy].y - 2.0f, g_TransPos4[Ememy].z - 0.5f),
					D3DXVECTOR3(g_TransPos4[Ememy].x + 2.5f, g_TransPos4[Ememy].y + 2.0f, g_TransPos4[Ememy].z + 0.5f),
					D3DXVECTOR3(CX_model::XmodelPos().x, CX_model::XmodelPos().y + 1, CX_model::XmodelPos().z) - mu,
					D3DXVECTOR3(CX_model::XmodelPos().x, CX_model::XmodelPos().y - 1, CX_model::XmodelPos().z) + mu))
				{		
					PlaySound(SOUND_LABEL_SE_KASOKU);
					CDashEffect::Createdash_effect(CX_model::XmodelPos().x, CX_model::XmodelPos().y + 1.0f, CX_model::XmodelPos().z-1.0f);
					b_dash2 = true;
				}
			}
		}
	}

	if (CX_model::boost2() == true)
	{
		b_dash2 = false;
	}

	if (CX_model::XmodelPos().y > 2.5f)
	{
		b_dash2 = false;
	}

	LPDIRECT3DDEVICE9 pDevice = CRender::GetD3DDevice();

	if (pDevice == NULL) { return; }

	//�r���[�}�g���b�N�X���擾����
	pDevice->GetTransform(D3DTS_VIEW, &g_viewInverse);

	//view�t�s��쐬
	D3DXMatrixInverse(&g_viewInverse, NULL, &g_viewInverse);

	g_viewInverse._41 = g_viewInverse._42 = g_viewInverse._43 = 0.0f;
}

void CDashSide::DrawItem()
{
	LPDIRECT3DDEVICE9 pDevice = CRender::GetD3DDevice();
	if (pDevice == NULL) { return; }

	//���C�g��ON�EOFF
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//���e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int a = 0; a < MAX_DASHSIDE; a++)
	{
		if (ememy[a])
		{
			D3DXMatrixIdentity(&g_mtxWorld_Item);

			//FVF�̐ݒ�
			//FVF->�f�o�C�X�ɋ�����
			pDevice->SetFVF(FVF_VERTEX_DASHSIDE);

			//�e�N�X�`�����Z�b�g
			pDevice->SetTexture(0, g_pTextures_dash[color[a]]);

			D3DXMatrixRotationY(&g_Rotation, D3DXToRadian(g_Rot6));

			//�r���{�[�h�̈ړ�
			D3DXMatrixTranslation(&g_Trans, g_TransPos4[a].x, g_TransPos4[a].y, g_TransPos4[a].z);

			g_mtxWorld_Item = g_mtxWorld_Item  * g_Rotation;

			g_mtxWorld_Item = g_mtxWorld_Item  * g_Trans;

			//���[���h�s��̐ݒ�(�D���ȃ^�C�~���O�ŌĂ�)
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld_Item);

			pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(VERTEX_BILLBOARD));

			pDevice->SetIndices(g_pIndexBuffer);

			pDevice->DrawIndexedPrimitive
			(D3DPT_TRIANGLELIST,//D3DPT_TRIANGLESTRIP//D3DPT_LINESTRIP//D3DPT_TRIANGLELIST
				0,//�C���f�b�N�X�̊J�n���l
				0,
				6,					//�C���f�b�N�X�̐�
				0,
				2);					//�v���~�e�B�u��
		}
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

void CDashSide::VertexBuffer_Field()
{

	VERTEX_BILLBOARD b[] =
	{
		{ D3DXVECTOR3(-3, 0, 1),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(0, 0) },
		{ D3DXVECTOR3(3, 0, 1),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(1, 0) },
		{ D3DXVECTOR3(-3, 0,-1),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(0, 1) },
		{ D3DXVECTOR3(3, 0, -1),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(1, 1) },
	};

	VERTEX_BILLBOARD *pV;

	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);

	// �z����R�s�[����
	memcpy(pV, b, sizeof(b));

	g_pVertexBuffer->Unlock();
}

void CDashSide::IndexBuffer_Field()
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

bool CDashSide::HitPlayer()
{
	return b_dash2;
}