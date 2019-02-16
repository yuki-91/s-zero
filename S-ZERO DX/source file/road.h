//-----------------------------------//
//------ロード処理---------------//
//-------[road.h]--------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#ifndef _ROAD_H_
#define _ROAD_H_
#include "main.h"
#include "camera.h"
#include "light.h"
#include "scene.h"
#define MAX_ROAD (69)	
class CRoad3D :public CScene
{
private:
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;
	D3DXMATRIX m_mtxWorld;
	D3DXVECTOR3 mp_Position[MAX_ROAD];
public:
	static CRoad3D *Create();
	CRoad3D();
	~CRoad3D();
	virtual void Init();//仮想関数
	virtual void Uninit();//純粋仮想関数
	virtual void Update();
	virtual void Draw();
};
#endif 
