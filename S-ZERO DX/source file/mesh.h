//-----------------------------------//
//-------���b�V���t�B�[���h����------//
//---------------[mesh.h]------------//
//------Author:�{ �C�G-------------//
//-----------------------------------//
#ifndef _MESH_H_
#define _MESH_H_

#include <d3d9.h>
#include <d3dx9.h>

class CField
{
private:
	typedef struct
	{
		D3DXVECTOR3 Pos;//���W
		D3DXVECTOR3 Normal;//�@��
		D3DCOLOR color;	//�J���[
		D3DXVECTOR2 texcoord;
	}VERTEX3D;

	VERTEX3D* pV;

	static D3DXMATRIX m_mtxView;//�r���[�s��
	static D3DXMATRIX m_mtxProj;//�v���W�F�N�V�����s��

	static int m_nVertexNum;
	static int m_nPrimitiveNum;
	static int m_nIndexNum;

	static D3DXMATRIX m_mtxMove;//���s�ړ��s��

	VERTEX3D* m_pVertex;
	WORD* m_pIndex;

	static LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
	static LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;

	static D3DXMATRIX mtxWorld[5];

	static D3DXMATRIX m_mtxRotX;//X��]�s��
	static D3DXMATRIX m_mtxRotZ;//Z��]�s��

	D3DXVECTOR3 vx;
	D3DXVECTOR3 vz;
	D3DXVECTOR3 nx;
	D3DXVECTOR3 nz;
	D3DXVECTOR3 n;
	static LPDIRECT3DDEVICE9 m_Device;
	static LPDIRECT3DTEXTURE9 m_Texture;

public:
	void CreateMeshfield(float width, int divNum);
	void DestroyMeshfield(void);
	float GetHeight(D3DXVECTOR3 position);
	void DrawMeshfield(void);
};
#endif