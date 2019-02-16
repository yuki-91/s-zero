//-----------------------------------//
//�W�����v�{�[�h���o�[�X����-[jump_board_reveres.h]-//
//-----------------------------------//
//------Author:�{ �C�G-------------//
//-----------------------------------//
#ifndef _JUMP_REVERESEBOARD_H_
#define _JUMP_REVERESEBOARD_H_
#include "main.h"

// ���_����(1�ځF���W�A2�ځF�J���[,3�ځF�e�N�X�`���[)

#define MAX_JUMP_REVERESE (4)	//�r���{�[�h�̌�

enum TEXTURE_JUMP_REVERESE_ENUM
{
	TEXTURE_JUMP_REVERESE_NULL = -1,
	TEXTURE_JUMP_REVERESE_BOARD,
	TEXTURE_JUMP_REVERESE_MAX
};

typedef struct
{
	char fileName[256];
}TEXTURE_JUMP_REVERESE;

static const TEXTURE_JUMP_REVERESE g_aTexture_k[] =
{
	{ "data/texture/jumpdai2.png" },
};
class CJump_Reverse {
public:
	static bool Initjump();
	static void Uninitjump();
	static void Updatejump();
	static void Drawjump();
	static bool HitPlayer();
private:
	static LPDIRECT3DTEXTURE9 g_pTextures_dash[TEXTURE_JUMP_REVERESE_MAX];	//�e�N�X�`���z��
	static D3DXMATRIX g_mtxWorld_jump;		//���[���h�ϊ��s��
	static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer;		// �o�[�e�b�N�X�o�b�t�@�̃|�C���^
	static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer;		// �C���f�b�N�X�o�b�t�@�̃|�C���^
	static void VertexBuffer_Field();
	static void IndexBuffer_Field();
	static D3DXMATRIX g_viewInverse;
	static D3DXMATRIX g_Trans, g_Rotation;
	static D3DXVECTOR3 g_TransPos3[MAX_JUMP_REVERESE];
	static int color[MAX_JUMP_REVERESE];
	static bool ememy[MAX_JUMP_REVERESE];
	static int Life[MAX_JUMP_REVERESE];
	static float  g_Rot5;
	static bool b_dash;
	static int jump_count;

};
#endif 