//----------------------------------//
//-------ÉXÉeÅ[ÉW3Dèàóù-------------//
//----[3d_stage_gimic.h]------------//
//------Author:é¬ã{ óCãG------------//
//----------------------------------//
#ifndef _3DSTAGE_H_
#define _3DSTAGE_H_
#include "main.h"
#include "scene.h"
#include "camera.h"
#include "light.h"

class CStageGimic :public CScene
{
private:
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;
	D3DXMATRIX m_mtxWorld;
	Light *C_light;

public:
	static CStageGimic *Create();
	CStageGimic();
	~CStageGimic();
	virtual void Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
};
#endif