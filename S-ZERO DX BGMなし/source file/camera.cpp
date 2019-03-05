//-----------------------------------//
//----カメラ処理-------[camera.cpp]--//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#include "camera.h"
#include"renderer.h"
#include"input.h"
#include"player.h"
#include"mode_game.h"
#include "myInput.h"
#include "mode_title.h"

float camera_handle_left = 0.0f;
float camera_handle_right = 0.0f;
float camera_handle_left_drift = 0.0f;
float camera_handle_right_drift = 0.0f;

D3DVIEWPORT9 viewport = { WIN_X, WIN_Y, WIN_W, WIN_H, 0.0f, 1.0f };
D3DVIEWPORT9 viewport_bak;

LPDIRECT3DDEVICE9 Camera::m_Device;
D3DXMATRIX Camera::m_mtxView;
D3DXMATRIX Camera::m_mtxProj;
D3DXVECTOR3 Camera::m_eye, Camera::m_at, Camera::m_up;
D3DXVECTOR3 Camera::dir;
D3DXVECTOR3 Camera::m_front, Camera::m_right;	//単位ベクトル
D3DXMATRIX Camera::m_mtxRot;	//回転行列

bool Camera::b_count;
float Camera::m_speed;		//移動速度
float Camera::m_radian;		//回転速度
float Camera::m_stopup = 0.0f;
int Camera::m_count;
bool Camera::b_back__millor;

bool camera_drift_state_left = false;
bool camera_drift_state_righrt = false;
Camera::Camera()
{
	m_front = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_right = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_speed = 0.3f;
	m_radian = 0.01f;
}

Camera::~Camera()
{
}

void Camera::Init(void)
{
	m_Device = CRender::GetD3DDevice();
	m_Device->GetViewport(&viewport_bak);		//	元のビューポート矩形を取っておく
	m_eye = { 0.0f, 2.5f, -3.5f };
	m_at = { 0.0f, 2.0f, 0.0f };
	m_up = { 0.0f, 0.5f, 0.0f };
	m_front = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	m_right = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_speed = 0.3f;
	m_radian = 0.01f;
	b_count = false;
	m_count = 0;
	b_back__millor = false;
	camera_handle_left = 0.0f;
	camera_handle_right = 0.0f;
	camera_handle_left_drift = 0.0f;
	camera_handle_right_drift = 0.0f;
	camera_drift_state_left = false;
	camera_drift_state_righrt = false;
}

void Camera::Uninit(void)
{
}

