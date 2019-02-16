//-----------------------------------//
//----“–‚½‚è”»’èˆ—-[hit.h]---------//
//-----------------------------------//
//------Author:Â‹{ —C‹G-------------//
//-----------------------------------//
#ifndef _JUDGENEMY_H_
#define _JUDGENEMY_H_

class CHit {
public:
	static bool HitCircle(float x0, float y0, float z0, float r0, float x1, float y1, float z1, float r1);

	static bool AABB(D3DXVECTOR3 Amin, D3DXVECTOR3 Amax, D3DXVECTOR3 Bmin, D3DXVECTOR3 Bmax);
	
	static bool ColorHIt(int colorA, int colorB);
};
#endif