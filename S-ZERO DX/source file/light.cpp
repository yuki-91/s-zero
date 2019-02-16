//----------------------------------///
//------------ライト処理-------------//
//------------[light.cpp]------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#include "light.h"
#include"renderer.h"
Light::Light()
{
}

Light::~Light()
{
}

void Light::Init(void)
{
	m_Device = CRender::GetD3DDevice();
	ZeroMemory(&mat, sizeof(mat));
	mat.Diffuse.r = 1.0f;
	mat.Diffuse.g = 1.0f;
	mat.Diffuse.b = 1.0f;
	mat.Diffuse.a = 1.0f;
	mat.Ambient.r = 1.0f;
	mat.Ambient.g = 1.0f;
	mat.Ambient.b = 1.0f;
	mat.Ambient.a = 1.0f;

	ZeroMemory(&light, sizeof(light));
	light.Type = D3DLIGHT_DIRECTIONAL;
	D3DXVECTOR3 vecDir(1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	light.Diffuse.a = 1.0f;
	light.Ambient.r = 0.5f;
	light.Ambient.g = 0.5f;
	light.Ambient.b = 0.5f;
	light.Ambient.a = 1.0f;
}

void Light::Uninit(void)
{
}

void Light::Update(void)
{

}

void Light::Draw(void)
{
	m_Device->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_Device->SetLight(0, &light);
	m_Device->LightEnable(0, TRUE);

	m_Device->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
	m_Device->SetMaterial(&mat);
}

void Light::Release()
{
	Uninit();
	delete this;		//自分自身のポインタ
}