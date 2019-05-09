//-----------------------------------//
//--------モードゲーム処理-----------//
//----------[mode_game.cpp]----------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#include "mode_game.h"
#include "mode.h"
#include "main.h"
#include"camera.h"
#include"input.h"
#include"light.h"
#include "start_check.h"
#include"sky_box.h"
#include "mesh.h"
#include "Polygon.h"
#include "number.h"
#include "score.h"
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "Polygon.h"
#include "Enemy.h"
#include "mode_result.h"
#include "hit.h"
#include "Explosion.h"
#include "tree_bill.h"
#include "item_box.h"
#include "road.h"
#include "road_side.h"
#include "road_curve.h"
#include "dashboard.h"
#include "dashboard_side.h"
#include "coin.h"
#include "mode_ranking.h"
#include "sound.h"
#include "EnemyShadow.h"
#include "coin_effect.h"
#include "dash_effect.h"
#include "smoke_effect.h"
#include "drifting_effect.h"
#include "start_effect.h"
#include "kasoku_effect.h"
#include "manager.h"
#include "itembox_effect.h"
#include "mode_result.h"
#include "myInput.h"
#include "star_effect.h"
#include "jump_board.h"
#include "jump_effect.h"
#include "fade.h"
#include"jump_board_reverse.h"
#include"drifting_effect_mini.h"

CField *CModeGame::m_Field;
CScore *CModeGame::m_Score;
Camera *CModeGame::m_camera;

static CField *m_Field;
static CScore *m_Score;
static Camera *m_camera;

//ラップ処理
float CModeGame::time = 6000;		//ラップタイム１週目
float CModeGame::time2 = 6000;		//ラップタイム２週目
float CModeGame::time3 = 6000;		//ラップタイム３週目
bool CModeGame::TargetPoint = false;	//ラップチェックポイント１
bool CModeGame::TargetPoint2 = false;	//ラップチェックポイント２
bool CModeGame::TargetPoint3 = false;	//ラップチェックポイント３
bool CModeGame::TargetPoint4 = false;	//ラップチェックポイント４
int CModeGame::Lap = 0;					//ラップ数カウント

//タイム処理
int CModeGame::Dtime;					//タイム管理
int CModeGame::Dtime2;					//タイム管理
int CModeGame::Dtime3;					//タイム管理
int CModeGame::onetime;					//1週目タイム
int CModeGame::twotime;					//2週目タイム
int CModeGame::threetime;				//3週目タイム
int CModeGame::result = 0;				//ランキング画面へ
bool CModeGame::rap = false;			//ラップ数カウント

//スタートカウントダウン処理
bool CModeGame::use = false;			//ゲーム開始判別
int CModeGame::ModelLife;				//カウントダウンカウント
bool CModeGame::bCount0 = false;		//カウントダウン描画
bool CModeGame::bCount1 = false;		//カウントダウン描画
bool CModeGame::bCount2 = false;		//カウントダウン描画
bool CModeGame::bCount3 = false;		//カウントダウン描画
bool CModeGame::startTime = false;		//全ラップタイム管理
bool CModeGame::dash = false;			//ロケットスタート判別

//ジュゲム処理
float CModeGame::jugemu;				//ジュゲム位置
bool CModeGame::jug;					//ジュゲム管理
float CModeGame::jug2;					//ジュゲム逆走管理
float CModeGame::jug_last_y;			//ジュゲムラスト告知
int CModeGame::lastlap = false;			//ジュゲムラスト告知タイム

float CModeGame::x_map;					//ミニマッププレイヤー位置Ｘ
float CModeGame::z_map;					//ミニマッププレイヤー位置Ｚ
int CModeGame::OpIn = 0;				//フェードイン
int CModeGame::FadeOpCount = 0;			//フェードアウト


//アイテム処理
int CModeGame::item_rand = 0;			//アイテムのランダム
int CModeGame::item_rand2 = 0;			//アイテム２のランダム
int CModeGame::color;					//はてなの色変更
int CModeGame::hatena_a = 0;			//はてな表示
int CModeGame::hatena2_a = 0;			//はてな２表示
int CModeGame::kinoko_a = 0;			//キノコ表示
int CModeGame::kinoko2_a = 0;			//ダブルキノコ表示
int CModeGame::kinoko3_a = 0;			//トリプルキノコ表示
int CModeGame::p_kinoko_a = 0;			//パワフルキノコ表示
int CModeGame::green__shell_a = 0;		//緑甲羅表示
int CModeGame::coin_a = 0;				//コイン表示
int CModeGame::star_a = 0;				//スター表示

//アイテム保留
int CModeGame::kinoko_a_keep = 0;		//キノコ表示２
int CModeGame::kinoko2_a_keep = 0;		//ダブルキノコ表示２
int CModeGame::kinoko3_a_keep = 0;		//トリプルキノコ表示２
int CModeGame::p_kinoko_a_keep = 0;		//パワフルキノコ表示２
int CModeGame::green__shell_a_keep = 0;	//緑甲羅表示２
int CModeGame::coin_a_keep = 0;			//コイン表示２
int CModeGame::star_a_keep = 0;			//スター表示２

