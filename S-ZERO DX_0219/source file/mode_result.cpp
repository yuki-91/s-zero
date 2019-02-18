//-----------------------------------//
//--ƒ‚[ƒhƒŠƒUƒ‹ƒgà–¾ˆ—-----------//
//------------[mode_result.cpp]------//
//------Author:Â‹{ —C‹G-------------//
//-----------------------------------//
#include "mode_result.h"
#include "mode_title.h"
#include "manager.h"
#include "input.h"
#include "mode_ranking.h"
#include "Polygon.h"
void CModeResult::Init()
{

}

void CModeResult::Uninit()
{
}

void CModeResult::Update()
{
	if (GetKeyboardPress(DIK_T))
	{
		CManager::SetMode(new CModeRanking());
	}
}

void CModeResult::Draw()
{
	CPolygon::PolygonDraw2(3, D3DCOLOR_RGBA(255, 255, 255, 255), 0, 0, 1366, 768, 1366, 768, 0, 0, 1366, 768);
}
