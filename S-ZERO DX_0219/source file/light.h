//----------------------------------///
//------------ÉâÉCÉgèàóù-------------//
//------------[light.h]------------//
//------Author:é¬ã{ óCãG-------------//
//-----------------------------------//
#ifndef _LIGHT_H_
#define _LIGHT_H_
#include "main.h"

class Light
{
public:
	Light();
	~Light();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Release();
private:
	LPDIRECT3DDEVICE9 m_Device;
	D3DMATERIAL9 mat;
	D3DLIGHT9 light;
	
};
#endif 
