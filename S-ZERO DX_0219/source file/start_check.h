//-----------------------------------//
//-------スタートチェック処理--------//
//----[start_check.h]--------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#ifndef _STARTCHECK_H_
#define _STARTCHECK_H_
#include "main.h"
#include "scene.h"
#include "camera.h"
#include "light.h"

class CScene3D :public CScene
{
private:
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;
	D3DXMATRIX m_mtxWorld;
	Light *C_light;

public:
	static CScene3D *Create();
	CScene3D();
	~CScene3D();
	virtual void Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
};
#endif 
