//-----------------------------------//
//----ÉÇÅ[ÉhÉ^ÉCÉgÉãèàóù-----------//
//-----------[title.cpp]--------------//
//------Author:é¬ã{ óCãG-------------//
//-----------------------------------//

#include "mode_title.h"
#include "myInput.h"
#include "Polygon.h"
#include "main.h"
#include "manager.h"
#include "input.h"
#include "mode_game.h"
#include "sound.h"
#include "fade.h"
#include "mode_operation.h"
#include "mode_rule.h"
#include "player.h"
#include "renderer.h"
Camera *CModeTitle::m_camera_t;
static Camera *m_camera_t;
int CModeTitle::count = 0;
int CModeTitle::wall_xy = 0;
int CModeTitle::FadeTitleCount = 0;
int CModeTitle::TitleIn = 0;
bool CModeTitle::g_bGoOp = false;
bool CModeTitle::b_opening_rot = false;

void CModeTitle::Init()
{
	b_opening_rot = true;
	Camera::Init();
	TitleIn = 0;
	FadeTitleCount = 0;
	g_bGoOp = false;
}

void CModeTitle::Uninit()
{
	b_opening_rot = false;
	m_camera_t->Release();
}

void CModeTitle::Update()
{
	b_opening_rot = true;
	Camera::Update();
	CX_model::Update();
	if (TitleIn >= 255)
	{
		if (MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_A)|| MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_B) || MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_START) ||GetKeyboardTrigger(DIK_SPACE))
		{
			b_opening_rot = false;
			PlaySound(SOUND_LABEL_BUTTON);
			g_bGoOp = true;
		
		}
	}
	//ÉQÅ[ÉÄÇ÷

	count++;
	if (count < 100)
	{
		count++;
	}
	wall_xy++;

	if (wall_xy > 4000)
	{
		wall_xy = 0;
	}
	
}

void CModeTitle::Draw()
{

	LPDIRECT3DDEVICE9 pD3DDevice = CRender::GetD3DDevice();


	pD3DDevice->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	CPolygon::PolygonDraw2(2, D3DCOLOR_RGBA(255, 255, 255, 255), 0, 0, 1366, 768, 1366, 768, 0, 0, 1366, 768);
	CPolygon::PolygonDraw2(14, D3DCOLOR_RGBA(255, 255, 255, 255), -wall_xy * 0.5, -wall_xy * 0.5, 10000, 10000, 114, 150, 0, 0, 10000, 10000);
	CPolygon::PolygonDraw2(19, D3DCOLOR_RGBA(255, 255, 255, count*3), 290, 540, 737, 187, 737, 187, 0, 0, 737, 187);
	CPolygon::PolygonDraw2(21, D3DCOLOR_RGBA(255, 255, 255, 255), 150, 40, 837, 287, 837, 287, 0, 0, 837, 287);
	CPolygon::PolygonDraw2(22, D3DCOLOR_RGBA(255, 255, 255, 255), 1000, 40, 337, 287, 337, 287, 0, 0, 337, 287);
	Camera::Draw();
	CX_model::Draw();
	if (TitleIn < 255)
	{
		TitleIn += 5;
		CFade::CreateFade(TitleIn, false, false);
	}

	if (g_bGoOp == true)
	{

		if (FadeTitleCount>255)
		{
			CFade::CreateFade(255, true, false);
			CManager::SetMode(new CModeRule());
		}
		else
		{
			CFade::CreateFade(FadeTitleCount, true, false);
		}

		FadeTitleCount += 5;

	}
	
}

bool CModeTitle::Get_opening_rot()
{
	return b_opening_rot;
}