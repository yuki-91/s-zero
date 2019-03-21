//-----------------------------------//
//----------�G�l�~�[����-[Enemy.h]-//
//-----------------------------------//
//------Author:�{ �C�G-------------//
//-----------------------------------//
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"

#define MAX_BILLBOARD (18)	//�r���{�[�h�̌�

enum TEXTURE_B_ENUM
{
	TEXTURE_B_NULL = -1,
	TEXTURE_B_MEN_BLUE,
	TEXTURE_B_MEN_RED,
	TEXTURE_B_MEN_GREEN,
	TEXTURE_B_MAX
};


typedef struct
{
	char fileName[256];
}TEXTURE_B;

static const TEXTURE_B g_aTexture_b[] = 
{
	{ "data/texture/kribo.png" },
	{ "data/texture/green_shell.png" },
	{ "data/texture/dossun.png" }
};

class CBillboard {
public:
	static bool InitBillboard();
	static void UninitBillboard();
	static void UpdateBillboard();
	static void DrawBillboard();
	static bool HitPlayer();
	static int CoinHit();
private:
	static LPDIRECT3DTEXTURE9 g_pTextures_bill[TEXTURE_B_MAX];	//�e�N�X�`���z��
	static LPDIRECT3DTEXTURE9 g_pTexture;
	static D3DXMATRIX g_mtxWorld_Billboard;		//���[���h�ϊ��s��
	static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer;		// �o�[�e�b�N�X�o�b�t�@�̃|�C���^
	static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer;		// �C���f�b�N�X�o�b�t�@�̃|�C���^
	static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer2;		// �o�[�e�b�N�X�o�b�t�@�̃|�C���^
	static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer2;		// �C���f�b�N�X�o�b�t�@�̃|�C���^
	static D3DXMATRIX g_Pos;		//�ʒu�̍s��
	static void VertexBuffer_Field();
	static void IndexBuffer_Field();
	static D3DXMATRIX g_Shadow;		//�e�̃��[���h�s��
	static D3DXMATRIX g_viewInverse;
	static D3DXMATRIX g_Trans, g_Rotation;
	static D3DXVECTOR3 g_TransPos[MAX_BILLBOARD];
	static int color[MAX_BILLBOARD];
	static bool ememy[MAX_BILLBOARD];
	static int Life[MAX_BILLBOARD];
	static void VertexBuffer_Shadow2();
	static void IndexBuffer_Shadow2();
	static float  g_Rot2;
	static bool  b_dos2;
	static bool  b_dos5;
	static bool  b_dos8;
	static bool  b_dos11;
	static bool  b_dos14;
	static bool  b_dos17;
	static bool  b_kuri0;
	static bool  b_kuri3;
	static bool  b_kuri6;
	static bool  b_kuri9;
	static bool  b_kuri12;
	static bool  b_kame1;
	static bool  b_kame4;
	static bool  b_kame7;
	static bool  b_kame10;
	static bool  b_kame13;
	static bool  b_kame16;
	static int e_coin;
	static bool b_hit;
	static int dos_count;
};
#endif //_BILLBOARD_H_