//アイテム使用
bool CModeGame::b_kinoko_x = false;		//キノコ使用しているか
bool CModeGame::b_kinoko1_x = false;	//シングルキノコ使用しているか
bool CModeGame::b_kinoko2_x = false;	//ダブルキノコ使用しているか
bool CModeGame::b_kinoko3_x = false;	//トリプルキノコ使用しているか
bool CModeGame::b_pw_kinoko_x = false;	//パワフルキノコ使用しているか
bool CModeGame::b_green_shell = false;	//緑甲羅使用しているか
bool CModeGame::b_coin_x = false;		//コイン使用しているか
bool CModeGame::b_star_x = false;		//スター使用しているか
bool CModeGame::b_pw = false;			//パワフルダッシュキノコ使用しているか
int CModeGame::pw_dash_time = 0;		//パワフルダッシュキノコ時間

bool CModeGame::hatenafal = false;		//はてな使用しているか
bool CModeGame::hatenafal2 = false;		//はてな２使用しているか
bool CModeGame::hatena_change = false;	//はてな中
bool CModeGame::hatena_change2 = false;	//はてな2中
bool CModeGame::item_hatena_use = false; //はてな使用中か
int CModeGame::item_count = 0;			//はてなカウント
int CModeGame::item_count2 = 0;			//はてなカウント２
bool CModeGame::hatena_bgm = false;		//はてなのBGM管理
bool CModeGame::hatena_bgm2 = false;	//はてな2のBGM管理




void CModeGame::Init()
{
	PlaySound(SOUND_LABEL_START_ENGIN);
	PlaySound(SOUND_LABEL_START);
	Camera::Init();

	m_Field = new CField();	//インスタンス生成
	m_Field->CreateMeshfield(300.0f, 30);
	time = 0;
	time2 = 0;
	time3 = 0;
	use = false;
	lastlap = false;
	TargetPoint = false;
	TargetPoint2 = false;
	TargetPoint3 = false;
	TargetPoint4 = false;
	bCount0 = false;
	bCount1 = false;
	bCount2 = false;
	bCount3 = false;
	startTime = false;
	Lap = 0;
	ModelLife = -100;
	dash = false;
	color = 0;
	item_count = 0;
	item_count2 = 0;
	hatena_a = 0;
	hatena2_a = 0;
	kinoko_a = 0;
	kinoko2_a = 0;
	kinoko3_a = 0;
	p_kinoko_a = 0;
	green__shell_a = 0;
	coin_a = 0;
	star_a = 0;

	kinoko_a_keep = 0;
	kinoko2_a_keep = 0;
	kinoko3_a_keep = 0;
	p_kinoko_a_keep = 0;
	green__shell_a_keep = 0;
	coin_a_keep = 0;
	star_a_keep = 0;

	b_kinoko_x = false;
	b_kinoko1_x = false;
	b_kinoko2_x = false;
	b_kinoko3_x = false;
	b_pw_kinoko_x = false;
	b_coin_x = false;
	b_star_x = false;
	hatenafal = false;
	hatenafal2 = false;
	result = 0;
	rap = false;
	onetime = 0;
	twotime = 0;
	threetime = 0;
	jugemu = 0;
	jug = false;
	jug2 = false;
	jug_last_y = 0;
	item_rand = 0;
	item_rand2 = 0;
	OpIn = 0;
	FadeOpCount = 0;

	hatena_bgm = false;
	hatena_bgm2 = false;
	hatena_change = false;
	hatena_change2 = false;

	pw_dash_time = 0;
	b_pw = false;
	item_hatena_use = false;
}

void CModeGame::Uninit()
{
	m_camera->Release();
	StopSound();
	StopSound(SOUND_LABEL_STAR);
	StopSound(SOUND_LABEL_ITEMBOX);

}



void CModeGame::Update()
{
	Camera::Update();
	CX_model::Update();
	CXmodel::Update();
	CBillboard::UpdateBillboard();
	CShadow::UpdateShadow();
	CTreeBill::UpdateTreeBill();
	CItem::UpdateItem();
	CCoin::UpdateCoin();
	CJump::Updatejump();
	CJump_Reverse::Updatejump();
	CDash::UpdateItem();
	CDashSide::UpdateItem();
	CExplosion::UpdateExplosion();
	CDashEffect::Updatedash_effect();
	CSmokeEffect::Updatesmoke_explosion();
	CDriftingEffect::UpdateDrifting_effect();
	CDrifting_MEffect::UpdateDrifting_M_effect();
	CStEffect::UpdateStart_effect();
	CKasokuEffect::UpdateKasoku_effect();
	CCoinEffect::UpdateCoin_Effect();
	CItemBoxEffect::UpdateItembox_Effect();
	CStarEffect::UpdateStar_effect();
	CJumpEffect::UpdateJump_Effect();

	rap = false;
	OpIn += 5;
	color++;

	CModeGame::Lap_Check();

	CModeGame::Lap_Time();

	CModeGame::CountDown();

	CModeGame::UpdateJugem();

	CModeGame::Item();

	//リトライ
	if (GetKeyboardTrigger(DIK_R))
	{
		StopSound();
		StopSound(SOUND_LABEL_STAR);
		StopSound(SOUND_LABEL_START_ENGIN);
		CManager::SetMode(new CModeGame());
	}
	//強制終了
	if (GetKeyboardTrigger(DIK_E))
	{
		StopSound();
		StopSound(SOUND_LABEL_STAR);
		StopSound(SOUND_LABEL_START_ENGIN);
		CManager::SetMode(new CModeRanking());
	}


	//ミニマップ
	x_map = CX_model::XmodelPos().x;
	z_map = -CX_model::XmodelPos().z;	
}

