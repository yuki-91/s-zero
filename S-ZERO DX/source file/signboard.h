//-----------------------------------//
//----------ä≈î¬èàóù------------------//
//-------[signboard.h]--------------//
//------Author:é¬ã{ óCãG-------------//
//-----------------------------------//
#ifndef _SIGNBOARD_H_
#define _SIGNBOARD_H_
#include "main.h"
#include "camera.h"
#include "light.h"
#include "scene.h"
#define MAX_SIGNBOARD (2)	

class CSingnBoard :public CScene
{
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer2;
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;
	D3DXMATRIX m_mtxWorld;
	D3DXVECTOR3 mp_Position[MAX_SIGNBOARD];
	LPDIRECT3DTEXTURE9 m_Texture2;
public:
	static CSingnBoard *Create();
	CSingnBoard();
	~CSingnBoard();
	virtual void Init();//âºëzä÷êî
	virtual void Uninit();//èÉêàâºëzä÷êî
	virtual void Update();
	virtual void Draw();
};
#endif 
