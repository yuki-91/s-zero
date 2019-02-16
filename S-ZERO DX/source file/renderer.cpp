//-----------------------------------//
//------�����_���[����---------------//
//-------[renderer.cpp]--------------//
//------Author:�{ �C�G-------------//
//-----------------------------------//
#include "renderer.h"
#include <stdio.h>
#include <Windows.h>
#include "main.h"
#include"input.h"

LPDIRECT3D9 CRender::m_D3D;
LPDIRECT3DDEVICE9 CRender::m_D3DDevice;

bool CRender::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	//Direct3D�C���^�t�F�[�X�̍쐬
	m_D3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_D3D == NULL)
	{
		return false;
	}
	//return true;

	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_D3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return false;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));								//���̕��̏�����
	d3dpp.BackBufferWidth = SCREEN_WIDTH;							//����ʂ̕�
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							//����ʂ̍���
	d3dpp.BackBufferFormat = d3ddm.Format;							//�F��
	d3dpp.BackBufferCount = 1;										//�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						//�f���M���̓���(DISCARD�͐���)
	d3dpp.EnableAutoDepthStencil = TRUE;							//TRUE�ŗǂ�
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						//���͂��̏�ԁ@��̃t�H�[�}�b�g
	d3dpp.Windowed = bWindow;										//TRUE�ŃE�B���h�E���[�h,FALSE�Ńt���X�N���[�����[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//�t���X�N���[�����[�h���̃��t���b�V�����[�g��Hz����ύX
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//���j�^�[��Hz���ɉ����ĕ`��


	if (FAILED(m_D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_D3DDevice)))
	{
		return false;
	}

	m_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	//SRC		--������`�悷�����
	//DEST		--���łɕ`�悳��Ă�����
	//SRC_RGB * SRC_a + DEST_RGB * (1 - SRC_a)
	//�����SRC_a = 0�@������w�i�F��100%�\��
	m_D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	//���_�f�[�^��UV�l��ύX
	//�e�N�X�`���̃A�h���X�O���Q�Ɓ@
	m_D3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_D3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	m_D3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//���ۂ̃T�C�Y�����������Ȃ鎞�̃t�B���^�����O

	//m_D3DDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);	//���ۂ̃T�C�Y�����傫���Ȃ鎞�̃t�B���^�����O

	//m_D3DDevice->SetSamplerState(0,D3DSAMP_MIPFILTER,D3DTEXF_LINEAR);	//�~�b�v�}�b�v�t�@�C���Ԃ̃t�B���^�����O�@�� 128*128��256*256�̊�



	//LINEAR--���`�ۊǁA����̐F���u�����h

	//�~�b�v�}�b�v--�����̃T�C�Y�̉摜�𐶐����Ă����B

	InitKeyboard(hInstance, hWnd);

	return true;
}

void CRender::Uninit()
{
	if (m_D3DDevice != NULL)
	{
		m_D3DDevice->Release();
		m_D3DDevice = NULL;
	}
	if (m_D3D != NULL)
	{
		m_D3D->Release();
		m_D3D = NULL;
	}
}

void CRender::DrawBegin()
{
	m_D3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(1, 1, 1, 1), 1.0F, 0);

	m_D3DDevice->BeginScene();
	
}

void CRender::DrawEnd()
{
	m_D3DDevice->EndScene();

	m_D3DDevice->Present(NULL, NULL, NULL, NULL);
}


LPDIRECT3DDEVICE9 CRender::GetD3DDevice(void)
{
	return m_D3DDevice;
}