void CModeGame::Draw()
{
	Camera::Draw();
	CX_model::Draw();
	CXmodel::Draw();
	CExplosion::DrawExplosion();
	CDashEffect::Drawdash_effect();
	CSmokeEffect::Drawsmoke_explosion();
	CDriftingEffect::DrawDrifting_effect();
	CDrifting_MEffect::DrawDrifting_M_effect();
	CStEffect::DrawStart_effect();
	CKasokuEffect::DrawKasoku_effect();
	CCoinEffect::DrawCoin_Effect();
	CItemBoxEffect::DrawItembox_Effect();
	CStarEffect::DrawStar_effect();
	CBillboard::DrawBillboard();	
	CTreeBill::DrawTreeBill();
	CJumpEffect::DrawJump_Effect();
	CItem::DrawItem();
	CCoin::DrawCoin();
	CJump::Drawjump();
	CJump_Reverse::Drawjump();
	CDash::DrawItem();
	CDashSide::DrawItem();
	m_Field->DrawMeshfield();
	CShadow::DrawShadow();


	if (OpIn < 255)
	{
		CFade::CreateFade(OpIn, false, false);
	}

	//g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),D3DCOLOR_RGBA(255,255,255,255),1.0F,0);
	m_Score->DrawScore(Dtime, 5, 100, -90, false);
	
	
	//ラップ数タイム
	if (Lap >= 1) {
		m_Score->DrawScore(onetime, 5, 100, 0, false);
		CPolygon::PolygonDraw2(4, D3DCOLOR_RGBA(255, 255, 255, 255), 0, 100, 100, 50, 100, 50, 0, 0, 100, 50);
		CPolygon::PolygonDraw2(18, D3DCOLOR_RGBA(200, 200, 200, 255), 193, 115, 80, 80, 80, 80, 0, 0, 80, 80);
	}
	if (Lap >= 2) {
		m_Score->DrawScore(twotime, 5, 100, 70, false);
		CPolygon::PolygonDraw2(5, D3DCOLOR_RGBA(255, 255, 255, 255), 0, 170, 100, 50, 100, 50, 0, 0, 100, 50);
		CPolygon::PolygonDraw2(18, D3DCOLOR_RGBA(200, 200, 200, 255), 193, 185, 80, 80, 80, 80, 0, 0, 80, 80);
	}
	if (Lap >= 3) {
		m_Score->DrawScore(threetime, 5, 100, 140, false);
		CPolygon::PolygonDraw2(6, D3DCOLOR_RGBA(255, 255, 255, 255), 0, 240, 100, 50, 100, 50, 0, 0, 100, 50);
		CPolygon::PolygonDraw2(18, D3DCOLOR_RGBA(200, 200, 200, 255), 193, 255, 80, 80, 80, 80, 0, 0, 80, 80);
	}
	//タイム
	CPolygon::PolygonDraw2(8, D3DCOLOR_RGBA(255, 255, 255, 255), 0, 20, 100, 50, 100, 50, 0, 0, 100, 50);

	CPolygon::PolygonDraw2(18, D3DCOLOR_RGBA(200, 200, 200, 255), 193, 25, 80, 80, 80, 80, 0, 0, 80, 80);

	
	//Lap数
	if (Lap == 0) {
		CPolygon::PolygonDraw2(4, D3DCOLOR_RGBA(255, 255, 255, 255), 1000, 660, 337, 107, 337, 107, 0, 0, 337, 107);
	}
	if (Lap == 1) {
		CPolygon::PolygonDraw2(5, D3DCOLOR_RGBA(255, 255, 255, 255), 1000, 660, 337, 107, 337, 107, 0, 0, 337, 107);
	}
	if (Lap == 2) {
		CPolygon::PolygonDraw2(6, D3DCOLOR_RGBA(255, 255, 255, 255), 1000, 660, 337, 107, 337, 107, 0, 0, 337, 107);
		if (lastlap <= 500) {
			CPolygon::PolygonDraw2(3, D3DCOLOR_RGBA(255, 255, 255, 255), 700, 100 + jugemu + jug_last_y, 300, 300, 300, 300, 0, 0, 300, 300);
		}
	}
	if (Lap == 3) {
		CPolygon::PolygonDraw2(7, D3DCOLOR_RGBA(255, 255, 255, 255), 390, 290, 537, 187, 537, 187, 0, 0, 537, 187);
	}
	//カウントダウン
	if (bCount3) {
		CPolygon::PolygonDraw2(9, D3DCOLOR_RGBA(255, 255, 255, 255), 570, 270, 220, 285, 220, 285, 0, 0, 220, 285);
		CPolygon::PolygonDraw2(25, D3DCOLOR_RGBA(255, 255, 255, 255), 800, 100+ jugemu, 300, 300, 300, 300, 0, 0, 300, 300);
	}
	if (bCount2) {
		CPolygon::PolygonDraw2(10, D3DCOLOR_RGBA(255, 255, 255, 255), 570, 270, 220, 285, 220, 285, 0, 0, 220, 285);
		CPolygon::PolygonDraw2(26, D3DCOLOR_RGBA(255, 255, 255, 255), 800, 100 + jugemu, 300, 300, 300, 300, 0, 0, 300, 300);
	}
	if (bCount1) {
		CPolygon::PolygonDraw2(11, D3DCOLOR_RGBA(255, 255, 255, 255), 570, 270, 220, 285, 220, 285, 0, 0, 220, 285);
		CPolygon::PolygonDraw2(27, D3DCOLOR_RGBA(255, 255, 255, 255), 800, 100 + jugemu, 300, 300, 300, 300, 0, 0, 300, 300);
	}
	if (bCount0) {
		CPolygon::PolygonDraw2(12, D3DCOLOR_RGBA(255, 255, 255, 255), 470, 290, 501, 253, 501, 253, 0, 0, 501, 253);
		CPolygon::PolygonDraw2(24, D3DCOLOR_RGBA(255, 255, 255, 255), 800.0f, 100.0f + jug2, 300.0f, 300.0f, 300, 300, 0, 0, 300, 300);
		
	}
	//コイン数
	CPolygon::PolygonDraw2(13, D3DCOLOR_RGBA(255, 255, 255, 255), 10, 660, 80, 80, 80, 80, 0, 0, 80, 80);
	m_Score->DrawScore(CCoin::ScoreCoin(), 2, 90, 575, false);

	//マップ
	CPolygon::PolygonDraw2(28, D3DCOLOR_RGBA(255, 255, 255, 255), 980, 10, 490, 320, 490, 320, 0, 0, 490, 320);

	//マップ水
	CPolygon::PolygonDraw2(20, D3DCOLOR_RGBA(255, 255, 255, 255), 1200.0f, 230.0f, 75, 75, 75, 75, 0, 0, 75, 75);

	//マップマリオ
	CPolygon::PolygonDraw2(29, D3DCOLOR_RGBA(255, 255, 255, 255), 1200.0f + x_map, 150.0f + z_map, 45, 45, 45, 45, 0, 0, 45, 45);
	
	//丸2
	CPolygon::PolygonDraw2(15, D3DCOLOR_RGBA(255, 255, 255, 255), 315, 5, 90, 90, 90, 90, 0, 0, 90, 90);
	//丸
	CPolygon::PolygonDraw2(15, D3DCOLOR_RGBA(255, 255, 255, 255), 375, 10, 200, 200, 200, 200, 0, 0, 200, 200);


	if (CItem::GetItem() == true) {
		//はてな
		CPolygon::PolygonDraw2(16, D3DCOLOR_RGBA(color *1, color *2, color *3, hatena_a), 395.0f, 30.0f, 150.0f, 150.0f, 150, 150, 0, 0, 150, 150);
	}
	
	//キノコ
	CPolygon::PolygonDraw2(17, D3DCOLOR_RGBA(255, 255, 255, kinoko_a), 395.0f, 30.0f, 150.0f, 150.0f, 150, 150, 0, 0, 150, 150);

	//トリプルダッシュキノコ
	CPolygon::PolygonDraw2(30, D3DCOLOR_RGBA(255, 255, 255, kinoko3_a), 395.0f, 30.0f, 150.0f, 150.0f, 150, 150, 0, 0, 150, 150);

	//ダブルダッシュキノコ
	CPolygon::PolygonDraw2(31, D3DCOLOR_RGBA(255, 255, 255, kinoko2_a), 395.0f, 30.0f, 150.0f, 150.0f, 150, 150, 0, 0, 150, 150);

	//コイン
	CPolygon::PolygonDraw2(13, D3DCOLOR_RGBA(255, 255, 255, coin_a), 395.0f, 30.0f, 150.0f, 150.0f, 150, 150, 0, 0, 150, 150);

	//スター
	CPolygon::PolygonDraw2(2, D3DCOLOR_RGBA(255, 255, 255, star_a), 395.0f, 30.0f, 150.0f, 150.0f, 150, 150, 0, 0, 150, 150);

	//パワフルダッシュキノコ
	CPolygon::PolygonDraw2(33, D3DCOLOR_RGBA(255, 255, 255, p_kinoko_a), 395.0f, 30.0f, 150.0f, 150.0f, 150, 150, 0, 0, 150, 150);

	//緑甲羅
	CPolygon::PolygonDraw2(34, D3DCOLOR_RGBA(255, 255, 255, green__shell_a), 395.0f, 30.0f, 150.0f, 150.0f, 150, 150, 0, 0, 150, 150);

	//保留アイテム
	if (CItem::GetItem2() == true) {
		//はてな2
		CPolygon::PolygonDraw2(16, D3DCOLOR_RGBA(color * 1, color * 2, color * 3, hatena2_a), 325.0f, 15.0f, 65.0f, 65.0f, 65.0f, 65.0f, 0, 0, 65.0f, 65.0f);
	}

	//キノコ
	CPolygon::PolygonDraw2(17, D3DCOLOR_RGBA(255, 255, 255, kinoko_a_keep), 325.0f, 15.0f, 65.0f, 65.0f, 65.0f, 65.0f, 0, 0, 65.0f, 65.0f);

	//トリプルダッシュキノコ
	CPolygon::PolygonDraw2(30, D3DCOLOR_RGBA(255, 255, 255, kinoko3_a_keep), 325.0f, 15.0f, 65.0f, 65.0f, 65.0f, 65.0f, 0, 0, 65.0f, 65.0f);

	//ダブルダッシュキノコ
	CPolygon::PolygonDraw2(31, D3DCOLOR_RGBA(255, 255, 255, kinoko2_a_keep), 325.0f, 15.0f, 65.0f, 65.0f, 65.0f, 65.0f, 0, 0, 65.0f, 65.0f);

	//コイン
	CPolygon::PolygonDraw2(13, D3DCOLOR_RGBA(255, 255, 255, coin_a_keep), 325.0f, 15.0f, 65.0f, 65.0f, 65.0f, 65.0f, 0, 0, 65.0f, 65.0f);

	//スター
	CPolygon::PolygonDraw2(2, D3DCOLOR_RGBA(255, 255, 255, star_a_keep), 325.0f, 15.0f, 65.0f, 65.0f, 65.0f, 65.0f, 0, 0, 65.0f, 65.0f);

	//パワフルダッシュキノコ
	CPolygon::PolygonDraw2(33, D3DCOLOR_RGBA(255, 255, 255, p_kinoko_a_keep), 325.0f, 15.0f, 65.0f, 65.0f, 65.0f, 65.0f, 0, 0, 65.0f, 65.0f);

	//緑甲羅
	CPolygon::PolygonDraw2(34, D3DCOLOR_RGBA(255, 255, 255, green__shell_a_keep), 325.0f, 15.0f, 65.0f, 65.0f, 65.0f, 65.0f, 0, 0, 65.0f, 65.0f);

	//逆走ジュゲム
	if (TargetPoint && !TargetPoint2 && !TargetPoint3 && TargetPoint4)
	{
		CPolygon::PolygonDraw2(1, D3DCOLOR_RGBA(255, 255, 255, 255), 500, 100 + jugemu, 300, 300, 300, 300, 0, 0, 300, 300);
	}

	//スタートジュゲム
	if (!TargetPoint2 && !TargetPoint3 && !TargetPoint &&TargetPoint4)
	{
		CPolygon::PolygonDraw2(1, D3DCOLOR_RGBA(255, 255, 255, 255), 500, 100 + jugemu, 300, 300, 300, 300, 0, 0, 300, 300);
	}

	if (!TargetPoint2 && TargetPoint3 && !TargetPoint &&TargetPoint4)
	{
		CPolygon::PolygonDraw2(1, D3DCOLOR_RGBA(255, 255, 255, 255), 500, 100 + jugemu, 300, 300, 300, 300, 0, 0, 300, 300);
	}

	if (TargetPoint && TargetPoint4 && !TargetPoint3 && TargetPoint2)
	{
		CPolygon::PolygonDraw2(1, D3DCOLOR_RGBA(255, 255, 255, 255), 500, 100 + jugemu, 300, 300, 300, 300, 0, 0, 300, 300);
	}

	if (!TargetPoint3 && TargetPoint4 && TargetPoint && !TargetPoint2)
	{
		CPolygon::PolygonDraw2(1, D3DCOLOR_RGBA(255, 255, 255, 255), 500, 100 + jugemu, 300, 300, 300, 300, 0, 0, 300, 300);
	}

	if (TargetPoint3 && TargetPoint4 && TargetPoint && !TargetPoint2)
	{
		CPolygon::PolygonDraw2(1, D3DCOLOR_RGBA(255, 255, 255, 255), 500, 100 + jugemu, 300, 300, 300, 300, 0, 0, 300, 300);
		TargetPoint = false;
		TargetPoint3 = false;
		TargetPoint4 = false;
	}

	if (!TargetPoint3 && TargetPoint4 && TargetPoint && TargetPoint2)
	{
		CPolygon::PolygonDraw2(1, D3DCOLOR_RGBA(255, 255, 255, 255), 500, 100, 300, 300, 300, 300, 0, 0, 300, 300);
		TargetPoint = false;
		TargetPoint2 = false;
		TargetPoint4 = false;
	}

	if (TargetPoint3 && TargetPoint4 && TargetPoint2 && !TargetPoint)
	{
		CPolygon::PolygonDraw2(1, D3DCOLOR_RGBA(255, 255, 255, 255), 500, 100, 300, 300, 300, 300, 0, 0, 300, 300);
		TargetPoint2 = false;
		TargetPoint3 = false;
		TargetPoint4 = false;
	}

	//ランキング画面へ
	if (result >=20) {

		StopSound(SOUND_LABEL_ITEMBOX);
		StopSound(SOUND_LABEL_STAR);
		StopSound(SOUND_LABEL_START_ENGIN);
		if (FadeOpCount>255)
		{
			CFade::CreateFade(255, true, false);
			CManager::SetMode(new CModeRanking());
		}
		else
		{
			CFade::CreateFade(FadeOpCount, true, false);
		}

		FadeOpCount += 5;
	}

}

