//-----------------------------------//
//-----���[�h�����������-----------//
//--------[mode_operation.h]------//
//------Author:�{ �C�G-------------//
//-----------------------------------//
#ifndef _MODEOPERATION_H_
#define _MODEOPERATION_H_
#include "mode.h"

class CModeOperation :public CMode
{
private:
	static int wall_xy ;
	static int FadeOpCount ;
	static int OpIn;
	static bool g_bGogame;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};
#endif 
