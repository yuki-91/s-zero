//-----------------------------------//
//------�V���h�E����-[EnemyShadow.h]-//
//-----------------------------------//
//------Author:�{ �C�G-------------//
//-----------------------------------//
#ifndef _ENEMYSHADOW_H_
#define _ENEMYSHADOW_H_
#include "main.h"

#define MAX_SHADOW (1)	//�r���{�[�h�̌�

class CShadow {
public:
	static bool InitShadow();
	static void UninitShadow();
	static void UpdateShadow();
	static void DrawShadow();
private:
	static LPDIRECT3DTEXTURE9 g_pTexture2;
	static D3DXMATRIX g_mtxWorld_Shadow;		//���[���h�ϊ��s��
	static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer2;		// �o�[�e�b�N�X�o�b�t�@�̃|�C���^
	static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer2;		// �C���f�b�N�X�o�b�t�@�̃|�C���^
	static D3DXMATRIX g_Pos;		//�ʒu�̍s��
	static D3DXMATRIX g_Shadow;		//�e�̃��[���h�s��
	static D3DXMATRIX g_viewInverse;
	static D3DXMATRIX g_Trans, g_Rotation;
	static D3DXVECTOR3 g_TransPos[MAX_SHADOW];
	static int color[MAX_SHADOW];
	static bool ememy[MAX_SHADOW];
	static int Life[MAX_SHADOW];
	static void CreateShadow2();
	static void VertexBuffer_Shadow2();
	static void IndexBuffer_Shadow2();
};
#endif 