void CModeGame::Lap_Check() {

	D3DXVECTOR3 mu = D3DXVECTOR3(6, 4, 6);

	//ラップチェックタイム当たり判定
	if (CHit::AABB(D3DXVECTOR3(-150.0f, -5.0f, 100.0f),
		D3DXVECTOR3(-100.0f, 5.0f, 150.0f),
		D3DXVECTOR3(CX_model::XmodelPos().x, CX_model::XmodelPos().y - 1, CX_model::XmodelPos().z) - mu,
		D3DXVECTOR3(CX_model::XmodelPos().x, CX_model::XmodelPos().y - 1, CX_model::XmodelPos().z) + mu))
	{
		TargetPoint = true;
	}

	if (CHit::AABB(D3DXVECTOR3(-150.0f, -5.0f, -150.0f),
		D3DXVECTOR3(-100.0f, 5.0f, -100.0f),
		D3DXVECTOR3(CX_model::XmodelPos().x, CX_model::XmodelPos().y - 1, CX_model::XmodelPos().z) - mu,
		D3DXVECTOR3(CX_model::XmodelPos().x, CX_model::XmodelPos().y - 1, CX_model::XmodelPos().z) + mu))
	{
		TargetPoint2 = true;
	}

	if (CHit::AABB(D3DXVECTOR3(100.0f, -5.0f, -150.0f),
		D3DXVECTOR3(150.0f, 5.0f, -100.0f),
		D3DXVECTOR3(CX_model::XmodelPos().x, CX_model::XmodelPos().y - 1, CX_model::XmodelPos().z) - mu,
		D3DXVECTOR3(CX_model::XmodelPos().x, CX_model::XmodelPos().y - 1, CX_model::XmodelPos().z) + mu))
	{
		TargetPoint3 = true;
	}

	if (CHit::AABB(D3DXVECTOR3(100.0f, -5.0f, 100.0f),
		D3DXVECTOR3(150.0f, 5.0f, 150.0f),
		D3DXVECTOR3(CX_model::XmodelPos().x, CX_model::XmodelPos().y - 1, CX_model::XmodelPos().z) - mu,
		D3DXVECTOR3(CX_model::XmodelPos().x, CX_model::XmodelPos().y - 1, CX_model::XmodelPos().z) + mu))
	{
		TargetPoint4 = true;
	}

	if (TargetPoint&&TargetPoint2&&TargetPoint3&&TargetPoint4)
	{
		if (CHit::AABB(D3DXVECTOR3(-10.0f, -5.0f, 10.0f),
			D3DXVECTOR3(10.0f, 5.0f, 0.0f),
			D3DXVECTOR3(CX_model::XmodelPos().x, CX_model::XmodelPos().y - 1, CX_model::XmodelPos().z) - mu,
			D3DXVECTOR3(CX_model::XmodelPos().x, CX_model::XmodelPos().y - 1, CX_model::XmodelPos().z) + mu))
		{
			rap = true;
			Lap++;
			TargetPoint = false;
			TargetPoint2 = false;
			TargetPoint3 = false;
			TargetPoint4 = false;
			if (Lap == 2) {
				PlaySound(SOUND_LABEL_LASTLAP);
			}
		}
	}
}

