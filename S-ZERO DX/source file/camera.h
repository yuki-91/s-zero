//-----------------------------------//
//----�J��������-------[camera.h]--//
//-----------------------------------//
//------Author:�{ �C�G-------------//
//-----------------------------------//
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "main.h"

class Camera
{
public:
	Camera();
	~Camera();
	static void Init(void);
	static void Uninit(void);
	static void Update(void);
	static void Draw(void);
	void Release();
	D3DXVECTOR3 Camera::CameralPos();
	static bool Camera::Get_back_millor();
private:
	static LPDIRECT3DDEVICE9 m_Device;
	static D3DXMATRIX m_mtxView;
	static D3DXMATRIX m_mtxProj;
	static D3DXVECTOR3 m_eye, m_at, m_up;
	static D3DXVECTOR3 dir;
	static D3DXVECTOR3 m_front, m_right;	//�P�ʃx�N�g��
	static float m_speed;		//�ړ����x
	static float m_radian;		//��]���x
	static D3DXMATRIX m_mtxRot;	//��]�s��
	static bool b_count;
	static int m_count;
	static bool b_back__millor;
};
#endif