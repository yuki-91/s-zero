//-----------------------------------//
//------�����_���[����---------------//
//-------[renderer.h]--------------//
//------Author:�{ �C�G-------------//
//-----------------------------------//
#ifndef _RENDEREH_
#define _RENDEREH_
#include "main.h"
#include <d3d9.h>
#include <d3dx9.h> 


class CRender
{
private:
	static LPDIRECT3D9 m_D3D;
	static LPDIRECT3DDEVICE9 m_D3DDevice;
public:
	static bool Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	static void Uninit();
	static void DrawBegin();
	static void DrawEnd();

	//�_�C���N�g3D�f�o�C�X�̎擾
	static LPDIRECT3DDEVICE9 GetD3DDevice(void);

};
#endif 
