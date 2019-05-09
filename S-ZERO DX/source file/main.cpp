//-----------------------------------//
//---------------------[main.cpp]----//
//-----------------------------------//
//------Author:�{ �C�G-------------//
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
//------------�}�N����`------------//
//----------------------------------//
#define CLASS_NAME  "sample"			//�E�B���h�E�̃N���X��
#define WINDOW_NAME "S-ZERO DX"	//�E�B���h�E�̃L���v�V������

//�v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	//LRESULT�͐����⎸�s��Ԃ��߂�l�̌^

																				//imgui
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

																				//���C���֐�
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LPDIRECT3DDEVICE9 pD3DDevice = CRender::GetD3DDevice();
	hPrevInstance = hPrevInstance;
	lpCmdLine = lpCmdLine;

	WNDCLASSEX wcex = {						//���������鎞�l��^������@�@(���Ԃ���)
		sizeof(WNDCLASSEX),					//�@�@�@���̍\���̎��̂̃T�C�[�Y
		CS_VREDRAW | CS_HREDRAW,			//
		WndProc,							//�v���V�[�W���֐� ���b�Z�[�W���[�v����Ƃ��g���֐�
		0,
		0,
		hInstance,
		NULL,								//�A�C�R���̃^�C�v
		LoadCursor(NULL, IDC_ARROW),		//�}�E�X�J�[�\��(��Ɨ̈�Ƀ}�E�X��\������A�C�R��)
		(HBRUSH)(COLOR_WINDOW + 1),			//��Ɨ̈�̐F(�f�t�H���g)
		NULL,								//�N���X�l�[�� �o�^�l�[��
		CLASS_NAME,
		NULL								//�~�j�A�C�R���w��
	};

	RegisterClassEx(&wcex);								//�E�B���h�E�N���X�̓o�^

	DWORD WStyle = WS_OVERLAPPEDWINDOW &~(WS_MAXIMIZEBOX | WS_THICKFRAME);
	RECT wr = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };//�}�`�̃f�[�^�\����

	AdjustWindowRect(&wr, WStyle, false);//(�}�`�̃f�[�^�A�h���X,�E�B���h�E�X�^�C��,���j���[���邩�H(true,false));

	RECT dr;

	bool bWindow = false;

	bWindow = bWindow;

	GetWindowRect(GetDesktopWindow(), &dr);				//�f�X�N�g�b�v�̃T�C�Y�𑪂�
	int x = (dr.right - SCREEN_WIDTH) / 2;				//��ʂ̐^��X���W�����߂�
	int y = (dr.bottom - SCREEN_HEIGHT) / 2;			//��ʂ̐^��Y���W�����߂�

	HWND hWnd = CreateWindowEx(					//�E�B���h�E�쐬
		0,
		CLASS_NAME,
		WINDOW_NAME,							//�^�C�g���̖��O
		WStyle,
		x,										//X���W
		y,										//Y���W
		SCREEN_WIDTH,							//�X�N���[���̕�
		SCREEN_HEIGHT,							//�X�N���[���̍���
		NULL,									//�e�E�B���h�E�Ƃ̊֌W(�Ȃ�)
		NULL,									//���j���[�n���h��(���e)
		hInstance,								//�C���X�^���X�n���h��
		NULL
	);

	ShowWindow(hWnd, nShowCmd);

	UpdateWindow(hWnd);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplWin32_Init(hWnd);

	
	//������
	CManager::Init(hInstance, hWnd, true);
	/*if (!Init(hInstance, hWnd, true))
	{
	MessageBox(hWnd, "�x��", "���b�Z�[�W", (MB_OK));
	}*/
	ImGui_ImplDX9_Init(CRender::GetD3DDevice());
	//���b�Z�[�W���[�v
	MSG msg;
	DWORD dwExecLastTime = 0;//�O��̃t���[���������I���������
	DWORD dwCurrentTime = 0;//���̎���

							//����\��ݒ�
	timeBeginPeriod(1);
	do {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//�Q�[������)60fps�Ń��[�v����悤�ɂ���
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwExecLastTime) * 60 >= 1000)
			{//�Q�[������
				dwExecLastTime = dwCurrentTime;
				//�X�V����
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
				//�`�揈��
				CManager::Draw();
				
				dwExecLastTime = dwCurrentTime;
			}
		}
		//�㏈��

	} while (msg.message != WM_QUIT);
	CManager::Uninit();

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	//����\��߂�
	timeEndPeriod(1);

	return (int)msg.wParam;



}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID = 0;

#if defined(_DEBUG)||(DEBUG)
	//ImGui�ɑ���𔽉f�����邽�߂̃E�B���h�E
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) { return true; }
#endif //  _DEBUG

	switch (uMsg)
	{
	case WM_CREATE:

		break;

	case WM_KEYDOWN:

		switch (wParam)
		{
			// ESC������
		case VK_ESCAPE:
#ifdef _DEBUG
			PostQuitMessage(0);//WM_QUIT���b�Z�[�W�̑��M
#endif
			nID = MessageBox(hWnd, "�I�����܂����H", "�x��", MB_YESNO | MB_DEFBUTTON2);
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

	case WM_DESTROY: PostQuitMessage(0);//WM_QUIT���b�Z�[�W�̑��M

		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);//��{�I�ȃ��b�Z�[�W��������B
}