//-----------------------------------//
//--�Q�[�g����---------------[gate.h]//
//-----------------------------------//
//------Author:�{ �C�G-------------//
//-----------------------------------//
#ifndef _GATE_H_
#define _GATE_H_
#include "mesh.h"

enum TEXTURE_GATE_3D_ENUM
{
	TEXTURE_3D_NULLG = -1,
	TEXTURE_3D_GATE,
	TEXTURE_3D_MAXG
};

typedef struct
{
	char fileName[256];
	int width;
	int height;
}TEXTURE_3DG;

static const TEXTURE_3DG g_aTexture3DGate[] =
{
	{ "data/texture/Block.png",2560,1600 },
};

class CGate {
public:
	static bool InitGate(void);
	static void UninitGate();
	static void UpdateGate();
	static void DrawGate();
	static D3DXVECTOR3 GatePos();
	static float GateRot();
private:
	static LPD3DXMESH g_pMeshG;	//���b�V���f�[�^
	static DWORD g_nMaterialNumG;		//�}�e���A���̐�
	static LPD3DXBUFFER g_pMaterialsGBufferG;		//�}�e���A���̃o�b�t�@�[
	static LPD3DXBUFFER g_pMaterialsG;
	static D3DMATERIAL9*	g_pMeshGMaterialsG;	// �}�e���A�����
	static LPDIRECT3DTEXTURE9 pMeshTex2[TEXTURE_3D_MAXG];	// ���b�V���̃e�N�X�`��
	static D3DXMATRIX g_World;
	static D3DXMATRIX g_Pos;		//�ʒu�̍s��
	static D3DXVECTOR3 g_Transmodel;		//�ړ�
	static D3DXVECTOR3 g_Dir;		//����
	static D3DXMATRIX g_RotGation, g_mtxScale;	//��] �g��
	static D3DXMATRIX g_Shadow;		//�e�̃��[���h�s��
	static float  g_RotG;
	static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer;		// �o�[�e�b�N�X�o�b�t�@�̃|�C���^
	static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer;		// �C���f�b�N�X�o�b�t�@�̃|�C���^
	static LPDIRECT3DTEXTURE9 pTextures;
};

#endif //_GATE_H_