//-----------------------------------//
//----ƒ‚[ƒhƒ‹[ƒ‹à–¾ˆ—-----------//
//------[mode_rule.h]--------------//
//------Author:Â‹{ —C‹G-------------//
//-----------------------------------//
#ifndef _MODERULE_H_
#define _MODERULE_H_
#include "mode.h"

class CModeRule :public CMode
{
private:
	static int FadeRuCount;
	static int RuIn;
	static bool g_bGoRu;
	static int wall_xy;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};
#endif 
