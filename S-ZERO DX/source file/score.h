//-----------------------------------//
//----ƒXƒRƒA•`‰æˆ—------[score.h]--//
//-----------------------------------//
//------Author:Â‹{ —C‹G-------------//
//-----------------------------------//
#ifndef _SCORE_H_
#define _SCORE_H_
#include"number.h"

class CScore 
{
private:
	static CNumber *m_Number;

public:
	void DrawScore(int score, int dig, float x, float y, bool bZero);
};



#endif // _SCORE_H_