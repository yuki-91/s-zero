//-----------------------------------//
//----------エフェクト処理---------------//
//----------[effect.h]--------------//
//------Author:篠宮 佑季-------------//
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
	virtual void Init() {};//仮想関数
	virtual void Uninit() = 0;//純粋仮想関数
	virtual void Update() = 0;
	virtual void Draw() = 0;
	
};
#endif 
