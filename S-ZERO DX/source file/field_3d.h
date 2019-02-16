//----------------------------------//
//------�t�B�[���h����-------------//
//---------[faield3d.h]------------//
//------Author:�{ �C�G------------//
//----------------------------------//
#ifndef _3DFIELD_H_
#define _3DFIELD_H_
#include "main.h"
#include "scene.h"
#include "camera.h"
#include "light.h"
#define MAX_FIELD (13)

class CRoadFIield :public CScene
{
private:
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;
	D3DXMATRIX m_mtxWorld;
	D3DXVECTOR3 mp_Position[MAX_FIELD];
public:
	static CRoadFIield *Create();
	CRoadFIield();
	~CRoadFIield();
	virtual void Init();//���z�֐�
	virtual void Uninit();//�������z�֐�
	virtual void Update();
	virtual void Draw();
};
#endif 