//-----------------------------------//
//------���[�h�J�[�u����---------------//
//-------[roadcurve.h]--------------//
//------Author:�{ �C�G-------------//
//-----------------------------------//
#ifndef _ROADCURVE_H_
#define _ROADCURVE_H_
#include "main.h"
#include "camera.h"
#include "light.h"
#include "scene.h"
#define MAX_ROADCURVE (22)	//�r���{�[�h�̌�


enum TEXTURE_CURVE_ENUM
{
	TEXTURE_CURVE_NULL = -1,
	TEXTURE_CURVE_1,
	TEXTURE_CURVE_2,
	TEXTURE_CURVE_3,
	TEXTURE_CURVE_4,
	TEXTURE_CURVE_MAX
};


typedef struct
{
	char fileName[256];
}TEXTURE_CURVE;

static const TEXTURE_CURVE g_aTexture_c[] =
{
	{ "data/texture/roadtypcar04a.png" },
	{ "data/texture/roadtypcar04d.png" },
	{ "data/texture/roadtypcar04c.png" },
	{ "data/texture/roadtypcar04.png" }
};

class CRoadCurveD :public CScene
{
private:
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;
	D3DXMATRIX m_mtxWorld;;
	D3DXVECTOR3 mp_Position[MAX_ROADCURVE];
public:
	static CRoadCurveD *Create();
	CRoadCurveD();
	~CRoadCurveD();
	virtual void Init();//���z�֐�
	virtual void Uninit();//�������z�֐�
	virtual void Update();
	virtual void Draw();
};
#endif 
