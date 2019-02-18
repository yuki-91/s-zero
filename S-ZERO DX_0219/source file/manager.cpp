//-----------------------------------//
//--マネージャー処理---[manager.cpp]---//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "Enemy.h"
#include "player.h"
#include "mode_title.h"
#include "mode_game.h"
#include "mode_ranking.h"
#include "sound.h"
#include "myInput.h"
#include "EnemyShadow.h"
#include "dash_effect.h"
#include "smoke_effect.h"
#include "drifting_effect.h"
#include "kasoku_effect.h"
#include "gate.h"
#include "start_effect.h"
#include "start_check.h"
#include"sky_box.h"
#include "mesh.h"
#include "Polygon.h"
#include "number.h"
#include "score.h"
#include "mode.h"
#include "Explosion.h"
#include "tree_bill.h"
#include "item_box.h"
#include "road.h"
#include "road_side.h"
#include "road_curve.h"
#include "dashboard.h"
#include "dashboard_side.h"
#include "coin.h"
#include "coin_effect.h"
#include "fade.h"
#include "itembox_effect.h"
#include "3d_stagegimic.h"
#include "field_3d.h"
#include "signboard.h"
#include "star_effect.h"
#include "jump_board.h"
#include "jump_effect.h"
#include "jump_board_reverse.h"
#include "green_shell.h"
#include "drifting_effect_mini.h"

Light *CManager::m_Light;
CScene *CManager::m_Scene;
CMode *CManager::m_Mode;


MyInputKeyboard *Keyboard = NULL;
MyInputGamepad  *Gamepad = NULL;

void CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	CRender::Init(hInstance, hWnd, bWindow);

	InitSound(hWnd);
	m_Light = new Light();	//インスタンス生成
	m_Light->Init();
	InitKeyboard(hInstance, hWnd);

	Keyboard = new MyInputKeyboard();
	Gamepad = new MyInputGamepad();

	Keyboard->Initialize(hInstance, hWnd);
	Gamepad->Initialize();

	CPolygon::PolygonInit2();
	CFade::InitFade();
	CGate::InitGate();
	CXmodel::Create();
	CBillboard::InitBillboard();
	CShadow::InitShadow();
	CTreeBill::InitTreeBill();
	CItem::InitItem();
	CCoin::InitCoin();
	CJump::Initjump();
	CJump_Reverse::Initjump();
	CDash::InitItem();
	CDashSide::InitItem();
	CScene3D::Create();
	CStageGimic::Create();
	CRoad3D::Create();
	CRoadSide3D::Create();
	CRoadFIield::Create();
	CRoadCurveD::Create();
	CSingnBoard::Create();
	CX_model::Create();
	InitBullet();
	CExplosion::InitExplosion();
	CDashEffect::Initdash_effect();
	CSmokeEffect::Initsmoke_explosion();
	CDriftingEffect::InitDrifting_effect();
	CDrifting_MEffect::InitDrifting_M_effect();
	CStEffect::InitStart_effect();
	CKasokuEffect::InitKasoku_effect();
	CCoinEffect::InitCoin_Effect();
	CItemBoxEffect::InitItembox_Effect();
	CStarEffect::InitStar_effect();
	CJumpEffect::InitJump_Effect();
	CManager::SetMode(new CModeTitle());
}

void CManager::Uninit()
{
	StopSound();
	
	UninitSound();
	UninitKeyboard();
	MyInputGamepad::Uninitialize();
	m_Light->Release();
	CPolygon::PolygonUninit2();
	CFade::UninitFade();
	m_Mode->Uninit();
	CExplosion::UninitExplosion();
	CDashEffect::Uninitdash_effect();
	CSmokeEffect::Uninitsmoke_explosion();
	CDriftingEffect::UninitDrifting_effect();
	CDrifting_MEffect::UninitDrifting_M_effect();
	CStEffect::UninitStart_effect();
	CKasokuEffect::UninitKasoku_effect();
	CCoinEffect::UninitCoin_Effect();
	CItemBoxEffect::UninitItembox_Effect();
	CJumpEffect::UninitJump_Effect();
	CStarEffect::UninitStar_effect();
	CBillboard::UninitBillboard();
	CShadow::UninitShadow();
	CTreeBill::UninitTreeBill();
	CItem::UninitItem();
	CCoin::UninitCoin();
	CJump::Uninitjump();
	CJump_Reverse::Uninitjump();
	UninitBullet();
	CDash::UninitItem();
	CDashSide::UninitItem();
	CScene::UninitAll();
	CX_model::Uninit();
	CXmodel::Uninit();
	CGate::UninitGate();
	m_Scene->Release();
	CScene::UninitAll();
	Keyboard->Uninitialize();
	Gamepad->Uninitialize();

	delete Keyboard;
	delete Gamepad;

	CRender::Uninit();
}

void CManager::Update()
{
	
	UpdateKeyboard();
	Keyboard->Update();
	Gamepad->Update();
	m_Light->Update();
	CScene::UpdateAll();
	m_Mode->Update();
}

void CManager::Draw()
{
	CRender::DrawBegin();
	m_Light->Draw();

	CScene::DrawAll();
	
	m_Mode->Draw();

	CRender::DrawEnd();
}



void CManager::SetMode(CMode *Mode)
{
	if (m_Mode != NULL)
	{
		m_Mode->Uninit();
		delete m_Mode;
	}
	m_Mode = Mode;

	if (m_Mode != NULL)
	{
		m_Mode->Init();
	}
}
