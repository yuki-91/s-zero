//-----------------------------------//
//---------------------[main.cpp]----//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#include <stdio.h>
#include <Windows.h>
#include "main.h"
#include"renderer.h"
#include"manager.h"

#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "player.h"
#include "sound.h"
//----------------------------------//
//------------マクロ定義------------//
//----------------------------------//
#define CLASS_NAME  "sample"			//ウィンドウのクラス名
#define WINDOW_NAME "S-ZERO DX"	//ウィンドウのキャプション名

//プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	//LRESULTは成功や失敗を返す戻り値の型

																				//imgui
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

																				//メイン関数
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LPDIRECT3DDEVICE9 pD3DDevice = CRender::GetD3DDevice();
	hPrevInstance = hPrevInstance;
	lpCmdLine = lpCmdLine;

	WNDCLASSEX wcex = {						//初期化する時値を与える方法　(順番あり)
		sizeof(WNDCLASSEX),					//　　　この構造体自体のサイーズ
		CS_VREDRAW | CS_HREDRAW,			//
		WndProc,							//プロシージャ関数 メッセージループするとき使う関数
		0,
		0,
		hInstance,
		NULL,								//アイコンのタイプ
		LoadCursor(NULL, IDC_ARROW),		//マウスカーソル(作業領域にマウスを表示するアイコン)
		(HBRUSH)(COLOR_WINDOW + 1),			//作業領域の色(デフォルト)
		NULL,								//クラスネーム 登録ネーム
		CLASS_NAME,
		NULL								//ミニアイコン指定
	};

	RegisterClassEx(&wcex);								//ウィンドウクラスの登録

	DWORD WStyle = WS_OVERLAPPEDWINDOW &~(WS_MAXIMIZEBOX | WS_THICKFRAME);
	RECT wr = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };//図形のデータ構造体

	AdjustWindowRect(&wr, WStyle, false);//(図形のデータアドレス,ウィンドウスタイル,メニューあるか？(true,false));

	RECT dr;

	bool bWindow = false;

	bWindow = bWindow;

	GetWindowRect(GetDesktopWindow(), &dr);				//デスクトップのサイズを測る
	int x = (dr.right - SCREEN_WIDTH) / 2;				//画面の真ん中X座標を求める
	int y = (dr.bottom - SCREEN_HEIGHT) / 2;			//画面の真ん中Y座標を求める

	HWND hWnd = CreateWindowEx(					//ウィンドウ作成
		0,
		CLASS_NAME,
		WINDOW_NAME,							//タイトルの名前
		WStyle,
		x,										//X座標
		y,										//Y座標
		SCREEN_WIDTH,							//スクリーンの幅
		SCREEN_HEIGHT,							//スクリーンの高さ
		NULL,									//親ウィンドウとの関係(なし)
		NULL,									//メニューハンドル(内容)
		hInstance,								//インスタンスハンドル
		NULL
	);

	ShowWindow(hWnd, nShowCmd);

	UpdateWindow(hWnd);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplWin32_Init(hWnd);

	
	//初期化
	CManager::Init(hInstance, hWnd, true);
	/*if (!Init(hInstance, hWnd, true))
	{
	MessageBox(hWnd, "警告", "メッセージ", (MB_OK));
	}*/
	ImGui_ImplDX9_Init(CRender::GetD3DDevice());
	//メッセージループ
	MSG msg;
	DWORD dwExecLastTime = 0;//前回のフレーム処理が終わった時間
	DWORD dwCurrentTime = 0;//今の時間

							//分解能を設定
	timeBeginPeriod(1);
	do {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//ゲーム処理)60fpsでループするようにする
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwExecLastTime) * 60 >= 1000)
			{//ゲーム処理
				dwExecLastTime = dwCurrentTime;
				//更新処理
				CManager::Update();
				// ImGui
				// Start the ImGui frame
				ImGui_ImplDX9_NewFrame();
				ImGui_ImplWin32_NewFrame();
				ImGui::NewFrame();
				ImGuiWindowFlags isWindowStyle = (
					ImGuiWindowFlags_NoTitleBar );
		#if defined(_DEBUG)||(DEBUG)
				ImGui::SetNextWindowSize(ImVec2(500, 100));
				ImGui::Begin("Framerate", false);
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				ImGui::Text("player_pos.x = %f", CX_model::XmodelPos().x);
				ImGui::Text("player_pos.y = %f", CX_model::XmodelPos().y);
				ImGui::Text("player_pos.z= %f", CX_model::XmodelPos().z);
				ImGui::End();
				ImGui::EndFrame();
		#endif //  _DEBUG
				//描画処理
				CManager::Draw();
				
				dwExecLastTime = dwCurrentTime;
			}
		}
		//後処理

	} while (msg.message != WM_QUIT);
	CManager::Uninit();

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	//分解能を戻す
	timeEndPeriod(1);

	return (int)msg.wParam;



}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID = 0;

#if defined(_DEBUG)||(DEBUG)
	//ImGuiに操作を反映させるためのウィンドウ
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) { return true; }
#endif //  _DEBUG

	switch (uMsg)
	{
	case WM_CREATE:

		break;

	case WM_KEYDOWN:

		switch (wParam)
		{
			// ESCｷｰ入力
		case VK_ESCAPE:
#ifdef _DEBUG
			PostQuitMessage(0);//WM_QUITメッセージの送信
#endif
			nID = MessageBox(hWnd, "終了しますか？", "警告", MB_YESNO | MB_DEFBUTTON2);
			if (nID == IDYES)
			{
				StopSound();
				DestroyWindow(hWnd);
			}
			break;

		default:
			break;
		}
		break;

	case WM_DESTROY: PostQuitMessage(0);//WM_QUITメッセージの送信

		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);//基本的なメッセージを肩代わり。
}
