//-----------------------------------//
//--マネージャー処理---[manager.h]---//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "main.h"
#include"camera.h"
#include"input.h"
#include"light.h"
#include "mode_game.h"
class CManager
{
private:
	static Light *m_Light;
	static CScene *m_Scene;
	static CMode *m_Mode;

public:

	static void Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	static void Uninit();
	static void Update();
	static void Draw();
	static void SetMode(CMode *Mode);
	//static CField *GetField();
};
#endif 
