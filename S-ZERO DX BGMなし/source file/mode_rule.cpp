//-----------------------------------//
//----ƒ‚[ƒhƒ‹[ƒ‹à–¾ˆ—-----------//
//------[mode_rule.cpp]--------------//
//------Author:ŽÂ‹{ —C‹G-------------//
//-----------------------------------//
#include "mode_rule.h"
#include "myInput.h"
#include "Polygon.h"
#include "main.h"
#include "manager.h"
#include "input.h"
#include "mode_game.h"
#include "sound.h"
#include "fade.h"
#include "mode_operation.h"
int CModeRule::wall_xy;
int CModeRule::FadeRuCount = 0;
int CModeRule::RuIn = 0;
bool CModeRule::g_bGoRu = false;


void CModeRule::Init()
{
	FadeRuCount = 0;
	RuIn = 0;
	g_bGoRu = false;
}

void CModeRule::Uninit()
{
}

void CModeRule::Update()
{
	if (RuIn >= 255)
	{
		if (MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_A) || MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_B) || MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_START) || GetKeyboardTrigger(DIK_SPACE))
		{
			PlaySound(SOUND_LABEL_BUTTON);
			g_bGoRu = true;

		}
	}
	RuIn += 5;
	wall_xy++;
	if (wall_xy > 4000)
	{
		wall_xy = 0;
	}
}

void CModeRule::Draw()
{
	CPolygon::PolygonDraw2(14, D3DCOLOR_RGBA(255, 255, 255, 255), -wall_xy * 0.5, -wall_xy * 0.5, 10000, 10000, 114, 150, 0, 0, 10000, 10000);
	CPolygon::PolygonDraw2(23, D3DCOLOR_RGBA(255, 255, 255, 255), 0, 0, 1366, 768, 1366, 768, 0, 0, 1366, 768);

	if (RuIn < 255)
	{
		CFade::CreateFade(RuIn, false, false);
	}

	//ƒQ[ƒ€‚Ö
	if (g_bGoRu == true)
	{

		if (FadeRuCount>255)
		{
			CFade::CreateFade(255, true, false);
			CManager::SetMode(new CModeOperation());
		}
		else
		{
			CFade::CreateFade(FadeRuCount, true, false);
		}

		FadeRuCount += 5;

	}
}