void CModeGame::Lap_Time() {

	//ラップタイム管理
	if (Lap != 3)
	{
		if (startTime) {
			time++;
		}

	}
	time = max(0, time);


	if (Lap == 1)
	{
		time2++;
	}
	time2 = max(0, time2);

	if (Lap == 2)
	{
		time3++;
		lastlap++;
	}

	if (Lap == 3) {
		result++;
	}

	time3 = max(0, time3);

	//タイム管理
	Dtime = (int)(time / 0.6);
	Dtime2 = (int)(time2 / 0.6);
	Dtime3 = (int)(time3 / 0.6);

	if (Dtime < 0)
	{
		Dtime = 0;
	}

	//ラップタイム
	if (rap == true && Lap == 1) {
		onetime = Dtime;
	}
	if (rap == true && Lap == 2) {
		twotime = Dtime2;
	}
	if (rap == true && Lap == 3) {
		threetime = Dtime3;
	}
}

void CModeGame::CountDown() {

	//カウントダウン処理
	ModelLife++;

	if (ModelLife > 0 && ModelLife < 40)
	{
		PlaySound(SOUND_LABEL_SE_COUNTDOWN);
	}


	//カウント3のとき
	if (ModelLife > 40 && ModelLife < 90)
	{
		hatenafal = false;
		hatenafal2 = false;
		item_count = 0;
		item_count2 = 0;
		bCount3 = true;
		use = false;
		dash = false;
	}
	//カウント2のとき
	if (ModelLife > 90 && ModelLife < 140)
	{
		bCount2 = true;
		bCount3 = false;
		use = false;
		dash = true;
	}
	//カウント1のとき
	if (ModelLife > 140 && ModelLife < 190)
	{
		bCount1 = true;
		bCount2 = false;
		use = false;
		dash = false;

	}
	//カウント0のとき
	if (ModelLife > 190)
	{
		bCount0 = true;
		use = true;
		bCount1 = false;
		dash = false;
	}

	//カウントダウン終了処理
	if (ModelLife > 240)
	{
		bCount0 = false;
		startTime = true;
		dash = false;
	}
}

