//-----------------------------------//
//----�R�C������---------[coin.cpp]--//
//-----------------------------------//
//------Author:�{ �C�G-------------//
//-----------------------------------//
#ifndef _COIN_H_
#define _COIN_H_
#include "main.h"


// ���_����(1�ځF���W�A2�ځF�J���[,3�ځF�e�N�X�`���[)

#define MAX_COIN (24)	//�r���{�[�h�̌�

enum TEXTURE_COIN_ENUM
{
	TEXTURE_COIN_NULL = -1,
	TEXTURE_COIN1,
	TEXTURE_COIN_MAX
};

typedef struct
{
	char fileName[256];
}TEXTURE_COIN;

static const TEXTURE_COIN g_aTexture_co[] =
{
	{ "data/texture/coin.png" }
};


class CCoin {
public:
	static bool InitCoin();
	static void UninitCoin();
	static void UpdateCoin();
	static void DrawCoin();
	static int ScoreCoin();
private:
	static LPDIRECT3DTEXTURE9 g_pTextures_coin[TEXTURE_COIN_MAX] ;	//�e�N�X�`���z��
	static D3DXMATRIX g_mtxWorld_Coin;		//���[���h�ϊ��s��
	static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer;		// �o�[�e�b�N�X�o�b�t�@�̃|�C���^
	static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer;		// �C���f�b�N�X�o�b�t�@�̃|�C���^
	static void VertexBuffer_Field();
	static void IndexBuffer_Field();
	static D3DXMATRIX g_viewInverse;
	static D3DXMATRIX g_Trans, g_Rotation;
	static D3DXVECTOR3 g_TransPosC[MAX_COIN];
	static int color[MAX_COIN];
	static bool ememy[MAX_COIN];
	static int Life[MAX_COIN];
	static float  g_Rot7;
	static int score;

};
#endif 