//-----------------------------------//
//----モードタイトル処理-----------//
//------------[title.h]--------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#ifndef _TITLE_H_
#define _TITLE_H_
#include "mode.h"
#include "camera.h"
class CModeTitle :public CMode
{
private:
	static Camera *m_camera_t;
	static int count;
	static int wall_xy;
	static int FadeTitleCount;
	static int TitleIn ;
	static bool g_bGoOp;
	static bool b_opening_rot;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	static bool Get_opening_rot();
};
#endif 

