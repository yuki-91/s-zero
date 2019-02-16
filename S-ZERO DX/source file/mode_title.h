//-----------------------------------//
//----モードタイトル処理-----------//
//------------[title.h]--------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#ifndef _TITLE_H_
#define _TITLE_H_
#include "mode.h"

class CModeTitle :public CMode
{
private:
	static int count;
	static int wall_xy;
	static int FadeTitleCount;
	static int TitleIn ;
	static bool g_bGoOp;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};
#endif 

