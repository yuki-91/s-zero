//-----------------------------------//
//----------�G�t�F�N�g����---------------//
//----------[effect.h]--------------//
//------Author:�{ �C�G-------------//
//-----------------------------------//
#ifndef _EFFECT_H_
#define _EFFECT_H_
#include "main.h"
#include <d3d9.h>
#include <d3dx9.h> 

class CEffect
{
public:
	CEffect();
	virtual ~CEffect();
	virtual void Init() {};//���z�֐�
	virtual void Uninit() = 0;//�������z�֐�
	virtual void Update() = 0;
	virtual void Draw() = 0;
	
};
#endif 
