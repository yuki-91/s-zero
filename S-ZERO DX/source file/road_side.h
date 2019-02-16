//-----------------------------------//
//------���[�h�T�C�h����---------------//
//-------[roadside.h]--------------//
//------Author:�{ �C�G-------------//
//-----------------------------------//
#ifndef _ROADSIDE_H_
#define _ROADSIDE_H_
#include "main.h"
#include "camera.h"
#include "light.h"
#include "scene.h"
#define MAX_ROADSIDE (23)	//�r���{�[�h�̌�

class CRoadSide3D :public CScene
{
private:
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;
	D3DXMATRIX m_mtxWorld;
	D3DXVECTOR3 mp_Position[MAX_ROADSIDE];
public:
	static CRoadSide3D *Create();
	CRoadSide3D();
	~CRoadSide3D();
	virtual void Init();//���z�֐�
	virtual void Uninit();//�������z�֐�
	virtual void Update();
	virtual void Draw();
};
#endif 