void CModeGame::UpdateJugem() {

	//ジュゲム動き
	if (bCount0) {
		jug2 -= 6;
	}

	if (!bCount0) {
		if (jugemu >= 7.0f)
		{
			jug = false;
		}
		if (jugemu <= 0.0f)
		{
			jug = true;
		}
		if (jug == true)
		{
			jugemu += 0.4f;
		}
		else {
			jugemu -= 0.4f;
		}
	}
}

void CModeGame::Item() {

	//アイテム獲得
	if (CItem::GetItem() == true)
	{
		if (!hatenafal)
		{
			item_count++;
			hatena_a = 255;
			item_rand = rand() % 4 + 1;
			hatena_bgm = true;
		}
	}

	//トリプルダッシュキノコ処理
	if ((MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_LEFT_SHOULDER) && CX_model::kinohit() == false) && b_kinoko1_x && !b_kinoko2_x && !CX_model::Getkinoko_count() &&  !CX_model::Get_posy() || (GetKeyboardTrigger(DIK_L) && CX_model::kinohit() == false) && b_kinoko1_x && !b_kinoko2_x && !CX_model::Getkinoko_count() && !CX_model::Get_posy())
	{
		PlaySound(SOUND_LABEL_WAHAAKINO);
		kinoko_a = 0;
		b_kinoko3_x = false;
		b_kinoko1_x = false;
		b_kinoko2_x = false;
		hatenafal = false;
	}

	if ((MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_LEFT_SHOULDER) && CX_model::kinohit() == false) && !CX_model::Get_posy() && item_hatena_use && !b_kinoko3_x && !b_kinoko2_x && !b_kinoko1_x && !b_pw_kinoko_x || (GetKeyboardTrigger(DIK_L) && CX_model::kinohit() == false) && !CX_model::Get_posy() && item_hatena_use && !b_kinoko3_x && !b_kinoko2_x && !b_kinoko1_x && !b_pw_kinoko_x)
	{
		hatenafal2 = true;
		hatena_change = true;
		hatena_change2 = true;
		hatenafal = true;
		item_count = item_count2;

		item_hatena_use = false;
	}
	else
		if (CItem::GetItem2() == true && hatenafal)
		{
			if (!hatenafal2)
			{
				item_hatena_use = true;
				item_count2++;
				hatena2_a = 255;
				item_rand2 = rand() % 4 + 1;
				//item_rand2 = 1;
				hatena_bgm2 = true;
			}
		}

	if (item_count >= 200)
	{
		hatena_change2 = false;
		hatena_change = false;

		switch (item_rand)
		{
		case 1://きのこ
			kinoko_a = 255;
			b_kinoko_x = true;
			break;

		case 2://コイン
			coin_a = 255;
			b_coin_x = true;
			break;

		case 3://スター
			star_a = 255;
			b_star_x = true;
			break;

		case 4://トリプルダッシュキノコ
			kinoko3_a = 255;
			b_kinoko3_x = true;
			b_kinoko2_x = false;
			b_kinoko1_x = false;
			break;

		case 5://パワフルダッシュキノコ
			p_kinoko_a = 255;
			b_pw_kinoko_x = true;
			break;
		case 6://緑甲羅
			green__shell_a = 255;
			b_green_shell = true;
			break;
		}
		hatenafal = true;
	}
	else {
		b_kinoko_x = false;
		b_coin_x = false;
		b_star_x = false;
	}


	//アイテム使用
	if ((MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_LEFT_SHOULDER) && CX_model::kinohit() == false) && !CX_model::Get_posy() || (GetKeyboardTrigger(DIK_L) && CX_model::kinohit() == false)  && !CX_model::Get_posy())
	{


		coin_a = 0;
		star_a = 0;
		kinoko_a = 0;

		item_count = 0;
		b_kinoko_x = false;
		b_coin_x = false;
		b_star_x = false;

		if (b_kinoko3_x || b_kinoko2_x || b_kinoko1_x || b_pw_kinoko_x) {
			hatenafal = true;
		}
		else
		{
			hatenafal = false;
		}

		hatena_bgm = false;
	}

	if (b_kinoko_x || b_pw_kinoko_x) {
		PlaySound(SOUND_LABEL_WAHAAKINO);
	}
	if (b_star_x) {
		PlaySound(SOUND_LABEL_STAR);
	}



	if ((MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_LEFT_SHOULDER) && CX_model::kinohit() == false) && !b_kinoko3_x &&b_kinoko2_x && !CX_model::Getkinoko_count()  && !CX_model::Get_posy() || (GetKeyboardTrigger(DIK_L) && CX_model::kinohit() == false) && !b_kinoko3_x && b_kinoko2_x && !CX_model::Getkinoko_count() && !CX_model::Get_posy())
	{

		PlaySound(SOUND_LABEL_WAHAAKINO);
		kinoko2_a = 0;
		kinoko_a = 255;
		b_kinoko1_x = true;
		b_kinoko2_x = false;
		b_kinoko3_x = false;
	}

	if ((MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_LEFT_SHOULDER) && CX_model::kinohit() == false) && !b_kinoko2_x && b_kinoko3_x && !CX_model::Getkinoko_count()  && !CX_model::Get_posy() || (GetKeyboardTrigger(DIK_L) && CX_model::kinohit() == false) && !b_kinoko2_x&& b_kinoko3_x && !CX_model::Getkinoko_count()  && !CX_model::Get_posy())
	{
		PlaySound(SOUND_LABEL_WAHAAKINO);
		kinoko2_a = 255;
		kinoko3_a = 0;
		b_kinoko1_x = false;
		b_kinoko2_x = true;
		b_kinoko3_x = false;
	}

	//パワプルダッシュキノコ
	if (CX_model::pw_dash_dele())
	{
		p_kinoko_a = 0;
		b_pw_kinoko_x = false;
		hatenafal = false;
	}

	//ラストラップジュゲムのY軸
	if (lastlap >= 200) {
		jug_last_y -= 3;
	}

	if (item_count2 >= 200)
	{
		item_hatena_use = false;
		hatena_change2 = false;
		hatena_change = false;

		switch (item_rand2)
		{
		case 1://きのこ
			kinoko_a_keep = 255;
			break;

		case 2://コイン
			coin_a_keep = 255;
			break;

		case 3://スター
			star_a_keep = 255;
			break;

		case 4://トリプルダッシュキノコ
			kinoko3_a_keep = 255;
			break;

		case 5://パワフルダッシュキノコ
			p_kinoko_a_keep = 255;
			break;
		case 6://緑甲羅
			green__shell_a_keep = 255;
			break;
		}
		hatenafal2 = true;
	}

	if ((MyInputGamepad::GetButtonTrigger(MYGAMEPAD_BUTTON_LEFT_SHOULDER) && CX_model::kinohit() == false)  && !CX_model::Get_posy() || (GetKeyboardTrigger(DIK_L) && CX_model::kinohit() == false) && !CX_model::Get_posy())
	{
		//item_count = 200;
		if (!b_kinoko3_x && !b_kinoko2_x && !b_kinoko1_x)
		{

			if (!b_pw_kinoko_x)
			{
				if (kinoko_a_keep == 255)
				{
					item_rand = 1;
					item_count = 200;
					hatenafal = true;
					kinoko_a_keep = 0;

				}
				if (coin_a_keep == 255)
				{
					item_rand = 2;
					item_count = 200;
					hatenafal = true;
					coin_a_keep = 0;

				}

				if (star_a_keep == 255)
				{
					item_rand = 3;
					item_count = 200;
					hatenafal = true;
					star_a_keep = 0;

				}
				if (kinoko3_a_keep == 255)
				{
					item_rand = 4;
					item_count = 200;
					hatenafal = true;
					kinoko3_a_keep = 0;

				}

				if (p_kinoko_a_keep == 255) {
					item_rand = 5;
					item_count = 200;
					hatenafal = true;
					p_kinoko_a_keep = 0;
				}
				hatenafal2 = true;
			}

			hatenafal2 = false;
		}
		green__shell_a_keep = 0;


		hatena_bgm2 = false;
		item_count2 = 0;
	}

	if (CX_model::pw_dash_dele())
	{
		if (kinoko_a_keep == 255)
		{
			item_rand = 1;
			item_count = 200;
			hatenafal = true;
			kinoko_a_keep = 0;

		}
		if (coin_a_keep == 255)
		{
			item_rand = 2;
			item_count = 200;
			hatenafal = true;
			coin_a_keep = 0;

		}

		if (star_a_keep == 255)
		{
			item_rand = 3;
			item_count = 200;
			hatenafal = true;
			star_a_keep = 0;

		}
		if (kinoko3_a_keep == 255)
		{
			item_rand = 4;
			item_count = 200;
			hatenafal = true;
			kinoko3_a_keep = 0;

		}

		if (p_kinoko_a_keep == 255) {
			item_rand = 5;
			item_count = 200;
			hatenafal = true;
			p_kinoko_a_keep = 0;
		}
		b_pw = false;
	}
}

