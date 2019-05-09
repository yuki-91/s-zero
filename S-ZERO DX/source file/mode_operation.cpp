//-----------------------------------//
//-----ƒ‚[ƒh‘€ìà–¾ˆ—-----------//
//--------[mode_operation.cpp]------//
//------Author:ŽÂ‹{ —C‹G-------------//
//-----------------------------------//
#include "mode_operation.h"
#include "myInput.h"
#include "Polygon.h"
#include "main.h"
#include "manager.h"
#include "input.h"
#include "mode_game.h"
#include "sound.h"
#include "fade.h"

int CModeOperation::wall_xy;
int CModeOperation::FadeOpCount = 0;
int CModeOperation::OpIn = 0;
bool CModeOperation::g_bGogame = false;

void CModeOperation::Init()
{
	FadeOpCount = 0;
	OpIn = 0;
	g_bGogame = false;

}

void CModeOperation::Uninit()
{

}

void CModeOperation::Update()
{
	if (OpIn >= 255)
	{
		if (MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_A) || MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_B) || MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_START) || GetKeyboardTrigger(DIK_SPACE))
		{
			PlaySound(SOUND_LABEL_BUTTON);
			g_bGogame = true;

		}
	}
	OpIn += 5;

	wall_xy++;
	if (wall_xy > 4000)
	{
		wall_xy = 0;
	}
}

void CModeOperation::Draw()
{
	CPolygon::PolygonDraw2(14, D3DCOLOR_RGBA(255, 255, 255, 255), -wall_xy * 0.5, -wall_xy * 0.5, 10000, 10000, 114, 150, 0, 0, 10000, 10000);
	CPolygon::PolygonDraw2(32, D3DCOLOR_RGBA(255, 255, 255, 255), 0, 0, 1366, 768, 1366, 768, 0, 0, 1366, 768);

	if (OpIn < 255)
	{
		CFade::CreateFade(OpIn, false, false);
	}

	//ƒQ[ƒ€‚Ö
	if (g_bGogame == true)
	{

		if (FadeOpCount>255)
		{
			CFade::CreateFade(255, true, false);
			CManager::SetMode(new CModeGame());
		}
		else
		{
			CFade::CreateFade(FadeOpCount, true, false);
		}

		FadeOpCount += 5;

	}
}
