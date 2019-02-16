//-----------------------------------//
//------ロードサイド処理---------------//
//-------[roadside.h]--------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#ifndef _ROADSIDE_H_
#define _ROADSIDE_H_
#include "main.h"
#include "camera.h"
#include "light.h"
#include "scene.h"
#define MAX_ROADSIDE (23)	//ビルボードの個数

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
	virtual void Init();//仮想関数
	virtual void Uninit();//純粋仮想関数
	virtual void Update();
	virtual void Draw();
};
#endif 
