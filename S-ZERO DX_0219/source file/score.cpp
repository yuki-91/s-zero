//-----------------------------------//
//----�X�R�A�`�揈��-----[score.cpp]-//
//-----------------------------------//
//------Author:�{ �C�G-------------//
//-----------------------------------//
#define _CRT_SECURE_NO_WARNINGS
#include<windows.h>
#include<stdio.h>
#include<string.h>
#include"number.h"
#include"score.h"


CNumber *CScore::m_Number;

//----------------------------------//
//----------�X�R�A�`�揈��--------//
//----------------------------------//
void CScore::DrawScore(int score,int dig, float x, float y, bool bZero)
{
	char buf[256];

	if(dig<= 0){
		sprintf(buf,"%d",score);
		dig = strlen(buf);
	}
	else {
		int maxScore = 9;
		int pow10 = 10;
		for(int i = 1; i <  dig; i++){

			maxScore += 9 * pow10;
			pow10 *= 10;
	}
		maxScore +=9;

		score = min(score,maxScore);


	}
	//score == 1234567
	for(int i = dig -1 ; i>=0;i--) {
		int n = score % 10;
		m_Number = new CNumber();	//�C���X�^���X����
		m_Number->DrawNumber(n, x + (float)NUMBER_WIDTH * (float)i, y);
		score /= 10;
		if(bZero && score == 0 )
		{
			return;
		}
		//int n = score��10�Ŋ������]��
	}

}