void Camera::Update(void)
{

	if (CModeTitle::Get_opening_rot() == true)
	{
		D3DXMatrixIdentity(&m_mtxRot);
		D3DXMatrixRotationY(&m_mtxRot, 0.03f);
		//atからのベクトル
		dir = m_eye - m_at;
		//回転行列とベクトルを合成
		D3DXVec3TransformNormal(&dir, &dir, &m_mtxRot);
		m_eye = m_at + dir;
		m_at.y = 1.0f;
		//m_up.z = -5.0f;
	
	}
	else {


		if (CX_model::modelUse() == true)
		{
			b_count = true;
		}
		else
		{
			b_count = false;
		}



		if (b_count && !b_back__millor) {


			//ハンドル移動操作
			if (!MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_STAIC4) && !GetKeyboardPress(DIK_A))
			{
				if (camera_handle_left < 0) {
					camera_handle_left = 0.0f;
				}
			}
			if (!MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_STAIC3) && !GetKeyboardPress(DIK_D))
			{
				if (camera_handle_right > 0) {
					camera_handle_right = 0.0f;
				}
			}
			//ハンドルドリフト移動操作
			if (!MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_RIGHT_SHOULDER) && !GetKeyboardPress(DIK_J))
			{
				if (camera_handle_left_drift < 0) {
					camera_handle_left_drift = 0.0f;
				}
				if (camera_handle_right_drift > 0) {
					camera_handle_right_drift = 0.0f;
				}

				camera_drift_state_righrt = false;
				camera_drift_state_left = false;
			}
	
			//視点ドリフト中心右回転
			if (MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_STAIC3) && MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_RIGHT_SHOULDER) || GetKeyboardPress(DIK_D) && GetKeyboardPress(DIK_J))
			{
				camera_drift_state_righrt = true;

				
				
			
			}
			else
				//視点中心右回転
				if (MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_STAIC3) || GetKeyboardPress(DIK_D))
				{
					if (camera_handle_right < 0.025) {
						camera_handle_right += 0.001f;
					}
					//回転行列
					D3DXMatrixRotationY(&m_mtxRot, camera_handle_right);
					//atからのベクトル
					dir = m_eye - m_at;
					//回転行列とベクトルを合成
					D3DXVec3TransformNormal(&dir, &dir, &m_mtxRot);
					m_eye = m_at + dir;
				}
			//視点ドリフト中心左回転
			if (MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_STAIC4) && MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_RIGHT_SHOULDER) || GetKeyboardPress(DIK_A) && GetKeyboardPress(DIK_J))
			{
				camera_drift_state_left = true;
				
				
				
			}
			else
				//視点中心左回転
				if (MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_STAIC4) || GetKeyboardPress(DIK_A))
				{
					if (camera_handle_left > -0.025) {
						camera_handle_left -= 0.001f;
					}
					//回転行列
					D3DXMatrixRotationY(&m_mtxRot, camera_handle_left);
					//atからのベクトル
					dir = m_eye - m_at;
					//回転行列とベクトルを合成
					D3DXVec3TransformNormal(&dir, &dir, &m_mtxRot);
					m_eye = m_at + dir;
				}
		}

		if (camera_drift_state_left) 
		{
			if (MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_RIGHT_SHOULDER) || GetKeyboardPress(DIK_J))
			{
				camera_handle_left_drift -= 0.001f;
				if (camera_handle_left_drift < -0.03f) {
					camera_handle_left_drift = -0.03f;
				}
				//回転行列
				D3DXMatrixRotationY(&m_mtxRot, camera_handle_left_drift);
				//atからのベクトル
				dir = m_eye - m_at;
				//回転行列とベクトルを合成
				D3DXVec3TransformNormal(&dir, &dir, &m_mtxRot);
				m_eye = m_at + dir;
			}
		}

		if (camera_drift_state_righrt)
		{
			if (MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_RIGHT_SHOULDER) || GetKeyboardPress(DIK_J))
			{
				camera_handle_right_drift += 0.001f;
				if (camera_handle_right_drift > 0.03f) {
					camera_handle_right_drift = 0.03f;
				}
				//回転行列
				D3DXMatrixRotationY(&m_mtxRot, camera_handle_right_drift);
				//atからのベクトル
				dir = m_eye - m_at;
				//回転行列とベクトルを合成
				D3DXVec3TransformNormal(&dir, &dir, &m_mtxRot);
				m_eye = m_at + dir;
			}
		}

		m_count++;

		if (m_count <= 126 && CModeTitle::Get_opening_rot() == false) {
			D3DXMatrixIdentity(&m_mtxRot);
			D3DXMatrixRotationY(&m_mtxRot, 0.05f);
			//atからのベクトル
			dir = m_eye - m_at;
			//回転行列とベクトルを合成
			D3DXVec3TransformNormal(&dir, &dir, &m_mtxRot);
			m_eye = m_at + dir;
		}
		else
		{
			if (MyInputGamepad::GetButtonPress(MYGAMEPAD_BUTTON_X) || GetKeyboardPress(DIK_I))
			{
				b_back__millor = true;
				m_eye = m_at - dir;
			}
			else
			{
				b_back__millor = false;
				m_eye = m_at + dir;
			}
		}



		if (CModeGame::GOAL() == 3 && CModeTitle::Get_opening_rot() == false)
		{
			D3DXMatrixIdentity(&m_mtxRot);
			D3DXMatrixRotationY(&m_mtxRot, 0.05f);
			//atからのベクトル
			dir = m_eye - m_at;
			//回転行列とベクトルを合成
			D3DXVec3TransformNormal(&dir, &dir, &m_mtxRot);
			m_eye = m_at + dir;
		}
	}
	 for (int n = 0; n < 2; n++) {
		 D3DXVECTOR3 playerFront = CX_model::GetFront();
		 D3DXVECTOR3 eye(m_eye.x + CX_model::XmodelPos().x, m_eye.y + CX_model::XmodelPos().y, m_eye.z + CX_model::XmodelPos().z);
		 D3DXVECTOR3 at(m_at.x + CX_model::XmodelPos().x, m_at.y + CX_model::XmodelPos().y, m_at.z + CX_model::XmodelPos().z);
		 D3DXVECTOR3 up(m_up.x, m_up.y, m_up.z);

		 if (0 == n) {
			 D3DXMatrixLookAtLH(&m_mtxView, &eye, &at, &up);
			 D3DXMatrixPerspectiveFovLH(&m_mtxProj, D3DX_PI / 3,/*D3DXToRadian(60)*/(float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 1000.0f);
		 }
	 }


}

void Camera::Draw(void)
{
		m_Device->SetTransform(D3DTS_VIEW, &m_mtxView);
		m_Device->SetTransform(D3DTS_PROJECTION, &m_mtxProj);
}

void Camera::Release()
{
	Uninit();
	delete this;		//自分自身のポインタ
}

//キャラの位置
D3DXVECTOR3 Camera::CameralPos()
{
	return m_eye;
}

bool Camera::Get_back_millor()
{
	return b_back__millor;
}