CField * CModeGame::GetField()
{

	return m_Field;
}
bool  CModeGame::GetUse()
{
	return use;
}

int  CModeGame::GetDash()
{
	return ModelLife;
}


int  CModeGame::GetKinoko()
{
	return kinoko_a;
}

bool  CModeGame::Gethatena()
{
	return hatenafal;
}

bool  CModeGame::Gethatena2()
{
	return hatenafal2;
}

bool  CModeGame::Getkinoko_X()
{
	return b_kinoko_x;
}

bool  CModeGame::Getkinoko1_X()
{
	return b_kinoko1_x;
}

bool  CModeGame::Getkinoko2_X()
{
	return b_kinoko2_x;
}

bool  CModeGame::Getkinoko3_X()
{
	return b_kinoko3_x;
}

bool  CModeGame::Get_Pw_kinoko_X()
{
	return b_pw_kinoko_x;
}

bool  CModeGame::Getcoin_X()
{
	return b_coin_x;
}

bool  CModeGame::Getstar_X()
{
	return b_star_x;
}

bool  CModeGame::Hatena_Bgm()
{
	return hatena_bgm;
}

bool  CModeGame::Hatena_Bgm2()
{
	return hatena_bgm2;
}

int  CModeGame::SougouScore()
{
	return Dtime;

}

int  CModeGame::GOAL()
{

	return Lap;

}

bool  CModeGame::Hatena_Change()
{
	return hatena_change;
}

bool  CModeGame::Hatena_Change2()
{
	return hatena_change2;
}