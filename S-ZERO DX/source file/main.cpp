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

//----------------------------------//
//------------マクロ定義------------//
//----------------------------------//
#define CLASS_NAME  "sample"			//ウィンドウのクラス名
#define WINDOW_NAME "S-ZERO DX"	//ウィンドウのキャプション名

//プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	//LRESULTは成功や失敗を返す戻り値の型


//メイン関数
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{

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

	//初期化
	CManager::Init(hInstance, hWnd, true);
	/*if (!Init(hInstance, hWnd, true))
	{
	MessageBox(hWnd, "警告", "メッセージ", (MB_OK));
	}*/

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
				//描画処理
				CManager::Draw();

				dwExecLastTime = dwCurrentTime;
			}
		}
		//後処理

	} while (msg.message != WM_QUIT);
	CManager::Uninit();

	//分解能を戻す
	timeEndPeriod(1);

	return (int)msg.wParam;



}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID = 0;

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
