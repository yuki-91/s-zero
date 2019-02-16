//-----------------------------------//
//----------�Ŕ���------------------//
//-------[signboard.h]--------------//
//------Author:�{ �C�G-------------//
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
	virtual void Init();//���z�֐�
	virtual void Uninit();//�������z�֐�
	virtual void Update();
	virtual void Draw();
};
#endif 
