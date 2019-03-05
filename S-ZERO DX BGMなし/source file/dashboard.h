//-----------------------------------//
//�_�b�V���{�[�h����-[dashboard.h]-//
//-----------------------------------//
//------Author:�{ �C�G-------------//
//-----------------------------------//
#ifndef _DASHBOARD_H_
#define _DASHBOARD_H_
#include "main.h"

// ���_����(1�ځF���W�A2�ځF�J���[,3�ځF�e�N�X�`���[)

#define MAX_DASH (12)	//�r���{�[�h�̌�

enum TEXTURE_DASH_ENUM
{
	TEXTURE_DASH_NULL = -1,
	TEXTURE_DASH_BOARD1,
	TEXTURE_DASH_BOARD2,
	TEXTURE_DASH_MAX
};

typedef struct
{
	char fileName[256];
}TEXTURE_DASH;

static const TEXTURE_DASH g_aTexture_d[] =
{
	{ "data/texture/dash.png" },
	{ "data/texture/dash3.png" },
};
class CDash {
public:
	static bool InitItem();
	static void UninitItem();
	static void UpdateItem();
	static void DrawItem();
	static bool HitPlayer();
private:
	static LPDIRECT3DTEXTURE9 g_pTextures_dash[TEXTURE_DASH_MAX];	//�e�N�X�`���z��
	static D3DXMATRIX g_mtxWorld_Item;		//���[���h�ϊ��s��
	static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer;		// �o�[�e�b�N�X�o�b�t�@�̃|�C���^
	static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer;		// �C���f�b�N�X�o�b�t�@�̃|�C���^
	static void VertexBuffer_Field();
	static void IndexBuffer_Field();
	static D3DXMATRIX g_viewInverse;
	static D3DXMATRIX g_Trans, g_Rotation;
	static D3DXVECTOR3 g_TransPos3[MAX_DASH];
	static int color[MAX_DASH];
	static bool ememy[MAX_DASH];
	static int Life[MAX_DASH];
	static float  g_Rot5;
	static bool b_dash;
};
#endif 