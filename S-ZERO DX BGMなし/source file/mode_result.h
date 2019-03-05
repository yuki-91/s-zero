//-----------------------------------//
//--モードリザルト説明処理-----------//
//------[mode_result.h]------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#ifndef _MODERESULT_H_
#define _MODERESULT_H_
#include "mode.h"
#include "main.h"


class CModeResult :public CMode
{
private:

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};
#endif 

