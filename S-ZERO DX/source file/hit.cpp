//-----------------------------------//
//----当たり判定処理-[hit.cpp]-------//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#include "main.h"
#include "hit.h"

bool CHit::HitCircle(float x0, float y0, float z0, float r0, float x1, float y1, float z1, float r1)
{
	float x = x1 - x0;
	float y = y1 - y0;
	float z = z1 - z0;
	float l = x * x + y * y + z * z;
	return l < (r0 + r1) * (r0 + r1) * (r0 + r1);
}

// Amin = Aの最小の座標　Amax = Aの最大の座標  Bmin = Bの最小の座標　Bmax = Bの最大の座標
bool CHit::AABB(D3DXVECTOR3 Amin, D3DXVECTOR3 Amax, D3DXVECTOR3 Bmin, D3DXVECTOR3 Bmax)
{
	//X軸判定
	if(Amin.x > Bmax.x)return false;
	if(Amax.x < Bmin.x)return false;

	//Y軸判定
	if(Amin.y > Bmax.y)return false;
	if(Amax.y < Bmin.y)return false;

	//Z軸判定
	if(Amin.z > Bmax.z)return false;
	if(Amax.z < Bmin.z)return false;

	return true;
}

bool CHit::ColorHIt(int colorA, int colorB)
{

	if(colorA == colorB){return true;}

	return false;
}
