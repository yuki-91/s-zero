//-----------------------------------//
//--------ÉÇÅ[ÉhÉQÅ[ÉÄèàóù-----------//
//----------[mode_game.h]----------//
//------Author:é¬ã{ óCãG-------------//
//-----------------------------------//
#ifndef _MODEGAME_H_
#define _MODEGAME_H_
#include "mode.h"
#include "main.h"
#include"camera.h"
#include"input.h"
#include"light.h"
#include "mesh.h"
#include "score.h"


class CModeGame :public CMode
{

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	static CField *GetField();
	static bool GetUse();
	static int GetDash();
	static int GetKinoko();
	static bool Gethatena();
	static bool Getkinoko_X();
	static bool Getkinoko1_X();
	static bool Getkinoko2_X();
	static bool Getkinoko3_X();
	static bool Get_Pw_kinoko_X();
	static bool Getcoin_X();
	static bool Getstar_X();
	static int  SougouScore();
	static int GOAL();
	static bool Hatena_Bgm();

private:
	static CField *m_Field;
	static CScore *m_Score;
	static Camera *m_camera;

	static float score;
	static float time;
	static float time2;
	static float time3;
	static bool TargetPoint;
	static bool TargetPoint2;
	static bool TargetPoint3;
	static bool TargetPoint4;
	static int Lap;
	static bool use;
	static int ModelLife;
	static bool bCount0;
	static bool bCount1;
	static bool bCount2;
	static bool bCount3;
	static bool startTime ;
	static bool dash ;
	static int color;
	static int item_count;
	static int hatena_a;
	static int kinoko_a;
	static int kinoko2_a;
	static int kinoko3_a;
	static int p_kinoko_a;
	static int green__shell_a;
	static int star_a;
	static int coin_a;
	static int Dtime;
	static int Dtime2;
	static int Dtime3;
	static bool b_kinoko_x;
	static bool b_kinoko1_x;
	static bool b_kinoko2_x;
	static bool b_kinoko3_x;
	static bool b_pw_kinoko_x;
	static bool b_coin_x;
	static bool b_star_x;
	static bool b_green_shell;
	static bool hatenafal;
	static bool itemget;
	static int result ;
	static bool rap ;
	static int onetime;
	static int twotime;
	static int threetime;
	static float jugemu;
	static bool jug;
	static float jug2;
	static float jug_last_y;
	static float x_map;
	static float z_map;
	static int lastlap;
	static int item_rand;
	static bool hatena_bgm;
	static int OpIn;
	static int FadeOpCount;
};
#endif 





