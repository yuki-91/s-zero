//-----------------------------------//
//�W�����v�{�[�h����-[jump_board.cpp]-//
//-----------------------------------//
//------Author:�{ �C�G-------------//
//-----------------------------------//
//�C���N���[�h��
#include "jump_board_reverse.h"
#include "dash_effect.h"
#include"kasoku_effect.h"
#include"hit.h"
#include "camera.h"
#include "renderer.h"
#include "player.h"
#include "mode_game.h"
#include "sound.h"
#define FVF_VERTEX_JUMP_REVERESEBOARD (D3DFVF_XYZ|D3DFVF_DIFFUSE | D3DFVF_TEX1 )
LPDIRECT3DTEXTURE9 CJump_Reverse::g_pTextures_dash[TEXTURE_JUMP_REVERESE_MAX] = { NULL };	//�e�N�X�`���z��
D3DXMATRIX CJump_Reverse::g_mtxWorld_jump;		//���[���h�ϊ��s��
LPDIRECT3DVERTEXBUFFER9 CJump_Reverse::g_pVertexBuffer = NULL;		// �o�[�e�b�N�X�o�b�t�@�̃|�C���^
LPDIRECT3DINDEXBUFFER9 CJump_Reverse::g_pIndexBuffer = NULL;		// �C���f�b�N�X�o�b�t�@�̃|�C���^
D3DXMATRIX CJump_Reverse::g_viewInverse;
D3DXMATRIX CJump_Reverse::g_Trans, CJump_Reverse::g_Rotation;
D3DXVECTOR3 CJump_Reverse::g_TransPos3[MAX_JUMP_REVERESE];
int CJump_Reverse::color[MAX_JUMP_REVERESE];
bool CJump_Reverse::ememy[MAX_JUMP_REVERESE];
int CJump_Reverse::Life[MAX_JUMP_REVERESE];
float  CJump_Reverse::g_Rot5 = 0.0f;
bool CJump_Reverse::b_dash = false;
int CJump_Reverse::jump_count = 0.0f;
typedef struct
{
	D3DXVECTOR3 pos;		//���W
	D3DCOLOR color;			//�F
	D3DXVECTOR2 texture;	//�e�N�X�`�����W
}VERTEX_BILLBOARD;

bool CJump_Reverse::Initjump()
{
	b_dash = false;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9  pDevice = CRender::GetD3DDevice();

	if (pDevice == NULL)
	{
		return false;
	}

	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);

	HRESULT hr;

	for (int i = 0; i<TEXTURE_JUMP_REVERESE_MAX; i++)
	{

		hr = D3DXCreateTextureFromFile(pDevice, g_aTexture_k[i].fileName, &g_pTextures_dash[i]);

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
		FVF_VERTEX_JUMP_REVERESEBOARD,
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

	g_TransPos3[0] = D3DXVECTOR3(-130.0f, 1.2f, -45.0f);
	g_TransPos3[1] = D3DXVECTOR3(-33.0f, 1.2f, -45.0f);
	g_TransPos3[2] = D3DXVECTOR3(40.0f, 1.2f, 65.0f);
	g_TransPos3[3] = D3DXVECTOR3(-37.0f, 1.2f, 35.0f);


	//�F�ݒ�
	for (int c = 0; c < MAX_JUMP_REVERESE; c++)
	{
		color[c] = c % 1;
		ememy[c] = true;
		Life[c] = 0;
	}

	VertexBuffer_Field();
	IndexBuffer_Field();

	return true;
}

void CJump_Reverse::Uninitjump()
{

	for (int i = 0; i < TEXTURE_JUMP_REVERESE_MAX; i++)
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

void CJump_Reverse::Updatejump()
{
	D3DXVECTOR3 mu = D3DXVECTOR3(0.5f, 0.5f, 0.5f);

	//�����蔻��
	for (int Ememy = 0; Ememy < MAX_JUMP_REVERESE; Ememy++)
	{
		//�o�����Ă��邩
		if (ememy[Ememy])
		{
			//�o��
			if (ememy[Ememy])
			{
				//�����蔻��
				if (CHit::AABB(D3DXVECTOR3(g_TransPos3[Ememy].x - 2.7f, g_TransPos3[Ememy].y - 4.0f, g_TransPos3[Ememy].z - 4.0f),
					D3DXVECTOR3(g_TransPos3[Ememy].x + 2.7f, g_TransPos3[Ememy].y + 3.0f, g_TransPos3[Ememy].z + 3.0f),
					D3DXVECTOR3(CX_model::XmodelPos().x, CX_model::XmodelPos().y + 1, CX_model::XmodelPos().z) - mu,
					D3DXVECTOR3(CX_model::XmodelPos().x, CX_model::XmodelPos().y - 1, CX_model::XmodelPos().z) + mu))
				{
					//PlaySound(SOUND_LABEL_SE_KASOKU);
					//CDashEffect::Createdash_effect(CX_model::XmodelPos().x, CX_model::XmodelPos().y + 1.0f, CX_model::XmodelPos().z);
					b_dash = true;

				}
			}

		}

	}
	if (b_dash == true)
	{
		jump_count++;
		if (jump_count > 5)
		{
			b_dash = false;
			jump_count = 0;
		}
	}
	if (CX_model::boost() == true)
	{
		b_dash = false;
	}

	if (CX_model::XmodelPos().y > 2.5f)
	{
		b_dash = false;
	}


	LPDIRECT3DDEVICE9 pDevice = CRender::GetD3DDevice();

	if (pDevice == NULL) { return; }

	//�r���[�}�g���b�N�X���擾����
	pDevice->GetTransform(D3DTS_VIEW, &g_viewInverse);

	//view�t�s��쐬
	D3DXMatrixInverse(&g_viewInverse, NULL, &g_viewInverse);

	g_viewInverse._41 = g_viewInverse._42 = g_viewInverse._43 = 0.0f;

}

void CJump_Reverse::Drawjump()
{
	LPDIRECT3DDEVICE9 pDevice = CRender::GetD3DDevice();
	if (pDevice == NULL) { return; }

	//���C�g��ON�EOFF
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//���e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int a = 0; a < MAX_JUMP_REVERESE; a++)
	{
		if (ememy[a])
		{
			D3DXMatrixIdentity(&g_mtxWorld_jump);

			//FVF�̐ݒ�
			//FVF->�f�o�C�X�ɋ�����
			pDevice->SetFVF(FVF_VERTEX_JUMP_REVERESEBOARD);

			//�e�N�X�`�����Z�b�g
			pDevice->SetTexture(0, g_pTextures_dash[color[a]]);

			D3DXMatrixRotationY(&g_Rotation, D3DXToRadian(g_Rot5));

			//�r���{�[�h�̈ړ�
			D3DXMatrixTranslation(&g_Trans, g_TransPos3[a].x, g_TransPos3[a].y, g_TransPos3[a].z);

			g_mtxWorld_jump = g_mtxWorld_jump  * g_Rotation;

			g_mtxWorld_jump = g_mtxWorld_jump  * g_Trans;

			//���[���h�s��̐ݒ�(�D���ȃ^�C�~���O�ŌĂ�)
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld_jump);

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

void CJump_Reverse::VertexBuffer_Field()
{

	VERTEX_BILLBOARD b[] =
	{
		{ D3DXVECTOR3(-2, 0.1, 3),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(0, 0) },
		{ D3DXVECTOR3(2, 0.1, 3),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(1, 0) },
		{ D3DXVECTOR3(-2, 0.9,-3),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(0, 1) },
		{ D3DXVECTOR3(2, 0.9, -3),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(1, 1) },
	};

	VERTEX_BILLBOARD *pV;

	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);

	// �z����R�s�[����
	memcpy(pV, b, sizeof(b));

	g_pVertexBuffer->Unlock();
}


void CJump_Reverse::IndexBuffer_Field()
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

bool CJump_Reverse::HitPlayer()
{
	return b_dash;
}